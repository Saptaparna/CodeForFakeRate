#include <vector>
#include <iostream>
#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"


void calculate_weightedFR_electron(){

  double QCD_CrossSection[8] = {8148778.0, 1033680.0, 156293.3, 34138.15, 1759.549, 113.8791, 26.9921, 3.550036};
  double QCD_Events[8] = {3238802, 699016, 818856, 5630869, 265485, 2017630, 1788376, 6882230};
  double QCD_FakeRate_Electrons[8] = {0.157, 0.156, 0.105, 0.112, 0.142, 0.132, 0.121, 0.126};
  double QCD_LooseElectrons[8] = {374, 179, 257, 1276, 42, 264, 246, 733}; 
  double QCD_FakeRate_Electrons_b[8] = {0.141, 0.125, 0.094, 0.079, 0.105, 0.111, 0.063, 0.097};
  double QCD_LooseElectrons_b[8] = {199, 112, 138, 633, 19, 108, 95, 351};
  double weighted_fake_rate = 0.0;
  double Numerator = 0.0;
  double Denominator = 0.0;
  double weighted_fake_rate_b = 0.0;
  double Numerator_b = 0.0;
  double Denominator_b = 0.0;
  double QCD_FakeRate_Electrons_c[8] = {0.224, 0.240, 0.189, 0.139, 0.200, 0.258, 0.139, 0.128}; 
  double QCD_LooseElectrons_c[8] = {58, 25, 37, 194, 5, 31, 36, 78};
  double weighted_fake_rate_c = 0.0;
  double Numerator_c = 0.0;
  double Denominator_c = 0.0;
  double QCD_FakeRate_Electrons_l[8] = {0.154, 0.191, 0.085, 0.147, 0.167, 0.120, 0.165, 0.157};
  double QCD_LooseElectrons_l[8] = {117.0, 42.0, 82.0, 449, 18.0, 125.0, 115.0, 304};
  double weighted_fake_rate_l = 0.0;
  double Numerator_l = 0.0;
  double Denominator_l = 0.0;
  double QCD_FakeRate_Electrons_unmatched[8] = {0.230, 0.188, 0.222, 0.204, 0.211, 0.271, 0.281, 0.311};
  double QCD_LooseElectrons_unmatched[8] = {1741, 639, 951, 6393, 251, 1803, 1331, 4158};
  double weighted_fake_rate_unmatched = 0.0;
  double Numerator_unmatched = 0.0;
  double Denominator_unmatched = 0.0;


  for (int i=0; i<8; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseElectrons[i])/QCD_Events[i]);
    Numerator += QCD_FakeRate_Electrons[i]*vis_X_sec;
    Denominator += vis_X_sec;
    }
    weighted_fake_rate = Numerator/Denominator;


    cout << "weighted_fake_rate = " <<  weighted_fake_rate << endl;




  for (int i=0; i<8; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseElectrons_b[i])/QCD_Events[i]);
    Numerator_b += QCD_FakeRate_Electrons_b[i]*vis_X_sec;
    Denominator_b += vis_X_sec;
    }
    weighted_fake_rate_b = Numerator_b/Denominator_b;


    cout << "weighted_fake_rate_b = " <<  weighted_fake_rate_b << endl;

  for (int i=0; i<8; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseElectrons_c[i])/QCD_Events[i]);
    Numerator_c += QCD_FakeRate_Electrons_c[i]*vis_X_sec;
    Denominator_c += vis_X_sec;
    }
    weighted_fake_rate_c = Numerator_c/Denominator_c;


   cout << "weighted_fake_rate_c = " <<  weighted_fake_rate_c << endl;


  for (int i=0; i<8; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseElectrons_l[i])/QCD_Events[i]);
    Numerator_l += QCD_FakeRate_Electrons_l[i]*vis_X_sec;
    Denominator_l += vis_X_sec;
    }
    weighted_fake_rate_l = Numerator_l/Denominator_l;


    cout << "weighted_fake_rate_l = " <<  weighted_fake_rate_l << endl;

  for (int i=0; i<8; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseElectrons_unmatched[i])/QCD_Events[i]);
    Numerator_unmatched += QCD_FakeRate_Electrons_unmatched[i]*vis_X_sec;
    Denominator_unmatched += vis_X_sec;
    }
    weighted_fake_rate_unmatched = Numerator_unmatched/Denominator_unmatched;


    cout << "weighted_fake_rate_unmatched = " <<  weighted_fake_rate_unmatched << endl;


}
