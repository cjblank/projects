import numpy as np
import pandas as pd
import datetime, calendar

class CleanData():
    def __init__(self, df):
        self.df = df
        
    def clean_bad_dates(self):
        print("total points: %i" % (len(self.df.index)))

        # filter bad end points
        mask = (self.df["End Time"] != "-")
        self.df = self.df[mask]
        print("good end points: %i" % (mask.sum()))

        # filter bad dates
        self.df[["End Time", "Shipment Date"]] = self.df[["End Time", "Shipment Date"]].apply(pd.to_datetime)
        #self.df["Shipment Date"] = pd.to_datetime(self.df["Shipment Date"])

        mask = (self.df["End Time"] >= self.df["Shipment Date"])
        self.df = self.df[mask]
        print("good backwards points: %i" % (mask.sum()))

    def clean_max_days(self):

        # filter dates too long
        delta = pd.Series(self.df["End Time"] - self.df["Shipment Date"])
        delta = delta.astype('timedelta64[D]').astype('int32') # convert time to int

        TL_mask = (delta <= 8) & ((self.df["Mode"] == "TL") | (self.df["Mode"] == "LTL"))
        RL_mask = (delta <= 30) & (self.df["Mode"] == "RAIL")
        IM_mask = (delta <= 22) & (self.df["Mode"] == "IM")

        self.df = self.df[TL_mask | RL_mask | IM_mask]
        print("good transport points: %i" % (TL_mask.sum() + RL_mask.sum() + IM_mask.sum()))

    def finalize(self):
        self.df = self.df.reset_index()

#------------------------------------------------------------------------
# CLEAN DATA -> CLEANER TRAINING DATAFRAME
#------------------------------------------------------------------------
class FilterData():
    def __init__(self, df, bday = False, dotw = False, month_ind = False, miles = False, the_rest=True, days=True):
        self.df = df                # Clean data df
        self.bday = bday            # True changes days delta to business days delta
        self.dotw = dotw            # True adds DOTW
        self.month_ind = month_ind  # True replaces categorical days with interval month progress
        self.miles = miles          # True adds in miles
        self.the_rest = the_rest    # True adds in the rest of the signifcant variables
        self.days = days            # True adds in progress for days
        
        self.delta = None  # Actual out
        self.training = pd.DataFrame()

        # type everything
        print("Typing variables...")
        self.df["Shipment Date"] = self.df["Shipment Date"].astype('datetime64')
        self.df["End Time"] = self.df["End Time"].astype('datetime64')
        self.df["Weight Tons"] = self.df["Weight Tons"].astype('float64')
        self.df["Miles"] = self.df["Miles"].astype("int64")

        self.df["Source System"] = self.df["Source System"].astype("category")
        self.df["Division"] = self.df["Division"].astype("category")
        self.df["Direction"] = self.df["Direction"].astype("category")
        self.df["Mode"] = self.df["Mode"].astype("category")
        self.df["Origin Zip"] =  self.df["Origin Zip"].astype("category")
        self.df["Origin State"] =  self.df["Origin State"].astype("category")
        self.df["Destination Zip"] =  self.df["Destination Zip"].astype("category")
        self.df["Destination State"] =  self.df["Destination State"].astype("category")
        self.df["Carrier SCAC"] = self.df["Carrier SCAC"].astype("category")
        self.df["Carrier Type"] = self.df["Carrier Type"].astype("category")
        self.df["Vehicle Type"] = self.df["Vehicle Type"].astype("category")

    def parse(self):
        # Variables always in training
        var_toadd = {}
        var_toadd["month"] = pd.Categorical(list(map(lambda x:x.month, self.df["Shipment Date"]))) # account seasonality

        # Parse args
        if self.dotw:
            print("Implement DOTW...")
            var_toadd["dotw"] = pd.Categorical(list(map(lambda x:x.weekday(), self.df["Shipment Date"])))

        if self.bday:
            print("Implement business delta...")
            end = self.df["End Time"].values.astype('datetime64[D]')
            ship = self.df["Shipment Date"].values.astype('datetime64[D]')
            self.delta = np.busday_count(ship, end)
            self.delta = pd.Series(self.delta)
        else:
            print("Implement regular delta...")
            self.delta = pd.Series(self.df["End Time"] - self.df["Shipment Date"])
            self.delta = self.delta.astype('timedelta64[D]').astype('int32') # convert time to int

        if self.days:
            if self.month_ind:
                print("Implement month progress indicator...")
                day = pd.Series(list(map(lambda x:x.day, self.df["Shipment Date"])))
                days_month = pd.Series(list(map(lambda x:calendar.monthrange(x.year, x.month)[1], self.df["Shipment Date"])))
                var_toadd["month_ind"] = day/days_month
            else:
                print("Implement categorical day...")
                day = pd.Categorical(list(map(lambda x:x.day, self.df["Shipment Date"])))
                var_toadd["day"] = day

        if self.miles:
            print("Implement miles...")
            var_toadd["miles"] = self.df["Miles"]

        if self.the_rest:
            print("Implement the rest...")
            var_toadd["weight"] = self.df["Weight Tons"]
            var_toadd["system"] = self.df["Source System"]
            var_toadd["division"] = self.df["Division"]
            var_toadd["direction"] = self.df["Direction"]
            var_toadd["mode"] = self.df["Mode"]
            #var_toadd["carrier"] = self.df["Carrier SCAC"]
            #var_toadd["carrier_t"] = self.df["Carrier Type"]
            #var_toadd["origin"] = self.df["Origin State"]
            #var_toadd["dest"] = self.df["Destination State"] 
            #var_toadd["vehicle"] = self.df["Vehicle Type"]
            #var_toadd["origin"] = self.df["Origin Zip"] TOOOOOO MUCH MEMORY
            #var_toadd["dest"] = self.df["Destination Zip"] 

        # create clean df
        print("Update training...")
        self.training = pd.DataFrame(var_toadd)

    def ignore_same_day(self):
        mask = (self.delta != 0)
        self.training = self.training[mask]
        self.delta = self.delta[mask]

    def filter_transport(self, _type="all"):
        if _type == "rail":
            print("Filtering by rail...")
            mask = (self.training["mode"] == "RAIL")
        elif _type == "truck":
            print("Filtering by truck...")
            mask = (self.training["mode"] =="TL" | self.training["mode"] =="LTL")
        elif _type == "im":
            print("Filtering by intermodal...")
            mask = (self.training["mode"] =="IM")

        if _type != "all":
            self.training = self.training[mask]
            self.delta = self.delta[mask]
