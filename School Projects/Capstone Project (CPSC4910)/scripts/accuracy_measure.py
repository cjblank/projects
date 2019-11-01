percent_wrong = abs(training_d['delta'] - training_d['predicted'])/(training_d['delta'])

percent_wrong_array = np.asarray(percent_wrong)
count_within_range = (percent_wrong_array < 0.25).sum()

print("amount within range: " + count_within_range)
print("percent within range: " + count_within_range/len(percent_wrong)*100)
