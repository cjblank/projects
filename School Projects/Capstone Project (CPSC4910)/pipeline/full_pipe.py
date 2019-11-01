import numpy as np
import pandas as pd
import pipeline

from sklearn import preprocessing
from sklearn import metrics
from sklearn.model_selection import KFold

from sksurv.preprocessing import OneHotEncoder
from sksurv.linear_model import CoxPHSurvivalAnalysis
from sksurv.metrics import concordance_index_censored

from sklearn.linear_model import LinearRegression

def train_and_eval(model, training_d, delta):
    if 0 in delta:
        print("fix same day shipment metrics")
        delta += .001 

    kfold = KFold(n_splits=5, shuffle=True)
    scores = []
    mses = []
    maes = []
    percents = []
    for result in kfold.split(training_d, delta):
        trns = (training_d.iloc[result[0]], delta.iloc[result[0]])
        tests = (training_d.iloc[result[1]], delta.iloc[result[1]])
        model.fit(trns[0], trns[1])

        # metrics
        score = model.score(tests[0], tests[1])
        scores.append(score)
        predicts = model.predict(tests[0])

        mae =  metrics.mean_absolute_error(tests[1], predicts)
        maes.append(mae)
        mse =  metrics.mean_squared_error(tests[1], predicts)
        mses.append(mse)

        # benchmark
        percent_wrong = abs(tests[1] - predicts)/(tests[1])
        percent_wrong_array = np.asarray(percent_wrong)
        count_within_range = (percent_wrong_array < 0.25).sum()

        percents.append(count_within_range/len(percent_wrong)*100)

    print("mean average errors: ", maes)
    print("mean square errors: ", mses)
    print("r^2-values: ", scores)
    print("benchmark: ", percents)

print("------------------------------------------------------------------------")
print(" ALL -> CLEAN")
print("------------------------------------------------------------------------")

print("Reading all.csv...")
_input = pd.read_csv("/media/veracrypt1/all.csv", dtype="object")

staging = pipeline.CleanData(_input)
staging.clean_bad_dates()
staging.clean_max_days()
staging.finalize()

print("------------------------------------------------------------------------")
print(" CLEAN -> FILTERED")
print("------------------------------------------------------------------------")

data = pipeline.FilterData(staging.df, dotw=True, bday=True)
staging = None
data.parse()

print("------------------------------------------------------------------------")
print(" LIN REG MODEL")
print("------------------------------------------------------------------------")

training_x = OneHotEncoder().fit_transform(data.training)

model = LinearRegression()
train_and_eval(model, training_x, data.delta)

print("------------------------------------------------------------------------")
print(" SURVIVAL MODEL")
print("------------------------------------------------------------------------")

delta_y = np.zeros(len(data.delta), dtype=[('status', '?'), ('delta', '<i4')])
delta_y['status'] = (data.delta != 'NaN')
delta_y['delta'] = data.delta

model = CoxPHSurvivalAnalysis()

kfold = KFold(n_splits=1, shuffle=True)
scores = []
mses = []
maes = []
percents = []
for result in kfold.split(training_d, delta):
    print("Fitting...")
    trns = (training_d.iloc[result[0]], delta[result[0]])
    tests = (training_d.iloc[result[1]], delta[result[1]])
    model.fit(trns[0], trns[1])

    # metrics
    print("Scoring...")
    score = model.score(tests[0], tests[1])
    scores.append(score)
    predicts = model.predict(tests[0])

    mae =  metrics.mean_absolute_error(tests[1], predicts)
    maes.append(mae)
    mse =  metrics.mean_squared_error(tests[1], predicts)
    mses.append(mse)

    # benchmark
    #percent_wrong = abs(tests[1] - predicts)/(tests[1])
    #percent_wrong_array = np.asarray(percent_wrong)
    #count_within_range = (percent_wrong_array < 0.25).sum()

    #percents.append(count_within_range/len(percent_wrong)*100)

print("mean average errors: ", maes)
print("mean square errors: ", mses)
print("r^2-values: ", scores)
#print("benchmark: ", percents)
