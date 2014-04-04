#ifndef GetFakeRate_cxx
#define GetFakeRate_cxx

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
  
  int MIN_BTAG_FR =-1; 
  bool b_MuMu = false;
  bool b_ElEl = false;
  int year;  
  if (argc < 5){
    cout<<"Four arguments are required: channel, year, sample name file name and mother (if MC) "<<endl;
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
  } else if (strcmp(argv[1],"ElEl")==0) {
    channel = 2;
    b_ElEl = true;
    cout<<"Processing ElEl"<<endl;
    suffix = "ElEl";
    treeSuf = "elel";
  } else {
    cout<<"Dilepton channel must be MuMu/ElEl"<<endl;
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
  
  int mother = atoi(argv[5]); 
  //if(sampleName==FakeRate_Data){
    //mother = 10;

//	}
  cout << "Init LumiReWeighting"<<endl;
  
  std::string generatedFile("/data1/speer/tblsm/tools/data/pu_mc.root");
  std::string dataFile("/data1/speer/tblsm/tools/data/pu_data.root");
  std::string genHistName("PUS10_Distr");
  std::string dataHistName("PUS10_Distr");
  fexists(generatedFile,true);
  fexists(dataFile,true);
  LumiReWeighting lumiReWeighting(generatedFile, dataFile, genHistName, dataHistName);
  
  cout << "Done lumi reweighting" << endl;
  //Output file
  TFile* outFile = new TFile("gfOutFile_"+sampleName+"_"+suffix+"_"+long(mother)+".root", "RECREATE");
  
  
  unsigned int nCutSteps = 6;
  
  vector <TH1F*> h_CutFlow(NSAMPLES);
  
  
  vector <StandardHistosFR*>  LL_stdfr_h(NSAMPLES);
  vector <StandardHistosFR*>  BLS_stdfr_h(NSAMPLES);
  vector <StandardHistosFR*>  LJZV_stdfr_h(NSAMPLES);
  vector <StandardHistosFR*>  CSVM_stdfr_h(NSAMPLES);
  vector <StandardHistosFR*>  CSVMnoTop_stdfr_h(NSAMPLES);
  vector <StandardHistosFR*>  B2BLJ_stdfr_h(NSAMPLES); 
  vector <StandardHistosFR*>  VBTAG_stdfr_h(NSAMPLES);
  
  TH1D* LElec_RelIso = new TH1D("LElec_RelIso", "LElec_RelIso", 100, 0.0, 10.0);
  TH1D* TElec_RelIso = new TH1D("TElec_RelIso", "TElec_RelIso", 100, 0.0, 10.0);
  TH1D* LMuon_RelIso = new TH1D("LMuon_RelIso", "LMuon_RelIso", 100, 0.0, 10.0);
  TH1D* TMuon_RelIso = new TH1D("TMuon_RelIso", "TMuon_RelIso", 100, 0.0, 10.0);

 
  int nProc = 0;
  int nRawEvents = 0;
  int nLooseLeptons = 0;
  int nLepPtCut = 0;
  int nAwayJet =0;
  int nMET=0;
  int nMT=0;
  int nZveto =0;
  int nTightLeptons = 0;
  outFile->cd();
  cout << "Before the loop over samples" << endl;  

  for (unsigned int i = 0; i < NSAMPLES; i++){
    if (samples[i] == FakeRate_Data){// || samples[i] == FakeRate_MC ){   
      cout << "Looping over "<<sNames[i]<<" "<< treeClass.at(i)->getEntries()<<endl;    
      h_CutFlow.at(i) = new TH1F("h_CutFlow_"+sNames[i]+"_"+suffix, "h_CutFlow_"+sNames[i]+"_"+suffix, nCutSteps, 0.5, nCutSteps + 0.5);
      h_CutFlow.at(i)->Sumw2();
      
      //Exactly one loose lepton
      if(i==0) outFile->mkdir("LL");
      outFile->cd("LL");
      LL_stdfr_h.at(i) = new StandardHistosFR("LL", suffix, sNames[i], sScale[i]);
      
      outFile->cd();
      
      //Baseline selection: away jet with pt of 40 GeV, MET < 25, transverse mass < 25
      if(i==0) outFile->mkdir("BLS");
      outFile->cd("BLS");
      BLS_stdfr_h.at(i) = new StandardHistosFR("BLS", suffix, sNames[i], sScale[i]);
      
      outFile->cd();
      
      //Lepton-Jet Z-veto
      if(i==0) outFile->mkdir("LJZV");
      outFile->cd("LJZV");
      LJZV_stdfr_h.at(i) = new StandardHistosFR("LJZV", suffix, sNames[i], sScale[i]);
      
      outFile->cd();
      
      //At least one CSVM jet
      if(i==0) outFile->mkdir("CSVM");
      outFile->cd("CSVM");
      CSVM_stdfr_h.at(i) = new StandardHistosFR("CSVM", suffix, sNames[i], sScale[i]);
      
      outFile->cd();
      
      //At least one CSVM jet and M(b,l) < 130 or M(b, l) > 180
      if(i==0) outFile->mkdir("CSVMnoTop");
      outFile->cd("CSVMnoTop");
      CSVMnoTop_stdfr_h.at(i) = new StandardHistosFR("CSVMnoTop", suffix, sNames[i], sScale[i]);
      
      outFile->cd();
      
      //Back to back jets
      if(i==0) outFile->mkdir("B2BLJ");
      outFile->cd("B2BLJ");
      B2BLJ_stdfr_h.at(i) = new StandardHistosFR("B2BLJ", suffix, sNames[i], sScale[i]);
      
      
      outFile->cd();
      
      //BTag veto
      if(i==0) outFile->mkdir("VBTAG");
      outFile->cd("VBTAG");
      VBTAG_stdfr_h.at(i) = new StandardHistosFR("VBTAG", suffix, sNames[i], sScale[i]);
      
      outFile->cd();
    }
  }
  cout << "Histograms created" << endl;
  for (unsigned int i = 0; i < NSAMPLES; i++){
    
    unsigned int isam = samples[i]; 
    if (samples[i] == FakeRate_Data){// || samples[i] == FakeRate_MC ){
      
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
        //cout << "treeClass.at(i)->looseLeptons.size() = " << treeClass.at(i)->looseLeptons.size() << endl;

        if ((treeClass.at(i)->looseLeptons.size() ==1 )){ 
	  teve->lepton1=treeClass.at(i)->looseLeptons.at(0);
          if (b_ElEl)  {
 	    if(treeClass.at(i)->looseElecs.size() == 1 && treeClass.at(i)->looseMuons.size() == 0){// && treeClass.at(i)->dataEE && treeClass.at(i)->dataEE>0){
               //cout << "treeClass.at(i)->looseElecs.size() = " << treeClass.at(i)->looseElecs.size() << endl;
               //if(samples[i]==FakeRate_Data){
		//b_LepCuts=true;
		//}
              //cout << "treeClass.at(i)->looseElecs.at(0)->origin() = " << treeClass.at(i)->looseElecs.at(0)->origin() << endl;
              if(treeClass.at(i)->looseElecs.at(0)->origin()==mother){	
                 //cout << "treeClass.at(i)->looseElecs.at(0)->origin() = " << treeClass.at(i)->looseElecs.at(0)->origin() << endl;
                 b_LepCuts = true;
	      }	
	    }	
	  }
	   else if(b_MuMu && treeClass.at(i)->looseMuons.size() == 1 && treeClass.at(i)->looseElecs.size() == 0){// && treeClass.at(i)->dataMM && treeClass.at(i)->dataMM>0){
                 //if(samples[i]==FakeRate_Data){
		  // b_LepCuts=true;
	        //	}
                 if(treeClass.at(i)->looseMuons.at(0)->origin()==mother){
		   b_LepCuts = true;
	       } 
	   }
	 }	
         
	
	if ((treeClass.at(i)->goodLeptons.size() ==1)){
          teve->lepton1 = treeClass.at(i)->goodLeptons.at(0);
	  if(b_ElEl) {
            if(treeClass.at(i)->goodElecs.size() == 1 && treeClass.at(i)->goodMuons.size() == 0){// && treeClass.at(i)->dataEE && treeClass.at(i)->dataEE>0){
             //if(samples[i]==FakeRate_Data){
	       //b_Tight=true;	
	     //}	
             if(treeClass.at(i)->goodElecs.at(0)->origin()==mother){ 
	       b_Tight=true;
	     }
             //if(samples[i]==FakeRate_MC){ good_matched->Fill(treeClass.at(i)->goodElecs.at(0)->matched);}
	   }
	  }
	  else if(b_MuMu){// && treeClass.at(i)->dataMM && treeClass.at(i)->dataMM>0){
		if( treeClass.at(i)->goodMuons.size() == 1 && treeClass.at(i)->goodElecs.size() == 0){
		  //if(samples[i]==FakeRate_Data){
                  //b_Tight=true; 
                  //} 
                  if(treeClass.at(i)->goodMuons.at(0)->origin()==mother){
 	  	  b_Tight=true;
		 }	 
	     }
	  }
	}
	
	if(b_LepCuts){
	  nLooseLeptons++;
	  teve->lepton1 = treeClass.at(i)->looseLeptons.at(0); 
	  teve->theLeptons=treeClass.at(i)->looseLeptons; 
	  teve->met = treeClass.at(i)->PF_met_pt;
	  teve->nPV = treeClass.at(i)->nPV;
	  teve->met_phi = treeClass.at(i)->PF_met_phi; 
	  if(year==2011){
          	teve->weight = treeClass.at(i)->weight_PU_3D;
	  }	
          else{  teve->weight = 1.0;}
	  //Avi's max pt cut -- can go a little higher for electrons, but not for muons
	  //if (teve->lepton1->lv.Pt() > 35.) continue;
	  //Jet Cuts
          //cout << "teve->lepton1->lv.Pt() = " << teve->lepton1->lv.Pt() << endl;	
          nLepPtCut++;
   	  //cout<<"Found data event: "<<treeClass.at(i)->run<<" : "<<treeClass.at(i)->lumi<<" : "<<long(treeClass.at(i)->event)<<endl;
          teve->vGoodJets = treeClass.at(i)->goodJets(teve->theLeptons);
	  //Require an away jet with dR > 1
	  bool b_AwayJet = false;
	  bool b_ZVeto   = false;
	  bool b_TTbar   = false;
	  
	  bool b_b2bJL   = false;
	    
	  double maxLJinvMass = 0;
	    
	  vector <double> lepJetMass;
	/*  bool b_Z = false;
	 
           for (unsigned int il = 0; il < treeClass.at(i)->allElecs.size(); il++){
              double mz = (teve->lepton1->lv + treeClass.at(i)->allElecs.at(il)->lv).M();
              if (mz < 106 and mz > 76){
                 b_Z = true;
                 break;
                  }

            }

            for (unsigned int il = 0; il < treeClass.at(i)->allMuons.size(); il++){
              double mz = (teve->lepton1->lv + treeClass.at(i)->allMuons.at(il)->lv).M();
              if (mz < 106 and mz > 76){
                 b_Z = true;
                 break;
                  } 

            } 

          if(b_Z) continue;*/


          for (unsigned int ij = 0; ij < teve->vGoodJets.size(); ij++){
	    
          teve->ht += teve->vGoodJets.at(ij)->lv.Pt();
	    if (teve->vGoodJets.at(ij)->csvMedium != 0) teve->nBTags++; //Medium
	    
	    TLorentzVector vlj = teve->vGoodJets.at(ij)->lv + teve->lepton1->lv;
	   
            
            lepJetMass.push_back(vlj.M());
	    if (teve->vGoodJets.at(ij)->lv.DeltaR(teve->lepton1->lv) > 1 and teve->vGoodJets.at(ij)->lv.Pt() > 40){ 
	      b_AwayJet = true;
	    }
	    
	    if (vlj.M() > maxLJinvMass) maxLJinvMass = vlj.M();
	    
	      if (vlj.M() > 76 and vlj.M() < 106) b_ZVeto = true;
	      
	      if (cos(teve->vGoodJets.at(ij)->lv.DeltaPhi(teve->lepton1->lv)) < -0.99) b_b2bJL = true;
	  }
	  
	  double dphi = fabs(teve->met_phi - teve->lepton1->lv.Phi());
	  
	  if (dphi > TMath::Pi()) dphi = TMath::TwoPi() - dphi;
	  
            teve->met = treeClass.at(i)->PF_met_pt;
	    double mt2 = 2 * teve->lepton1->lv.Pt() * teve->met * (1 - cos(dphi));;
	    
	    teve->mt  = sqrt(mt2);
	    
	    LL_stdfr_h.at(i)->fillTLHistos(teve, treeClass.at(i), b_Tight);
	    
	    //Before cuts = 1;
	    
	    h_CutFlow.at(i)->Fill(1.0, teve->weight);
	    
	    //if (not b_AwayJet)  continue;
	    
	    nAwayJet++;
	    
	    h_CutFlow.at(i)->Fill(2.0, teve->weight);
	    
	    //if (teve->met > 25) continue;
	    nMET++;
	    h_CutFlow.at(i)->Fill(3.0, teve->weight);
	    
	    //if (sqrt(mt2) > 25) continue;
	    nMT++;
	    h_CutFlow.at(i)->Fill(4.0, teve->weight);
	    
	    //End of baseline selection
	    
	    
	    BLS_stdfr_h.at(i)->fillTLHistos(teve, treeClass.at(i), b_Tight);
	    
	    if (b_b2bJL) B2BLJ_stdfr_h.at(i)->fillTLHistos(teve, treeClass.at(i), b_Tight);
	    
	    //if (not (b_ZVeto)){// || samples[i]==FakeRate_Data)){
	      LJZV_stdfr_h.at(i)->fillTLHistos(teve, treeClass.at(i), b_Tight);
	      if(b_ElEl) LElec_RelIso->Fill(teve->lepton1->relIso);
              if(b_MuMu) LMuon_RelIso->Fill(teve->lepton1->relIso);
              nZveto++;
              if(b_Tight){
                nTightLeptons++;
                if(b_ElEl) TElec_RelIso->Fill(teve->lepton1->relIso);
                if(b_MuMu) TMuon_RelIso->Fill(teve->lepton1->relIso);
              }
            //}
            //     if (nBTags >= MIN_NBTAG_FR and not b_ZVeto){
            if (teve->nBTags >= MIN_BTAG_FR){
	      CSVM_stdfr_h.at(i)->fillTLHistos(teve, treeClass.at(i), b_Tight);
	      
	      if (not b_TTbar) CSVMnoTop_stdfr_h.at(i)->fillTLHistos(teve, treeClass.at(i), b_Tight);
	    }
	    if (teve->nBTags == 0){
	      VBTAG_stdfr_h.at(i)->fillTLHistos(teve, treeClass.at(i), b_Tight);
	    }
           //if(b_ElEl) LElec_RelIso->Fill(teve->lepton1->relIso);
           //if(b_MuMu) LMuon_RelIso->Fill(teve->lepton1->relIso);
	   //if(b_Tight){
	     //nTightLeptons++;	
             //if(b_ElEl) TElec_RelIso->Fill(teve->lepton1->relIso);
             //if(b_MuMu) TMuon_RelIso->Fill(teve->lepton1->relIso);

		//}
	}//b_LepCuts	
      }//End of "if" statement
    }//End loop over tree entries
  }//End loop over NSAMPLES 
  
  
  for (unsigned int i = 0; i < NSAMPLES; i++){
    unsigned int isam = samples[i]; 
    if (samples[i] == FakeRate_Data){// || samples[i] == FakeRate_MC ){    
        LL_stdfr_h.at(i)->scaleTLHistos(teve);
	LL_stdfr_h.at(i)->getRatioHistos(teve);
	
	BLS_stdfr_h.at(i)->scaleTLHistos(teve);
	BLS_stdfr_h.at(i)->getRatioHistos(teve);
	
	LJZV_stdfr_h.at(i)->scaleTLHistos(teve);
	LJZV_stdfr_h.at(i)->getRatioHistos(teve);
	
	CSVM_stdfr_h.at(i)->scaleTLHistos(teve);
	CSVM_stdfr_h.at(i)->getRatioHistos(teve);
	
	CSVMnoTop_stdfr_h.at(i)->scaleTLHistos(teve);
	CSVMnoTop_stdfr_h.at(i)->getRatioHistos(teve);
	
	B2BLJ_stdfr_h.at(i)->scaleTLHistos(teve);
	B2BLJ_stdfr_h.at(i)->getRatioHistos(teve);
	
	VBTAG_stdfr_h.at(i)->scaleTLHistos(teve);
	VBTAG_stdfr_h.at(i)->getRatioHistos(teve);
        	
	h_CutFlow.at(i)->Scale(sScale.at(i));
	cout << "nRawEvents = " << nRawEvents << endl;
        cout << "nLooseLeptons = " << nLooseLeptons << endl;
        cout << "nLepPtCut = " << nLepPtCut << endl;      
	cout << "nAwayJet = " << nAwayJet<< endl;
        cout << "nMET = " << nMET << endl;
	cout << "nMT = " << nMT << endl;
        cout << "nZveto = " << nZveto << endl;	
        cout << "nTightLeptons = " << nTightLeptons << endl;
        cout << "fake_rate = " << double(nTightLeptons)/double(nZveto); 
	}
  }	
  outFile->Write();
  return 0;
  }

#endif
