#ifndef LooseTopPartnersv4_cxx
#define LooseTopPartnersv4_cxx

#include "LoadData_2012.C"
#include "tPrimeStandardHistos.C"
#include <iomanip>
#include "Objects/interface/HcalLaserEventFilter2012.h"
#include "Objects/interface/LumiReWeighting.h"
#include "MassAMWT/interface/TopMassVariables.h"
#include "MassAMWT/interface/AMWT.h"
#include <set>

using std::cout;
using std::endl;

typedef map< unsigned int, set<unsigned int> > LumiEventMapType;
typedef map<unsigned int, LumiEventMapType> RunEventMapType;

RunEventMapType eventMap;
unsigned int prevRun;
unsigned int prevLS;

bool checkEvent(){

 for (unsigned int i = 0; i < NSAMPLES; i++){
    unsigned int isam = samples[i];
    if (samples[i] == FakeRate_Data){
     if (eventMap.empty()) {
      prevRun = prevLS = -1;
     }

     if ((treeClass.at(i)->run!=prevRun) && (eventMap.find(treeClass.at(i)->run) == eventMap.end())) {
      eventMap[treeClass.at(i)->run] = LumiEventMapType();
    }

    if (((treeClass.at(i)->run!=prevRun) || (treeClass.at(i)->lumi!=prevLS))
      && (eventMap[treeClass.at(i)->run].find(treeClass.at(i)->lumi) == eventMap[treeClass.at(i)->run].end())) {
      eventMap[treeClass.at(i)->run][treeClass.at(i)->lumi] = set<unsigned int>();
      eventMap[treeClass.at(i)->run][treeClass.at(i)->lumi].insert(treeClass.at(i)->event);
      prevRun = treeClass.at(i)->run;
      prevLS = treeClass.at(i)->lumi;
    return true;
  }
  prevRun = treeClass.at(i)->run;
  prevLS = treeClass.at(i)->lumi;
  if (eventMap[treeClass.at(i)->run][treeClass.at(i)->lumi].find(treeClass.at(i)->event) != eventMap[treeClass.at(i)->run][treeClass.at(i)->lumi].end()){
    return false;
  }
  eventMap[treeClass.at(i)->run][treeClass.at(i)->lumi].insert(treeClass.at(i)->event);
  return true;
		}//sample selection

	}//NSAMPLES braces
  return EXIT_SUCCESS;
}//close function braces


int main( int argc, const char* argv[] ){


  double PR_MU = 0.942;
  double PR_EL = 0.860;
  double FR_MU = 0.340;
  double FR_EL = 0.240;
  int MIN_NBTAG = 1;
    
  bool b_MuMu = false;
  bool b_ElMu = false;
  bool b_ElEl = false;
  int year;
  if (argc < 5){
    cout<<"Four arguments are required: channel, year, sample name file name"<<endl;
    return 0;

  } 
  
  HcalLaserEventFilter2012 hcal("./AllBadHCALLaser.txt.gz");
    
  TString treeSuf;
  TString suffix;
  
  double f1 = 0;
  double f2 = 0;
  
  double p1 = 0; 
  double p2 = 0;

  int channel;  
  if      (strcmp(argv[1], "MuMu")==0){
    b_MuMu = true;
    channel = 0;
    cout<<"Processing MuMu"<<endl;
    suffix  = "MuMu";
    treeSuf = "mumu";
    
    p1 = PR_MU;
    p2 = PR_MU;
    
    f1 = FR_MU;
    f2 = FR_MU;
  }
  else if (strcmp(argv[1],"ElMu")==0){
    channel = 1;
    b_ElMu = true;
    cout<<"Processing ElMu"<<endl;
    suffix  = "ElMu";
    treeSuf = "elmu";
    
    p1 = PR_EL;
    p2 = PR_MU;
    
    f1 = FR_EL;
    f2 = FR_MU;
  }
  else if (strcmp(argv[1],"ElEl")==0){
    b_ElEl = true;
    channel = 2;
    cout<<"Processing ElEl"<<endl;
    suffix = "ElEl";
    treeSuf = "elel";
    
    p1 = PR_EL;
    p2 = PR_EL;
    
    f1 = FR_EL;
    f2 = FR_EL;
  }
  else{
    cout<<"Dilepton channel must be MuMu/ElMu/ElEl"<<endl;

    return 0;

  }  
  year = atoi(argv[2]);
  TString fileName(argv[4]);
  TString sampleName(argv[3]);
  TprimeEvent * teve = new TprimeEvent();
  if (year ==2011) {
    initAll_2011(treeSuf, fileName, channel, sampleName);
  } else if (year ==2012) {
    initAll_2012(fileName, channel, sampleName);
  } else {
    cout <<"Year has to be 2011 or 2012\n";
    return 0;
  }
  

  
  
  TFile* outFile = new TFile("fkOutFile_"+suffix+".root", "RECREATE");
  
  
  unsigned int nCutSteps = 6;
  
  vector <TH1F*> h_CutFlow(NSAMPLES);
  vector <TH1F*> h_nSignal;
  
  vector <StandardHistos*> allCuts_std_h(NSAMPLES);
  vector <StandardHistos*> twoLepAS_std_h(NSAMPLES);
  vector <StandardHistos*> twoLepZQV_std_h(NSAMPLES);
  vector <StandardHistos*> twoLepSS_std_h(NSAMPLES);
  vector <StandardHistos*> twoLepSS1B_std_h(NSAMPLES);
  vector <StandardHistos*> twoLepTwoJ_std_h(NSAMPLES);
  vector <StandardHistos*> twoLepFourJ_std_h(NSAMPLES);
  vector <StandardHistos*> LTE2J_std_h(NSAMPLES);
  vector <StandardHistos*> LTE1J_std_h(NSAMPLES); 
  vector <StandardHistos*> ZeroJets_std_h(NSAMPLES);
  vector <StandardHistos*> twoLepOneBJets_std_h(NSAMPLES);
  vector <StandardHistos*> twoLepOneBmet_std_h(NSAMPLES);
  vector <StandardHistos*> twoLepTwoBmet_std_h(NSAMPLES);
  vector <StandardHistos*> twoLepTwoBJets_std_h(NSAMPLES);
   
  outFile->cd();
  int nProc = 0; 
  
  for (unsigned int i = 0; i < NSAMPLES; i++){
    
    if(samples[i]==FakeRate_Data) {
      h_CutFlow.at(i) = new TH1F("h_CutFlow_"+sNames[i]+"_"+suffix, "h_CutFlow_"+sNames[i]+"_"+suffix, nCutSteps, 0.5, nCutSteps + 0.5);
      h_CutFlow.at(i)->Sumw2();
      
      //Top Level Directory -- all cuts
      allCuts_std_h.at(i) = new StandardHistos("", suffix, sNames[i], sScale[i], true); 
      
      //Two Leptons All Signs
      if(i==0) outFile->mkdir("TwoLeptonsAS");
      outFile->cd("TwoLeptonsAS");
      twoLepAS_std_h.at(i) = new StandardHistos("2L_AS", suffix, sNames[i], sScale[i], true);
      
      outFile->cd();
      
      //Z and Quarkonia veto
      if (i==0) outFile->mkdir("TwoLeptonsZQV");
      outFile->cd("TwoLeptonsZQV");
      twoLepZQV_std_h.at(i) = new StandardHistos("2L_ZQV", suffix, sNames[i], sScale[i], true);	
      
      outFile->cd();
      
      //Clean same sign leptons
      if(i==0) outFile->mkdir("TwoLeptonsSS");
      outFile->cd("TwoLeptonsSS");
      twoLepSS_std_h.at(i) = new StandardHistos("2L_SS", suffix, sNames[i], sScale[i], true);
      
      outFile->cd();
      
      //Clean same sign leptons + 1 btag
      if(i==0) outFile->mkdir("TwoLeptonsSS1B");
      outFile->cd("TwoLeptonsSS1B");
      twoLepSS1B_std_h.at(i) = new StandardHistos("2L_SS1B", suffix, sNames[i], sScale[i], true);
      
      outFile->cd();
      
      //Two or more jets
      if(i==0) outFile->mkdir("TwoLTwoJ");
      outFile->cd("TwoLTwoJ");
      twoLepTwoJ_std_h.at(i) = new StandardHistos("2L_2J", suffix, sNames[i], sScale[i], true);
      
      outFile->cd();
      
      //Four or more jets
      if(i==0) outFile->mkdir("TwoLFourJ");
      outFile->cd("TwoLFourJ");
      twoLepFourJ_std_h.at(i) = new StandardHistos("2L_4J", suffix, sNames[i], sScale[i], true);
      
      outFile->cd();
      
      //Less than or equal to 2 jets
      if(i==0) outFile->mkdir("LTE2J");
      outFile->cd("LTE2J");
      LTE2J_std_h.at(i) = new StandardHistos("LTE2J", suffix, sNames[i], sScale[i], true);
      
      outFile->cd();
      
      //Less than or equal to 1 jet
      if(i==0) outFile->mkdir("LTE1J");
      outFile->cd("LTE1J");
      LTE1J_std_h.at(i) = new StandardHistos("LTE1J", suffix, sNames[i], sScale[i], true);
      
      outFile->cd();
      
      //Zero jets
      if(i==0) outFile->mkdir("ZeroJets");
      outFile->cd("ZeroJets");
      ZeroJets_std_h.at(i) = new StandardHistos("ZeroJets", suffix, sNames[i], sScale[i], true);
      
      outFile->cd();
    
     //extra dirs added to make plots
   
     if(i==0) outFile->mkdir("TwoLTwoJ1B");
     outFile->cd("TwoLTwoJ1B");
     twoLepOneBJets_std_h.at(i) = new StandardHistos("2L_2J1B", suffix, sNames[i], sScale[i], true);

     if(i==0) outFile->mkdir("TwoLTwoJ2B");
     outFile->cd("TwoLTwoJ2B");
     twoLepTwoBJets_std_h.at(i) = new StandardHistos("2L_2J2B", suffix, sNames[i], sScale[i], true);

     if(i==0) outFile->mkdir("TwoLTwoJ1Bmet");
     outFile->cd("TwoLTwoJ1Bmet");
     twoLepOneBmet_std_h.at(i) = new StandardHistos("2L_2J1Bmet", suffix, sNames[i], sScale[i], true);
 
     if(i==0) outFile->mkdir("TwoLTwoJ2Bmet");
     outFile->cd("TwoLTwoJ2Bmet");
     twoLepTwoBmet_std_h.at(i) = new StandardHistos("2L_2J2Bmet", suffix, sNames[i], sScale[i], true);


    }//run only for selected SAMPLE
   }//end loop over SAMPLES
  
  
  for (unsigned int i = 0; i < NSAMPLES; i++){
    unsigned int isam = samples[i];
    if (samples[i] == FakeRate_Data){ 
      
      Long64_t nEIT = treeClass.at(i)->getEntries();
      cout<<"Events to be processed: "<<nEIT<<endl;
      
      
      Long64_t iEvent = (Long64_t)(treeClass.at(i)->event + 0.01);
      
      
      for (Long64_t il = 0; il < nEIT; il++){
        treeClass.at(i)->GetEntry(il);
	if (nProc % 100000 == 0) cout<<"Processed "<<nProc<<" events so far"<<endl;

	nProc++;
        
	//Initialize TprimeEvent class
	teve->clearEvent();
	teve->suffix = suffix;
	teve->isam = isam;
      
	//if (isData){
    	 if (!checkEvent()) {
      	  continue;
    		}
      	//}
        teve->weight = 1.0;//treeClass.at(i)->weight_PU_3D;
      
        teve->theLeptons=treeClass.at(i)->looseLeptons;
        //Tree-level cuts only (2 leptons > 20 GeV, 2 jets > 30 GeV)
        h_CutFlow.at(i)->Fill(1.0, teve->weight);	
	//Reject events with more than two tight leptons
	
	bool b_LepCuts = false;
        if (treeClass.at(i)->goodMuons.size() + treeClass.at(i)->goodElecs.size() > 2) continue;
	TString eventType = "";
        if (b_MuMu and treeClass.at(i)->dataMM && treeClass.at(i)->dataMM>0 && treeClass.at(i)->lntElecs.size() == 0 and treeClass.at(i)->goodElecs.size() == 0){
	  if (treeClass.at(i)->goodMuons.size() == 2){
	    eventType = "Nt11";
            teve->lepton1 = treeClass.at(i)->goodMuons.at(0);
	    teve->lepton2 = treeClass.at(i)->goodMuons.at(1);
            b_LepCuts = true;
	  }
	  else if (treeClass.at(i)->goodMuons.size() == 1 and treeClass.at(i)->lntMuons.size() > 0){
            eventType = "Nt01";
	    //cout<<"Found event: "<<treeClass.at(i)->run<<" : "<<treeClass.at(i)->lumi<<" : "<<treeClass.at(i)->event<<endl;
            teve->lepton1  = treeClass.at(i)->lntMuons.at(0);
	    teve->lepton2  = treeClass.at(i)->goodMuons.at(0);
	    
	    b_LepCuts = true;
	  }
	  else if (treeClass.at(i)->goodMuons.size() == 0 and treeClass.at(i)->lntMuons.size() > 1){
	    eventType = "Nt00";
            teve->lepton1  = treeClass.at(i)->lntMuons.at(0);
	    teve->lepton2  = treeClass.at(i)->lntMuons.at(1);
	    
	    b_LepCuts = true;
	  }
	 else if (treeClass.at(i)->lntMuons.size() == 0 and treeClass.at(i)->goodMuons.size() == 0){
	    //cout << "No good nor loose-not-good found" << endl;
            b_LepCuts = false;
	 }
	}
        
	else if (b_ElMu && treeClass.at(i)->dataEM && treeClass.at(i)->dataEM>0){
	  if (treeClass.at(i)->goodMuons.size() == 1 and treeClass.at(i)->goodElecs.size() == 1){
	    eventType = "Nt11";
	    
	    teve->lepton1  = treeClass.at(i)->goodMuons.at(0);
	    teve->lepton2  = treeClass.at(i)->goodElecs.at(0);
	    
	    b_LepCuts = true;
	  }
	  else if (treeClass.at(i)->goodMuons.size() == 1 and treeClass.at(i)->goodElecs.size() == 0 and treeClass.at(i)->lntElecs.size() > 0){
	    eventType = "Nt01";
	    
	    teve->lepton1  = treeClass.at(i)->goodMuons.at(0);
	    teve->lepton2  = treeClass.at(i)->lntElecs.at(0);
	    
	    b_LepCuts = true;
	  }
	  else if (treeClass.at(i)->goodElecs.size() == 1 and treeClass.at(i)->goodMuons.size() == 0 and treeClass.at(i)->lntMuons.size() > 0){
	    eventType = "Nt10";
	    
	    teve->lepton1  = treeClass.at(i)->lntMuons.at(0);
	    teve->lepton2  = treeClass.at(i)->goodElecs.at(0);
	    
	    b_LepCuts = true;
	  }
	  else if (treeClass.at(i)->goodElecs.size() == 0 and treeClass.at(i)->goodMuons.size() == 0 and treeClass.at(i)->lntMuons.size() > 0 and treeClass.at(i)->lntElecs.size() > 0){
	    eventType = "Nt00";
	    
	    teve->lepton1  = treeClass.at(i)->lntMuons.at(0);
	    teve->lepton2  = treeClass.at(i)->lntElecs.at(0);
	    
	    b_LepCuts = true;
	  }
	}
	
	else if (b_ElEl and treeClass.at(i)->dataEE && treeClass.at(i)->dataEE>0 and treeClass.at(i)->lntMuons.size() == 0 and treeClass.at(i)->goodMuons.size() == 0){
	  if (treeClass.at(i)->goodElecs.size() == 2){
	    eventType = "Nt11";
	    
	    teve->lepton1  = treeClass.at(i)->goodElecs.at(0);
	    teve->lepton2  = treeClass.at(i)->goodElecs.at(1);
	    
	    b_LepCuts = true;
	  }
	  else if (treeClass.at(i)->goodElecs.size() == 1 and treeClass.at(i)->lntElecs.size() > 0){
	    eventType = "Nt01";
	    
	    teve->lepton1  = treeClass.at(i)->lntElecs.at(0);
	    teve->lepton2  = treeClass.at(i)->goodElecs.at(0);
	    
	    b_LepCuts = true;
	  }
	  else if (treeClass.at(i)->goodElecs.size() == 0 and treeClass.at(i)->lntElecs.size() > 1){
	    eventType = "Nt00";
	    
	    teve->lepton1  = treeClass.at(i)->lntElecs.at(0);
	    teve->lepton2  = treeClass.at(i)->lntElecs.at(1);
	    
	    b_LepCuts = true;
	  }
	}
	
	//Make sure not to count same lepton as electron and muon
	if (b_ElMu and b_LepCuts and teve->lepton1->lv.DeltaR(teve->lepton2->lv) < 0.1) b_LepCuts = false;
        if(b_LepCuts){  teve->leptonSum = teve->lepton1->lv + teve->lepton2->lv;
	  //Sort leptons by pt
	  if (teve->lepton2->lv.Pt() > teve->lepton1->lv.Pt()){
	    TLepton* tmpTprimeL = teve->lepton1;
	  
	    teve->lepton1 = teve->lepton2;
	    teve->lepton2 = tmpTprimeL;
	  }
	
	teve->vGoodJets = treeClass.at(i)->goodJets(teve->theLeptons);    
	
	for (unsigned int ij = 0; ij < teve->vGoodJets.size(); ij++){
	  teve->ht += teve->vGoodJets.at(ij)->lv.Pt();
	  if (teve->vGoodJets.at(ij)->csvMedium != 0) teve->nBTags++; //Medium
	 }
        }
	//cout << "teve->nBTags = " << teve->nBTags << endl; 
	bool b_SSL        = true; 
        if(b_LepCuts){b_SSL = (teve->lepton1->charge == teve->lepton2->charge);}
	bool b_PassZVeto  = true;
	bool b_MuoniaVeto = true;
	
	if (b_LepCuts){
	  h_CutFlow.at(i)->Fill(2.0, teve->weight);
	  twoLepAS_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true); 
	  //Muonia and Z vetoes		
	  if(teve->leptonSum.M() < 20) b_MuoniaVeto = false;
	  if (b_ElEl or b_MuMu){
	    if(teve->leptonSum.M() < 106 and teve->leptonSum.M() > 76) b_PassZVeto = false;
	  }
	}
	
	if (b_LepCuts and b_SSL){
	  h_CutFlow.at(i)->Fill(3.0, teve->weight);
	  twoLepSS_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true);
	  
	  if (teve->nBTags > MIN_NBTAG) twoLepSS1B_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true);
	}
	
	//if (b_LepCuts and b_SSL and b_PassZVeto and b_MuoniaVeto){// and teve->nBTags > MIN_NBTAG){
	  if (b_LepCuts and b_SSL){
          h_CutFlow.at(i)->Fill(4.0, teve->weight);
          twoLepZQV_std_h.at(i)->fillAllHistos(teve, treeClass.at(i),eventType, true);
	  
	  if (teve->vGoodJets.size() >= 2) twoLepTwoJ_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true);
	  if (teve->vGoodJets.size() <= 2) LTE2J_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true);
	  if (teve->vGoodJets.size() <= 1) LTE1J_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true);
          if (teve->vGoodJets.size() == 0) ZeroJets_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true);

          cout << "teve->nBTags = " << teve->nBTags << endl;	  
          if(teve->vGoodJets.size() >= 2 && teve->nBTags >= 1 )twoLepOneBJets_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true);
          if(teve->vGoodJets.size() >= 2 && teve->nBTags >= 2 )twoLepTwoBJets_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true); 
          if((b_ElMu || teve->met > 30) && teve->nBTags >= 1)twoLepOneBmet_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true);
          if((b_ElMu || teve->met > 30) && teve->nBTags >= 2)twoLepTwoBmet_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true);
	  if (teve->vGoodJets.size() > 3){
	    h_CutFlow.at(i)->Fill(5.0, teve->weight);
	    twoLepFourJ_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true);
	    
	   /*   if (teve->ht > MIN_HT){
	      if (isam >= T53m400) h_nSignal.at(isam - T53m400)->Fill(1.0, teve->weight);
	      
	      h_CutFlow.at(i)->Fill(6.0, teve->weight);
	      allCuts_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true);
	      }*/
	  }
	  
	}
      }//end loop over tree entries
    }//run only for selected SAMPLE
  }//end loop over SAMPLES
  
  for (unsigned int i = 0; i < NSAMPLES; i++){
    unsigned int isam = samples[i];  
    if(samples[i]==FakeRate_Data) {
      allCuts_std_h.at(i)    ->getTotFakes(f1, f2, p1, p2);
      twoLepAS_std_h.at(i)   ->getTotFakes(f1, f2, p1, p2);
      twoLepZQV_std_h.at(i)  ->getTotFakes(f1, f2, p1, p2);
      twoLepSS_std_h.at(i)   ->getTotFakes(f1, f2, p1, p2);
      twoLepSS1B_std_h.at(i) ->getTotFakes(f1, f2, p1, p2);
      twoLepTwoJ_std_h.at(i) ->getTotFakes(f1, f2, p1, p2);
      twoLepFourJ_std_h.at(i)->getTotFakes(f1, f2, p1, p2);
      LTE2J_std_h.at(i)->getTotFakes(f1, f2, p1, p2);
      LTE1J_std_h.at(i)->getTotFakes(f1, f2, p1, p2);
      ZeroJets_std_h.at(i)->getTotFakes(f1, f2, p1, p2);
      twoLepOneBJets_std_h.at(i)->getTotFakes(f1, f2, p1, p2);
      twoLepTwoBJets_std_h.at(i)->getTotFakes(f1, f2, p1, p2);
      twoLepOneBmet_std_h.at(i)->getTotFakes(f1, f2, p1, p2);
      twoLepTwoBmet_std_h.at(i)->getTotFakes(f1, f2, p1, p2);
      allCuts_std_h.at(i)->scaleAllHistos(true);
      twoLepAS_std_h.at(i)->scaleAllHistos(true);
      twoLepZQV_std_h.at(i)->scaleAllHistos(true);
      twoLepSS_std_h.at(i)->scaleAllHistos(true);
      twoLepSS1B_std_h.at(i)->scaleAllHistos(true);
      twoLepTwoJ_std_h.at(i)->scaleAllHistos(true);
      twoLepFourJ_std_h.at(i)->scaleAllHistos(true);
      twoLepOneBJets_std_h.at(i)->scaleAllHistos(true);
      twoLepTwoBJets_std_h.at(i)->scaleAllHistos(true);
      twoLepOneBmet_std_h.at(i)->scaleAllHistos(true);
      twoLepTwoBmet_std_h.at(i)->scaleAllHistos(true);
      LTE2J_std_h.at(i)->scaleAllHistos(true);
      LTE1J_std_h.at(i)->scaleAllHistos(true);
      ZeroJets_std_h.at(i)->scaleAllHistos(true);
    }
  }
  outFile->Write();
  return EXIT_SUCCESS;
  
}


#endif 
