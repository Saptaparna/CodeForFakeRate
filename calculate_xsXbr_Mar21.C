#include <vector>
#include <iostream>
#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"
#include "TGraphErrors.h"
#include "TCanvas.h"

void calculate_xsXbr_Mar21(){

gROOT->SetStyle("Plain");

TCanvas* c1 = new TCanvas("c1", "c1", 600, 400);

double mass_point[12] = {400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500};
double production_crossection[12]={2.29628, 0.570253, 0.169633, 0.0569446, 0.0207939, 0.00806877, 0.00327093, 0.00136811, 0.000584949, 0.00025337, 0.000110438, 0.0000481274};
double crossection_error[12] = {0.000268799, 6.4313e-05, 1.88079e-05, 6.1872e-06, 2.23075e-06, 8.61428e-07, 3.54482e-07, 1.48054e-07, 6.51815e-08, 2.78846e-08, 1.21757e-08, 5.3551e-09};
double nominal_branching_ratio_bW[12] = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
double nominal_branching_ratio_tZ[12] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25};
double nominal_branching_ratio_tH[12] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25};
double Hbb_br[12] = {0.569, 0.569, 0.569, 0.569, 0.569, 0.569, 0.569, 0.569, 0.569, 0.569, 0.569, 0.569};
double HWW_br[12] = {0.215, 0.215, 0.215, 0.215, 0.215, 0.215, 0.215, 0.215, 0.215, 0.215, 0.215, 0.215};
double infb[12] = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};
double Hbb_br[12] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
double HWW_br[12] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};


double cross_xs_BWBW[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double cross_xs_BWTH[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double cross_xs_BWTZ[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double cross_xs_TZTZ[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double cross_xs_THTH[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double cross_xs_THTZ[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

double cross_xs_error_BWBW[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double cross_xs_error_BWTH[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double cross_xs_error_BWTZ[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double cross_xs_error_TZTZ[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double cross_xs_error_THTH[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double cross_xs_error_THTZ[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};



for (int i=0; i<12; i++){
  cross_xs_BWBW[i] = production_crossection[i]*nominal_branching_ratio_bW[i]*nominal_branching_ratio_bW[i]*infb[i];

  cross_xs_error_BWBW[i] =  crossection_error[i]*nominal_branching_ratio_bW[i]*nominal_branching_ratio_bW[i]*infb[i];

  cross_xs_TZTZ[i] = production_crossection[i]*nominal_branching_ratio_tZ[i]*nominal_branching_ratio_tZ[i]*infb[i];

  cross_xs_error_TZTZ[i] =  crossection_error[i]*nominal_branching_ratio_tZ[i]*nominal_branching_ratio_tZ[i]*infb[i];

  cross_xs_BWTZ[i] = production_crossection[i]*nominal_branching_ratio_bW[i]*nominal_branching_ratio_tZ[i]*2*infb[i];

  cross_xs_error_BWTZ[i] = crossection_error[i]*nominal_branching_ratio_bW[i]*nominal_branching_ratio_tZ[i]*2*infb[i];

//  cross_xs_BWTH[i] = production_crossection[i]*nominal_branching_ratio_bW[i]*nominal_branching_ratio_tH[i]*2*Hbb_br[i]*infb[i] + production_crossection[i]*nominal_branching_ratio_bW[i]*nominal_branching_ratio_tH[i]*2*HWW_br[i]*infb[i];

   cross_xs_BWTH[i] = production_crossection[i]*nominal_branching_ratio_bW[i]*nominal_branching_ratio_tH[i]*2*infb[i];
 
  //cross_xs_error_BWTH[i] = crossection_error[i]*nominal_branching_ratio_bW[i]*nominal_branching_ratio_tH[i]*2*Hbb_br[i]*infb[i] + crossection_error[i]*nominal_branching_ratio_bW[i]*nominal_branching_ratio_tH[i]*2*HWW_br[i]*infb[i];
   
  cross_xs_error_BWTH[i] = crossection_error[i]*nominal_branching_ratio_bW[i]*nominal_branching_ratio_tH[i]*2*infb[i];

  //cross_xs_THTZ[i] = production_crossection[i]*nominal_branching_ratio_tZ[i]*nominal_branching_ratio_tH[i]*2*Hbb_br[i]*infb[i] + production_crossection[i]*nominal_branching_ratio_tZ[i]*nominal_branching_ratio_tH[i]*2*HWW_br[i]*infb[i];

  cross_xs_THTZ[i] = production_crossection[i]*nominal_branching_ratio_bW[i]*nominal_branching_ratio_tH[i]*2*infb[i];

  //cross_xs_error_THTZ[i] =  crossection_error[i]*nominal_branching_ratio_tZ[i]*nominal_branching_ratio_tH[i]*2*Hbb_br[i]*infb[i] + crossection_error[i]*nominal_branching_ratio_tZ[i]*nominal_branching_ratio_tH[i]*2*HWW_br[i]*infb[i];

  cross_xs_error_THTZ[i] =  crossection_error[i]*nominal_branching_ratio_tZ[i]*nominal_branching_ratio_tH[i]*2*infb[i];

//  cross_xs_THTH[i] = production_crossection[i]*nominal_branching_ratio_tH[i]*nominal_branching_ratio_tH[i]*Hbb_br[i]*Hbb_br[i]*infb[i] + production_crossection[i]*nominal_branching_ratio_tH[i]*nominal_branching_ratio_tH[i]*HWW_br[i]*HWW_br[i]*infb[i] + production_crossection[i]*nominal_branching_ratio_tH[i]*nominal_branching_ratio_tH[i]*Hbb_br[i]*HWW_br[i]*2*infb[i];

  cross_xs_THTH[i] = production_crossection[i]*nominal_branching_ratio_tH[i]*nominal_branching_ratio_tH[i]*infb[i];

  //cross_xs_error_THTH[i] = crossection_error[i]*nominal_branching_ratio_tH[i]*nominal_branching_ratio_tH[i]*Hbb_br[i]*Hbb_br[i]*infb[i] + crossection_error[i]*nominal_branching_ratio_tH[i]*nominal_branching_ratio_tH[i]*HWW_br[i]*HWW_br[i]*infb[i] + crossection_error[i]*nominal_branching_ratio_tH[i]*nominal_branching_ratio_tH[i]*Hbb_br[i]*HWW_br[i]*2*infb[i];
  
  cross_xs_error_THTH[i] = crossection_error[i]*nominal_branching_ratio_tH[i]*nominal_branching_ratio_tH[i]*infb[i];

  cout << "cross_xs_BWBW " << "@" << mass_point[i] << " = " << cross_xs_BWBW[i] << " with an error of " << cross_xs_error_BWBW[i] << endl;
  cout << "cross_xs_BWTH " << "@" << mass_point[i] << " = " << cross_xs_BWTH[i] << " with an error of " << cross_xs_error_BWTH[i] << endl;
  cout << "cross_xs_BWTZ " << "@" << mass_point[i] << " = " << cross_xs_BWTZ[i] << " with an error of " << cross_xs_error_BWTZ[i] << endl;
  cout << "cross_xs_TZTZ " << "@" << mass_point[i] << " = " << cross_xs_TZTZ[i] << " with an error of " << cross_xs_error_TZTZ[i] << endl;
  cout << "cross_xs_THTZ " << "@" << mass_point[i] << " = " << cross_xs_THTZ[i] << " with an error of " << cross_xs_error_THTZ[i] << endl;
  cout << "cross_xs_THTH " << "@" << mass_point[i] << " = " << cross_xs_THTH[i] << " with an error of " << cross_xs_error_THTH[i] << endl;
  
  
	}
  double mass_point_error[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  c1->SetLogy();
  //c1->SetLogx(); 
  TGraphErrors *xs_vs_br_1 = new TGraphErrors(12, mass_point, production_crossection, mass_point_error, crossection_error);
  xs_vs_br_1->SetTitle("Cross Section as function of mass");
  xs_vs_br_1->SetLineColor(kBlue);
  xs_vs_br_1->SetMarkerColor(kBlue);
  xs_vs_br_1->SetMarkerStyle(20);
  xs_vs_br_1->SetMarkerSize(2.0);
  xs_vs_br_1->SetLineWidth(3);
  xs_vs_br_1->GetYaxis()->SetRangeUser(0.0, 600);
  xs_vs_br_1->GetXaxis()->SetTitle("Mass in GeV");
  xs_vs_br_1->GetYaxis()->SetTitle("Production cross section in fb");
  xs_vs_br_1->Draw("APL*");    
  

  leg = new TLegend(0.7,0.13,0.9,0.16);
  leg->SetFillColor(0);
  //leg->SetHeader("Mass vs X-section");
  leg->AddEntry(xs_vs_br_1,"t t' Production Cross-Section","PL");
  leg->Draw();

  
  c1->SaveAs("xs_vs_br_Mar21.pdf");
  c1->SaveAs("xs_vs_br_Mar21.eps");
}
