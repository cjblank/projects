import numpy as np
import pandas as pd
from pipeline import cleanToTrain

from sklearn import preprocessing
from sklearn import metrics
from sklearn.model_selection import KFold

from sklearn.linear_model import LinearRegression

# exec(open("linreg.py").read())

def train_and_eval(model, training_d, delta):
    delta = delta.replace(0,0.5) # fix predict for benchmark

    kfold = KFold(n_splits=5, shuffle=True)
    scores = []
    mses = []
    maes = []
    percents = []
    for result in kfold.split(training_d, delta):
        model.fit(training_d.iloc[result[0]], delta.iloc[result[0]])

        # metrics
        score = model.score(training_d.iloc[result[1]], delta.iloc[result[1]])
        scores.append(score)
        mae =  metrics.mean_absolute_error(delta.iloc[result[1]],model.predict(training_d.iloc[result[1]]))
        maes.append(mae)
        mse =  metrics.mean_squared_error(delta.iloc[result[1]],model.predict(training_d.iloc[result[1]]))
        mses.append(mse)

        # benchmark
        predicts = model.predict(training_d.iloc[result[1]])
        percent_wrong = abs(delta.iloc[result[1]] - predicts)/(delta.iloc[result[1]])
        percent_wrong_array = np.asarray(percent_wrong)
        count_within_range = (percent_wrong_array < 0.25).sum()

        percents.append(count_within_range/len(percent_wrong)*100)


    # r-values (not great)
    print("mean average errors")
    print(maes)
    print()
    print("mean square errors")
    print(mses)
    print()
    print("r^2-values")
    print(scores)
    print()
    print("benchmark")
    print(percents)

print("------------------------------------------------------------------------")
print(" CLEAN -> TRAINING")
print("------------------------------------------------------------------------")

print("Reading csv...")
_input = pd.read_csv("/mnt/a/clean.csv", dtype="object")

data = cleanToTrain(_input, dotw=True, bday=True)
data.parse()

print("------------------------------------------------------------------------")
print(" LIN REG MODEL")
print("------------------------------------------------------------------------")
model = LinearRegression(n_jobs=8)
train_and_eval(model, pd.get_dummies(data.training), data.delta)
