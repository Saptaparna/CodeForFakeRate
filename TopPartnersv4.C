#ifndef TopPartnersv4_cxx
#define TopPartnersv4_cxx

#include "LoadData_2012.C"
#include "tPrimeStandardHistos.C"
#include "MassAMWT/interface/TopMassVariables.h"
#include "MassAMWT/interface/AMWT.h"
#include <iomanip>
#include "Objects/interface/HcalLaserEventFilter2012.h"
#include "Objects/interface/LumiReWeighting.h"


double misIDprob[15] = {0.00130973,  0.00153928,  0.00154326,  0.000791874, 0.000406848,
			0.00029017,  0.000208527, 0.000161353, 0.000241185, 0.000291503,
			0.000408998, 0.000738134, 0.00144478,  0.00154651,  0.00137379
};

double getChargeMisIdProb(double eta);

int main( int argc, const char* argv[] ){

  int MIN_NBTAG =-1;
  int MIN_HT =0;

  bool b_MuMu = false;
  bool b_ElMu = false;
  bool b_ElEl = false;
  int sign;
  int leptons = 2;
  int year;
  if (argc <5) {
    cout<<"Need 5 arguments:\n";
    cout<<"- dilepton channel (MuMu, MuEl, ElEl)\n";
    cout<<"- signs (OS, LS, TRI)\n";
    cout<<"- year"<<endl;
    cout<<"- sample"<<endl;
    cout<<"- root file name"<<endl;
    return 0;
  }
  HcalLaserEventFilter2012 hcal("./AllBadHCALLaser.txt.gz");

  TString treeSuf;
  string suffix;
  int channel;
  if (strcmp(argv[1],"MuMu")==0) {
    b_MuMu = true;
    channel = 0;
    cout<<"Processing MuMu"<<endl;
    suffix  = "MuMu";
    treeSuf = "mumu";
  } else if ((strcmp(argv[1],"ElMu")==0)||(strcmp(argv[1],"MuEl")==0)) {
    channel = 1;
    b_ElMu = true;
    cout<<"Processing ElMu"<<endl;
    suffix  = "MuEl";
    treeSuf = "muel";
  } else if (strcmp(argv[1],"ElEl")==0) {
    channel = 2;
    b_ElEl = true;
    cout<<"Processing ElEl"<<endl;
    suffix = "ElEl";
    treeSuf = "elel";
  } else {
    cout<<"Dilepton channel must be MuMu/MuEl/ElEl"<<endl;
    return 0;
  }

  if (strcmp(argv[2],"OS")==0) {
    sign = -1;
  } else if (strcmp(argv[2],"SS")==0) {
    sign = +1;
  } else if (strcmp(argv[2],"TRI")==0) {
    sign = 0;
    leptons = 3;
  } else {
    cout<<"Lepton number/sign must be (OS, LS, TRI)"<<endl;
    return 0;
  }
  year = atoi(argv[3]);

  TString sampleName(argv[4]);
  TString fileName(argv[5]);

  cout << "Looking for "<<endl;
  cout << "- Year: " << year<<endl;
  cout << "- dilepton channel "<< suffix<<endl;
  cout << "- signs/leptons "<<sign<<"/"<<leptons<<endl;

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

  std::string generatedFile("/data1/speer/tblsm/pileup/pu_mc.root");
  std::string dataFile("/data1/speer/tblsm/data/DoubleMu2011A/pu_data.root");
  std::string genHistName("PUS10_Distr");
  std::string dataHistName("PUS10_Distr");
  fexists(generatedFile,true);
  fexists(dataFile,true);
  LumiReWeighting lumiReWeighting(generatedFile, dataFile, genHistName, dataHistName);

  //Output file
  char name[300];
  time_t rawtime;
  time ( &rawtime );
  
  sprintf(name,"ptOutFile_%s_%i_%s_%s_%lx.root",argv[2],year, argv[4], suffix.c_str(),rawtime+getpid()+getppid());
  cout << "Output: "<<rawtime<<" "<<getpid()<< " "<<getppid()<<" "<<name<<endl;
  TFile* outFile = new TFile(name, "RECREATE");

  unsigned int nCutSteps = 6;

  vector <TH1F*> h_CutFlow(NSAMPLES);
  vector <TH1F*> h_nSignal;

  vector <StandardHistos*> allCuts_std_h(NSAMPLES);
  vector <StandardHistos*> twoLepAS_std_h(NSAMPLES);
  vector <StandardHistos*> twoLepZQV_std_h(NSAMPLES), twoLepTwoJmet_std_h(NSAMPLES);
  vector <StandardHistos*> twoLepSS_std_h(NSAMPLES);
  vector <StandardHistos*> twoLepSS1B_std_h(NSAMPLES);
  vector <StandardHistos*> twoLepTwoJ_std_h(NSAMPLES), twoLepTwoBJets_std_h(NSAMPLES), twoLepOneBJets_std_h(NSAMPLES);
  vector <StandardHistos*> twoLepFourJ_std_h(NSAMPLES);

  vector <StandardHistos*> LTE2J_std_h(NSAMPLES);
  vector <StandardHistos*> LTE1J_std_h(NSAMPLES);
  vector <StandardHistos*> ZeroJets_std_h(NSAMPLES);

  outFile->cd();

  for (unsigned int i = 0; i < NSAMPLES; i++){
      cout << "init histos "<<i<<" "<<samples[i]<<" "<<sNames[i]<<endl;
    if (samples[i] == FakeRate_Data) continue;

    h_CutFlow.at(i) = new TH1F("h_CutFlow_"+sNames[i]+"_"+suffix, "h_CutFlow_"+sNames[i]+"_"+suffix, nCutSteps, 0.5, nCutSteps + 0.5);
    h_CutFlow.at(i)->Sumw2();

    //Top Level Directory -- all cuts
    allCuts_std_h.at(i) = new StandardHistos("", suffix,sNames[i], sScale[i]);

    //Two Leptons All Signs
    if (i == 0) outFile->mkdir("TwoLeptonsAS");
    outFile->cd("TwoLeptonsAS");
    twoLepAS_std_h.at(i) = new StandardHistos("2L_AS", suffix,sNames[i], sScale[i]);

    outFile->cd();

    //Z and Quarkonia veto
    if (i == 0) outFile->mkdir("TwoLeptonsZQV");
    outFile->cd("TwoLeptonsZQV");
    twoLepZQV_std_h.at(i) = new StandardHistos("2L_ZQV", suffix,sNames[i], sScale[i]);

    outFile->cd();

    //Clean same sign leptons
    if (i == 0) outFile->mkdir("TwoLeptonsSS");
    outFile->cd("TwoLeptonsSS");
    twoLepSS_std_h.at(i) = new StandardHistos("2L_SS", suffix,sNames[i], sScale[i]);

    outFile->cd();

    //Clean same sign leptons + 1 btag
    if (i == 0) outFile->mkdir("TwoLeptonsSS1B");
    outFile->cd("TwoLeptonsSS1B");
    twoLepSS1B_std_h.at(i) = new StandardHistos("2L_SS1B", suffix,sNames[i], sScale[i]);

    outFile->cd();

    double sf=1.;
    //Two or more jets
    if ((samples[i] == ZJets) ||(samples[i] == DY1050)) {
      switch( atoi(argv[1]) ) {
	case 1: sf=1.087; break;
	case 2: sf=1.0; break;
	case 3: sf=1.279; break;
	default: sf=1.0;
      }
    }

    if (i == 0) outFile->mkdir("TwoLTwoJ");
    outFile->cd("TwoLTwoJ");
    twoLepTwoJ_std_h.at(i) = new StandardHistos("2L_2J", suffix,sNames[i], sScale[i]*sf);

    outFile->cd();
    //Two or more jets, with MET
    if (i == 0) outFile->mkdir("TwoLTwoJmet");
    outFile->cd("TwoLTwoJmet");
    if ((samples[i] == ZJets) ||(samples[i] == DY1050)) {
      switch( atoi(argv[1]) ) {
	case 1: sf=1.087; break;
	case 2: sf=1.0; break;
	case 3: sf=1.279; break;
	default: sf=1.0;
      }
    }
    twoLepTwoJmet_std_h.at(i) = new StandardHistos("2L2Jmet", suffix,sNames[i], sScale[i]*sf);

    outFile->cd();

    //Two or more B- jets
    if ((samples[i] == ZJets) ||(samples[i] == DY1050)) {
      switch( atoi(argv[1]) ) {
	case 1: sf=1.43; break;
	case 2: sf=1.0; break;
	case 3: sf=1.070; break;
	default: sf=1.0;
      }
    }
    if (i == 0) outFile->mkdir("TwoLTwoB");
    outFile->cd("TwoLTwoB");
    twoLepTwoBJets_std_h.at(i) = new StandardHistos("2L_2B", suffix,sNames[i], sScale[i]*sf);

    outFile->cd();
    //One or more B- jets
    if ((samples[i] == ZJets) ||(samples[i] == DY1050)) {
      switch( atoi(argv[1]) ) {
	case 1: sf=1.311; break;
	case 2: sf=1.0; break;
	case 3: sf=1.417; break;
	default: sf=1.0;
      }
    }
    if (i == 0) outFile->mkdir("TwoLOneB");
    outFile->cd("TwoLOneB");
    twoLepOneBJets_std_h.at(i) = new StandardHistos("2L_1B", suffix,sNames[i], sScale[i]*sf);

    outFile->cd();

    //Four or more jets
    if (i == 0) outFile->mkdir("TwoLFourJ");
    outFile->cd("TwoLFourJ");
    twoLepFourJ_std_h.at(i) = new StandardHistos("2L_4J", suffix,sNames[i], sScale[i]);

    outFile->cd();

    //Less than or equal to 2 jets
    if (i == 0) outFile->mkdir("LTE2J");
    outFile->cd("LTE2J");
    LTE2J_std_h.at(i) = new StandardHistos("LTE2J", suffix,sNames[i], sScale[i]);

    outFile->cd();

    //Less than or equal to 1 jet
    if (i == 0) outFile->mkdir("LTE1J");
    outFile->cd("LTE1J");
    LTE1J_std_h.at(i) = new StandardHistos("LTE1J", suffix,sNames[i], sScale[i]);

    outFile->cd();

    //Less than or equal to 1 jet
    if (i == 0) outFile->mkdir("ZeroJets");
    outFile->cd("ZeroJets");
    ZeroJets_std_h.at(i) = new StandardHistos("ZeroJets", suffix,sNames[i], sScale[i]);

    outFile->cd();
  }

//   for (unsigned int isam = T53m400; isam < NSAMPLES; isam++){
//     h_nSignal.push_back(new TH1F("h_nSignal_"+sNames[i], "h_nSignal_"+sNames[i], 1, 0.5, 1.5));
//     h_nSignal.at(isam - T53m400)->Sumw2();
//   }
  TH1F* h_bckSum = new TH1F("h_Bckd_Sum", "h_Bckd_Sum", 1, 0.5, 1.5);
  h_bckSum->Sumw2();
  for (unsigned int i = 0; i < NSAMPLES; i++){
    cout << "Looping over "<<sNames[i]<<" "<< treeClass.at(i)->getEntries()<<endl;
    unsigned int isam = samples[i];
    if (isam == FakeRate_Data) continue;
    AMWT amwt((isam == Data));
    float weightCut = 5.0*(isam == Data?10.0:1.0);

    TH1F* h_tmp = new TH1F("h_tmp", "h_tmp", 1, 0.5, 1.5);

   //for (Long64_t il = 0; il < treeClass.at(i)->getEntries(); il++){
   for (Long64_t il = 0; il < 100; il++){
	  //cout << "zz\n";

      treeClass.at(i)->GetEntry(il);
      hcal.filter(treeClass.at(i)->run,treeClass.at(i)->lumi,treeClass.at(i)->event);
// 	if (treeClass.at(i)->run!=191277 || treeClass.at(i)->lumi!=698) continue;

      //Initialize TprimeEvent class
      teve->clearEvent();
      teve->suffix = suffix;
      teve->isam = isam;

/// Review PU:
      if (isam == Data) {
        teve->weight = 1.0;
      } else {
	if (year ==2011) teve->weight = treeClass.at(i)->weight_PU_3D;
	else teve->weight = treeClass.at(i)->weight_PU;
// 	else teve->weight = lumiReWeighting(treeClass.at(i)->weight_PU);
      }
// cout << "lumi weight "<<teve->weight<<"\n";
      

//       if (isam == TTW or isam == TTZ or isam == WWW) teve->weight = 1.0;

      //Tree-level cuts only (2 leptons > 20 GeV, 2 jets > 30 GeV)
      h_CutFlow.at(i)->Fill(1.0, teve->weight);

      //Lepton cuts first

      bool b_LepCuts = false;
      bool b_SSL     = true;
      //cout << "Size = " << treeClass.at(i)->goodLeptons.size()<< endl;
// treeClass.at(i)->nMuons<<
// treeClass.at(i)->allMuons.size()<<treeClass.at(i)->goodElecs.size()<<endl;
// treeClass.at(i)->printEvent();
// cout <<"=======================\n";
      if ((leptons == 2) && (treeClass.at(i)->goodLeptons.size() ==2 )) {

	teve->theLeptons=treeClass.at(i)->goodLeptons;
	
        b_SSL = ((treeClass.at(i)->goodLeptons[0]->charge*treeClass.at(i)->goodLeptons[1]->charge) == sign);
	if (b_MuMu && treeClass.at(i)->dataMM && treeClass.at(i)->dataMM>0 &&
		treeClass.at(i)->goodMuons.size() == 2 && treeClass.at(i)->goodElecs.size() == 0){
	  b_LepCuts = true;
	} else if (b_ElMu && treeClass.at(i)->dataEM && treeClass.at(i)->dataEM>0 &&
		treeClass.at(i)->goodMuons.size() == 1 && treeClass.at(i)->goodElecs.size() == 1){
	  b_LepCuts = true;
	} else if (b_ElEl && treeClass.at(i)->dataEE && treeClass.at(i)->dataEE>0 &&
		treeClass.at(i)->goodMuons.size() == 0 && treeClass.at(i)->goodElecs.size() == 2){
	  b_LepCuts = true;
	}

	if (b_LepCuts and samples[i] == ChargeMisID){
	  teve->weight = 0;
	  if (not teve->lepton1->isMuon()) teve->weight += getChargeMisIdProb(teve->lepton1->lv.Eta());
	  if (not teve->lepton2->isMuon()) teve->weight += getChargeMisIdProb(teve->lepton2->lv.Eta());
	}
      } else if ((leptons == 3) && (treeClass.at(i)->goodLeptons.size() >= 3 )) {
	teve->theLeptons=treeClass.at(i)->goodLeptons;
	b_LepCuts = b_SSL = true;
      }

      if (b_LepCuts) {
//  	cout << "b_LepCuts " <<treeClass.at(i)->goodLeptons[0]->charge << treeClass.at(i)->goodLeptons[1]->charge<<sign
// 	<<  " comp "<<      ((treeClass.at(i)->goodLeptons[0]->charge*treeClass.at(i)->goodLeptons[1]->charge) == sign)
// <<" multi "<<
//         (treeClass.at(i)->goodLeptons[0]->charge*treeClass.at(i)->goodLeptons[1]->charge)
// <<endl;

	teve->lepton1 = treeClass.at(i)->goodLeptons.at(0);
	teve->lepton2 = treeClass.at(i)->goodLeptons.at(1);
	teve->leptonSum = teve->lepton1->lv + teve->lepton2->lv;
	cout << "b_LepCuts " <<teve->lepton1->pt << teve->lepton2->eta<<endl;
      }
cout << "a\n";

     //Jet Cuts
      teve->vGoodJets = treeClass.at(i)->goodJets(teve->theLeptons);
cout << "a\n";

      for (unsigned int ij = 0; ij < teve->vGoodJets.size(); ij++){
	teve->ht += teve->vGoodJets.at(ij)->lv.Pt();
	if (teve->vGoodJets.at(ij)->csvMedium != 0) teve->nBTags++; //Medium
      }
      teve->met = treeClass.at(i)->PF_met_pt;
//       bool b_METcut = true;//teve->met<10;
      bool b_METcut = (b_ElMu || teve->met>40);

      bool b_PassZVeto  = true;
      bool b_MuoniaVeto = true;

      if (samples[i] == ChargeMisID) b_SSL = !b_SSL; //Invert selection for charge misID

      //Lepton cuts -- no charge requirement
      if (b_LepCuts){
	h_CutFlow.at(i)->Fill(2.0, teve->weight);
// 	cout << "a\n";
	twoLepAS_std_h.at(i)->fillAllHistos(teve,treeClass.at(i) );

	//Muonia and Z vetoes
	if (sign==-1) {
	  if (teve->leptonSum.M() < 20) b_MuoniaVeto = false;
 	  if (b_ElEl or b_MuMu){
	    if (teve->leptonSum.M() < 106 and teve->leptonSum.M() > 76) b_PassZVeto = false;
 	  }
	}
      }
//b_PassZVeto = true;
      if (b_LepCuts and b_SSL){
	h_CutFlow.at(i)->Fill(3.0, teve->weight);
	twoLepSS_std_h.at(i)->fillAllHistos(teve,treeClass.at(i) );

	if (teve->nBTags > MIN_NBTAG) twoLepSS1B_std_h.at(i)->fillAllHistos(teve,treeClass.at(i) );
      }

      if (b_LepCuts and b_SSL and b_PassZVeto and b_MuoniaVeto and teve->nBTags > MIN_NBTAG){

        h_CutFlow.at(i)->Fill(4.0, teve->weight);
	twoLepZQV_std_h.at(i)->fillAllHistos(teve,treeClass.at(i) );
	if (teve->vGoodJets.size() >= 2) {
	    h_CutFlow.at(i)->Fill(5.0, teve->weight);
	  twoLepTwoJ_std_h.at(i)->fillAllHistos(teve,treeClass.at(i) );
	  if (b_METcut) {
// 	    TopMassVariables tmv;
// 	    tmv.setLeptons(teve->lepton1->lv, teve->lepton2->lv);
// 	    tmv.setMET(treeClass.at(i)->PF_met_px,treeClass.at(i)->PF_met_py);
// 	    tmv.setJets(teve->vGoodJets.at(0)->lv,teve->vGoodJets.at(1)->lv);
// 	    amwt.findMass(&tmv);
//       printf("Test AMWT: %i / %i / %10.0f\n", treeClass.at(i)->run,treeClass.at(i)->lumi,treeClass.at(i)->event);
// 	    tmv.printAll();
// 	    if (tmv.peakWeight()>weightCut) {
// 	      teve->amwtPeakMass = tmv.peakMass();
// 	      teve->amwtPeakWeight = tmv.peakWeight();
// 	    }

	    twoLepTwoJmet_std_h.at(i)->fillAllHistos(teve,treeClass.at(i) );
	    if (teve->nBTags >= 2) twoLepTwoBJets_std_h.at(i)->fillAllHistos(teve,treeClass.at(i) );
	    if (teve->nBTags >= 1) twoLepOneBJets_std_h.at(i)->fillAllHistos(teve,treeClass.at(i) );
	    


	  }
	  if (teve->vGoodJets.size() <= 2) LTE2J_std_h.at(i)->fillAllHistos(teve,treeClass.at(i) );
	  if (teve->vGoodJets.size() <= 1) LTE1J_std_h.at(i)->fillAllHistos(teve,treeClass.at(i) );
	  if (teve->vGoodJets.size() == 0) ZeroJets_std_h.at(i)->fillAllHistos(teve,treeClass.at(i) );
	}

	if (teve->vGoodJets.size() > 3){
	  h_CutFlow.at(i)->Fill(5.0, teve->weight);
	  twoLepFourJ_std_h.at(i)->fillAllHistos(teve,treeClass.at(i) );

 	  if (teve->ht > MIN_HT){
// 	    if (samples[i] >= T53m400) h_nSignal.at(samples[i] - T53m400)->Fill(1.0, teve->weight);

	    h_tmp->Fill(1.0, teve->weight);

	    if (samples[i] == Data){
	      cout<<"Found data event: "<<treeClass.at(i)->run<<" : "<<treeClass.at(i)->lumi<<" : "<<treeClass.at(i)->event<<endl;
// 	      printEvent(teve);
	    }
	    h_CutFlow.at(i)->Fill(6.0, teve->weight);
	    allCuts_std_h.at(i)->fillAllHistos(teve,treeClass.at(i) );
	  }
	}
      }
    }
    //End loop over entries

    //Add up same sign backgrounds
    if (samples[i] == WZ or samples[i] == ZZ or (samples[i] >= WWm and samples[i] <= TTZ)){
      h_tmp->Scale(sScale.at(i));
      h_bckSum->Add(h_tmp);
    }
    delete h_tmp;
  }
  //End loop over samples

  for (unsigned int i = 0; i < NSAMPLES; i++){
    if (samples[i] != Data and samples[i] != FakeRate_Data and samples[i] != ChargeMisID){
      allCuts_std_h.at(i)->scaleAllHistos();
      twoLepAS_std_h.at(i)->scaleAllHistos();
      twoLepZQV_std_h.at(i)->scaleAllHistos();
      twoLepSS_std_h.at(i)->scaleAllHistos();
      twoLepSS1B_std_h.at(i)->scaleAllHistos();
      twoLepTwoJ_std_h.at(i)->scaleAllHistos();
      twoLepTwoJmet_std_h.at(i)->scaleAllHistos();
      twoLepTwoBJets_std_h.at(i)->scaleAllHistos();
      twoLepOneBJets_std_h.at(i)->scaleAllHistos();
      twoLepFourJ_std_h.at(i)->scaleAllHistos();

      LTE2J_std_h.at(i)->scaleAllHistos();
      LTE1J_std_h.at(i)->scaleAllHistos();
      ZeroJets_std_h.at(i)->scaleAllHistos();
    }
  }

  outFile->Write();
  cout <<"Jobe Done\n";
  return 0;
}

double getChargeMisIdProb(double eta){
  //Translation of eta to index: eta varies from -2.4 to 2.4 in intervals of 0.32
  int ib = (int) ((eta + 2.4) / 0.32);

  //Take care of rounding screwups
  if (ib > 14) ib = 14;
  if (ib < 0 ) ib = 0;

  return misIDprob[ib];
}

#endif
