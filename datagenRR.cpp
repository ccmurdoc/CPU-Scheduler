#include <stdio.h>
#include <iomanip>
#include <math.h> // for log function
#include <iostream>
#include <fstream>
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
       return (double)(-mean*log (random(&seed)));
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
  int   hist[10];
  int   index;
  int   i;

  int   max_CPU_burst, min_CPU_burst;
  int   this_CPU_burst_length;
  int   this_priority;
  int   ave_interarr_time;
  int last_arrival_time = 0;
  long this_arrival_time;
  int temp;

  ofstream myfile;
  myfile.open ("datagenRR.txt");

  cout << "Maximum CPU Burst: ";
  cin >>   max_CPU_burst;
  cout << "Minimum CPU Burst: ";
  cin >>   min_CPU_burst;
  cout << "Average Interarrival Time: ";
  cin >>   ave_interarr_time;

// Assuming that there are 10000 processes
    for ( i = 1; i <= 15; i++ ) {

      parameters(ave_interarr_time, last_arrival_time, max_CPU_burst,
                 min_CPU_burst, &this_priority, &this_arrival_time,
                 &this_CPU_burst_length);

      myfile << setw( 4 ) << i << setw(12)  << this_arrival_time << setw( 20) << this_CPU_burst_length;
      myfile << setw(6) << this_priority << endl;


      last_arrival_time = this_arrival_time;
    }

    cout << endl;
    cout << "Data for Round Robin Scheduling have been Generated!" << endl;

    myfile.close();

  return 0;
} // function main
