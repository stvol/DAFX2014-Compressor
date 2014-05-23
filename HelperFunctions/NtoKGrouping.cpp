#include "NtoKGrouping.h"

CNtoKGrouping::CNtoKGrouping(void)
{
}
CNtoKGrouping::CNtoKGrouping(int NrOfInChns, int NrOfOutChns)
{
		
}

CNtoKGrouping::~CNtoKGrouping(void)
{

}

int CNtoKGrouping::processSamples (double **In, double **Out, in nSamples)
{


}
void CNtoKGrouping::setNrOfOutChns(int NrOfOuts)
{

}
void CNtoKGrouping::setNrOfInChns(int NrOfOuts)
{


}
void CNtoKGrouping::connect(int InChn, int ToOutChn)
{

}
void setMode(int Mode)
{

}

void CNtoKGrouping::allocateMen(void)
{

}
void deleteeMen(void)
{


}




int m_Mode; // 0 = max, 1 = mean, 2 = MeanAbs 
	int m_NrOfInChns;
	int m_NrOfOutChns;
	int m_NrOfConnectors;
	int *m_NrOfInsPerOut;
	double *m_MeanOut;
	double *m_MaxOut;
	double *m_MaxAbsOut;


