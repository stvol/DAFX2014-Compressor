#ifndef _TGM_NTOK_GROUPING_H
#define _TGM_NTOK_GROUPING_H

class NtoKGrouping
{
public:
	NtoKGrouping(void);
	NtoKGrouping(int NrOfInChns, int NrOfOutChns);
	~NtoKGrouping(void);
	int processSamples (double **In, double **Out, in nSamples);
	void setNrOfOutChns(int NrOfOuts);
	void setNrOfInChns(int NrOfOuts);
	void connect(int InChn, int ToOutChn);
	void setMode(int Mode);

private:
	int m_Mode; // 0 = max, 1 = mean, 2 = MeanAbs 
	int m_NrOfInChns;
	int m_NrOfOutChns;
	int *

};

#endif

