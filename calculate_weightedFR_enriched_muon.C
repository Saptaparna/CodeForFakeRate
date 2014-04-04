#include <vector>
#include <iostream>
#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"


void calculate_weightedFR_enriched_muon(){

  double QCD_CrossSection[9] = {66090000, 8082000.0, 1024000.0, 157800.0, 34020.0, 1757.0, 115.2, 27.01, 3.57};
  double QCD_Events[9] = {2044814, 4470648, 5712650, 6627827, 1180379, 4174174, 2036405, 2441874, 2447270};
  double QCD_FakeRate_Muons_b[9] = {0.311, 0.266, 0.259, 0.252, 0.251, 0.216, 0.205, 0.223, 0.218};
  double QCD_LooseMuons_b[9] = {859, 9030, 16130, 15438, 1964, 4327, 1632, 1649, 1457};
  double weighted_fake_rate_b = 0.0;
  double Numerator_b = 0.0;
  double Denominator_b = 0.0;
  double QCD_FakeRate_Muons_c[9] = {0.297, 0.286, 0.284, 0.297, 0.276, 0.256, 0.261, 0.258, 0.269};
  double QCD_LooseMuons_c[9] = {101, 1342, 2428, 2364, 395, 1095, 452, 485, 452};
  double weighted_fake_rate_c = 0.0;
  double Numerator_c = 0.0;
  double Denominator_c = 0.0;
  double QCD_FakeRate_Muons_l[9] = {0.456, 0.359, 0.324, 0.299, 0.288, 0.295, 0.379, 0.273, 0.307};
  double QCD_LooseMuons_l[9] = {171, 727, 759, 617, 90, 261, 108, 139, 117};
  double weighted_fake_rate_l = 0.0;
  double Numerator_l = 0.0;
  double Denominator_l = 0.0;
  double QCD_FakeRate_Muons_average[9] = {0.332, 0.275, 0.265, 0.259, 0.256, 0.227, 0.225, 0.234, 0.235};
  double QCD_LooseMuons_average[9] = {1131, 11099, 19317, 18419, 2449, 5683, 2192, 2273, 2026};
  double weighted_fake_rate_average = 0.0;
  double Numerator_average = 0.0;
  double Denominator_average = 0.0;



  for (int i=0; i<9; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseMuons_b[i])/QCD_Events[i]);
    Numerator_b += QCD_FakeRate_Muons_b[i]*vis_X_sec;
    Denominator_b += vis_X_sec;
    } 
    weighted_fake_rate_b = Numerator_b/Denominator_b;
      


   cout << "weighted_fake_rate_b = " <<  weighted_fake_rate_b << endl;
    
  for (int i=0; i<9; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseMuons_c[i])/QCD_Events[i]);
    Numerator_c += QCD_FakeRate_Muons_c[i]*vis_X_sec;
    Denominator_c += vis_X_sec;
    }
    weighted_fake_rate_c = Numerator_c/Denominator_c;



   cout << "weighted_fake_rate_c = " <<  weighted_fake_rate_c << endl;


  for (int i=0; i<9; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseMuons_l[i])/QCD_Events[i]);
    Numerator_l += QCD_FakeRate_Muons_l[i]*vis_X_sec;
    Denominator_l += vis_X_sec;
    }
    weighted_fake_rate_l = Numerator_l/Denominator_l;



   cout << "weighted_fake_rate_l = " <<  weighted_fake_rate_l << endl;

  for (int i=0; i<9; i++){
    double vis_X_sec = ((QCD_CrossSection[i]*QCD_LooseMuons_average[i])/QCD_Events[i]);
    Numerator_average += QCD_FakeRate_Muons_average[i]*vis_X_sec;
    Denominator_average += vis_X_sec;
    }
    weighted_fake_rate_average = Numerator_average/Denominator_average;



   cout << "weighted_fake_rate_average = " <<  weighted_fake_rate_average << endl;

 


}   
 
