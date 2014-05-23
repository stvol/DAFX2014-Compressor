/*------------------------------------------------------------------*\
 Interface to a Peak Rider Plugin for mono audio signals.
 public domain
 Author: Matthias Stennes, Stephanus Volke (TGM) (Jade-Hochschule)
 Version 1.0
 \*------------------------------------------------------------------*/

#ifndef _PEAKRIDER_H_TGM_
#define _PEAKRIDER_H_TGM_

#include <math.h>

class CPeakRider
{
public:
	CPeakRider(double tau_r_peak, double fs);
	~CPeakRider(void);
	void reset(void);
	int analyseSamples(double *In, double *Out, int nSamples);
	inline double analyseOneSample(double In)
    {
        double outGain = (In > (m_alpha*m_lastOut))?(In):(m_lastOut);
        m_lastOut = m_alpha*m_lastOut + (1-m_alpha)* outGain;
        double Out = outGain;
        return Out;
    };
    
	int setTauRPeak(double tau_r_peak);
    int setSampleRate(double fs);
    
protected:
	double m_alpha, m_lastOut, m_fs, m_tauRPeak;
    
private:
    int computeAlpha(void);
    
    
};



#endif

