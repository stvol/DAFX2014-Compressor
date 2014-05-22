/*------------------------------------------------------------------*\
 This file is a smoothing Plugin.
 public domain
 Author: Jan Willhaus, Julian Kahnert (TGM) (Jade-Hochschule)
\*------------------------------------------------------------------*/

#include "Smoothing.h"
#include <math.h>

/* Constructor */
CSmoothing::CSmoothing(void) {
    
	reset();
}

/* Destructor */
CSmoothing::~CSmoothing(void) {

     /* NOP */
}


/* Reset */
void CSmoothing::reset(void) {
    
	switch (smoothingType) {
        case 1: /* Only true log */
            curOut = 1;
            break;
            
        default:
            curOut = 0;
            break;
    }
}

/* Process */
int CSmoothing::processSamples(double *In, double *Out, int nSamples) {
    
	int kk;
    double InSample;
    
    for (kk=0; kk<nSamples; ++kk) {
        
        InSample = *In;
        In++;
        
        *Out = processOneSample(InSample);
        
        Out++;
        
    }

	return 0;

}

int CSmoothing::setSmoothingRates(double tauAttack, double tauRelease) {
    
    switch (smoothingType) {
        case 0:
            att_rate = exp(-1/(tau_att*fs));
            rel_rate = exp(-1/(tau_rel*fs));
            break;
            
        case 1:
            att_rate = pow(10, (tau_att*0.001)/(10*fs));
            rel_rate = pow(10, -(tau_rel*0.001)/(10*fs));
            break;
            
        case 2:
            att_rate = tau_att/fs;
            rel_rate = tau_rel/fs;
            break;
            
        default:
            break;
    }
    
    
    return 0;
}


int CSmoothing::setSmoothingType(unsigned int newSmoothingType) {
    
    smoothingType = newSmoothingType;
    
    reset();
    
    return 0;
}
