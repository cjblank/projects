import pandas as pd
import numpy as np
import sklearn
from sklearn import linear_model
from sklearn.utils import shuffle
from pandas import ExcelWriter
from pandas import ExcelFile

df = pd.read_excel("18-01.xlsx")

df = df[['Actual Transit (AT) (End Time - Start Time)','Min Miles', 'Miles', 'Max Miles','Weight Tons']]

#print("Column Headings: ")
#print(df.columns)

df = df[df['Actual Transit (AT) (End Time - Start Time)'] != '-']
df = df[df['Min Miles'] != '-']
df = df[df['Max Miles'] != '-']

#df.drop(badMinM)
#df.drop(badMaxM)

predict = "Actual Transit (AT) (End Time - Start Time)"

x = np.array(df.drop([predict], 1))
y = np.array(df[predict])

x_train, x_test, y_train, y_test = sklearn.model_selection.train_test_split(x, y, test_size=0.1)

linear = linear_model.LinearRegression()

linear.fit(x_train, y_train)
acc = linear.score(x_test,y_test)



print("r^2 value: " + str(acc))

predictions = linear.predict(x_test)


#-----------------------------------------------------
# This will test the accuracy according to Westrock's 
#   expectations
#-----------------------------------------------------
count = 0
for x in range(len(predictions)):
    absoluteVal = y_test[x] - predictions[x]
    if (abs(absoluteVal) / y_test[x]) < .25:
        count+=1

    #print(predictions[x], y_test[x])

accuracy = count/len(predictions)

print("Model's accuracy: " + str(accuracy))



