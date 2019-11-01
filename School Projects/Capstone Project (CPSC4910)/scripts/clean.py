import numpy as np
import pandas as pd
import datetime
import os

# exec(open("clean.py").read())

#------------------------------------------------------------------------
# CLEAN AND READ DATA
#------------------------------------------------------------------------
base_directory = "/media/veracrypt1/"
directory = os.fsencode(base_directory + "original")

current_time = datetime.datetime.now()

for file in os.listdir(directory):
    filename = os.fsdecode(file)
    print("Reading " + filename + "...")
    _input = pd.read_excel(base_directory + "original/" + filename, thousands=',')

    # filter bad input
    mask = (_input["End Time"] != "-") & (_input["Miles"] > 1) 
    _input = _input[mask]

    # filter bad dates
    _input["End Time"] = pd.to_datetime(_input["End Time"]) 
    _input["Shipment Date"] = pd.to_datetime(_input["Shipment Date"])
    mask = (_input["End Time"] >= _input["Shipment Date"]) & (_input["End Time"] <= current_time)
    _input = _input[mask]

    _input.reindex()

    # create clean df
    delta = pd.Series(_input["End Time"] - _input["Shipment Date"])
    delta = delta.astype('timedelta64[D]').astype('int32') # convert time to int
    month = pd.Categorical(list(map(lambda x:x.month, _input["Shipment Date"])))
    day = pd.Categorical(list(map(lambda x:x.day, _input["Shipment Date"])))
    weekday = pd.Categorical(list(map(lambda x:x.weekday(), _input["Shipment Date"])))

    training = pd.DataFrame({
        'month' : month,
        'day' : day,
        'weekday' : weekday,
        'm_sys' : _input["Source System"],
        'mode' : _input["Mode"],
        'segment' : _input["Division"],
        'direction' : _input["Direction"],
        'dist' : _input["Miles"],
        'weight' : _input["Weight Tons"],
        'delta' : delta})

    print("Writing to " + filename + ".csv...")
    training.to_csv(base_directory + 'csv/' + filename + '.csv', index=False)

