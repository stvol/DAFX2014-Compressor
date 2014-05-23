/*------------------------------------------------------------------*\
 this file is a PeakRMSMix Plugin 
 public domain
 Author: Jonas Klug, Johannes Schmid (TGM) (Jade-Hochschule)
 \*------------------------------------------------------------------*/
#include "PeakRMSMix.h"


PeakRMSMix::PeakRMSMix(void)
{
	m_MixRatio = 0.5
}

PeakRMSMix::~PeakRMSMix(void)
{
}

void PeakRMSMix::setMixRatio(double MixRatio)
{
	m_MixRatio = MixRatio;
}

void PeakRMSMix::samplesMix(double *InPeak, double *InRMS, int nSamples)
{
	
	int kk;
	for (kk = 0; kk < nSamples; kk++)
	{
	  double InSamplePeak = *InPeak;
	  InPeak++;
	  double InSampleRMS = *InRMS;
	  InRMS++;

	  Mix[kk] = oneSampleMix(InSamplePeak, InSampleRMS) ;
	}
}

