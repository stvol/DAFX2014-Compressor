/*------------------------------------------------------------------*\
 This file is a smoothing Plugin.
 public domain
 Author: Jan Willhaus, Julian Kahnert (TGM) (Jade-Hochschule)
\*------------------------------------------------------------------*/
 
#ifndef _CSMOOTHING_H_TGM_
#define _CSMOOTHING_H_TGM_

class CSmoothing
{
public:
	CSmoothing(void);
    
	~CSmoothing(void);
    
	void reset(void);
    
	int processSamples(double *In, double *Out, int nSamples);
    
	inline double processOneSample(double In) {
        
        switch (smoothingType) {
                
            case 0: /* Logarithmic */
                if (In > curOut*att_rate) {
                    curOut = curOut*att_rate + (1-att_rate)*In;
                    
                } else if (In < curOut*rel_rate) {
                    curOut = curOut*rel_rate + (1-att_rate)*In;
                    
                }
                break;
                
            case 1: /* True Logarithmic */
                if (In > curOut*att_rate) {
                    curOut = curOut*att_rate;
                    
                } else if (In < curOut*rel_rate) {
                    curOut = curOut*rel_rate;
                    
                }
                break;
                
            case 2: /* Linear */
                if (In > curOut+att_rate) {
                    curOut = curOut+att_rate;
                    
                } else if (In < curOut-rel_rate) {
                    curOut = curOut-rel_rate;
                    
                }
                break;
                
            default:
                break;
        }
        
        return curOut;
        
    };
    
    int setSmoothingRates(double tauAttack, double tauRelease);
    
    int setSmoothingType(unsigned int newSmoothingType);


protected:
    unsigned int smoothingType;
    
    double tau_att;
    double tau_rel;
    
    double att_rate;
    double rel_rate;
        
    double curOut;
    double fs;
};

#endif
