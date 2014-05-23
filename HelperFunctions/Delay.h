/*------------------------------------------------------------------*\
 Interface to a Delay Plugin for mono audio signals with an static
 delay time of 80 samples.
 public domain
 Author: Nils Schreiber, Philip Luedtke , Stephanus Volke (TGM) (Jade-Hochschule)
 Version 1.0 
 Version 1.1 change to pointer concept
 \*------------------------------------------------------------------*/

#ifndef _DELAY_H_TGM_
#define _DELAY_H_TGM_


class CDelay
{
public:
	CDelay(void);
	CDelay(int Delay);
	~CDelay(void);
	void reset(void);
	int processSamples(double *In, double *Out, int nSamples);
	inline double processOneSample(double In)
    {
        double Out = m_buffer[m_Counter];
		m_buffer[m_Counter] = In;
		m_Counter++;
		if (m_Counter == m_SamplesOfDelay)
			m_Counter = 0;
        return Out;
    };
    
protected:
    int m_SamplesOfDelay;
    int m_LastSample;
	double *m_buffer;
	int m_Counter;

};



#endif
