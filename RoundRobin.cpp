//Round Robin Scheduling
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

//Global Variable
int stacks = 15;

int main() {
    //Local variables
    auto begin = chrono::high_resolution_clock::now();
    int i, t[stacks];
    double tstp;
    int total_wt;
    int total_tat;
    int tat;
    int burst[stacks];
    int arrival[stacks];
    int process[stacks];
    int rem_bt[stacks];
    int priority[stacks];
    int wt[stacks];
    double tst;
    int sum;
    double cpuUt;

    //File stream, opens the files
    ifstream myfile;
    ofstream schedFile;
    myfile.open ("datagenRR.txt");
    schedFile.open ("RR_output.txt");

    //Quantum number
    int quantum = 3;

    cout << "Processing... Please Wait..." << endl;

    //Outputs them into a text file
    schedFile << "Process " << "\t" << "Arrival Time" << "\t" << "Burst Time" << "\t" << "Priority"
              << "\t" << "Completion Time   " << "\t" << "Waiting Time " << "\t" << "Turnaround Time" << endl;
    schedFile << endl;

    //Processing each process for Round Robin
    for ( i = 1; i <= stacks; i++ ) {

        //Getting all the values from the output text file
        myfile >> process[i];
        myfile >> arrival[i];
        myfile >> burst[i];
        myfile >> priority[i];

        int ct;

        //Each burst time is the remaining burst time
        for (int i = 1 ; i <= stacks ; i++) {
            rem_bt[i] =  burst[i];
        }

        t[0] = 0;

        while (1)
        {
            bool done = true; //Boolean value for each process

            //Processing each process
            for (int i = 1 ; i <= stacks; i++)
            {
                //If the the remaining burst time more than 0
                if (rem_bt[i] > 0)
                {
                    done = false; //Boolean value for not done for that process

                    //If the remaining burst time is more than the quantum number
                    if (rem_bt[i] > quantum)
                    {
                        t[i] += quantum; //Add quantum to the completion time
                        rem_bt[i] -= quantum; //Subtract quantum time to the burst time
                    }

                    //If the remaining burst time is less than or equal the quantum number
                    else
                    {
                        t[i] = t[i-1] + rem_bt[i]; //Calculate Completion time
                        wt[i] = arrival[i] - t[i] - burst[i]; //Calculate waiting time
                        rem_bt[i] = 0; //Remaining burst time is 0
                    }
                }
            }

            // If all processes are done
            if (done == true)
              break;
        }

        tat = burst[i]+ wt[i]; //Calculating the turnaround time

        total_wt = total_wt + wt[i]; //Calculating the total waiting time
        total_tat = total_tat + tat; //Calculating the total turnaround time

        tst = (double)tst + t[i]; //Calculating the total completion time/service time
        tstp = (double)tstp + process[i]; //Calculating the total number of process

        //Output the result into a text file
        schedFile << process[i] << "\t\t" << arrival[i] << "\t\t" << burst[i] << "\t\t"
                  << priority[i] << "\t\t" << t[i] << "\t\t\t" << wt[i] << "\t\t" << tat << endl;

    }

    //Calculations for the elapsed time
    auto end = chrono::high_resolution_clock::now();
    auto dur = end - begin;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

    //Calculations for CPU UTILIZATION and CPU IDLE
    double CPUUTL = 0;
    double CPUIDL = 0;
    CPUUTL = ((tstp/tst))*100;
    CPUIDL = 100 -CPUUTL;

    schedFile << "\n_________________________________________________________" << endl;
    schedFile << "\n             Statistics for the RUN" << endl;
    schedFile << "\n     Number of processes: " << stacks;
    schedFile << "\n     Total Elapsed time:  " << ms << " ms ";
    schedFile << "\n     Average Waiting Time = "
              << total_wt;
    schedFile << "\n     Average Turn Around time = "
              << total_tat;
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
              << (tst - t[stacks])/stacks << "ms" << endl; //Calculations for the average response time
    schedFile << "_________________________________________________________" << endl;

    cout << "\nThe Round Robin Scheduling Has Been Successfully Processed!" << endl
          << "\nPlease Look the Output in the File Named RR_output.txt" << endl;

    //Closing the files
    myfile.close();
    schedFile.close();

    return 0;
}
