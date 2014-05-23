/*------------------------------------------------------------------*\
 Implmentation of a Dynamic Compressor.
 public domain
 Author: Hagen Jaeger, Sven Kliesch (TGM) (Jade-Hochschule)
 \*------------------------------------------------------------------*/

#include <math.h>
#include "GainTable.h"

CGainTable::CGainTable(void)
{
    m_Thres_log= 0.;
    m_Knee_log = 0.;
    m_Ratio  = 1.;
    m_Makeup_log = 0.;
}

CGainTable::CGainTable(double Thres, double Ratio, double Makeup, double KneeWidth)
{
    m_Thres_log= Thres;
    m_Knee_log = KneeWidth;
    m_Ratio  =Ratio;
    m_Makeup_log =Makeup;
}

int CGainTable::processSamples(double *In, double *Out, int nSamples)
{
	int kk;
	for (kk = 0; kk < nSamples; kk++)
	{
		// Filterung
        double InSample = *In;
        In++;
        
        *Out = processOneSample(InSample);
        Out++;
	}
	return 0;
    
}

void CGainTable::setThres(double Thres_log)
{
	m_Thres_log = Thres_log;
}

void CGainTable::setKnee(double Knee_log)
{
	m_Knee_log = Knee_log;
}

void CGainTable::setRatio(double Ratio)
{
	m_Ratio = Ratio;
}

void CGainTable::setMakeup(double Makeup_log)
{
	m_Makeup_log = Makeup_log;
}


CGainTable::~CGainTable(void)
{
}