Instructions for CPU Scheduling
Authors: James Lopez
	 Chantal Murdock

#CPU Scheduler for: FCFS, SJF with preemption, RR (with specified time quantum), and Priority with preemption

Read these instructions carefully.

For FCFS, Preemptive SJF and Priority:

	1. FIRSTLY! Open datagen.cpp and run the program to generate random 
	   number of burst time and arrival time of each process.
	   The values are generated in a text file called datagen.txt.
	   
	2. If you want to do FCFS first, open FCFS.cpp and run the 
	   CPU scheduling for FCFS. The values are outputted in a
	   text file called FCFS_ouput.txt
	   
	3. If you want to do Preemptive SJF first, open SJF.cpp 
	   and run the CPU scheduling for Preemptive SJF. 
	   Since it has 10000 process, you have to wait like 5 mins to complete the run.
	   The values are outputted in a text file called SJF_ouput.txt
	
	4. If you want to do Preemptive Priority first, open Priority.cpp 
	   and run the CPU scheduling for Preemptive Priority.
	   Since it has 10000 process, you have to wait like 5 mins to complete the run.
	   The values are outputted in a text file called Prio_ouput.txt
	   
	Note: Since it has 10000 process, you have to wait like 5 mins to complete the run
		  for Preemptive SJF and Preemptive Priority.
	   
For Round Robin:

	1. FIRSTLY! Open datagenRR.cpp and run the program to generate random 
	   number of burst time and arrival time of each process.
	   The values are generated in a text file called datagenRR.txt.
	   
	Note: Since this algorithm takes a lot of time to process 100-10000 processes (It took hours and even days)
	      We only generate 15 processes (It only took 20-30 seconds.)
		  
	2. Open RoundRobin.cpp and run the CPU scheduling for Round Robin. 
	   The values are outputted in a text file called RR_ouput.txt
	   
	
