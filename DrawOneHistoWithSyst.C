#ifndef DrawOneHistoWithSyst_cxx
#define DrawOneHistoWithSyst_cxx

#include <TStyle.h>
#include <TString.h>
#include <TFile.h>
#include <TH1F.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TPaveText.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
//include "LoadData_2012.C"
#include "tdrstyle.C"

// #include "tPrimeStandardHistos.C"

using namespace std;


enum Samples_t {Data,    ChargeMisID, FakeRate,
		TTbar,   ZJets,   DY1050,WJets, 
		WW,      WZ,      ZZ,      
		WGEl,    WGMu,
		T_tW,    Tbar_tW, T_t,     Tbar_t, T_s,   Tbar_s,
		WWm,     WWp,     WWW,  
		TTW,     TTZ,	  TTWW,
		Tprime500_bWbW,
		Tprime500_bWtZ, Tprime500_bWtH, Tprime500_tHtZ, 
		Tprime500_tZtZ, Tprime500_tHtH
};

const unsigned int totalSamples = 30;

Samples_t allSamples[totalSamples] = {
		Data,    ChargeMisID, FakeRate,
		TTbar,   ZJets,   DY1050,WJets, 
		WW,      WZ,      ZZ,      
		WGEl,    WGMu,
		T_tW,    Tbar_tW, T_t,     Tbar_t, T_s,   Tbar_s,
		WWm,     WWp,     WWW,  
		TTW,     TTZ,	  TTWW,
		Tprime500_bWbW,
		Tprime500_bWtZ, Tprime500_bWtH, Tprime500_tHtZ, 
		Tprime500_tZtZ, Tprime500_tHtH
};

TString allNames[totalSamples] = {"Data",    "ChargeMisID", "FakeRate_Data",
			    "TTbar",   "ZJets",   "DY1050","WJets",
			    "WW",      "WZ",      "ZZ", 
			    "WGEl",    "WGMu",
			    "T_tW",    "Tbar_tW", "T_t",     "Tbar_t", "T_s", "Tbar_s",
			    "WWm",     "WWp",     "WWW",  
			    "TTW",     "TTZ", 	  "TTWW",
			    "Tprime500_bWbW",
			    "Tprime500_bWtZ", "Tprime500_bWtH", "Tprime500_tHtZ", 
			    "Tprime500_tZtZ", "Tprime500_tHtH"
};

TString legendNames[totalSamples] = {"Data",    "Charge MisID", "Non-prompt",
			    "TTbar",   "ZJets",   "DY1050","WJets",
			    "WW",      "WZ",      "ZZ", 
			    "WGEl",    "WGMu",
			    "T_tW",    "Tbar_tW", "T_t",     "Tbar_t", "T_s", "Tbar_s",
			    "WWm",     "WWp",     "WWW",  
			    "TTW",     "TTZ", 	  "TTWW",
			    "Tprime500_bWbW",
			    "Tprime500_bWtZ", "Tprime500_bWtH", "Tprime500_tHtZ", 
			    "Tprime500_tZtZ", "Tprime500_tHtH"
};
   
Color_t color[totalSamples] = {
	kBlack, kCyan, kGray,				// Data,    ChargeMisID, FakeRate,
	kRed,   kBlue,kBlue,   kBlue+3, 	// TTbar,   ZJets,   DY1050,WJets,
	kGreen-9,      kViolet+1,      kAzure-2,//WW,      WZ,      ZZ,
	0,0, // WGEl,    WGMu,
	kViolet,    kViolet, kViolet,     kViolet, kViolet,   kViolet, //Single Top
	kGreen-9,     kGreen-9,     kGreen+2,  	// WWm,     WWp,     WWW, 
	kRed+1,     kOrange,kOrange+2,		// TTW,     TTZ,     TTWW,
	kPink, 					// Tprime500_bWbW,
	kAzure+10, kOrange+4, kViolet+2, 	// Tprime500_bWtZ, Tprime500_bWtH, Tprime500_tHtZ,
kMagenta, kMagenta+4};				// Tprime500_tZtZ, Tprime500_tHtH

vector <unsigned int> indices(totalSamples, -1);

//This is for OS:


// const unsigned int NSAMPLES = 3;
// Samples_t samples[NSAMPLES] = {
// Data, 
// ZJets, DY1050
// };

// const unsigned int NSAMPLES = 17;
// Samples_t samples[NSAMPLES] = {
// Data, 
// TTbar, ZJets, DY1050, WJets,
//  T_tW,    Tbar_tW, T_t,     Tbar_t, T_s,   Tbar_s,
// Tprime500_bWbW, Tprime500_bWtH, Tprime500_tZtZ, Tprime500_tHtH, Tprime500_bWtZ, Tprime500_tHtZ
// };

//This is for SS:

const unsigned int NSAMPLES = 17; //change here
Samples_t samples[NSAMPLES] = {
Data, ChargeMisID, FakeRate,
WZ, ZZ,      
WWm,     WWp,     WWW,  
TTW,      TTWW, TTZ,
// Tprime500_tZtZ, Tprime500_bWtZ
Tprime500_bWbW, Tprime500_bWtH, Tprime500_tZtZ, Tprime500_tHtH, Tprime500_bWtZ, Tprime500_tHtZ
};

//This is for multi-lepton:

// const unsigned int NSAMPLES = 11;
// Samples_t samples[NSAMPLES] = {
// Data, 
// TTbar, ZJets, DY1050, WJets,
//  T_tW,    Tbar_tW, T_t,     Tbar_t, T_s,   Tbar_s
//  //WW,     
// //  WZ,
// //      ZZ,      
// // // // WGEl,    WGMu,
// // // For Tri: 16
// // Tprime500_tZtZ, Tprime500_bWtZ, Tprime500_tHtZ
// // WWm,     WWp,     WWW,  
// // TTW,     TTZ};
// };
// 



vector <TString> sNames;

vector <double> xSection;
vector <TH1D*>  Histos;
vector <double> sScale;
vector <double> systUnc;


/**
#DrawOneHisto parameter list:
#1: Input directory in root file
#2: Channel (ElEl, ElMu or MuMu   
#3: Prefix for histograms 
#4: Name of histogram
#5: Log or not log 
#6: x-Axis name
#7: Optional: rebin by this number
*/

float getMyEntries(TH1* histo)
{
  float tot=0.;
  for (int i=0;i<histo->GetNbinsX()+1;++i) {
    if (histo->GetBinContent(i)>0.) tot+=histo->GetBinContent(i);
  }
  return tot;
}

float getMinEntries(TH1* histo)
{
  float min=999999.;
  for (int i=0;i<histo->GetNbinsX()+1;++i) {
    if ((histo->GetBinContent(i)>0.) && (histo->GetBinContent(i)<min)) min=histo->GetBinContent(i);
  }
  return min;
}
float getMinEntries(TH1* histo, float min)
{
  for (int i=0;i<histo->GetNbinsX()+1;++i) {
    if ((histo->GetBinContent(i)>0.) && (histo->GetBinContent(i)<min)) min=histo->GetBinContent(i);
  }
  return min;
}

int main( int argc, const char* argv[] ){
  if (argc < 8){
    cout<<"Need at least 7 arguments. Only "<<argc<<" found."<<endl;
    return 1;
  }
  
  setTDRStyle();

  //Root file information
  TString rootFile  = argv[1];
  TString inDir  = argv[2];
  TString inSuff = argv[3];
  TString inPref = argv[4];
  TString inName = argv[5];

  //Drawing information
  int yLog = atoi(argv[6]);
  TString xTitle = argv[7];

  int rebin = 1;
  if (argc > 8) rebin = atoi(argv[8]);

  cout<<inDir<<" ";
  cout<<inSuff<<" ";
  cout<<inPref<<" ";
  cout<<inName<<" ";
  cout<<yLog<<" ";
  cout<<xTitle<<" ";
  cout<<rebin<<endl;

  const unsigned int NCHAN = 4;

  TFile *file0 = TFile::Open(rootFile);
  if (file0==0) {
    cout << "\n\nERROR: "<<rootFile<< " does not exist\n\n";
    return 1;
  }
  file0->cd();

  TH1F* histArray[NSAMPLES][NCHAN];
  if (inPref != "Top") inPref = "_"+inPref;
  else                 inPref = "";
  if (inDir != "Top") file0->cd(inDir);
  for (unsigned int isam = 0; isam < NSAMPLES; isam++){
//   cout << "ab "<<samples[isam]<< indices.size()<< endl;
    indices[samples[isam]] = isam;
    sNames.push_back(allNames[samples[isam]]);

    TString sampleName;
    if (isam < NSAMPLES) sampleName = sNames[isam];
    else                 sampleName = "FakeRate";

    cout << isam<<" "<<allNames[samples[isam]]<<" "<<color[samples[isam]]<<" "<<inName<<inPref<<"_"<<sampleName<<endl;;

    histArray[isam][0] = (TH1F*)gDirectory->Get(inName+inPref+"_"+sampleName+"_"+"MuMu");
    histArray[isam][1] = (TH1F*)gDirectory->Get(inName+inPref+"_"+sampleName+"_"+"ElMu");
    histArray[isam][2] = (TH1F*)gDirectory->Get(inName+inPref+"_"+sampleName+"_"+"ElEl");
    if ((histArray[isam][0]==0) || (histArray[isam][0]==0) || (histArray[isam][0]==0)) {
      cout << "\n\nERROR: One of the histograms do not exist: "<< inName<<inPref<<"_"<<sampleName<<"\n\n";
      gDirectory->ls();
      return 1;
    }
// cout <<  histArray[isam][0]->GetName()<<endl;
// cout <<  histArray[isam][0]->GetNbinsX()<<endl;
    if (rebin != 1){
      histArray[isam][0]->Rebin(rebin);
      histArray[isam][1]->Rebin(rebin);
      histArray[isam][2]->Rebin(rebin);
    }
    
    histArray[isam][3] = (TH1F*)histArray[isam][0]->Clone("histArray_"+sampleName);
    histArray[isam][3]->Add(histArray[isam][1]);
    histArray[isam][3]->Add(histArray[isam][2]);

//     if      (inSuff == "MuMu") histos.push_back(histArray[isam][0]);
//     else if (inSuff == "ElMu") histos.push_back(histArray[isam][1]);
//     else if (inSuff == "ElEl") histos.push_back(histArray[isam][2]);
//     else if (inSuff == "All")  histos.push_back(histArray[isam][3]);
//     else{
//       cout<<"Invalid suffix"<<endl;
//       return 1;
//     }
  }
//   //Calculate systematics
//   vector <TH1F*> selectedHistos;
// //   selectedHistos.push_back(histos.at(indices[ChargeMisID]));
//   selectedHistos.push_back(histos.at(indices[WZ]));                                      
//   selectedHistos.push_back(histos.at(indices[ZZ]));                                      
//   selectedHistos.push_back(histos.at(indices[WWp]));                                     
//   selectedHistos.push_back(histos.at(indices[WWm]));                                     
//   selectedHistos.push_back(histos.at(indices[WWW]));                                     
//   selectedHistos.push_back(histos.at(indices[TTW]));                                     
//   selectedHistos.push_back(histos.at(indices[TTZ]));                                      
// //   selectedHistos.push_back(histos.at(indices[FakeRate]));                              
// 
//   vector <double> selectedUnc;
// //   selectedUnc.push_back(systUnc.at(indices[ChargeMisID]));
//   selectedUnc.push_back(systUnc.at(indices[WZ));                                      
//   selectedUnc.push_back(systUnc.at(indices[ZZ));                                      
//   selectedUnc.push_back(systUnc.at(indices[WWp]));                                     
//   selectedUnc.push_back(systUnc.at(indices[WWm]));                                     
//   selectedUnc.push_back(systUnc.at(indices[WWW]));                                     
//   selectedUnc.push_back(systUnc.at(indices[TTW]));                                     
//   selectedUnc.push_back(systUnc.at(indices[TTZ]));                                      
// //   selectedUnc.push_back(systUnc.at(indices[FakeRate]));                              
// 
// 
//   TH1F* h_SumAll = (TH1F*)histos.at(ChargeMisID)->Clone("h_SumAll"); 
//   for (unsigned int ih = 1; ih < selectedHistos.size(); ih++){
//     h_SumAll->Add(selectedHistos.at(ih));
//   }
//   
//   TH1F* h_lumiBand = (TH1F*) h_SumAll->Clone("h_lumiBand");
//   
//   for (int ibin = 1; ibin < h_lumiBand->GetNbinsX()+1; ibin++){
// 
//     double uncStat = 0;
//     double uncSyst = 0;
//     double uncTot  = 0;
// 
//     for (unsigned int ih = 0; ih < selectedHistos.size(); ih++){
//       uncStat += selectedHistos.at(ih)->GetBinError(ibin)*selectedHistos.at(ih)->GetBinError(ibin);
//       uncSyst += selectedHistos.at(ih)->GetBinContent(ibin)*selectedHistos.at(ih)->GetBinContent(ibin)*selectedUnc.at(ih)*selectedUnc.at(ih);    
//     }
//  
//     uncTot = sqrt(uncStat + uncSyst);    
//     h_lumiBand->SetBinError(ibin, uncTot);
//   }

  for (int iChan = 0;iChan<4;++iChan) {
    switch( iChan ) {
      case 0: inSuff = "MuMu"; break;
      case 1: inSuff = "ElMu"; break;
      case 2: inSuff = "ElEl"; break;
      case 3: inSuff = "All" ; break;
    }
    vector <TH1F*> histos;
    for (unsigned int isam = 0; isam < NSAMPLES; isam++) {
      histos.push_back(histArray[isam][iChan]);
    }

  //Format data histogram
  histos.at(indices[Data])->SetMarkerStyle(20);
  for (int ibin = 0; ibin < histos.at(indices[Data])->GetNbinsX() + 1; ibin++){
    if (histos.at(indices[Data])->GetBinContent(ibin) == 0) histos.at(indices[Data])->SetBinContent(ibin, -10);
  }

  THStack* mystack = new THStack("mystack","mystack");
  TH1F * histo1D_mc = (TH1F *) histos.at(Data)->Clone("MC");
  histo1D_mc->Reset();
  TH1F * histo1D_signal = (TH1F *) histos.at(Data)->Clone("signal");
  histo1D_signal->Reset();
  histo1D_signal->SetMarkerStyle(22);
  histo1D_signal->SetMarkerSize(1.5);
  histo1D_signal->SetMarkerColor(kBlue);
  TH1F * ratio = (TH1F *) histos.at(Data)->Clone("ratio");

// Legend:

  TLegend * leg = new TLegend(0.76, 0.67, 0.88, 0.94, "","brNDC");
  leg->SetFillColor(10);
  leg->SetTextSize(0.02);
  leg->SetTextFont(42);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetLineStyle(0);

  leg->AddEntry(histos.at(Data), "Data", "lp");
  //leg->AddEntry(histo1D_signal, "Signal", "lp");

  cout << "Yield : "<< inSuff<<endl;
  cout << "Yield: Data  "<<getMyEntries(histos.at(Data))<<endl;

  float singeTopYield = 0.;
  float dyYield = 0.;
  float totalBackground = 0.;
  float minimum=999999;
  for (unsigned int isam = 0; isam < NSAMPLES; isam++){
    if (samples[isam]!=Data) {
      //histos.at(isam)->SetFillColor(color[samples[isam]]);
      if (samples[isam]< Tprime500_bWbW) {
        histos.at(isam)->SetFillColor(color[samples[isam]]);
        //if (samples[isam]==Tprime500_bWbW) leg->AddEntry(histos.at(isam), "Tprime500_bWbW", "lp");
        //if (samples[isam]==Tprime500_bWtZ) leg->AddEntry(histos.at(isam), "Tprime500_bWtZ", "lp");
        //if (samples[isam]==Tprime500_bWtH) leg->AddEntry(histos.at(isam), "Tprime500_bWtH", "lp");
        //if (samples[isam]==Tprime500_tHtH) leg->AddEntry(histos.at(isam), "Tprime500_tHtH", "lp");
        //if (samples[isam]==Tprime500_tHtZ) leg->AddEntry(histos.at(isam), "Tprime500_tHtZ", "lp");
        //if (samples[isam]==Tprime500_tZtZ) leg->AddEntry(histos.at(isam), "Tprime500_tZtZ", "lp");

        minimum=getMinEntries(histos.at(isam),minimum);
        totalBackground+=histos.at(isam)->Integral();

	if (!((samples[isam]>=T_tW)&& (samples[isam]<=Tbar_s))) {
	  if ((samples[isam]!= DY1050) && (samples[isam]!= ZJets))
            cout << "Yield: "<< legendNames[samples[isam]] << " "<< histos.at(isam)->Integral()<<" "<<getMyEntries(histos.at(isam))<<
	    endl;
	    else dyYield+=histos.at(isam)->Integral();
	} else singeTopYield+=histos.at(isam)->Integral();



	if (!((samples[isam]>=T_tW)&& (samples[isam]<=Tbar_s)) && 
	(samples[isam]!= DY1050) && (samples[isam]!= ZJets) &&
	(samples[isam]!= WWm)) 
	  leg->AddEntry(histos.at(isam), legendNames[samples[isam]], "f");
	if (samples[isam]==T_tW)
	  leg->AddEntry(histos.at(isam), "Single Top", "f");
	if (samples[isam]==ZJets)
	  leg->AddEntry(histos.at(isam), "Drell Yan", "f");
	if (samples[isam]==WWp)
	  leg->AddEntry(histos.at(isam), "W^{#pm}W^{#pm}", "f");
	mystack->Add(histos.at(isam));
	histo1D_mc->Add(histos.at(isam));
      } 
        if (samples[isam]==Tprime500_bWbW){
	  //mystack->Add(histos.at(isam));
          histos.at(isam)->SetLineColor(kGreen);
          histos.at(isam)->SetLineWidth(4);
	  histos.at(isam)->SetLineStyle(3);
	  //histos.at(isam)->Scale(1000);
	  histos.at(isam)->Draw();
          leg->AddEntry(histos.at(isam), "t^{'} 500 bWbW", "lp");
		}
        if (samples[isam]==Tprime500_bWtZ){ 
	  //mystack->Add(histos.at(isam));
	  histos.at(isam)->SetLineColor(kBlack);
          histos.at(isam)->SetLineWidth(4);
	  histos.at(isam)->SetLineStyle(3);
          //histos.at(isam)->Scale(1000);
          histos.at(isam)->Draw("same");
          leg->AddEntry(histos.at(isam), "t^{'} 500 bWtZ", "lp");
		}
        if (samples[isam]==Tprime500_bWtH){
          //mystack->Add(histos.at(isam));
          histos.at(isam)->SetLineColor(kBlue);
          histos.at(isam)->SetLineWidth(4);
          histos.at(isam)->SetLineStyle(3);
          //histos.at(isam)->Scale(1000);
          histos.at(isam)->Draw("same");
          leg->AddEntry(histos.at(isam), "t^{'} 500 bWtH", "lp");
		}
        if (samples[isam]==Tprime500_tHtH){
	  //mystack->Add(histos.at(isam));
	  histos.at(isam)->SetLineColor(kCyan);
          histos.at(isam)->SetLineWidth(4);
          histos.at(isam)->SetLineStyle(3);
          //histos.at(isam)->Scale(1000);
          histos.at(isam)->Draw("same");
          leg->AddEntry(histos.at(isam), "t^{'} 500 tHtH", "lp");
		}
        if (samples[isam]==Tprime500_tHtZ){
	  //mystack->Add(histos.at(isam));
	  histos.at(isam)->SetLineColor(6);
          histos.at(isam)->SetLineWidth(4);
          histos.at(isam)->SetLineStyle(3);
          //histos.at(isam)->Scale(1000);
          histos.at(isam)->Draw("same");
          leg->AddEntry(histos.at(isam), "t^{'} 500 tHtZ", "lp");
		}
        if (samples[isam]==Tprime500_tZtZ){
	  //mystack->Add(histos.at(isam));
	  histos.at(isam)->SetLineColor(40);
          histos.at(isam)->SetLineWidth(4);
          histos.at(isam)->SetLineStyle(3);
	  //histos.at(isam)->Scale(1000);
          histos.at(isam)->Draw("same");
          leg->AddEntry(histos.at(isam), "t^{'} 500 tZtZ", "lp");
     		}
      //else {
	//histo1D_signal->Add(histos.at(isam));
      //}
    }
  }
  cout << "Yield: DY: "<< dyYield<<endl;
  cout << "Yield: Single top: "<< singeTopYield<<endl;
  cout << "Yield: total background: "<< totalBackground<<endl;
  cout << "Yield: Signal Tprime 500: "<< histo1D_signal->Integral()/500.<<endl;

//   //Charge MisID
//   if (inSuff != "MuMu"){
//     histos.at(ChargeMisID)->SetFillColor(kAzure+6);
//     leg->AddEntry(histos.at(ChargeMisID), "Charge MisID", "f");
//     mystack->Add(histos.at(ChargeMisID));
//   }

//   //Fakes
//   histos.at(FakeRate)->SetFillColor(kGray);
//   histos.at(FakeRate)->SetLineColor(kBlack);
//   leg->AddEntry(histos.at(FakeRate), "Non-prompt", "f");
//   mystack->Add(histos.at(FakeRate));
  
  if (mystack->GetMaximum() > histos.at(indices[Data])->GetMaximum() + sqrt(histos.at(indices[Data])->GetMaximum())){
    if (yLog == 0) histos.at(indices[Data])->SetMaximum((mystack->GetMaximum() + sqrt(histos.at(indices[Data])->GetMaximum())) * 1.05);
    else           histos.at(indices[Data])->SetMaximum((mystack->GetMaximum() + sqrt(histos.at(indices[Data])->GetMaximum())) * 1.40);
  }


  //Larger description of channel
  TString schan = "";
  if (inSuff == "ElEl") schan = " - ee";
  if (inSuff == "ElMu") schan = " - e#mu";
  if (inSuff == "MuMu") schan = " - #mu#mu";
  if (inSuff == "All")  schan = "";

  if (yLog == 0) histos.at(indices[Data])->SetMinimum(0);
  else           histos.at(indices[Data])->SetMinimum(getMinEntries(histo1D_mc)/5);

  double maximum = max(histos.at(indices[Data])->GetMaximum(),histo1D_signal->GetMaximum());
  maximum = max(maximum,histo1D_mc->GetMaximum());
  if (yLog == 0) histos.at(indices[Data])->SetMaximum(maximum * 1.2);
  else           histos.at(indices[Data])->SetMaximum(maximum * 10);
  
//  histos.at(indices[Data])->GetXaxis()->SetTitle(xTitle+schan);
  histos.at(indices[Data])->GetYaxis()->SetTitle("Events");
  histos.at(indices[Data])->GetYaxis()->SetTitleOffset(1.3);

  TCanvas* canv = new TCanvas("canv", "canv", 600, 800);
  canv->SetLeftMargin(0.1);
  canv->SetRightMargin(0.03);
  canv->SetTopMargin(0.05);
  canv->SetBottomMargin(0.3);
  canv->cd();

  histos.at(indices[Data])->SetMarkerSize(1.2);
  histos.at(indices[Data])->GetXaxis()->SetLabelSize(0);
  histos.at(indices[Data])->GetXaxis()->SetTitleSize(0);
  histos.at(indices[Data])->Draw("P E x0");
  mystack->Draw("hist same");
//   mystack->GetHistogram()->Draw("same");
  histos.at(indices[Data])->Draw("P E same");
  histo1D_signal->Draw("P E same x0");
  
  gStyle->SetHatchesLineWidth(4);
  gStyle->SetErrorX(0.5);

//   h_lumiBand->SetFillStyle(3005);
//   h_lumiBand->SetFillColor(1);
//   h_lumiBand->Draw("samee2");

  leg->Draw();

  //Mandatory text boxes
  TLatex* text1 = new TLatex(1.570061,23.08044,"CMS Preliminary, 11.2 fb^{-1} at #sqrt{s} = 8 TeV");
  text1->SetNDC();
  text1->SetTextAlign(13);
  text1->SetX(0.12);
  text1->SetY(0.982);
  text1->SetTextFont(42);
  text1->SetTextSizePixels(20);
  text1->Draw();

  if (getMyEntries(histos.at(Data))>0. && (yLog == 1) ) gPad->SetLogy(yLog);

    TPad *pad = new TPad("pad", "pad", 0.0, 0.0, 1.0, 1.0);
    pad->SetTopMargin(0.7);
    pad->SetLeftMargin(0.1);
    pad->SetRightMargin(0.03);
    pad->SetFillColor(0);
    pad->SetFillStyle(0);
//     pad->SetTickx(1);
//     pad->SetTicky(1);
    pad->Draw();
    pad->cd(0);
    pad->SetGridy(true);
    ratio->Divide(histo1D_mc);
    ratio->GetXaxis()->SetTitle(xTitle+schan);
    ratio->GetYaxis()->SetNdivisions(505);
    ratio->Draw("p e x0");
    ratio->SetMaximum( 1.5);
    ratio->SetMinimum( 0.5);


//    histos.at(Data)->Draw("same");
  

  TString outName = inName+inPref;
  if (inSuff != "All") outName += "_"+inSuff;


  canv->SaveAs(outName+".png");
//   canv->SaveAs(outName+".eps");
  canv->SaveAs(outName+".pdf");
  }
}
// int main( int argc, const char* argv[] ){
// 
// TString channel[4] = {"ElEl","ElMu","MuMu", "All"} 
// 
//   TString rootFile  = argv[1];
//   TString inDir  = argv[2];
//   TString inSuff = argv[3];
//   TString inPref = argv[4];
//   TString inName = argv[5];
// 
//   //Drawing information
//   int yLog = atoi(argv[6]);
//   TString xTitle = argv[7];
// 
//   vector<TString> legend(NHISTOS);
//   legend.at(Lep1Pt)    = TString("Leading lepton p_{T} [GeV/c]");
// legend.at(Lep2Pt)    = TString("Second lepton p_{T} [GeV/c]");
// legend.at(Lep3Pt)    = TString("Third lepton p_{T} [GeV/c]"); 
// 
// legend.at(ElPt)	  = TString("Electron p_{T} [GeV/c]"); 
// legend.at(MuPt)	  = TString("Muon p_{T} [GeV/c]"); 
// 
// legend.at(ElEta)	  = TString(""); 
// legend.at(MuEta)	  = TString(""); 
// 
// legend.at(Jet1Pt)    = TString("Leading jet p_{T} [GeV/c]"); 
// legend.at(Jet2Pt)    = TString("Second jet p_{T} [GeV/c]"); 
// 
// legend.at(nJets)	  = TString("Number of Jets"	    ); 
// legend.at(nBJets)    = TString("Number of b-tagged jets"); 
// legend.at(nElec)	  = TString("Number of Electrons"); 
// legend.at(nMuon)	  = TString("Number of Muons"); 
// legend.at(nLept)	  = TString("Number of leptons"); 
// legend.at(sumPtL)    = TString("Sum of lepton p_{T} [GeV/c]"); 
// legend.at(sumPtJ)    = TString("Sum of jet p_{T} [GeV/c]"); 
// legend.at(MET)	  = TString("MET [GeV]"); 
// 
// legend.at(HT)	  = TString("HT [GeV]"); 
// 
// legend.at(LepInvM)   = TString("Invariant Mass of Lepton Pair [GeV/c^{2}]"); 
// legend.at(LepJInvM)  = TString(""); 
// legend.at(dRlept)      = TString("#delta R (l1,l2)"); 
// legend.at(mindR)	    = TString("Min (#delta R (l,b-jet))"); 
// legend.at(dR)	    = TString("#delta R (l,b-jet)"); 
// legend.at(minMlb)      = TString("Min(m_{lb}})"); 
// legend.at(Mlb)	    = TString("m_{lb}}"); 
//   
// };
// 
// 
//   for (int=0,i<4;++i)
//   {
//     for (unsigned int ih = 0; ih < NHISTOS; ih++){
//       drawSinglePlot(rootFile, inDir, channel[i] , "Lep1Pt"  1 legend[ih], 10);
// 
// }
// 
// }

#endif
