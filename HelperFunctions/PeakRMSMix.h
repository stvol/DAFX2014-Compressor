/*------------------------------------------------------------------*\
 this file is a PeakRMSMix Plugin 
 public domain
 Author: Jonas Klug, Johannes Schmid (TGM) (Jade-Hochschule)
 Version 1.0
 \*------------------------------------------------------------------*/
#ifndef _CPeakRMSMix_H_TGM
#define _CPeakRMSMix_H_TGM
#include <math.h>


class CPeakRMSMix
{
public:
	CPeakRMSMix(void);
	CPeakRMSMix(double mixRatio);
	~CPeakRMSMix(void);

	// RMS und Peak Mix
	void setMixRatio(double MixRatio);
	inline double processOneSample(double InPeak, double InRMS) 
	{
	  return InPeak*(m_MixRatio) + InRMS*(1-m_MixRatio);
	};
	int processSamples(double *InPeak, double *InRMS, double *Out, int nSamples);
	
private:
	double m_MixRatio; 
};
#endif