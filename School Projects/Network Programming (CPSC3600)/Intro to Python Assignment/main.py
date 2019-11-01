
#********************************************
#
#	things left to do:
#		4) make README.md file
#
#********************************************

from testContainer import *
from builtins import print
import statistics
import json

#calculates the average of the values
def average(results):
    TPList=results.testDict['Throughput']
    RTTList=results.testDict['RTT']
    CSList=results.testDict['ConnectionStatus']

    TPAvg=(sum(TPList)/len(TPList))
    RRTAvg=(sum(RTTList)/len(RTTList))
    CSAvg=(sum(CSList)/len(CSList))

    return TPAvg, RRTAvg, CSAvg


#calculates the standard deviation of the values
def standardDeviation(results):
	TPList=results.testDict['Throughput']
	RTTList=results.testDict['RTT']
	CSList=results.testDict['ConnectionStatus']

	TPstd=statistics.stdev(TPList)
	RTTstd=statistics.stdev(RTTList)
	CSstd=statistics.stdev(CSList)

	return TPstd, RTTstd, CSstd

#prints the calculations to the console
def printDict(tpavg, tpstd, rttavg, rttstd, csavg, csstd):
    print('You have entered ', testNum - 1, ' test results.\n')
    print('The average and standard deviation of Throughput are ', tpavg, ' and ', tpstd, '.')
    print('The average and standard deviation of RTT are ', rttavg, ' and ', rttstd, '.')
    print('The average and standard deviation of Connection Status are ', csavg, ' and ', csstd, '.')

#creates the JSON file
def write_to_json(my_dict):
    with open('results.json', 'w') as fp:
        json.dump(my_dict, fp)

container = TestResultContainer()

#while loop condition
temp=True

#keeps track of how many tests have been recorded
testNum = 1
while(temp):
    try:
        print ("Entering results for test ", testNum)
        container.testDict['Throughput'].append(float(input('Enter the Throughput: ')))
        tp=container.testDict.get('Throughput')
        container.testDict['RTT'].append(float(input('Enter the Round Trip Time: ')))
        rtt = container.testDict.get('RTT')
        container.testDict['ConnectionStatus'].append(float(input('Enter the Connection Status: ')))
        cs = container.testDict.get('ConnectionStatus')

        #gets the last value of the list so that the input can be validated later
        tp=tp[-1]
        rtt=rtt[-1]
        cs=cs[-1]

        #if else statement used to validate the user input
        if tp < 0 or rtt < 0 or cs < 0:
            print('Invalid input, please enter a positive number')
        else:
            testNum += 1
    #used to catch the "Ctrl+C" command from the user
    except KeyboardInterrupt:
        temp=False
        pass
    #used to catch errors when a user enters a non-float type
    except ValueError:
        print('Invalid input, pleas enter a valid number')

print ("\n\n-------------------------\nInput loop exited\n-------------------------\n")
TPavg, RTTavg, CSavg = average(container)
TPstd, RTTstd, CSstd = standardDeviation(container)

#round the averages to 3 decimal places
TPavg=round(TPavg, 3)
RTTavg=round(RTTavg, 3)
CSavg=round(CSavg, 3)

#round the average to 3 decimal places
TPstd=round(TPstd, 3)
RTTstd=round(RTTstd, 3)
CSstd=round(CSstd, 3)

printDict(TPavg, TPstd, RTTavg, RTTstd, CSavg, CSstd)

write_to_json(container.testDict)
