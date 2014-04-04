#ifndef LooseTopPartnersv4_cxx
#define LooseTopPartnersv4_cxx

#include "LoadData_2012.C"
#include "tPrimeStandardHistos.C"
#include <iomanip>
#include "Objects/interface/HcalLaserEventFilter2012.h"
#include "Objects/interface/LumiReWeighting.h"
#include "MassAMWT/interface/TopMassVariables.h"
#include "MassAMWT/interface/AMWT.h"


using std::cout;
using std::endl;

int main( int argc, const char* argv[] ){


  double PR_MU = 0.942;
  double PR_EL = 0.839;
  double FR_MU = 0.438;
  double FR_EL = 0.267;
  int MIN_NBTAG = -1;
    
  bool b_MuMu = false;
  bool b_MuEl = false;
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
  else if (strcmp(argv[1],"MuEl")==0){
    channel = 1;
    b_MuEl = true;
    cout<<"Processing MuEl"<<endl;
    suffix  = "MuEl";
    treeSuf = "muel";
    
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
    cout<<"Dilepton channel must be MuMu/MuEl/ElEl"<<endl;
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
  
  bool isData = (sampleIndex == Data or sampleIndex == ChargeMisID or sampleIndex == FakeRate);
  bool b_DoFakes  = (sampleIndex == FakeRate);
 
  unsigned int nCutSteps = 6;
  
  outFile->cd();
  int nProc = 0; 
  
  TH1F* h_CutFlow;
  TH1F* h_nSignal;

  TH1F  *topCutFlow = new TH1F("topCutFlow_"+sampleName+"_"+suffix, "topCutFlow_"+sampleName+"_"+suffix, 10, -0.5, 9.5);
  topCutFlow->Sumw2();
  TH1F  *topCutFlowRaw = new TH1F("topCutFlowRaw_"+sampleName+"_"+suffix, "topCutFlowRaw_"+sampleName+"_"+suffix, 10, -0.5, 9.5);
  topCutFlowRaw->Sumw2();
  TH1F  *weight = new TH1F("weight"+sampleName+"_"+suffix, "weight"+sampleName+"_"+suffix, 100, 0., 10.);
  weight->Sumw2();
  
  cout << "init histos "<<sampleIndex<<" "<<sampleName<<endl;
  
  h_CutFlow = new TH1F("h_CutFlow_"+sampleName+"_"+suffix, "h_CutFlow_"+sampleName+"_"+suffix, nCutSteps, -0.5, nCutSteps - 0.5);
  h_CutFlow->Sumw2();
  
  float unitSF[3]={1., 1., 1.};

   //Two Leptons All Signs
  StandardHistos* twoLepAS_std_h = prepareHistos(outFile, "TwoLeptonsAS", "2L_AS", channel, unitSF, b_DoFakes);

  //Clean same sign leptons
  StandardHistos* twoLepSS_std_h = prepareHistos(outFile, "TwoLeptonsSS", "2L_SS", channel, unitSF, b_DoFakes);
  
  //Z and Quarkonia veto
  StandardHistos* twoLepZQV_std_h = prepareHistos(outFile, "TwoLeptonsZQV", "2L_ZQV", channel, unitSF, b_DoFakes);

  //Two or more jets
  float sf2L2J[3]={1.381, 1., 1.315};
  StandardHistos* twoLepTwoJ_std_h = prepareHistos(outFile, "TwoLTwoJ", "2L_2J", channel, sf2L2J, b_DoFakes);

  //Two or more jets with MET
  float sf2L2Jmet[3]={1.696, 1., 1.625};
  StandardHistos* twoLepTwoJmet_std_h = prepareHistos(outFile, "TwoLTwoJmet", "2L_2Jmet", channel, sf2L2Jmet, b_DoFakes);

  //Two or more jets, 1b-tag
  float sf2L2J1B[3]={1.567, 1., 1.518};
  StandardHistos* twoLepOneBJets_std_h = prepareHistos(outFile, "TwoLTwoJ1B", "2L_2J1B", channel, sf2L2J1B, b_DoFakes);

  //Two or more jets, 1b-tag with MET
  float sf2L2J1Bmet[3]={ 1.729, 1., 1.839};
  StandardHistos* twoLepOneBmet_std_h = prepareHistos(outFile, "TwoLTwoJ1Bmet", "2L_2J1Bmet", channel, sf2L2J1Bmet, b_DoFakes);

  //Two or more jets, 2B-tag
  float sf2L2J2B[3]={1.547, 1., 1.493};
  StandardHistos* twoLepTwoBJets_std_h = prepareHistos(outFile, "TwoLTwoJ2B", "2L_2J2B", channel, sf2L2J2B, b_DoFakes);

  //Two or more jets, 2B-tag with MET
  float sf2L2J2Bmet[3]={1.131, 1., 1.318};
  StandardHistos* twoLepTwoBmet_std_h = prepareHistos(outFile, "TwoLTwoJ2Bmet", "2L_2J2Bmet", channel, sf2L2J2Bmet, b_DoFakes);

  //Four or more jets
  StandardHistos* twoLepFourJ_std_h = prepareHistos(outFile, "TwoLFourJ", "2L_4J", channel, unitSF, b_DoFakes);

  //Less than or equal to 2 jets
  StandardHistos* LTE2J_std_h = prepareHistos(outFile, "LTE2J", "LTE2J", channel, unitSF, b_DoFakes);

  //Less than or equal to 1 jet
  StandardHistos* LTE1J_std_h = prepareHistos(outFile, "LTE1J", "LTE1J", channel, unitSF, b_DoFakes);

  // 0 jets
  StandardHistos* ZeroJets_std_h = prepareHistos(outFile, "ZeroJets", "ZeroJets", channel, unitSF, b_DoFakes);

  TH1F* h_bckSum = new TH1F("h_Bckd_Sum", "h_Bckd_Sum", 1, 0.5, 1.5);
  h_bckSum->Sumw2();

  cout << "Looping over "<<sampleName<<" "<< treeClass->getEntries()<<endl;
  AMWT amwt((sampleIndex == Data));
  float weightCut = 0.;//5.0*(sampleIndex == Data?10.0:1.0);

  TH1F* h_tmp = new TH1F("h_tmp", "h_tmp", 1, 0.5, 1.5);

// set cuts:
  double leptonPtCut = 30.;
  treeClass->setLeptonPtCut(leptonPtCut);
  treeClass->setJetPtCut(30.);
      
  for (Long64_t il = 0; il < nEIT; il++){
     
        Long64_t nEIT = treeClass.at(i)->getEntries();
        cout<<"Events to be processed: "<<nEIT<<endl;
        hcal.filter(treeClass->run,treeClass->lumi,treeClass->event);
        treeClass.at(i)->GetEntry(il);
	Long64_t iEvent = (Long64_t)(treeClass.at(i)->event + 0.01);
	if (nProc % 100000 == 0) cout<<"Processed "<<nProc<<" events so far"<<endl;

	nProc++;
        
	//Initialize TprimeEvent class
	teve->clearEvent();
	teve->suffix = suffix;
        teve->isam = sampleIndex;
        TString eventType = "";

    	if (isData) {
      	  teve->weight = 1.0;
    	  } else {
          teve->weight = treeClass->weight_PU_ABC;
    	 }
        h_CutFlow->Fill(0.0, teve->weight);

         bool b_LepCuts = false;
         bool b_LeptonSignCut     = true;

    	 //Select only events which pass the trigger for the channel we are looking at and avoid overlaps for data
         bool b_SelTrigMM = ((!isData || treeClass->dataMM) && treeClass->trigMM > 0);
         bool b_SelTrigEM = ((!isData || treeClass->dataEM) && treeClass->trigEM > 0);
         bool b_SelTrigEE = ((!isData || treeClass->dataEE) && treeClass->trigEE > 0);



        teve->theLeptons=treeClass.at(i)->looseLeptons;
        //Tree-level cuts only (2 leptons > 20 GeV, 2 jets > 30 GeV)
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
        
	else if (b_MuEl && treeClass.at(i)->dataEM && treeClass.at(i)->dataEM>0){
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
	if (b_MuEl and b_LepCuts and teve->lepton1->lv.DeltaR(teve->lepton2->lv) < 0.1) b_LepCuts = false;
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
	
	if (b_LepCuts and b_SSL and b_PassZVeto and b_MuoniaVeto and teve->nBTags > MIN_NBTAG){
	  h_CutFlow.at(i)->Fill(4.0, teve->weight);
          twoLepZQV_std_h.at(i)->fillAllHistos(teve, treeClass.at(i),eventType, true);
	  
	  if (teve->vGoodJets.size() >= 2) twoLepTwoJ_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true);
	  if (teve->vGoodJets.size() <= 2) LTE2J_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true);
	  if (teve->vGoodJets.size() <= 1) LTE1J_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true);
          if (teve->vGoodJets.size() == 0) ZeroJets_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true);
	  if (teve->vGoodJets.size() > 3){
	    h_CutFlow.at(i)->Fill(5.0, teve->weight);
	    twoLepFourJ_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true);
	    
	/*   //   if (teve->ht > MIN_HT){
	     // if (isam >= T53m400) h_nSignal.at(isam - T53m400)->Fill(1.0, teve->weight);
	      
	     // h_CutFlow.at(i)->Fill(6.0, teve->weight);
	     // allCuts_std_h.at(i)->fillAllHistos(teve, treeClass.at(i), eventType, true);
	     // }
	  }
	  
	}*/
      }//end loop over tree entries
    //}//run only for selected SAMPLE
  //}//end loop over SAMPLES
  
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
      allCuts_std_h.at(i)->scaleAllHistos(true);
      twoLepAS_std_h.at(i)->scaleAllHistos(true);
      twoLepZQV_std_h.at(i)->scaleAllHistos(true);
      twoLepSS_std_h.at(i)->scaleAllHistos(true);
      twoLepSS1B_std_h.at(i)->scaleAllHistos(true);
      twoLepTwoJ_std_h.at(i)->scaleAllHistos(true);
      twoLepFourJ_std_h.at(i)->scaleAllHistos(true);
      
      LTE2J_std_h.at(i)->scaleAllHistos(true);
      LTE1J_std_h.at(i)->scaleAllHistos(true);
      ZeroJets_std_h.at(i)->scaleAllHistos(true);
    }
  }
  outFile->Write();
  return EXIT_SUCCESS;
  
}


#endif 
