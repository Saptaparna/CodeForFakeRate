#include <vector>
#include <iostream>
#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"


void calculate_weightedFR_BCtoE_electron(){

 double QCD_CrossSection[4] = {74200000.0, 1191000.0, 30980.0, 4240.0};
 double QCD_Events[4] = {1531497, 2363149, 1736895, 3949658};
 double QCD_FakeRate_Electrons_b[4] = {0.137, 0.077, 0.069, 0.075};
 double QCD_LooseElectrons_b[4] = {7417, 29749, 10180, 13978};
 double weighted_fake_rate_b = 0.0;
 double Numerator_b = 0.0;
 double Denominator_b = 0.0;
 double QCD_FakeRate_Electrons_c[4] = {0.256, 0.142, 0.137, 0.140};
 double QCD_LooseElectrons_c[4] = {2457, 8004, 2931, 4248};
 double weighted_fake_rate_c = 0.0;
 double Numerator_c = 0.0;
 double Denominator_c = 0.0;
 double QCD_FakeRate_Electrons_l[4] = {0.384, 0.218, 0.132, 0.097};
 double QCD_LooseElectrons_l[4] = {13, 87, 113, 256};
 double weighted_fake_rate_l = 0.0;
 double Numerator_l = 0.0;
 double Denominator_l = 0.0;
 double QCD_FakeRate_Electrons_average[4] = {0.167, 0.0912, 0.085, 0.090};
 double QCD_LooseElectrons_average[4] = {9887, 37840, 13224, 18482};
 double weighted_fake_rate_average = 0.0;
 double Numerator_average = 0.0;
 double Denominator_average = 0.0;


 for (int i=0; i<4; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseElectrons_b[i])/QCD_Events[i]);
    Numerator_b += QCD_FakeRate_Electrons_b[i]*vis_X_sec;
    Denominator_b += vis_X_sec;
    }
    weighted_fake_rate_b = Numerator_b/Denominator_b;



   cout << "weighted_fake_rate_b = " <<  weighted_fake_rate_b << endl;

  for (int i=0; i<4; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseElectrons_c[i])/QCD_Events[i]);
    Numerator_c += QCD_FakeRate_Electrons_c[i]*vis_X_sec;
    Denominator_c += vis_X_sec;
    }
    weighted_fake_rate_c = Numerator_c/Denominator_c;



   cout << "weighted_fake_rate_c = " <<  weighted_fake_rate_c << endl;


  for (int i=0; i<4; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseElectrons_l[i])/QCD_Events[i]);
    Numerator_l += QCD_FakeRate_Electrons_l[i]*vis_X_sec;
    Denominator_l += vis_X_sec;
    }
    weighted_fake_rate_l = Numerator_l/Denominator_l;



   cout << "weighted_fake_rate_l = " <<  weighted_fake_rate_l << endl;

  for (int i=0; i<4; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseElectrons_average[i])/QCD_Events[i]);
    Numerator_average += QCD_FakeRate_Electrons_average[i]*vis_X_sec;
    Denominator_average += vis_X_sec;
    }
    weighted_fake_rate_average = Numerator_average/Denominator_average;



   cout << "weighted_fake_rate_average = " <<  weighted_fake_rate_average << endl;





}
