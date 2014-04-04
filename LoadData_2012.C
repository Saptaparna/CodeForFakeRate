#ifndef LoadData_cxx
#define LoadData_cxx

#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TH1D.h>
#include <TString.h>
#include <TLorentzVector.h>

#include <iostream>
#include <vector>

#include "tools/Objects/interface/treetop.h"
#include "tools/MassAMWT/interface/FileExists.h"
#include "tools/Objects/interface/TprimeEvent.h"

using namespace std;

enum Samples_t {Data,    ChargeMisID, FakeRate_Data, FakeRate_MC,
		TTbar,   ZJets,   DY1050,WJets, 
		WW,      WZ,      ZZ,      
		WGEl,    WGMu,
		T_tW,    Tbar_tW, T_t,     Tbar_t, T_s,   Tbar_s,
		WWm,     WWp,     WWW,  
		TTW,     TTZ, 
		Tprime500_bWbW,
		Tprime500_bWtZ, Tprime500_bWtH, Tprime500_tHtZ, 
		Tprime500_tZtZ, Tprime500_tHtH
};

const unsigned int totalSamples = 30;

Samples_t allSamples[totalSamples] = {Data,    ChargeMisID, FakeRate_Data, FakeRate_MC,
		TTbar,   ZJets,   DY1050,WJets, 
		WW,      WZ,      ZZ,      
		WGEl,    WGMu,
		T_tW,    Tbar_tW, T_t,     Tbar_t, T_s,   Tbar_s,
		WWm,     WWp,     WWW,  
		TTW,     TTZ, 
		Tprime500_bWbW,
		Tprime500_bWtZ, Tprime500_bWtH, Tprime500_tHtZ, 
		Tprime500_tZtZ, Tprime500_tHtH
};


TString allNames[totalSamples] = {"Data",    "ChargeMisID", "FakeRate_Data", "FakeRate_MC",
			    "TTbar",   "ZJets",   "DY1050","WJets",
			    "WW",      "WZ",      "ZZ", 
			    "WGEl",    "WGMu",
			    "T_tW",    "Tbar_tW", "T_t",     "Tbar_t", "T_s", "Tbar_s",
			    "WWm",     "WWp",     "WWW",  
			    "TTW",     "TTZ", 
			    "Tprime500_bWbW",
			    "Tprime500_bWtZ", "Tprime500_bWtH", "Tprime500_tHtZ", 
			    "Tprime500_tZtZ", "Tprime500_tHtH"
};
   
Color_t color[totalSamples] = {kBlack, 0,0,0,
kRed,   kBlue,kBlue,   kBlue+3, 
kGreen-9,      kViolet+1,      kAzure-2,      
0,0, // WGEl,    WGMu,
kViolet,    kViolet, kViolet,     kViolet, kViolet,   kViolet, //Single Top
kGreen-9,     kGreen-9,     kGreen+2,  
kRed+1,     kOrange, 
kCyan, 
kAzure+10, kOrange+4, kViolet+2, 
kMagenta, kMagenta+4};

vector <unsigned int> indices;


unsigned int NSAMPLES;

// Samples_t samples[NSAMPLES] = {
// Data, 
//  TTbar, WJets, ZJets, DY1050,
//  WW,      WZ,      ZZ,      
// // // WGEl,    WGMu,
//  T_tW,    Tbar_tW, T_t,     Tbar_t, T_s,   Tbar_s,
// // FOR OS: 19
// // Tprime500_bWbW, Tprime500_bWtH, Tprime500_tZtZ, Tprime500_tHtH, Tprime500_bWtZ, Tprime500_tHtZ
// // FOR SS: 15
// Tprime500_tZtZ, Tprime500_bWtZ
// // // For Tri: 16
// // Tprime500_tZtZ, Tprime500_bWtZ, Tprime500_tHtZ
// // WWm,     WWp,     WWW,  
// // TTW,     TTZ};
// };
// // 


//Constant parameters


vector <TString> sNames;
vector <Samples_t> samples;

vector <double> xSection;
vector <treetop*> treeClass;
vector <double> nEvents;
vector <TH1D*>  Histos;
vector <double> sScale;
vector <double> systUnc;


void initAll_2012(TString fileName, int channel, TString sampleName){

  double lumi[3] = {4938*0.987, 5108*0.935, 5147*0.957}; // MuMu, ElMu, ElEl
  NSAMPLES = 1;
  for (unsigned int i = 0; i<totalSamples;++i){
    //cout << allNames[i] <<" "<< sampleName<<endl;
    if (allNames[i] == sampleName) {
      sNames.push_back(allNames[i]);
      indices.push_back(allSamples[i]);
      samples.push_back(allSamples[i]);
      break;
    }
  }
  if (sNames.empty()) {
    cout << "Unknown sample "<<sampleName<<endl;
    exit(1);
  }
  //cout << "init tree "<<samples[0]<<" "<<sNames[0]<<endl;


  double mcUnc = sqrt (2 * 0.006 * 0.006 + //Trigger
		       2 * 0.03  * 0.03);  //Lepton Efficiency

  //Input files
      switch( samples[0] )
      {
        case Data:	break;
        case FakeRate_Data:  break;
        case FakeRate_MC: break;
	case TTbar:	   nEvents.push_back(7611405.0); 	xSection.push_back(225.197); break; //updated
	case ZJets:	   nEvents.push_back(30458572.0);	xSection.push_back(3532.8); break; //updated
	case DY1050:	   nEvents.push_back(7217505.0);	xSection.push_back(860.5); break; //updated
	case WJets:	   nEvents.push_back(18391897.0);	xSection.push_back(36257.2); break; //updated

	case WW:	   nEvents.push_back(9995466.0);	xSection.push_back(54.838*0.33*0.33); break; //LO: xSection.at(WW)   3.783;   //updated //multiplying by the branching fractions
	case WZ:	   nEvents.push_back(9995466.0);	xSection.push_back(0.879); systUnc.push_back(sqrt(mcUnc*mcUnc + 0.05*0.05  + 0.018*0.018 + 0.17*0.17));    ; break; //LO: xSection.at(WZ)   0.7192; 
	case ZZ:	   nEvents.push_back(9963515.0);	xSection.push_back(0.076); systUnc.push_back(sqrt(mcUnc*mcUnc + 0.011*0.011 + 0.006*0.006 + 0.075* 0.075)); ; break; //LO: xSection.at(ZZ)  0.03906;

	case WGEl:	   nEvents.push_back(524503.0);		xSection.push_back(137.3); break; //LO: xSection.at(WGEl)	= 114.7;  
	case WGMu:	   nEvents.push_back(521774.0);		xSection.push_back(137.3); break; //LO: xSection.at(WGMu)	= 114.6;  

	case T_tW:	   nEvents.push_back(497238.0);		xSection.push_back(22.2); break;//updated
	case Tbar_tW:	   nEvents.push_back(492996.0);		xSection.push_back(22.2); break;//updated
	case T_t:	   nEvents.push_back(3960306.0);	xSection.push_back(87.1); break;//updated
	case Tbar_t:	   nEvents.push_back(1933771.0);	xSection.push_back(87.1); break;//updated
	case T_s:	   nEvents.push_back(259693.0);		xSection.push_back(5.55); break;//updated
	case Tbar_s:	   nEvents.push_back(139871.0);  	xSection.push_back(5.55); break;//updated

	case WWm:	   nEvents.push_back(160000.0); 	xSection.push_back(0.055); systUnc.push_back(sqrt(mcUnc*mcUnc + 0.045*0.045 + 0.024*0.024 + 0.5*0.5)); break;
	case WWp:	   nEvents.push_back(130000.0); 	xSection.push_back(0.165); systUnc.push_back(sqrt(mcUnc*mcUnc + 0.045*0.045 + 0.024*0.024 + 0.5*0.5)); break;
	case WWW:	   nEvents.push_back(1201777.0);	xSection.push_back(0.038); systUnc.push_back(sqrt(mcUnc*mcUnc + 0.037*0.037 + 0.005*0.005 + 0.5*0.5)); break;

	case TTW:	   nEvents.push_back(1029608.0); 	xSection.push_back(0.169); systUnc.push_back(sqrt(mcUnc*mcUnc + 0.034*0.034 + 0.0094*0.0094 + 0.5*0.5)); break;
	case TTZ:	   nEvents.push_back(793155.0);  	xSection.push_back(0.139); systUnc.push_back(sqrt(mcUnc*mcUnc + 0.037*0.037 + 0.0025*0.0025 + 0.5*0.5)); break;
        case Tprime500_bWbW: nEvents.push_back(40910);		xSection.push_back(0.570253*0.496*0.496*500); systUnc.push_back( sqrt(mcUnc*mcUnc + 0.037*0.037 + 0.0025*0.0025 + 0.5*0.5)); break; 
	case Tprime500_bWtZ: nEvents.push_back(39457);		xSection.push_back(0.570253*0.496*0.171*2*500); systUnc.push_back(	 sqrt(mcUnc*mcUnc + 0.037*0.037 + 0.0025*0.0025 + 0.5*0.5)); break;
	case Tprime500_bWtH: nEvents.push_back(40235);		xSection.push_back(0.570253*0.496*0.333*2*0.76*500); systUnc.push_back(     sqrt(mcUnc*mcUnc + 0.037*0.037 + 0.0025*0.0025 + 0.5*0.5)); break;
	case Tprime500_tHtZ: nEvents.push_back(39268);		xSection.push_back(0.570253*0.333*0.171*2*0.76*500); systUnc.push_back(     sqrt(mcUnc*mcUnc + 0.037*0.037 + 0.0025*0.0025 + 0.5*0.5)); break;
	case Tprime500_tZtZ: nEvents.push_back(39698);		xSection.push_back(0.570253*0.171*0.171*500); systUnc.push_back(	sqrt(mcUnc*mcUnc + 0.037*0.037 + 0.0025*0.0025 + 0.5*0.5)); break;
        case Tprime500_tHtH: nEvents.push_back(40150);		xSection.push_back(0.570253*0.333*0.333*0.76*0.76*1000); systUnc.push_back(	  sqrt(mcUnc*mcUnc + 0.037*0.037 + 0.0025*0.0025 + 0.5*0.5)); break;
	default:	cout <<"Sample "<<samples[0] <<" not listed for 2012\n";exit(1);
      }
      fexists(fileName.Data(), true);
      treeClass.push_back(new treetop(fileName));
    if   (samples[0] == Data || samples[0] == FakeRate_Data || samples[0] == FakeRate_MC || samples[0] == ChargeMisID) sScale.push_back(1.0);
    else                                                     sScale.push_back(xSection[0] * lumi[channel-1] / nEvents[0]);

  
//   if (treeSuf != ""){
//     for (unsigned int it = 0; it < NSAMPLES; it++){
//       if (it == FakeRate) continue;
//       Trees.at(it) = (TTree*)treeClass.at(it)->Get("treetop_"+treeSuf);
//     }
//   }
}

void initAll_2011(TString treeSuf, TString fileName, int channel, TString sampleName){

  double lumi[3] = {4980,4980,4980}; // MuMu, ElMu, ElEl
  NSAMPLES = 1;
  for (unsigned int i = 0; i<totalSamples;++i){
    cout << allNames[i] <<" "<< sampleName<<endl;
    if (allNames[i] == sampleName) {
      sNames.push_back(allNames[i]);
      indices.push_back(allSamples[i]);
      samples.push_back(allSamples[i]);
      break;
    }
  }
  if (sNames.empty()) {
    cout << "Unknown sample "<<sampleName<<endl;
    exit(1);
  }
  cout << "init tree "<<samples[0]<<" "<<sNames[0]<<endl;


  double mcUnc = sqrt (2 * 0.006 * 0.006 + //Trigger
		       2 * 0.03  * 0.03);  //Lepton Efficiency

  //Input files
      switch( samples[0] )
      {

        case Data:	break;
	case TTbar:	   nEvents.push_back(3701947.0);  xSection.push_back(164.4);   break;
	case ZJets:	   nEvents.push_back(36277961.0); xSection.push_back(3048.0);  break;
	case WJets:	   nEvents.push_back(77105816.0); xSection.push_back(31314.0); break;

	case WW:	   nEvents.push_back(1197558.0);  	    xSection.push_back(4.882);					 ; break; //LO: xSection.at(WW)      = 3.783;  
	case WZ:	   nEvents.push_back(1221134.0);  xSection.push_back(0.879); systUnc.push_back(sqrt(mcUnc*mcUnc + 0.05*0.05   + 0.018*0.018 + 0.17*0.17)); break; //LO: xSection.at(WZ)      = 0.7192; 
	case ZZ:	   nEvents.push_back(1185188.0);  xSection.push_back(0.076); systUnc.push_back(sqrt(mcUnc*mcUnc + 0.011*0.011 + 0.006*0.006 + 0.075* 0.075)); break; //LO: xSection.at(ZZ)      = 0.03906;

	case WGEl:	   nEvents.push_back(524503.0);   xSection.push_back(137.3); break; //LO: xSection.at(WGEl)    = 114.7;  
	case WGMu:	   nEvents.push_back(521774.0);   xSection.push_back(137.3); break; //LO: xSection.at(WGMu)    = 114.6;  

	case T_tW:	   nEvents.push_back(814390.0);   xSection.push_back(7.87);   break;
	case Tbar_tW:	   nEvents.push_back(809984.0);   xSection.push_back(7.87);   break;
	case T_t:	   nEvents.push_back(3900171.0);  xSection.push_back(41.92);  break;
	case Tbar_t:	   nEvents.push_back(1944826.0);  xSection.push_back(22.65);  break;
	case T_s:	   nEvents.push_back(259971.0);   xSection.push_back(3.19);   break;
	case Tbar_s:	   nEvents.push_back(137980.0);   xSection.push_back(1.44);   break;

	case WWm:	   nEvents.push_back(160000.0);   xSection.push_back(0.055); systUnc.push_back(sqrt(mcUnc*mcUnc + 0.045*0.045 + 0.024*0.024 + 0.5*0.5)); break;
	case WWp:	   nEvents.push_back(130000.0);   xSection.push_back(0.165); systUnc.push_back(sqrt(mcUnc*mcUnc + 0.045*0.045 + 0.024*0.024 + 0.5*0.5)); break;
	case WWW:	   nEvents.push_back(1201777.0);  xSection.push_back(0.038); systUnc.push_back(sqrt(mcUnc*mcUnc + 0.037*0.037 + 0.005*0.005 + 0.5*0.5)); break;

	case TTW:	   nEvents.push_back(1029608.0);  xSection.push_back(0.169); systUnc.push_back(sqrt(mcUnc*mcUnc + 0.034*0.034 + 0.0094*0.0094 + 0.5*0.5)); break;
	case TTZ:	   nEvents.push_back(793155.0);   xSection.push_back(0.139); systUnc.push_back(sqrt(mcUnc*mcUnc + 0.037*0.037 + 0.0025*0.0025 + 0.5*0.5)); break;
	default:	cout <<"Sample "<<samples[0] <<" not listed for 2011\n";exit(1);

      }
      fexists(fileName.Data(), true);
      //cout << "need to review treetop usage for 2011\n";
      assert(false);
//      treeClass.push_back(new treetop(fileName,treeSuf));
      cout << "aa\n";
//   if (treeSuf != ""){
    if   (samples[0] == Data || samples[0] == FakeRate_Data ||samples[0] == FakeRate_MC || samples[0] == ChargeMisID) sScale.push_back(1.0);
    else                                                     sScale.push_back(xSection[0] * lumi[channel-1] / nEvents[0]);
      //cout << "aaaa\n";

  
//   if (treeSuf != ""){
//     for (unsigned int it = 0; it < NSAMPLES; it++){
//       if (it == FakeRate) continue;
//       Trees.at(it) = (TTree*)treeClass.at(it)->Get("treetop_"+treeSuf);
//     }
//   }
}

#endif
