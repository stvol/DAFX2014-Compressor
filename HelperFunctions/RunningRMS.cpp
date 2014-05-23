/*------------------------------------------------------------------*\
 this file is a Running RMS Plugin 
 public domain
 Author: Jonas Klug, Johannes Schmid (TGM) (Jade-Hochschule)
 \*------------------------------------------------------------------*/
#include "RunningRMS.h"

RunningRMS::RunningRMS(void)
{
	m_alpha = 0.9776; // Wert fuer 1ms Mittelung
	m_fs = 44100;
	m_stateRMS = 0;
}


RunningRMS::RunningRMS(int SamplingFrequenz, int tau)
{
	setAlpha(tau);
	m_fs = SamplingFrequenz;
	m_stateRMS = 0;
}

RunningRMS::~RunningRMS(void)
{
}


void RunningRMS::setAlpha(double tau)
{
	m_alpha = exp(-1/(tau*0.001*m_fs));
}

void RunningRMS::analyseSamplesRMS(double *In, int nSamples)
{
	int kk;
	for (kk = 0; kk < nSamples; kk++)
	{
		// Filterung 
	  double InSample = *In;
	  In++;
	  RMS[kk] = analyzeOneSampleRMS(double InSample);
	}
}





