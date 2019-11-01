import numpy as np
import pandas as pd
import datetime
import os
import argparse

def dir_path(string):
    if os.path.isdir(string):
        return string
    else:
        raise NotADirectoryError(string)

parser = argparse.ArgumentParser(description="raw data -> one csv")
parser.add_argument('input', help="directory to the raw data", type=dir_path)
parser.add_argument('output', help="directory for the csv", type=dir_path)
args = parser.parse_args()

print("-------------------------------------------------------")
print(" RAW -> ALL")
print("-------------------------------------------------------")
directory = os.fsencode(args.input)

output = pd.DataFrame()
for file in os.listdir(directory):
    filename = os.fsdecode(file)
    print("Reading " + filename + "...")
    df = pd.read_excel(args.input + '/' + filename, thousands=',')

    output = output.append(df, sort=True)

# drop irrelevant var
output = output.drop(columns=['End Time 1',
    'End Time 2',
    'End Time 3',
    'Start Time 1',
    'Start Time 2',
    'Start Time 3'])

print("Writing to all.csv...")
output.to_csv( args.output + '/' + 'all.csv', index=False)
