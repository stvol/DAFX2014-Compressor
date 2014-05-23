/*------------------------------------------------------------------*\
 this file is a Running RMS Plugin 
 public domain
 Author: Jonas Klug, Johannes Schmid (TGM) (Jade-Hochschule)
 \*------------------------------------------------------------------*/

#ifndef _CRUNNINGRMS_H_TGM
#define _CRUNNINGRMS_H_TGM
#include <math.h>


class RunningRMS
{
public:
	RunningRMS(void);
	RunningRMS(int SamplingFrequenz, int tau);
	~RunningRMS(void);


	// RMS Berechnung
	void setAlpha(double tau);
	
	inline double analyzeOneSampleRMS(double In)
	{
	  m_statesRMS = (1 - m_alphaRMS)*(In*In) + m_alphaRMS*m_stateRMS;
	  return sqrt(m_statesRMS);
	 };
	void analyseSamplesRMS(double *In, int nSamples);
	
	
private:
	double m_alphaRMS, m_fs, m_stateRMS, RMS[];
	
};

#endif