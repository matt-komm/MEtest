#include <iostream>
#include <iomanip> 
#include <time.h>
#include "CPPProcess.h"
#include "rambo.h"

int main(int argc, char** argv){

  // Create a process object
  CPPProcess process;

  // Read param_card and set parameters
  process.initProc("param_card.dat");

  double energy = 1500;
  double weight;
  
   vector<double*> p = get_momenta(process.ninitial, energy, 
				     process.getMasses(), weight);
/*
    float mean=0.0;
	float mean2=0.0;
	for (int run=0; run<10; ++run)
	{
		clock_t t = clock();
		for (int i = 0; i < 1000; ++i)
		{
     
            // Set momenta for this event
            process.setMomenta(p);

            // Evaluate matrix element
            process.sigmaKin();

            const double* matrix_elements = process.getMatrixElements();
		}
		t = clock() -t;
		mean+=(float)t/CLOCKS_PER_SEC;
		mean2+=(float)t*t/CLOCKS_PER_SEC/CLOCKS_PER_SEC;
	}
	printf("%5.4f +- %5.4f\n",mean/10.0,std::sqrt(mean2/10.0-mean*mean/100.0));
*/
     
    
    // Set momenta for this event
    process.setMomenta(p);

    // Evaluate matrix element
    process.sigmaKin();

    const double* matrix_elements = process.getMatrixElements();
    
    cout << "Momenta:" << endl;
    for(int i=0;i < process.nexternal; i++)
    cout << setw(4) << i+1 
    << setiosflags(ios::scientific) << setw(14) << p[i][0]
    << setiosflags(ios::scientific) << setw(14) << p[i][1]
    << setiosflags(ios::scientific) << setw(14) << p[i][2]
    << setiosflags(ios::scientific) << setw(14) << p[i][3] << endl;
    cout << " -----------------------------------------------------------------------------" << endl;

    // Display matrix elements
    for(int i=0; i<process.nprocesses;i++)
    cout << " Matrix element = " 
    << setiosflags(ios::fixed) << setprecision(17)
    << matrix_elements[i]
    << " GeV^" << -(2*process.nexternal-8) << endl;

    cout << " -----------------------------------------------------------------------------" << endl;
    
    return 0;
}
