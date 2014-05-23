/*------------------------------------------------------------------*\
 this file is a PeakRMSMix Plugin 
 public domain
 Author: Jonas Klug, Johannes Schmid (TGM) (Jade-Hochschule)
 \*------------------------------------------------------------------*/
#ifndef _CPeakRMSMix_H_TGM
#define _CPeakRMSMix_H_TGM
#include <math.h>


class PeakRMSMix
{
public:
	PeakRMSMix(void);
	~PeakRMSMix(void);

	// RMS und Peak Mix
	void setMixRatio(double MixRatio);
	inline double oneSampleMix(double InPeak, double InRMS) 
	{
	  return InPeak*(m_MixRatio) + InRMS*(1-m_MixRatio);
	};
	void samplesMix(double *InPeak, double *InRMS, int nSamples);
	
private:
	double m_MixRatio, Mix[]; 
};
#endif