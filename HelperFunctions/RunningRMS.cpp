/*------------------------------------------------------------------*\
 this file is a Running RMS Plugin 
 public domain
 Author: Jonas Klug, Johannes Schmid (TGM) (Jade-Hochschule)
 \*------------------------------------------------------------------*/
#include "RunningRMS.h"

CRunningRMS::CRunningRMS(void)
{
	m_alphaRMS = 0.9776; // Wert fuer 1ms Mittelung
	m_fs = 44100;
	m_stateRMS = 0;
}


CRunningRMS::CRunningRMS(double SamplingFrequenz, double tau)
{
	m_fs = SamplingFrequenz;
	setAlpha(tau);
	m_stateRMS = 0;
}

CRunningRMS::~CRunningRMS(void)
{
}


void CRunningRMS::setAlpha(double tau)
{
	m_alphaRMS = exp(-1/(tau*0.001*m_fs));
}

int CRunningRMS::analyseSamples(double *In, double * Out, int nSamples)
{
	int kk;
	for (kk = 0; kk < nSamples; kk++)
	{
        *Out = analyseOneSample(*In);
        Out++;
        In++;
	}
    return 0;

}





