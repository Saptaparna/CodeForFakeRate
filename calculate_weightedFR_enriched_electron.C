#include <vector>
#include <iostream>
#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"


void calculate_weightedFR_enriched_electron(){

 double QCD_CrossSection[5] = {74300000, 1191000.0, 30990.0, 4250.0, 810.0};
 double QCD_Events[5] = {2760959, 2905343, 4988263, 4826680, 3605443};
 double QCD_FakeRate_Electrons_b[5] = {0.444, 0.25, 0.108, 0.117, 0.1};
 double QCD_LooseElectrons_b[5] = {9, 12, 37, 17, 10};
 double weighted_fake_rate_b = 0.0;
 double Numerator_b = 0.0;
 double Denominator_b = 0.0;
 double QCD_CrossSection_c[4] = {1191000.0, 30990.0, 4250.0, 810.0};
 double QCD_FakeRate_Electrons_c[4] = {0.296, 0.237, 0.205, 0.2};
 double QCD_LooseElectrons_c[4] = {27, 39, 39, 20};
 double weighted_fake_rate_c = 0.0;
 double Numerator_c = 0.0;
 double Denominator_c = 0.0;
 double QCD_FakeRate_Electrons_l[5] = {0.295, 0.232, 0.228, 0.241, 0.259};
 double QCD_LooseElectrons_l[5] = {274, 607, 966, 834, 583};
 double weighted_fake_rate_l = 0.0;
 double Numerator_l = 0.0;
 double Denominator_l = 0.0;



 for (int i=0; i<5; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseElectrons_b[i])/QCD_Events[i]);
    Numerator_b += QCD_FakeRate_Electrons_b[i]*vis_X_sec;
    Denominator_b += vis_X_sec;
    }
    weighted_fake_rate_b = Numerator_b/Denominator_b;



   cout << "weighted_fake_rate_b = " <<  weighted_fake_rate_b << endl;

  for (int i=0; i<4; i++){
    double vis_X_sec = ((QCD_CrossSection_c[i]*QCD_LooseElectrons_c[i])/QCD_Events[i]);
    Numerator_c += QCD_FakeRate_Electrons_c[i]*vis_X_sec;
    Denominator_c += vis_X_sec;
    }
    weighted_fake_rate_c = Numerator_c/Denominator_c;



   cout << "weighted_fake_rate_c = " <<  weighted_fake_rate_c << endl;


  for (int i=0; i<5; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseElectrons_l[i])/QCD_Events[i]);
    Numerator_l += QCD_FakeRate_Electrons_l[i]*vis_X_sec;
    Denominator_l += vis_X_sec;
    }
    weighted_fake_rate_l = Numerator_l/Denominator_l;



   cout << "weighted_fake_rate_l = " <<  weighted_fake_rate_l << endl;






}
