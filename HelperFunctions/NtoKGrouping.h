/*------------------------------------------------------------------*\
 Interface to a N to K gruping class
 public domain
 Author: Joerg Bitzer (TGM) (Jade-Hochschule)
 \*------------------------------------------------------------------*/

#ifndef _TGM_NTOK_GROUPING_H
#define _TGM_NTOK_GROUPING_H

class CNtoKGrouping
{
public:
	CNtoKGrouping(void);
	CNtoKGrouping(int NrOfInChns, int NrOfOutChns);
	~CNtoKGrouping(void);
	int processSamples (double **In, double **Out, in nSamples);
	void setNrOfOutChns(int NrOfOuts);
	void setNrOfInChns(int NrOfOuts);
	void connect(int InChn, int ToOutChn);
	void setMode(int Mode);

private:
	void allocateMen(void);
	void deleteeMen(void);
	int m_Mode; // 0 = max, 1 = mean, 2 = MeanAbs 
	int m_NrOfInChns;
	int m_NrOfOutChns;
	int m_NrOfConnectors;
	int *m_NrOfInsPerOut;
	double *m_MeanOut;
	double *m_MaxOut;
	double *m_MaxAbsOut;
};

#endif

