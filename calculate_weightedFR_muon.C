#include <vector>
#include <iostream>
#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"


void calculate_weightedFR_muon(){

  double QCD_CrossSection[8] = {8148778.0, 1033680.0, 156293.3, 34138.15, 1759.549, 113.8791, 26.9921, 3.550036};
  double QCD_Events[8] = {3238802, 699016, 818856, 5630869, 265485, 2017630, 1788376, 6882230};
  double QCD_FakeRate_Muons[8] = {0.316, 0.191, 0.243, 0.263, 0.375, 0.179, 0.235, 0.222};
  double QCD_LooseMuons[8] = {174, 94, 123, 684, 24, 195, 153, 553};
  //double QCD_LooseElectrons[8] = {374, 179, 257, 1276, 42, 264, 246, 733};
  double QCD_FakeRate_Muons_b[8] = {0.307, 0.176, 0.266, 0.265, 0.222, 0.155, 0.222, 0.206};
  double QCD_LooseMuons_b[8] = {156, 85, 109, 588, 18, 148, 117, 408};
  double Numerator = 0.0;
  double Denominator = 0.0;
  double weighted_fake_rate = 0.0;
  double weighted_fake_rate_b = 0.0;
  double Numerator_b = 0.0;
  double Denominator_b = 0.0;
  double QCD_FakeRate_Muons_c[8] = {0.389, 0.333, 0.071, 0.244, 0.83, 0.261, 0.272, 0.249}; 
  double QCD_LooseMuons_c[8] = {18, 9, 14, 94, 6, 46, 33, 141};
  double weighted_fake_rate_c = 0.0;
  double Numerator_c = 0.0;
  double Denominator_c = 0.0;
  double QCD_FakeRate_Muons_l[8] = {0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.333, 1.0};
  double QCD_LooseMuons_l[8] = {0.0, 0.0, 0.0, 2, 0.0, 1.0, 3.0, 4.0};
  double weighted_fake_rate_l = 0.0;
  double Numerator_l = 0.0;
  double Denominator_l = 0.0;

  
  for (int i=0; i<8; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseMuons[i])/QCD_Events[i]);
    Numerator += QCD_FakeRate_Muons[i]*vis_X_sec;
    Denominator += vis_X_sec;
    }
    weighted_fake_rate = Numerator/Denominator;


    cout << "weighted_fake_rate = " <<  weighted_fake_rate << endl;



  for (int i=0; i<8; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseMuons_b[i])/QCD_Events[i]);
    Numerator_b += QCD_FakeRate_Muons_b[i]*vis_X_sec;
    Denominator_b += vis_X_sec;
    }
    weighted_fake_rate_b = Numerator_b/Denominator_b;


    cout << "weighted_fake_rate_b = " <<  weighted_fake_rate_b << endl;

  for (int i=0; i<8; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseMuons_c[i])/QCD_Events[i]);
    Numerator_c += QCD_FakeRate_Muons_c[i]*vis_X_sec;
    Denominator_c += vis_X_sec;
    }
    weighted_fake_rate_c = Numerator_c/Denominator_c;


   cout << "weighted_fake_rate_c = " <<  weighted_fake_rate_c << endl;


  for (int i=0; i<8; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseMuons_l[i])/QCD_Events[i]);
    Numerator_l += QCD_FakeRate_Muons_l[i]*vis_X_sec;
    Denominator_l += vis_X_sec;
    }
    weighted_fake_rate_l = Numerator_l/Denominator_l;


    cout << "weighted_fake_rate_l = " <<  weighted_fake_rate_l << endl;


}
