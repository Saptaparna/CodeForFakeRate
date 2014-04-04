#ifndef ClosureTest_cxx
#define ClosureTest_cxx

#include "LoadData_2012.C"
#include "tPrimeStandardHistos.C"
#include <iomanip>
#include "Objects/interface/HcalLaserEventFilter2012.h"
#include "Objects/interface/LumiReWeighting.h"
#include "MassAMWT/interface/TopMassVariables.h"
#include "MassAMWT/interface/AMWT.h"
#include "TCanvas.h"

using std::cout;
using std::endl;

int main( int argc, const char* argv[] ){
  
  int MIN_BTAG_FR =-1; 
  bool b_MuMu = false;
  bool b_ElEl = false;
  bool b_MuEl = false;
  int year;  
  if (argc < 4){
    cout<<"Four arguments are required: channel, year, sample name and file name"<<endl;
    return 0;
  }
  
  HcalLaserEventFilter2012 hcal("./AllBadHCALLaser.txt.gz");
  
  TString treeSuf;
  TString suffix;
  
  int channel;
  if (strcmp(argv[1],"MuMu")==0) {
    b_MuMu = true;
    channel = 0;
    cout<<"Processing MuMu"<<endl;
    suffix  = "MuMu";
    treeSuf = "mumu";
  } else if (strcmp(argv[1],"MuEl")==0) {
    channel = 1;
    b_MuEl = true;
    cout<<"Processing MuEl"<<endl;
    suffix = "MuEl";
    treeSuf = "muel";
  } else if (strcmp(argv[1],"ElEl")==0){ 
    channel = 2;
    b_ElEl = true;
    cout<<"Processing ElEl"<<endl;
    suffix = "ElEl";
    treeSuf = "elel";
  }
  else {
    cout<<"Dilepton channel must be MuMu/ElEl/MuEl"<<endl;
    return 0;
  }
  
  year = atoi(argv[2]);
  
  TString sampleName(argv[3]);
  TString fileName(argv[4]);
  
  TprimeEvent * teve = new TprimeEvent();
  if (year ==2011) {
    initAll_2011(treeSuf, fileName, channel, sampleName);
  } else if (year ==2012) {
    initAll_2012(fileName, channel, sampleName);
  } else {
    cout <<"Year has to be 2011 or 2012\n";
    return 0;
  }
  
  
  cout << "Init LumiReWeighting"<<endl;
  
  std::string generatedFile("/data1/speer/tblsm/tools/data/pu_mc.root");
  std::string dataFile("/data1/speer/tblsm/tools/data/pu_data.root");
  std::string genHistName("PUS10_Distr");
  std::string dataHistName("PUS10_Distr");
  fexists(generatedFile,true);
  fexists(dataFile,true);
  LumiReWeighting lumiReWeighting(generatedFile, dataFile, genHistName, dataHistName);
  //lumiReWeighting.weight(treeClass->nTrueInteractions);  
 
  cout << "Done lumi reweighting" << endl;
  TCanvas* c = new TCanvas("c", "c", 600, 400); 
  TH1D* h_weight = new TH1D("h_weight", "h_weight", 100, 0.0, 5.0); 
  //Output file
  TFile* outFile = new TFile("gfOutFile_"+sampleName+"_"+suffix+".root", "RECREATE");
  
  
  unsigned int nCutSteps = 6;
  int nProc=0;
  int nRawEvents=0; 
  double observed_events=0.0;
  double predicted_events=0.0;
  int N_events=0;
  int unmatched_0 = 0;
  int unmatched_1 = 0;
  int l_matched_0 = 0;
  int l_matched_1 = 0;
  int c_matched_0 = 0;
  int c_matched_1 = 0;
  int b_matched_0 = 0;
  int b_matched_1 = 0;  
  int w_matched_0 = 0;
  int w_matched_1 = 0;
  int bad_from_b_0 = 0;
  int bad_from_b_1 = 0;
  int bad_from_c_0 = 0;
  int bad_from_c_1 = 0;
  int bad_from_l_0 = 0;
  int bad_from_l_1 = 0;
  int bad_from_w_0 = 0;
  int bad_from_w_1 = 0; 
  int bad_unmatched_0 = 0;
  int bad_unmatched_1 = 0; 
  int N_events_bad_muons = 0;
  int N_events_bad_electrons = 0;
  int predicted_events_bad_muons = 0;
  int predicted_events_bad_electrons = 0;  
  int badMuons_from_b_0 = 0;
  int badMuons_from_b_1 = 0;
  int badMuons_from_c_0 = 0;
  int badMuons_from_c_1 = 0;
  int badMuons_from_l_0 = 0;
  int badMuons_from_l_1 = 0;
  int badMuons_from_w_0 = 0;
  int badMuons_from_w_1 = 0;
  int badMuons_unmatched_0 = 0;
  int badMuons_unmatched_1 = 0;
  int badElectrons_from_b_0 = 0;
  int badElectrons_from_b_1 = 0;
  int badElectrons_from_c_0 = 0;
  int badElectrons_from_c_1 = 0;
  int badElectrons_from_l_0 = 0;
  int badElectrons_from_l_1 = 0;
  int badElectrons_from_w_0 = 0;
  int badElectrons_from_w_1 = 0;  
  int badElectrons_unmatched_0 = 0;
  int badElectrons_unmatched_1 = 0; 
    

  for (unsigned int i = 0; i < NSAMPLES; i++){
    unsigned int isam = samples[i]; 
    if(samples[i] == FakeRate_Data){// || samples[i] == FakeRate_MC ){ 
      Long64_t nEIT = treeClass.at(i)->getEntries();
      
      cout<<"Events to be processed: "<<nEIT<<endl;
      
      Long64_t iEvent = (Long64_t)(treeClass.at(i)->event + 0.01);
      
      
      for (Long64_t il = 0; il < nEIT; il++){
	treeClass.at(i)->GetEntry(il);
        hcal.filter(treeClass.at(i)->run,treeClass.at(i)->lumi,treeClass.at(i)->event);
	
	if (nProc % 100000 == 0) cout<<"Processed "<<nProc<<" events so far"<<endl;
	
	nRawEvents++;
	
	nProc++;
	
	//Initialize TprimeEvent class
	teve->clearEvent();
	teve->suffix = suffix;
	teve->isam = isam;
	//Require exactly 1 lepton     
	
	bool b_LepCuts = false;
        bool b_Tight=false;
	double fake_rate=0.0;
        if ((treeClass.at(i)->looseLeptons.size() ==2 )){ 
	  teve->lepton1=treeClass.at(i)->looseLeptons.at(0);
          teve->lepton2=treeClass.at(i)->looseLeptons.at(1);
          if (b_ElEl)  {
 	    if(treeClass.at(i)->looseElecs.size() == 2 && treeClass.at(i)->looseMuons.size() == 0){
              b_LepCuts = true;
              fake_rate=0.154;
	    }	
	  }
          else if(b_MuEl && treeClass.at(i)->looseMuons.size() == 1 && treeClass.at(i)->looseElecs.size() == 1){
	    b_LepCuts = true;
	  }	
	  else if(b_MuMu && treeClass.at(i)->looseMuons.size() == 2 && treeClass.at(i)->looseElecs.size() == 0){
	    b_LepCuts = true;
            fake_rate=0.284;
	  }
	}	
        
	
	if ((treeClass.at(i)->goodLeptons.size() ==2)){
          teve->lepton1 = treeClass.at(i)->goodLeptons.at(0);
          teve->lepton2 = treeClass.at(i)->goodLeptons.at(1);
	  if(b_ElEl) {
            if(treeClass.at(i)->goodElecs.size() == 2 && treeClass.at(i)->goodMuons.size() == 0 ){
	      b_Tight=true;
            }
	  }
          else if(b_MuEl && treeClass.at(i)->goodElecs.size() == 1 && treeClass.at(i)->goodMuons.size() == 1){
	    b_Tight = true;
          }
	  else if(b_MuMu &&
		  treeClass.at(i)->goodMuons.size() == 2 && treeClass.at(i)->goodElecs.size() == 0){
	    b_Tight=true;
	  }
	}  
        lumiReWeighting.weight(treeClass.at(i)->nTrueInteractions);
	h_weight->Fill(lumiReWeighting.weight(treeClass.at(i)->nTrueInteractions));
        if(b_LepCuts){
	  if(abs(treeClass.at(i)->looseLeptons.at(0)->charge + treeClass.at(i)->looseLeptons.at(1)->charge)==2){
	    if(b_MuMu || b_ElEl){
              if(((  treeClass.at(i)->looseLeptons.at(0)->origin()==24 && treeClass.at(i)->looseLeptons.at(0)->goodLepton())
               && (treeClass.at(i)->looseLeptons.at(1)->origin()!=24 && treeClass.at(i)->looseLeptons.at(1)->goodLepton())) 
              || ((treeClass.at(i)->looseLeptons.at(1)->origin()==24 && treeClass.at(i)->looseLeptons.at(1)->goodLepton())
              && (treeClass.at(i)->looseLeptons.at(0)->origin()!=24 && treeClass.at(i)->looseLeptons.at(0)->goodLepton())) ){               observed_events++;// = observed_events + lumiReWeighting.weight(treeClass.at(i)->nTrueInteractions);  
	              if(treeClass.at(i)->looseLeptons.at(0)->origin()==0){
			unmatched_0++;
			}
		      if(treeClass.at(i)->looseLeptons.at(0)->origin()==1){
			l_matched_0++;
			}	
		      if(treeClass.at(i)->looseLeptons.at(0)->origin()==4){
			c_matched_0++;
			}
                      if(treeClass.at(i)->looseLeptons.at(0)->origin()==5){
			b_matched_0++;
			}
                      if(treeClass.at(i)->looseLeptons.at(0)->origin()==24){
			w_matched_0++;
			}

                      if(treeClass.at(i)->looseLeptons.at(1)->origin()==0){
			unmatched_1++;
			}
		      if(treeClass.at(i)->looseLeptons.at(1)->origin()==1){
			l_matched_1++;
			}	
		      if(treeClass.at(i)->looseLeptons.at(1)->origin()==4){
			c_matched_1++;
			}
                      if(treeClass.at(i)->looseLeptons.at(1)->origin()==5){
			b_matched_1++;
			}
                      if(treeClass.at(i)->looseLeptons.at(1)->origin()==24){
			w_matched_1++;
			} 	
			

	     }
	    if((((treeClass.at(i)->looseLeptons.at(0)->origin()==24 && treeClass.at(i)->looseLeptons.at(0)->goodLepton()))
               && !treeClass.at(i)->looseLeptons.at(1)->goodLepton())
               || ((treeClass.at(i)->looseLeptons.at(1)->origin()==24 
               && treeClass.at(i)->looseLeptons.at(1)->goodLepton())
               && !treeClass.at(i)->looseLeptons.at(0)->goodLepton())){
	      N_events++;// = N_events + lumiReWeighting.weight(treeClass.at(i)->nTrueInteractions);
	      predicted_events=(fake_rate/(1 - fake_rate))*N_events;
	      if(treeClass.at(i)->looseLeptons.at(0)->origin()==24 && treeClass.at(i)->looseLeptons.at(0)->goodLepton()){
                if(!treeClass.at(i)->looseLeptons.at(1)->goodLepton() && treeClass.at(i)->looseLeptons.at(1)->origin()==5) bad_from_b_1++;
                if(!treeClass.at(i)->looseLeptons.at(1)->goodLepton() && treeClass.at(i)->looseLeptons.at(1)->origin()==24) bad_from_w_1++;
                if(!treeClass.at(i)->looseLeptons.at(1)->goodLepton() && treeClass.at(i)->looseLeptons.at(1)->origin()==4) bad_from_c_1++;
                if(!treeClass.at(i)->looseLeptons.at(1)->goodLepton() && treeClass.at(i)->looseLeptons.at(1)->origin()==1)bad_from_l_1++;
                if(!treeClass.at(i)->looseLeptons.at(1)->goodLepton() && treeClass.at(i)->looseLeptons.at(1)->origin()==0) bad_unmatched_1++;


                }
               if(treeClass.at(i)->looseLeptons.at(1)->origin()==24 && treeClass.at(i)->looseLeptons.at(1)->goodLepton()){
                if(!treeClass.at(i)->looseLeptons.at(0)->goodLepton() && treeClass.at(i)->looseLeptons.at(0)->origin()==5) bad_from_b_0++;
                if(!treeClass.at(i)->looseLeptons.at(0)->goodLepton() && treeClass.at(i)->looseLeptons.at(0)->origin()==24) bad_from_w_0++;
                if(!treeClass.at(i)->looseLeptons.at(0)->goodLepton() && treeClass.at(i)->looseLeptons.at(0)->origin()==4) bad_from_c_0++;
                if(!treeClass.at(i)->looseLeptons.at(0)->goodLepton() && treeClass.at(i)->looseLeptons.at(0)->origin()==1)bad_from_l_0++;
                if(!treeClass.at(i)->looseLeptons.at(0)->goodLepton() && treeClass.at(i)->looseLeptons.at(0)->origin()==0) bad_unmatched_0++;

                 }
                }     
	    }//MuMu and ElEl condition closed
           else if(b_MuEl){
 	     if(((treeClass.at(i)->looseElecs.at(0)->origin()==24 && 
                  treeClass.at(i)->looseElecs.at(0)->goodElectron()) && 
                  (treeClass.at(i)->looseMuons.at(0)->origin()!=24 && 
                  treeClass.at(i)->looseMuons.at(0)->goodMuon())) || 
                  ((treeClass.at(i)->looseMuons.at(0)->origin()==24 && 
                  treeClass.at(i)->looseMuons.at(0)->goodMuon()) &&
                  (treeClass.at(i)->looseElecs.at(0)->origin()!=24 && 
                  treeClass.at(i)->looseElecs.at(0)->goodElectron()))){
		  observed_events++;	
                  if(treeClass.at(i)->looseElecs.at(0)->origin()==0){
			unmatched_0++;
			}
		      if(treeClass.at(i)->looseElecs.at(0)->origin()==1){
			l_matched_0++;
			}	
		      if(treeClass.at(i)->looseElecs.at(0)->origin()==4){
			c_matched_0++;
			}
                      if(treeClass.at(i)->looseElecs.at(0)->origin()==5){
			b_matched_0++;
			}
                      if(treeClass.at(i)->looseElecs.at(0)->origin()==24){
			w_matched_0++;
			}

                      if(treeClass.at(i)->looseMuons.at(0)->origin()==0){
			unmatched_1++;
			}
		      if(treeClass.at(i)->looseMuons.at(0)->origin()==1){
			l_matched_1++;
			}	
		      if(treeClass.at(i)->looseMuons.at(0)->origin()==4){
			c_matched_1++;
			}
                      if(treeClass.at(i)->looseMuons.at(0)->origin()==5){
			b_matched_1++;
			}
                      if(treeClass.at(i)->looseMuons.at(0)->origin()==24){
			w_matched_1++;
			} 	
             
		
	     }
             if(((treeClass.at(i)->looseElecs.at(0)->origin()==24 && 
                 treeClass.at(i)->looseElecs.at(0)->goodElectron()) &&
                 !treeClass.at(i)->looseMuons.at(0)->goodMuon())){
	         N_events_bad_muons++;
                 double fake_rate=0.284;
                 predicted_events_bad_muons = (fake_rate/(1 - fake_rate))*N_events_bad_muons;
                 if(treeClass.at(i)->looseElecs.at(0)->origin()==24 && treeClass.at(i)->looseElecs.at(0)->goodElectron()){
                   if(!treeClass.at(i)->looseMuons.at(0)->goodMuon() && treeClass.at(i)->looseMuons.at(0)->origin()==5) badMuons_from_b_0++;
                   if(!treeClass.at(i)->looseMuons.at(0)->goodMuon() && treeClass.at(i)->looseMuons.at(0)->origin()==24) badMuons_from_w_0++;
                   if(!treeClass.at(i)->looseMuons.at(0)->goodMuon() && treeClass.at(i)->looseMuons.at(0)->origin()==4) badMuons_from_c_0++;
                   if(!treeClass.at(i)->looseMuons.at(0)->goodMuon() && treeClass.at(i)->looseMuons.at(0)->origin()==1) badMuons_from_l_0++;
                   if(!treeClass.at(i)->looseMuons.at(0)->goodMuon() && treeClass.at(i)->looseMuons.at(0)->origin()==0) badMuons_unmatched_0++;


                                        }


              }//predicted if closed
             if(((treeClass.at(i)->looseMuons.at(0)->origin()==24 && treeClass.at(i)->looseMuons.at(0)->goodMuon()) && (!treeClass.at(i)->looseElecs.at(0)->goodElectron() && treeClass.at(i)->looseElecs.at(0)->origin()!=24))){
                 N_events_bad_electrons++;
                 double fake_rate=0.154;
                 predicted_events_bad_electrons = (fake_rate/(1 - fake_rate))*N_events_bad_electrons;
		 if(treeClass.at(i)->looseMuons.at(0)->origin()==24 && treeClass.at(i)->looseMuons.at(0)->goodMuon()){
                   if(!treeClass.at(i)->looseElecs.at(0)->goodElectron() && treeClass.at(i)->looseElecs.at(0)->origin()==5) badElectrons_from_b_0++;
                   if(!treeClass.at(i)->looseElecs.at(0)->goodElectron() && treeClass.at(i)->looseElecs.at(0)->origin()==24) badElectrons_from_w_0++;
                   if(!treeClass.at(i)->looseElecs.at(0)->goodElectron() && treeClass.at(i)->looseElecs.at(0)->origin()==4) badElectrons_from_c_0++;
                   if(!treeClass.at(i)->looseElecs.at(0)->goodElectron() && treeClass.at(i)->looseElecs.at(0)->origin()==1) badElectrons_from_l_0++;
                   if(!treeClass.at(i)->looseElecs.at(0)->goodElectron() && treeClass.at(i)->looseElecs.at(0)->origin()==0) badElectrons_unmatched_0++;


                                        }

                 }//predicted "if" closed
	      }//b_MuEl requirement	 
	    }//same sign charge requirement for loose leptons
	  }//b_LepCuts/setting multiplicity 	
       }//loop over entries
    }//if statement
  }//loop over samples
  
  
  //couts 
  cout << "observed_events = "  << observed_events  << endl;
  cout << "N_events = " << N_events << endl;
  cout << "predicted_events = " << predicted_events << endl;
  cout << "N_events_bad_electrons = " << N_events_bad_electrons << endl;
  cout << "N_events_bad_muons = " << N_events_bad_muons << endl;
  cout << "unmatched_0 = " << unmatched_0 << endl;
  cout << "predicted_events_bad_muons = " << predicted_events_bad_muons << endl;
  cout << "predicted_events_bad_electrons = " << predicted_events_bad_electrons << endl;
  cout << "unmatched_1 = " << unmatched_1 << endl;
  cout << "l_matched_0 = " << l_matched_0 << endl;
  cout << "l_matched_1 = " << l_matched_1 << endl;
  cout << "c_matched_0 = " << c_matched_0 << endl;
  cout << "c_matched_1 = " << c_matched_1 << endl;
  cout << "b_matched_0 = " << b_matched_0 << endl;
  cout << "b_matched_1 = " << b_matched_1 << endl;
  cout << "w_matched_0 = " << w_matched_0 << endl;
  cout << "w_matched_1 = " << w_matched_1 << endl;
  cout << "bad_unmatched_0 = " << bad_unmatched_0 << endl;
  cout << "bad_unmatched_1 = " << bad_unmatched_1 << endl;
  cout << "bad_from_1_0 = " << bad_from_l_0 << endl;
  cout << "bad_from_1_1 = " << bad_from_l_1 << endl;
  cout << "bad_from_c_0 = " << bad_from_c_0 << endl;
  cout << "bad_from_c_1 = " << bad_from_c_1 << endl;
  cout << "bad_from_b_0 = " << bad_from_b_0 << endl;
  cout << "bad_from_b_1 = " << bad_from_b_1 << endl;
  cout << "bad_from_w_0 = " << bad_from_w_0 << endl;
  cout << "bad_from_w_1 = " << bad_from_w_1 << endl;
  cout << "badMuons_unmatched_0 = " << badMuons_unmatched_0 << endl;
  cout << "badMuons_unmatched_1 = " << badMuons_unmatched_1 << endl;
  cout << "badMuons_from_1_0 = " << badMuons_from_l_0 << endl;
  cout << "badMuons_from_1_1 = " << badMuons_from_l_1 << endl;
  cout << "badMuons_from_c_0 = " << badMuons_from_c_0 << endl;
  cout << "badMuons_from_c_1 = " << badMuons_from_c_1 << endl;
  cout << "badMuons_from_b_0 = " << badMuons_from_b_0 << endl;
  cout << "badMuons_from_b_1 = " << badMuons_from_b_1 << endl;
  cout << "badMuons_from_w_0 = " << badMuons_from_w_0 << endl;
  cout << "badMuons_from_w_1 = " << badMuons_from_w_1 << endl;
  cout << "badElectrons_unmatched_0 = " << badElectrons_unmatched_0 << endl;
  cout << "badElectrons_unmatched_1 = " << badElectrons_unmatched_1 << endl;
  cout << "badElectrons_from_1_0 = " << badElectrons_from_l_0 << endl;
  cout << "badElectrons_from_1_1 = " << badElectrons_from_l_1 << endl;
  cout << "badElectrons_from_c_0 = " << badElectrons_from_c_0 << endl;
  cout << "badElectrons_from_c_1 = " << badElectrons_from_c_1 << endl;
  cout << "badElectrons_from_b_0 = " << badElectrons_from_b_0 << endl;
  cout << "badElectrons_from_b_1 = " << badElectrons_from_b_1 << endl;
  cout << "badElectrons_from_w_0 = " << badElectrons_from_w_0 << endl;
  cout << "badElectrons_from_w_1 = " << badElectrons_from_w_1 << endl;
  h_weight->Draw();
  c->SaveAs("weights.pdf");
  return 0;
}

#endif 
