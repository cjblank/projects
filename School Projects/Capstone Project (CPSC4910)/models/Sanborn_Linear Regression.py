%matplotlib inline
import matplotlib.pyplot as plt
import seaborn as sns; sns.set()
import numpy as np
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures
from sklearn.pipeline import make_pipeline
from sklearn.model_selection import KFold
import pandas as pd
from pandas.tseries.holiday import USFederalHolidayCalendar  # we may want to account for holidays and this would allow that
import datetime
from dateutil.parser import parse
import os
import geopy
from geopy.geocoders import Nominatim
base_directory = "A:/"

directory = os.fsencode(base_directory + "csv")

training = pd.DataFrame()
for file in os.listdir(directory):  # append data to df
    filename = os.fsdecode(file)
    print("Reading " + filename + "...")
    temp = pd.read_csv(base_directory + "csv/" + filename, thousands=',')
    training = pd.concat([training, temp], sort=True)

training.reset_index(inplace=True)

# convert to catagorical var
#training['day'] = training['day'].astype('category')
training['month'] = training['month'].astype('category')
training['direction'] = training['direction'].astype('category')
training['m_sys'] = training['m_sys'].astype('category')
training['mode'] = training['mode'].astype('category')
training['segment'] = training['segment'].astype('category')
training['weekday'] = training['weekday'].astype('category')

# set x and y
delta = training['delta']
training = training.drop(columns=['delta'])

# make dummy categorical variables for numpy
training_d = pd.get_dummies(training)

# add square of weight and distance
training_d['weight squared'] = training_d['weight']**2
training_d['distance squared'] = training_d['dist']**2
training_d.head()

training_d.dropna(axis=0, how='any', inplace=True)

X = training_d.drop(columns=['index'])
Y = delta

X.head()

#------------------------------------------------------------------------
# LIN REG MODEL
#------------------------------------------------------------------------

model = LinearRegression()
kfold = KFold(n_splits=5, shuffle=True)
scores = []
#MSE = []
#MAE = []
for result in kfold.split(X, Y):
    model.fit(X.iloc[result[0]], Y.iloc[result[0]])
    score = model.score(X.iloc[result[1]], Y.iloc[result[1]])
    scores.append(score)
    #MSE.append(metrics.mean_squared_error(Y.iloc[result[1]], X.iloc[result[1]]))

# r-values
print(scores)

# model = LinearRegression()
# model.fit(X, Y)
training_d['predicted'] = model.predict(X)

from sklearn.utils import resample
np.random.seed(1)
err = np.std([model.fit(*resample(X, Y)).coef_
              for i in range(10)], 0)

params = pd.Series(model.coef_, index=X.columns)

training_d['delta'] = delta
training_d[['delta', 'predicted']].plot(alpha=0.5)

from sklearn import metrics

print('Mean Absolute Error:', metrics.mean_absolute_error(training_d['delta'], training_d['predicted']))
print('Mean Squared Error:', metrics.mean_squared_error(training_d['delta'], training_d['predicted']))
print('\n')

print(pd.DataFrame({'effect': params.round(0),
                    'error': err.round(0)}))


percent_wrong = abs(training_d['delta'] - training_d['predicted'])/(training_d['delta'])

percent_wrong_array = np.asarray(percent_wrong)
count_within_range = (percent_wrong_array < 0.25).sum()

print("amount within range: " + count_within_range)
print("percent within range: " + count_within_range/len(percent_wrong)*100)