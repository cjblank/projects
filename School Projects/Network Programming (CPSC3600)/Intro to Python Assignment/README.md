Design:	
	I designed the program to take in the user input and add the input to the dictionary "testDict" in a single 
		line. I also used the else if function in Python to validate the user input by making temporary lists that 
		would store the values for 'Throughput', 'RTT', and 'ConnectionStatus'. I then converted those variables 
		into individual floats so that I could validate each data point that the user entered. I decided to catch 
		the 'ValueError' exception, due to me immediately casting the input to floats, so that invalid input 
		could be caught as soon as the user hit enter instead of giving them the option to continue entering 
		data. In terms of calculating the data, I decided to pass in the 'container' object and return each result 
		so that it would be easier to print to the console later in the program. 

Issues:
	I ran into mostly syntax issues while writing this program because it is the first time that I have tried 
		using Python. In terms of the design of the program, I had basically thought out the functionality 
		and put it to pseudocode before I implemented it in Python, so I didn't really run into problems 
		logically while coding. One minor issue that I found with my program that I was unable to correct
		was when a user tries to enter a character for the 'RTT' or 'ConnectionStatus'. I made the program 
		so that it picks up on character input immediately with entering the 'Throughput', but if a character 
		is entered for 'RTT' or 'ConnectionStatus', the program will loop back to the beginning after 
		recording the 'Throughput' and prompting you to enter the 'Throughput' again resulting in an extra
		data entry. 
		
Results:
	Evaluation Case 1:
		Throughput: 3.833 and 1.504
		RTT: 11.033 and 1.002
		Connection Status: 25.6 and 1.682
	Evaluation Case 2:
		Throughput: 3.755 and 1.034
		RTT: 14.325 and 4.394
		Connection Status: 20.692 and 5.822
