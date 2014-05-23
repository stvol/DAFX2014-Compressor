/*------------------------------------------------------------------*\
 This file is a Peak Rider Plugin for mono audio signals.
 public domain
 Author: Matthias Stennes, Stephanus Volke (TGM) (Jade-Hochschule)
 Version 1.0
 \*------------------------------------------------------------------*/

#include "PeakRider.h"

CPeakRider::CPeakRider(double tau_r_peak, double fs)
{
    reset();
    setSampleRate(fs);
    setTauRPeak(tau_r_peak);
    computeAlpha();
}

CPeakRider::~CPeakRider(void)
{}

void CPeakRider::reset(void)
{
    m_lastOut = 0.;
}


int CPeakRider::analyseSamples(double *In, double *Out, int nSamples)
{
    int kk;
	for (kk = 0; kk < nSamples; kk++)
	{
        *Out = analyseOneSample(*In);
        Out++;
        In++;
	}
    return 0;
}

    
int CPeakRider::setTauRPeak(double tau_r_peak)
{
    m_tauRPeak = tau_r_peak;
    computeAlpha();
    return 0;
}

int CPeakRider::setSampleRate(double fs)
{
    m_fs = fs;
    computeAlpha();
    return 0;
}

int CPeakRider::computeAlpha()
{
    m_alpha = exp(-1/(m_tauRPeak*0.001*m_fs));
    return 0;
}