/*------------------------------------------------------------------*\
 this file is a Running RMS Plugin 
 public domain
 Author: Jonas Klug, Johannes Schmid (TGM) (Jade-Hochschule)
 Version 1.0
 \*------------------------------------------------------------------*/

#ifndef _CRUNNINGRMS_H_TGM
#define _CRUNNINGRMS_H_TGM
#include <math.h>


class CRunningRMS
{
public:
	CRunningRMS(void);
	CRunningRMS(double SamplingFrequenz, double tau);
	~CRunningRMS(void);
	void reset(void){m_stateRMS = 0.;};

	// RMS Berechnung
	void setAlpha(double tau);
	
	inline double analyseOneSample(double In)
	{
	  m_stateRMS = (1 - m_alphaRMS)*(In*In) + m_alphaRMS*m_stateRMS;
	  return sqrt(m_stateRMS);
	 };
	int analyseSamples(double *In, double *Out, int nSamples);
	
	
private:
	double m_alphaRMS, m_fs, m_stateRMS;
	
};

#endif