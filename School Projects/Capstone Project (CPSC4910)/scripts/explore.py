import numpy as np
import pandas as pd
import datetime
import os

# exec(open("explore.py").read())
# Run this in the console
# All data gets collapsed into 1 dataframe

#------------------------------------------------------------------------
# CLEAN AND READ DATA
#------------------------------------------------------------------------
base_directory = "/media/veracrypt1/"
directory = os.fsencode(base_directory + "original")

data = pd.DataFrame()
for file in os.listdir(directory):
    filename = os.fsdecode(file)
    print("Reading " + filename + "...")
    _input = pd.read_excel(base_directory + "original/" + filename, thousands=',')
    data = data.append(_input, sort=True)
    data = data.reindex()
