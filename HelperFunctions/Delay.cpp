/*------------------------------------------------------------------*\
 This file is a Delay Plugin for mono audio signals with an static
 delay time of 80 samples.
 public domain
 Author:  Nils Schreiber, Philip Luedtke , Stephanus Volke (TGM) (Jade-Hochschule)
 \*------------------------------------------------------------------*/

#include "Delay.h"

CDelay::CDelay()
{
    reset();
}

CDelay::~CDelay(void)
{}

void CDelay::reset(void)
{
    int ii;
    for (ii = 0; ii<m_SamplesOfDelay; ii++)
    {
        m_buffer[ii] = 0;
    }
}


int CDelay::processSamples(double *In, double *Out, int nSamples)
{
    int kk;
	for (kk = 0; kk < nSamples; kk++)
	{
        *Out = processOneSample(*In);
        Out++;
        In++;
	}
    return 0;
}
