import numpy as np
import pandas as pd
import datetime
import os

from sklearn import preprocessing
from sklearn import metrics
from sklearn.model_selection import KFold
from sklearn.linear_model import LinearRegression

# exec(open("linreg.py").read())

#------------------------------------------------------------------------
# READ DATA
#------------------------------------------------------------------------
directory = os.fsencode("/media/veracrypt1/csv")

training = pd.DataFrame()
for file in os.listdir(directory): # append data to df
    filename = os.fsdecode(file)
    print("Reading " + filename + "...")
    temp = pd.read_csv("/media/veracrypt1/csv/" + filename, thousands=',')
    training = pd.concat([training, temp], sort=True)

training.reset_index(inplace=True)

# convert to catagorical var
training['day'] = training['day'].astype('category')
training['month'] = training['month'].astype('category')
training['direction'] = training['direction'].astype('category')
training['m_sys'] = training['m_sys'].astype('category')
training['mode'] = training['mode'].astype('category')
training['segment'] = training['segment'].astype('category')

# set x and y
delta = training['delta']
#training = training.drop(columns=['delta', 'weekday'])
training = training.drop(columns=['delta', 'day'])

# make dummy categorical variables for numpy
training_d = pd.get_dummies(training)

#------------------------------------------------------------------------
# LIN REG MODEL
#------------------------------------------------------------------------

model = LinearRegression()
#kfold = KFold(n_splits=5, shuffle=True)
kfold = KFold(n_splits=5, shuffle=True)
scores = []
mses = []
maes = []
for result in kfold.split(training_d, delta):
    model.fit(training_d.iloc[result[0]], delta.iloc[result[0]])
    score = model.score(training_d.iloc[result[1]], delta.iloc[result[1]])
    scores.append(score)
    mae =  metrics.mean_absolute_error(delta.iloc[result[1]],model.predict(training_d.iloc[result[1]]))
    maes.append(mae)
    mse =  metrics.mean_squared_error(delta.iloc[result[1]],model.predict(training_d.iloc[result[1]]))
    mses.append(mse)
    predicts = model.predict(training_d.iloc[result[1]])
    percent_wrong = abs(delta.iloc[result[1]] - predicts)/(delta.iloc[result[1]])
    percent_wrong_array = np.asarray(percent_wrong)
    count_within_range = (percent_wrong_array < 0.25).sum()

    print("amount within range: " + str(count_within_range) + "/" + str(len(percent_wrong)))
    print("percent within range: " + str(count_within_range/len(percent_wrong)*100))
    print()


# r-values (not great)
print("mean average errors")
print(maes)
print()
print("mean square errors")
print(mses)
print()
print("r-values")
print(scores)
