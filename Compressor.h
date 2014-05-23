#ifndef __COMPRESSOR__
#define __COMPRESSOR__

#include "IPlug_include_in_plug_hdr.h"

class Compressor : public IPlug
{
public:
  Compressor(IPlugInstanceInfo instanceInfo);
  ~Compressor();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
  double mGain;
};


enum EParams
{
  //Gaintable
  kThres,
  kKnee,
  kRatio,
  kMakeup,
  //Peakrider
  kTauRPeak,
  //RunningRMS
  kRMS,
  //Mix_RMS_Peak
  kMix,
  //Smoothing
  kSmoothingTypeRadio,
  kSmoothingAttackKnob,
  kSmoothingReleaseKnob,
  
  kNumParams
};

enum ELayout
{
  //GUI Abmessungen
  kWidth = GUI_WIDTH,
  kHeight = GUI_HEIGHT,
  
  //Gaintable + Labels
  kThresX = 600,
  kThresY = 260,
  kKneeX = 600,
  kKneeY = 330,
  kRatioX = 600,
  kRatioY = 400,
  kMakeupX = 600,
  kMakeupY = 470,
  kGainTableLabelX  = kThresX - 50,
  kGainTableLabelY0 = kThresY + 35,
  kGainTableLabelY1 = kThresY + 105,
  kGainTableLabelY2 = kThresY + 175,
  kGainTableLabelY3 = kThresY + 245,
  kKnob_Gaintable_Frames = 31,
  
  //Peakrider
  KTauRPeakX = 280,
  KTauRPeakY = 200,
  kKnob_PeakRider_Frames = 33,
  
  //Mix_RMS_Peak
  kRMSX = 280,
  kRMSY = 140,
  kMixX = 440,
  kMixY = 180,
  kKnob_RMS_Mix_Frames = 101,
  
	//Smoothing
	kSmoothingTypeRadioButton_W = 24,  // width of bitmap
	kSmoothingTypeRadioButton_H = 24,  // height of one of the bitmap images
	kSmoothingTypeRadio_X = 720, // Position
	kSmoothingTypeRadio_Y = 280,
	kSmoothingTypeRadio_N = 3,  // number of vertical buttons
  
	kSmoothingTypeRadioLabel_X  = kSmoothingTypeRadio_X + 28,
	kSmoothingTypeRadioLabel_Y0 = kSmoothingTypeRadio_Y,
	kSmoothingTypeRadioLabel_Y1 = kSmoothingTypeRadio_Y + 28,
	kSmoothingTypeRadioLabel_Y2 = kSmoothingTypeRadio_Y + 56,
	kSmoothingTypeRadioLabel_W = 50,  // width of label
	kSmoothingTypeRadioLabel_H = 20,   // heigth of label
  
	kSmoothingAttackKnob_X = 720,
	kSmoothingAttackKnob_Y = 360,
	kSmoothingReleaseKnob_X = 720,
	kSmoothingReleaseKnob_Y = 440,
  
	kSmoothingRadio_Frames = 2,
	kSmoothingButton_Frames = 60,
};

#endif
