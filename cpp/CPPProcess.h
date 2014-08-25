//==========================================================================
// This file has been automatically generated for C++ Standalone by
// MadGraph 5 v. 1.5.13, 2013-11-04
// By the MadGraph Development Team
// Please visit us at https://launchpad.net/madgraph5
//==========================================================================

#ifndef MG5_Sigma_sm_uux_bmupvmbxmumvmx_H
#define MG5_Sigma_sm_uux_bmupvmbxmumvmx_H

#include <complex> 
#include <vector> 

#include "Parameters_sm.h"

using namespace std; 

//==========================================================================
// A class for calculating the matrix elements for
// Process: u u~ > t t~ WEIGHTED=2
// *   Decay: t > b mu+ vm WEIGHTED=4
// *   Decay: t~ > b~ mu- vm~ WEIGHTED=4
// Process: c c~ > t t~ WEIGHTED=2
// *   Decay: t > b mu+ vm WEIGHTED=4
// *   Decay: t~ > b~ mu- vm~ WEIGHTED=4
// Process: d d~ > t t~ WEIGHTED=2
// *   Decay: t > b mu+ vm WEIGHTED=4
// *   Decay: t~ > b~ mu- vm~ WEIGHTED=4
// Process: s s~ > t t~ WEIGHTED=2
// *   Decay: t > b mu+ vm WEIGHTED=4
// *   Decay: t~ > b~ mu- vm~ WEIGHTED=4
//--------------------------------------------------------------------------

class CPPProcess
{
  public:

    // Constructor.
    CPPProcess() {}

    // Initialize process.
    virtual void initProc(string param_card_name); 

    // Calculate flavour-independent parts of cross section.
    virtual void sigmaKin(); 

    // Evaluate sigmaHat(sHat).
    virtual double sigmaHat(); 

    // Info on the subprocess.
    virtual string name() const {return "u u~ > b mu+ vm b~ mu- vm~ (sm)";}

    virtual int code() const {return 0;}

    const vector<double> & getMasses() const {return mME;}

    // Get and set momenta for matrix element evaluation
    vector < double * > getMomenta(){return p;}
    void setMomenta(vector < double * > & momenta){p = momenta;}
    void setInitial(int inid1, int inid2){id1 = inid1; id2 = inid2;}

    // Get matrix element vector
    const double * getMatrixElements() const {return matrix_element;}

    // Constants for array limits
    static const int ninitial = 2; 
    static const int nexternal = 8; 
    static const int nprocesses = 2; 

  private:

    // Private functions to calculate the matrix element for all subprocesses
    // Calculate wavefunctions
    void calculate_wavefunctions(const int perm[], const int hel[]); 
    static const int nwavefuncs = 13; 
    std::complex<double> w[nwavefuncs][18]; 
    static const int namplitudes = 1; 
    std::complex<double> amp[namplitudes]; 
    double matrix_uux_ttx_t_bmupvm_tx_bxmumvmx(); 

    // Store the matrix element value from sigmaKin
    double matrix_element[nprocesses]; 

    // Color flows, used when selecting color
    double * jamp2[nprocesses]; 

    // Pointer to the model parameters
    Parameters_sm * pars; 

    // vector with external particle masses
    vector<double> mME; 

    // vector with momenta (to be changed each event)
    vector < double * > p; 
    // Initial particle ids
    int id1, id2; 

}; 


#endif  // MG5_Sigma_sm_uux_bmupvmbxmumvmx_H
