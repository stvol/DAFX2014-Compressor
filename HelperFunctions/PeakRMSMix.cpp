/*------------------------------------------------------------------*\
 this file is a PeakRMSMix Plugin 
 public domain
 Author: Jonas Klug, Johannes Schmid (TGM) (Jade-Hochschule)
 \*------------------------------------------------------------------*/
#include "PeakRMSMix.h"


CPeakRMSMix::CPeakRMSMix(void)
{
	m_MixRatio = 0.5;
}

CPeakRMSMix::CPeakRMSMix(double mixRatio)
{
	m_MixRatio = mixRatio;
}
CPeakRMSMix::~CPeakRMSMix(void)
{
}

void CPeakRMSMix::setMixRatio(double MixRatio)
{
	m_MixRatio = MixRatio;
}

int CPeakRMSMix::processSamples(double *InPeak, double *InRMS, double * Out, int nSamples)
{
	
	int kk;
	for (kk = 0; kk < nSamples; kk++)
	{
	  double InSamplePeak = *InPeak;
	  InPeak++;
	  double InSampleRMS = *InRMS;
	  InRMS++;
      *Out = processOneSample(InSamplePeak,InSampleRMS);
      Out++;
	}
    return 0;
}

