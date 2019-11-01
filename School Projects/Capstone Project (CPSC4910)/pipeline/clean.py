import numpy as np
import pandas as pd
import datetime
import os
import argparse
import geopy
from geopy.geocoders import Nominatim
from geopy import distance
from geopy.extra.rate_limiter import RateLimiter
from tqdm import tqdm

def dir_path(string):
    if os.path.isdir(string):
        return string
    else:
        raise NotADirectoryError(string)

parser = argparse.ArgumentParser(description="raw data -> clean data")
parser.add_argument('input', help="directory to the raw data", type=dir_path)
parser.add_argument('output', help="directory for the clean data", type=dir_path)
args = parser.parse_args()

coordinates=pd.read_csv('miles.csv')

print("-------------------------------------------------------")
print(" RAW -> CLEAN")
print("-------------------------------------------------------")
directory = os.fsencode(args.input)

output = pd.DataFrame()
for file in os.listdir(directory):
    filename = os.fsdecode(file)
    print("Reading " + filename + "...")
    df = pd.read_excel(args.input + '/' + filename, index= len(args.input + '/' + filename), thousands=',')

    # filter bad end points
    mask = (df["End Time"] != "-")
    df = df[mask]

    # filter bad dates
    df["End Time"] = pd.to_datetime(df["End Time"]) 
    df["Shipment Date"] = pd.to_datetime(df["Shipment Date"])

    mask = (df["End Time"] >= df["Shipment Date"])
    df = df[mask]

    # filter dates too long
    delta = pd.Series(df["End Time"] - df["Shipment Date"])
    delta = delta.astype('timedelta64[D]').astype('int32') # convert time to int

    TL_mask = (delta <= 8) & ((df["Mode"] == "TL") | (df["Mode"] == "LTL"))
    RL_mask = (delta <= 30) & (df["Mode"] == "RAIL")
    IM_mask = (delta <= 22) & (df["Mode"] == "IM")
    df = df[TL_mask | RL_mask | IM_mask]

    #calculate miles-------------------------------------------------------------------------------
    

    df['Destination Address']=df['Destination City'] + ", " + df['Destination State']
    df['Origin Address']=df['Origin City'] + ", " + df['Origin State']

    df['Miles'] = 0.0

    de = 0
    oe = 0

    for index, row in tqdm(df.iterrows()):
        dest = coordinates.loc[coordinates['City'] == row['Destination Address']]['Coordinates']
        origin = coordinates.loc[coordinates['City'] == row['Origin Address']]['Coordinates']


        try:
            dest = [float(x) for x in dest.get(dest.index[0])[1:-1].split(', ')]
        except Exception as e:
            de+=1
            print('Exception occurred processing the destination coordinates. Exceptions = ', de)
            continue

        try:
            origin = [float(x) for x in origin.get(origin.index[0])[1:-1].split(', ')]
        except Exception as e:
            oe+=1
            print('Exception occurred processing the origin coordinates. Exceptions = ', oe)
            continue


        dist=distance.distance(dest,origin).miles
        df.at[index,'Miles']=dist
    #----------------------------------------------------------------------------------------------


    output = output.append(df, sort=True)

# drop irrelevant var
output = output.drop(columns=['End Time 1',
    'End Time 2',
    'End Time 3',
    'Start Time 1',
    'Start Time 2',
    'Start Time 3'])

print("Writing to clean.csv...")
output.to_csv( args.output + '/' + 'clean.csv', index=False)

# stats
print("Good points: %i" % len(output.index))
