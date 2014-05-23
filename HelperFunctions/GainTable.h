/*------------------------------------------------------------------*\
Interface to the Compress Class
public domain
Author: Hagen Jaeger, Sven Kliesch (TGM) (Jade-Hochschule)  
Version 1.0 HJ, SK
\*------------------------------------------------------------------*/
#ifndef _C_COMPRESS_H_TGM // include guard
#define _C_COMPRESS_H_TGM

#include <math.h>

class CGainTable
{
public:
	CGainTable(void);
	CGainTable(double Thres, double Ratio, double Makeup, double KneeWidth);


	~CGainTable(void);

	inline double processOneSample(double In)
	{
		double In_log = 20*log10(In);
        double Out_log;
        
		if (2*(In - m_Thres_log) < -(m_Knee_log)) //Wenn man unter dem Treshold und Knieeinfluss ist...
		{//keine Aenderung der Verstaerkung (Ratio 1:1)
			 Out_log = In_log;
		}

        else if (2*fabs(In_log - m_Thres_log) <= m_Knee_log) //Wenn man im Knieeinfluss ist...
		{//parabelfoermiger absinkender Verlauf (eben 'knie'foermig) bis Knieende
            Out_log = In_log + ( (1/m_Ratio) -1) 
                    * pow( (In_log - m_Thres_log + m_Knee_log/2) , 2) 
					/ (2*(m_Knee_log));
		}

        else if (2*(In_log - m_Thres_log) > m_Knee_log) //wenn man ueber dem Treshold und Knieeinfluss ist...
		{//Verstaerkungsaenderung mit Ratio (wenn Ratio 2:1, dann Steigung nur noch 0.5 statt 1
            Out_log = m_Thres_log + (In_log-m_Thres_log) * (1/m_Ratio);
		}

		Out_log += m_Makeup_log;
		return Out_log;

	};

	int processSamples(double *In, double *Out, int nSamples);

	void setThres(double Thres_log); 

	void setKnee(double Knee_log); 

	void setRatio(double Ratio); 
	void setMakeup(double Makeup_log); 

private:
	double m_Thres_log, m_Knee_log, m_Ratio, m_Makeup_log;
};

#endif // end of include guard
