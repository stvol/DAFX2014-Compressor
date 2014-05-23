#include "Compressor.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"

const int kNumPrograms = 1;

Compressor::Compressor(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo), mGain(1.)
{
  TRACE;
  
  // Parameter and GUI
  //arguments are: name, defaultVal, minVal, maxVal, step, label
  
  /* IControl Startwerte*\
   \* initialisieren     */
  
  //Gaintable Anfang
  GetParam(kThres)->InitDouble("Threshold", 0., -30., 0., 0.25, "dB");
  GetParam(kThres)->SetShape(1.);
  
  GetParam(kKnee)->InitDouble("Knee", 0., -20., 0., 0.25, "dB");
  GetParam(kKnee)->SetShape(1.);
  
  GetParam(kRatio)->InitDouble("Ratio", 0., 1., 10., 0.25, "Linear");
  GetParam(kRatio)->SetShape(1.);
  
  GetParam(kMakeup)->InitDouble("Makeup", 0., 0., 30., 0.25, "dB");
  GetParam(kMakeup)->SetShape(1.);
  // Gaintable Ende
  
  //Peakrider Anfang
  GetParam(kTauRPeak)-> InitDouble("TauRPeak",125., 0., 1000., 10.,"ms");
  GetParam(kTauRPeak)->SetShape(.2);
  //Peakrider Ende
  
  //RMS_Mix Anfang
  GetParam(kRMS)-> InitDouble("RMS_tau",125., 0., 1000., 10.,"ms");
  GetParam(kRMS)->SetShape(.2);
  
  GetParam(kMix)-> InitDouble("RMS_Mix_Peak",.5, 0., 1., 0.01,"");
  GetParam(kMix)->SetShape(.2);
  //RMS_Mix Ende
  
  //Smoothing Anfang
  GetParam(kSmoothingTypeRadio)->InitInt("IRadioButtonsControl Vert", 1, 1, 3, "button");
  GetParam(kSmoothingAttackKnob)->InitDouble("Attack", 10., 0., 500., 1.);
  GetParam(kSmoothingReleaseKnob)->InitDouble("Release", 100., 0., 500., 1.);
  //Smoothing Ende
  
  /* IControl GUI-Elelmente*\
   \* erzeugen              */
  
  // Hintergrundgrafik
  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
  pGraphics->AttachBackground(BG_ID, BG_FN);
  
  //Gaintable Knob
  IBitmap GainTableknob = pGraphics->LoadIBitmap(KNOB_GAINTABLE_ID, KNOB_GAINTABLE_FN,
                                                 kKnob_Gaintable_Frames);
  
  // Peakrider Knob
  IBitmap PeakRiderKnob = pGraphics->LoadIBitmap(KNOB_PEAKRIDER_ID, KNOB_PEAKRIDER_FN,
                                                 kKnob_PeakRider_Frames);
  
  // RMS und Mix Knob
  IBitmap RMS_Mix_Knob = pGraphics->LoadIBitmap(KNOB_RMS_MIX_ID, KNOB_RMS_MIX_FN,
                                                kKnob_RMS_Mix_Frames);
  
  // Smoothing Radiobutton und Knob
  IBitmap smoothingRadio = pGraphics->LoadIBitmap(RADIO_SMOOTHING_ID, RADIO_SMOOTHING_FN, kSmoothingRadio_Frames);
  IBitmap smoothingKnob  = pGraphics->LoadIBitmap(KNOB_SMOOTHING_ID, KNOB_SMOOTHING_FN, kSmoothingButton_Frames);
  
  // Labels (Textfelder)
  IText text(12, &COLOR_BLACK, "Verdana", IText::kStyleNormal, IText::kAlignNear, 0, IText::kQualityNonAntiAliased);
  
  /* IControl GUI-Elelmente*\
   \* platzieren            */
  
  //Gaintable Knobs Platzierung in GUI
  pGraphics->AttachControl(new IKnobMultiControl(this, kThresX, kThresY, kThres, &GainTableknob));
  pGraphics->AttachControl(new IKnobMultiControl(this, kKneeX, kKneeY, kKnee, &GainTableknob));
  pGraphics->AttachControl(new IKnobMultiControl(this, kRatioX, kRatioY, kRatio, &GainTableknob));
  pGraphics->AttachControl(new IKnobMultiControl(this, kMakeupX, kMakeupY, kMakeup, &GainTableknob));
  
  //Peakrider Knob
  pGraphics->AttachControl(new IKnobMultiControl(this, KTauRPeakX,
                                                 KTauRPeakY, kRMS, &PeakRiderKnob));
  
  //RMS und Mix
  pGraphics->AttachControl(new IKnobMultiControl(this, kRMSX,
                                                 kRMSY, kRMS, &RMS_Mix_Knob));
  
  pGraphics->AttachControl(new IKnobMultiControl(this, kMixX,
                                                 kMixY, kMix, &RMS_Mix_Knob));
  
  //Smoothing Radiobutton
  pGraphics->AttachControl(new IRadioButtonsControl(this, IRECT(
                                                                kSmoothingTypeRadio_X,
                                                                kSmoothingTypeRadio_Y,
                                                                kSmoothingTypeRadio_X + (kSmoothingTypeRadioButton_W*kSmoothingTypeRadio_N),
                                                                kSmoothingTypeRadio_Y + (kSmoothingTypeRadioButton_H*kSmoothingTypeRadio_N)),
                                                    kSmoothingTypeRadio, kSmoothingTypeRadio_N, &smoothingRadio));
  
  //Knob für Attackzeit
  pGraphics->AttachControl(new IKnobMultiControl(this,
                                                 kSmoothingAttackKnob_X,
                                                 kSmoothingAttackKnob_Y,
                                                 kSmoothingAttackKnob,
                                                 &smoothingKnob));
  
  //Knob für Releasezeit
  pGraphics->AttachControl(new IKnobMultiControl(this,
                                                 kSmoothingReleaseKnob_X,
                                                 kSmoothingReleaseKnob_Y,
                                                 kSmoothingReleaseKnob,
                                                 &smoothingKnob));
  
	//Label Gaintable Thres
  pGraphics->AttachControl(new ITextControl(this, IRECT(
                                                        kGainTableLabelX,
                                                        kGainTableLabelY0,
                                                        (kGainTableLabelX  + kSmoothingTypeRadioLabel_W),
                                                        (kGainTableLabelY0 + kSmoothingTypeRadioLabel_H)),
                                            &text, "Thres"));
  
	//Label Gaintable Knee
  pGraphics->AttachControl(new ITextControl(this, IRECT(
                                                        kGainTableLabelX,
                                                        kGainTableLabelY1,
                                                        (kGainTableLabelX + kSmoothingTypeRadioLabel_W),
                                                        (kGainTableLabelY1 + kSmoothingTypeRadioLabel_H)),
                                            &text, "Knee"));
  
  //Label Gaintable Ratio
  pGraphics->AttachControl(new ITextControl(this, IRECT(
                                                        kGainTableLabelX, 
                                                        kGainTableLabelY2, 
                                                        (kGainTableLabelX + kSmoothingTypeRadioLabel_W), 
                                                        (kGainTableLabelY2 + kSmoothingTypeRadioLabel_H)), 
                                            &text, "Ratio"));
  
  //Label Gaintable Makeup
  pGraphics->AttachControl(new ITextControl(this, IRECT(
                                                        kGainTableLabelX, 
                                                        kGainTableLabelY3, 
                                                        (kGainTableLabelX + kSmoothingTypeRadioLabel_W), 
                                                        (kGainTableLabelY3 + kSmoothingTypeRadioLabel_H)), 
                                            &text, "Makeup"));
  
  //Label Smoothing Radiobutton Log
  pGraphics->AttachControl(new ITextControl(this, IRECT(
                                                        kSmoothingTypeRadioLabel_X, 
                                                        kSmoothingTypeRadioLabel_Y0, 
                                                        (kSmoothingTypeRadioLabel_X  + kSmoothingTypeRadioLabel_W), 
                                                        (kSmoothingTypeRadioLabel_Y0 + kSmoothingTypeRadioLabel_H)), 
                                            &text, "Log"));
  
  //Label Smoothing Radiobutton True Log
  pGraphics->AttachControl(new ITextControl(this, IRECT(
                                                        kSmoothingTypeRadioLabel_X, 
                                                        kSmoothingTypeRadioLabel_Y1, 
                                                        (kSmoothingTypeRadioLabel_X + kSmoothingTypeRadioLabel_W), 
                                                        (kSmoothingTypeRadioLabel_Y1 + kSmoothingTypeRadioLabel_H)), 
                                            &text, "True Log"));
  
  //Label Smoothing Radiobutton Linear
  pGraphics->AttachControl(new ITextControl(this, IRECT(
                                                        kSmoothingTypeRadioLabel_X, 
                                                        kSmoothingTypeRadioLabel_Y2, 
                                                        (kSmoothingTypeRadioLabel_X + kSmoothingTypeRadioLabel_W), 
                                                        (kSmoothingTypeRadioLabel_Y2 + kSmoothingTypeRadioLabel_H)), 
                                            &text, "Linear"));
  
  
  
  
  
  
  AttachGraphics(pGraphics);
  

  //MakePreset("preset 1", ... );
  MakeDefaultPreset((char *) "-", kNumPrograms);
}

Compressor::~Compressor() {}

void Compressor::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
  // Mutex is already locked for us.

  double* in1 = inputs[0];
  double* in2 = inputs[1];
  double* out1 = outputs[0];
  double* out2 = outputs[1];

  for (int s = 0; s < nFrames; ++s, ++in1, ++in2, ++out1, ++out2)
  {
    *out1 = *in1 * mGain;
    *out2 = *in2 * mGain;
  }
}

void Compressor::Reset()
{
  TRACE;
  IMutexLock lock(this);
}

void Compressor::OnParamChange(int paramIdx)
{
  IMutexLock lock(this);

  switch (paramIdx)
  {
//    case kGain:
//      mGain = GetParam(kGain)->Value() / 100.;
      break;

    default:
      break;
  }
}
