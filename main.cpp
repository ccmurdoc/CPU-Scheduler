#include <stdio.h>
#include <iomanip>
#include <math.h> // for log function
#include <iostream>
#include <chrono>
using namespace std;
// Global variables

long int seed = 56329; //This should be changed if you need to make
                       // different runs.

// Function to generate uniformly distributed random
//   numbers between 0 and 1.

double random( long int* seed )

  // Warning:  random number generators are, by their
  //   nature, very machine dependent. This generator
  //   will require modification if not run on a
  //   machine with at least a 32 bit word for
  //   integers.

/* Park & Miller function (see CACM Oct. 88) integer version */
/* of their generator.                                       */
/* This should work correctly if largest integer is 2^31 - 1 */
/* or larger.                                                */

{  // function random
	long int  a = 16807,        // 7^5
	          m = 2147483647,   // 2^31 - 1
		  q = 127773,           // m / a (int divide)
		  r = 2836,		        // m % a
		  lo, hi, test;
	double dm = 2147483647;

	hi = *seed / q;
	lo = *seed % q;
	test = a * lo - r * hi;
	*seed = test > 0 ? test : test + m;
	return (double)(*seed/dm);
}  // function random

double exponential(float mean)
{ // function exponential
       return (double)(-mean*log(random(&seed)));
} // function exponential


// Generate process attributes:  primary memory size,
//   execution time (memory references), process type,
//   priority, generation time

void parameters(int   ave_interarrival_time, //between process arrivals
                    int   last_arival_time, //last process arrival time
                    int max_CPU_size,   //Maximum CPU Burst Size
                    int min_CPU_size,   // Minimum CPU Burst Size
                    int* priority,          //Priority
                    long*  arrival_time, //Time of arrival
                    int* CPU_burst_size) //CPU Burst Size

  // Procedures called:
  //   random:  to generate uniformly distributed random variates.
 //    exponential: to generate exponentially distributed random variates
  // Global variables:
  //   seed:  used by function random.

{ // function parameters
  *priority = 1 + int(10*random(&seed)); //generates priority between 1 and 10
  *arrival_time = (long) (last_arival_time + exponential((float) (ave_interarrival_time)) + 0.5);
  *CPU_burst_size = min_CPU_size + int((max_CPU_size-min_CPU_size)*random(&seed)); // generates CPU Burst size
} // function parameters


int main()

{
  auto begin = chrono::high_resolution_clock::now();

  int   hist[10];
  int   index;
  int   i;
  int   max_CPU_burst=25, min_CPU_burst=1;
  int   this_CPU_burst_length;
  int   this_priority;
  int   ave_interarr_time=6;
  int last_arrival_time = 2;
  long this_arrival_time;
  int temp;
  double tstp;
  int stacks=10000;

  int total_wt;
  int total_tat;
  int tat;
  int wt[stacks];
  float tst;
  int sum;
  float cpuUt;
  int burst[stacks];
  int process[stacks];
  int n = sizeof process / sizeof process[0];
  int service_time[n];

 /*cout << "Maximum CPU Burst: ";
  //cin >>   max_CPU_burst;
  cout << "Minimum CPU Burst: ";
  //cin >>   min_CPU_burst;
  cout << "Average Interarrival Time: ";
  //cin >>   ave_interarr_time;
  */

  cout << "Index " << "  Arrival time  "<< "CPU Burst Length " << "  Priority"
  << "   Service Time" << "       Waiting time"<< "      Turn Around Time"<<endl;
  cout<<endl;


        total_wt=0;
        total_tat=0;
// Assuming that there are stacks00 processes
    for ( i=1; i<=stacks; i++ )
	{

        parameters(ave_interarr_time, last_arrival_time, max_CPU_burst, min_CPU_burst, &this_priority, &this_arrival_time, &this_CPU_burst_length);

        burst[i]= this_CPU_burst_length;

        service_time[0]=0;

        // Add burst time of previous processes
        service_time[i] = service_time[i-1] + burst[i]; //Completion Time
        wt[0]=0;
        //service_time[i+1] + i;
        if(service_time[i]<0)
            service_time[i]=0;

             last_arrival_time = this_arrival_time;

        // Find waiting time for current process =
        // sum - last_arrival_time;
        wt[i] = service_time[i] - this_arrival_time;
        tat = burst[i]+ wt[i];

        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat;
        tst = (float)tst+service_time[i];
        tstp= (double)tstp+i;
        // If waiting time for a process is in negative
        // that means it is already in the ready queue
        // before CPU becomes idle so its waiting time is 0
           if (wt[i] < 0)
            wt[i] = 0;
       /* cout<<"Service time: "<<service_time[i] <<endl;
        cout<<"Waiting time: "<<wt[i]<<endl;*/

      cout << setw( 4 ) << i << setw(12)  << this_arrival_time << setw( 14) << this_CPU_burst_length;
        cout << setw(15) << this_priority <<setw(16)<<service_time[i]<<setw(18)<<wt[i]<<setw(20)<<tat<<endl;

	}
double CPUUTL=0;
double CPUIDL=0;
CPUUTL = ((tstp/tst))*100;
CPUIDL = 100 -CPUUTL;

    cout << endl;

    auto end = chrono::high_resolution_clock::now();
    auto dur = end - begin;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
     cout<<"_________________________________________________________"<<endl;
     cout<<"\n             Statistics for the RUN"<<endl;

    cout<< "\n     Number of processes: "<<stacks;
    cout<<"\n     Total Elapsed time:  "<<ms<<" ms "<<endl;

    cout<< "     Throughput = "
    <<(double)stacks/service_time[stacks]<<endl;

    cout<<"     CPU utilization =  Usage: "
    <<CPUUTL<<"%";
    cout<<"   Idle: "<<CPUIDL<< "%";
        cout << "\n     Average Waiting Time = "
         << (float)total_wt/stacks;
         cout<<" ms";
    cout << "\n     Average Turnaround Time = "
       << (float)total_tat/stacks;

       cout<<" ms"<< endl;
    cout<<"     Average response time = "
        <<(tst-service_time[stacks])/stacks<<"ms"<<endl;
        cout<<"_________________________________________________________"<<endl;

return 0;
  } // function main
