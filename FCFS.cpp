//FCFS Scheduling
//July 30, 2018
//Authors: James Lopez
//         Chantal Murdock
//Purpose: Make a program about four kinds of CPU scheduling:
//         FCFS, Preemptive SJF and Priority, and Round Robin

#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
using namespace std;
// Global variables

int stacks = 10000;

int main() {

    //Local variables
    auto begin = chrono::high_resolution_clock::now(); //FOr elapsed Time
    int   i;

    double tstp;
    int total_wt;
    int total_tat;
    int tat;
    int wt[stacks];
    float tst;
    int sum;
    float cpuUt;
    int process[stacks];
    int burst[stacks];
    int arrival[stacks];
    int priority[stacks];
    int service_time[stacks];

    //File stream, opens the files
    ifstream myfile;
    ofstream schedFile;
    myfile.open ("datagen.txt");
    schedFile.open ("FCFS_output.txt");

    total_wt=0;
    total_tat=0;

    cout << "Processing... Please Wait..." << endl;

    //Outputs them into a text file
    schedFile << "Process " << "\t" << "Arrival Time" << "\t" << "Burst Time"
              << "\t" << "Priority" << "\t" << "Completion Time   " << "\t"
              << "Waiting Time " << "\t" << "Turnaround Time" << endl;

    //Processing each process for first come first serve.
    for ( i=1; i <= stacks; i++ ) {
        service_time[0]=0;
        wt[0]=0;

        //Getting the values from the file output
        myfile >> process[i];
        myfile >> arrival[i];
        myfile >> burst[i];
        myfile >> priority[i];

        service_time[i] = service_time[i-1] + burst[i]; //Calculating completion time/service time

        //If it's less than 0 then the completion time is 0
        if(service_time[i] < 0)
            service_time[i] = 0;

        wt[i] = service_time[i] - arrival[i]; //Calculating the waiting time

        //If it's less than 0 then the waiting time is 0
        if (wt[i] < 0)
            wt[i] = 0;

        tat = burst[i] + wt[i]; //Calculating the turnaround time

        total_wt = total_wt + wt[i]; //Calculating the total waiting time
        total_tat = total_tat + tat; //Calculating the total turnaround time

        tst = (float)tst + service_time[i]; //Calculating the total completion time/service time
        tstp = (double)tstp + i; //Calculating the total number of process

        //Output the result to a text file
        schedFile << i << "\t\t"  << arrival[i] << "\t\t" << burst[i]
                  << "\t\t" << priority[i] << "\t\t" << service_time[i]
                  << "\t\t\t" << wt[i] << "\t\t" << tat << endl;
    }

    //Calculations for CPU UTILIZATION and CPU IDLE
    double CPUUTL = 0;
    double CPUIDL = 0;
    CPUUTL = ((tstp/tst)) * 100;
    CPUIDL = 100 - CPUUTL;

    schedFile << endl;

    //Calculations for the elapsed time
    auto end = chrono::high_resolution_clock::now();
    auto dur = end - begin;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

    schedFile << "_________________________________________________________" << endl;
    schedFile << "\n             Statistics for the RUN" << endl;
    schedFile << "\n     Number of processes: " << stacks;
    schedFile << "\n     Total Elapsed time:  " << ms << " ms " << endl;
    schedFile << "     Throughput = "
              << (double)stacks/ms << endl; //Calculations for throughput
    schedFile << "     CPU utilization =  Usage: "
              << CPUUTL << "%";
    schedFile << "   Idle: " << CPUIDL << "%";
    schedFile << "\n     Average Waiting Time = "
              << (double)total_wt/stacks; //Calculations for the average waiting time
    schedFile << " ms";
    schedFile << "\n     Average Turnaround Time = "
              << (double)total_tat/stacks; //Calculations for the average turnaround time
    schedFile << " ms" << endl;
    schedFile << "     Average response time = "
              << (tst-service_time[stacks])/stacks << "ms" << endl; //Calculations for the average response time
    schedFile << "_________________________________________________________" << endl;

    cout << "\nThe FCFS Scheduling Has Been Successfully Processed!" << endl
         << "\nPlease Look the Output in the File Named FCFS_output.txt" << endl;

    //Closes the files
    myfile.close();
    schedFile.close();

    return 0;
}
