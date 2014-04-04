#define treetop_cxx
#include "../interface/treetop.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <algorithm>

void treetop::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L treetop.C
//      Root > treetop t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

//    Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<1;jentry++) {
//    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
cout << "Get\n";

   }
}

double treetop::getEntries()
{
  if (entries<0) entries = fChain->GetEntriesFast();
  return entries;
}; 


void treetop::printEvent(int jentry)
{
  GetEntry(jentry);
  printEvent();
}

void treetop::printEvent()
{
  cout << "run / ls / event / goodLumi = " << run << " / "<< lumi<< " / "<< event<< " / "<< goodLumi<<endl;
  cout << "nElectrons = " << nElectrons << endl;
  for (unsigned int i = 0;i<allElecs.size();++i ) allElecs[i]->printLepton();
  cout << "nMuons = " << nMuons << endl;  
  for (unsigned int i = 0;i<allMuons.size();++i ) allMuons[i]->printLepton();
  cout << "nPFjet = " << allJets.size() << endl;  
  for (unsigned int i = 0;i<allJets.size();++i ) allJets[i]->printJet();
cout <<"=======================\n";
}

void treetop::checkLeptons()
{
  goodMuons.clear();
  goodElecs.clear();
  looseMuons.clear();
  looseElecs.clear();
  goodLeptons.clear();
  looseLeptons.clear();  
  lntElecs.clear();
  lntMuons.clear();

  for (unsigned int i = 0;i<allElecs.size();++i ) {
    if (allElecs[i]->goodElectron(30.0))   goodElecs.push_back(allElecs[i]);
    if (allElecs[i]->looseElectron(30.0)) looseElecs.push_back(allElecs[i]);
      }
  for (unsigned int i = 0;i<allMuons.size();++i ) {
    if (allMuons[i]->goodMuon(30.0))   goodMuons.push_back(allMuons[i]);
    if (allMuons[i]->looseMuon(30.0)) looseMuons.push_back(allMuons[i]);
  }

  for (unsigned int i = 0;i<allElecs.size();++i ) {
    if (allElecs[i]->looseElectron(30.0) && (!allElecs[i]->goodElectron(30.0))) lntElecs.push_back(allElecs[i]);
  }

  for (unsigned int i = 0;i<allMuons.size();++i ) {
    if (allMuons[i]->looseMuon(30.0) && (!allMuons[i]->goodMuon(30.0))) lntMuons.push_back(allMuons[i]);
   }



  vector <TLepton*> intLeptons_good;
  intLeptons_good.insert(intLeptons_good.end(), goodElecs.begin(), goodElecs.end());
  intLeptons_good.insert(intLeptons_good.end(), goodMuons.begin(), goodMuons.end());
  sort(intLeptons_good.begin(), intLeptons_good.end(), SortByPt());

  vector <TLepton*> intLeptons_loose;
  intLeptons_loose.insert(intLeptons_loose.end(), looseElecs.begin(), looseElecs.end());
  intLeptons_loose.insert(intLeptons_loose.end(), looseMuons.begin(), looseMuons.end());
  sort(intLeptons_loose.begin(), intLeptons_loose.end(), SortByPt());

  for (unsigned int i = 0;i<intLeptons_good.size();++i ) {
    bool pass=true;
    for (unsigned int j = 0;j<goodLeptons.size();++j )
      if (intLeptons_good[i]->lv.DeltaR(goodLeptons[j]->lv) < 0.1) pass=false;
    if (pass) goodLeptons.push_back(intLeptons_good[i]);
    }

  for (unsigned int i = 0;i<intLeptons_loose.size();++i ) {
    bool pass=true;
    for (unsigned int j = 0;j<looseLeptons.size();++j )
      if (intLeptons_loose[i]->lv.DeltaR(looseLeptons[j]->lv) < 0.1) pass=false;
    if (pass) looseLeptons.push_back(intLeptons_loose[i]);
    }



}

vector <TJet*> treetop::goodJets(const vector <TLepton*> & leptons)
{
  vector <TJet*>  theJets;
  for (unsigned int i = 0;i<allJets.size();++i ) {
    bool answer = true;
    
    for (unsigned int j = 0;j<leptons.size();++j ) 
      if (! allJets[i]->checkJetLeptondR(*leptons[j])) answer = false;
    if (answer) theJets.push_back(allJets[i]);
  }
  
  return theJets;

}

treetop::treetop(const TString &filename)
{
 cout << "Opening: "<<filename<<endl;
  TFile *f = new TFile(filename);
  TTree *tree = (TTree*)gDirectory->Get("ljmet");
  Init(tree);
}

treetop::treetop(TTree *tree)
{
  Init(tree);
}
treetop::~treetop()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t treetop::GetEntry(Long64_t entry)
{
//Clear previous containers:
  for (unsigned int i = 0;i<allMuons.size();++i ) delete allMuons[i];
  for (unsigned int i = 0;i<allElecs.size();++i ) delete allElecs[i];
  for (unsigned int i = 0;i<allJets.size();++i ) delete allJets[i];
  allMuons.clear();
  allElecs.clear();
  allJets.clear();
  

  // Read contents of entry.
  if (!fChain) return 0;
  int stat =  fChain->GetEntry(entry);
  nMuons = muCharge->size();
  nElectrons = elPt->size();
  nPFjet = AK5JetTBag->size();

  std::vector<double>::iterator muMother_ptIt     = (*muMother_pt).begin();
  std::vector<double>::iterator muMother_etaIt    = (*muMother_eta).begin();
  std::vector<double>::iterator muMother_phiIt    = (*muMother_phi).begin();
  std::vector<double>::iterator muMother_energyIt = (*muMother_energy).begin();  
  std::vector<int>::iterator muMother_idIt     = (*muMother_id).begin();
  std::vector<int>::iterator muMother_statusIt = (*muMother_status).begin();   


  for (int i = 0;i<nMuons;++i ) {
    allMuons.push_back(new TLepton((*muCharge)[i], (*muPt)[i],
      (*muEta)[i], (*muPhi)[i], (*muEnergy)[i],
      (*muRelIso)[i], (*muDxy)[i], (*muDz)[i],
      (*muGlobal)[i],(*muNTrackerLayers)[i],
      (*muChi2)[i], (*muNValMuHits)[i], (*muNValPixelHits)[i], (*muNMatchedStations)[i]));
   
   if( (*muNumberOfMothers).size() > 0){
      allMuons.at(i)->SetMatching((*muNumberOfMothers)[i], muMother_ptIt, muMother_etaIt, muMother_phiIt,
      muMother_energyIt, muMother_idIt, muMother_statusIt, 
      (*muPdgId)[i], (*muStatus)[i], (*muMatched)[i], (*muGen_Reco_dr)[i]);
     }
 
  }

  std::vector<double>::iterator elMother_ptIt     = (*elMother_pt).begin();
  std::vector<double>::iterator elMother_etaIt    = (*elMother_eta).begin();
  std::vector<double>::iterator elMother_phiIt    = (*elMother_phi).begin();
  std::vector<double>::iterator elMother_energyIt = (*elMother_energy).begin();  
  std::vector<int>::iterator elMother_idIt     = (*elMother_id).begin();
  std::vector<int>::iterator elMother_statusIt = (*elMother_status).begin();   

 
  for (int i = 0;i<nElectrons;++i) {
    allElecs.push_back(new TLepton((*elCharge)[i], (*elPt)[i],
      (*elEta)[i], (*elPhi)[i], (*elEnergy)[i],
      (*elRelIso)[i], (*elDxy)[i], (*elDZ)[i],
      (*elIsEBEE)[i], (*elQuality)[i], (*elChargeConsistent)[i],
      (*elNotConversion)[i], (*elDeta)[i], (*elDphi)[i], 
      (*elSihih)[i], (*elHoE)[i], (*elD0)[i], (*elOoemoop)[i],
      (*elMHits)[i], (*elNotConversion)[i]));
    
    if((*elNumberOfMothers).size() > 0){
      allElecs.at(i)->SetMatching((*elNumberOfMothers)[i], elMother_ptIt, elMother_etaIt, elMother_phiIt,
      elMother_energyIt, elMother_idIt, elMother_statusIt,
      (*elPdgId)[i], (*elStatus)[i], (*elMatched)[i], (*elGen_Reco_dr)[i]);
    }
    
  }
  
  for (int i = 0;i<nPFjet;++i ) 
    allJets.push_back(new TJet((*AK5JetPt)[i],
      (*AK5JetEta)[i], (*AK5JetPhi)[i], (*AK5JetEnergy)[i], (*AK5JetTBag)[i]));
  PF_met_px = PF_met_pt*cos(PF_met_phi);
  PF_met_py = PF_met_pt*sin(PF_met_phi);

  checkLeptons();
  return stat;
}

Long64_t treetop::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fChain;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void treetop::Init(TTree *tree)
{

  if (!tree) return;

  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  entries = -1;

   AK5JetTBag = 0;
   nTrueInteractions = 0;
   CA8DaughterMotherIndex = 0;
   CA8JetIndex = 0;
   CA8JetnDaughters = 0;
   CATopDaughterMotherIndex = 0;
   CATopJetIndex = 0;
   CATopJetnDaughters = 0;
   elChargeConsistent = 0;
   elCharge = 0;
   elIsEBEE = 0;
   elMHits = 0;
   elNotConversion = 0;
   elQuality = 0;
   elVtxFitConv = 0;
   genID = 0;
   genIndex = 0;
   genMotherID = 0;
   genMotherIndex = 0;
   genStatus = 0;
   muCharge = 0;
   muGlobal = 0;
   muNMatchedStations = 0;
   muNTrackerLayers = 0;
   muNValMuHits = 0;
   muNValPixelHits = 0;
   AK5JetEnergy = 0;
   AK5JetEta = 0;
   AK5JetPhi = 0;
   AK5JetPt = 0;
   CA8DaughterEnergy = 0;
   CA8DaughterEta = 0;
   CA8DaughterPhi = 0;
   CA8DaughterPt = 0;
   CA8JetEnergy = 0;
   CA8JetEta = 0;
   CA8JetMass = 0;
   CA8JetPhi = 0;
   CA8JetPt = 0;
   CATopDaughterEnergy = 0;
   CATopDaughterEta = 0;
   CATopDaughterPhi = 0;
   CATopDaughterPt = 0;
   CATopJetEnergy = 0;
   CATopJetEta = 0;
   CATopJetMinPairMass = 0;
   CATopJetPhi = 0;
   CATopJetPt = 0;
   CATopJetTopMass = 0;
   elD0 = 0;
   elDZ = 0;
   elDeta = 0;
   elDphi = 0;
   elDxy = 0;
   elEnergy = 0;
   elEta = 0;
   elHoE = 0;
   elOoemoop = 0;
   elPhi = 0;
   elPt = 0;
   elRelIso = 0;
   elSihih = 0;
   genEnergy = 0;
   genEta = 0;
   genPhi = 0;
   genPt = 0;
   muChi2 = 0;
   muDxy = 0;
   muDz = 0;
   muEnergy = 0;
   muEta = 0;
   muPhi = 0;
   muPt = 0;
   muRelIso = 0;
   //muon gen information:
   muGen_Reco_dr=0;
   muMother_energy=0;
   muMother_eta=0;
   muMother_phi=0;
   muMother_pt=0;
   muMatched=0;
   muMother_id=0;
   muMother_status=0;
   muPdgId=0;
   muStatus=0;
   muNumberOfMothers=0;
   //electron gen information: 
   elGen_Reco_dr=0;
   elMother_energy=0;
   elMother_eta=0;
   elMother_phi=0;
   elMother_pt=0;
   elMatched=0;
   elMother_id=0;
   elMother_status=0;
   elPdgId=0;
   elStatus=0;
   elNumberOfMothers=0;

//    // Set branch addresses and branch pointers
//    if (!tree) return;
//    fChain = tree;
//    fCurrent = -1;
//    fChain->SetMakeClass(1);
// 

   fChain->SetBranchAddress("run_CommonCalc", &run, &b_run_CommonCalc);
   fChain->SetBranchAddress("lumi_CommonCalc", &lumi, &b_lumi_CommonCalc);
   fChain->SetBranchAddress("event_CommonCalc", &event, &b_event_CommonCalc);

   fChain->SetBranchAddress("bunchXing_PileUpCalc", &bunchXing, &b_bunchXing_PileUpCalc);
   fChain->SetBranchAddress("nInteractions_PileUpCalc", &nInteractions, &b_nInteractions_PileUpCalc);
   fChain->SetBranchAddress("nTrueInteractions_PileUpCalc", &nTrueInteractions, &b_nInteractions_PileUpCalc);
   fChain->SetBranchAddress("dataEE_DileptonCalc", &dataEE, &b_dataEE_DileptonCalc);
   fChain->SetBranchAddress("dataEM_DileptonCalc", &dataEM, &b_dataEM_DileptonCalc);
   fChain->SetBranchAddress("dataMM_DileptonCalc", &dataMM, &b_dataMM_DileptonCalc);
// 
// 
//    fChain->SetBranchAddress("nAllJets_CommonCalc", &nAllJets_CommonCalc, &b_nAllJets_CommonCalc);
//    fChain->SetBranchAddress("nLooseMuons_CommonCalc", &nLooseMuons_CommonCalc, &b_nLooseMuons_CommonCalc);
// 
//    fChain->SetBranchAddress("nSelBtagJets_CommonCalc", &nSelBtagJets_CommonCalc, &b_nSelBtagJets_CommonCalc);
//    fChain->SetBranchAddress("nSelElectrons_CommonCalc", &nSelElectrons_CommonCalc, &b_nSelElectrons_CommonCalc);
//    fChain->SetBranchAddress("nSelJets_CommonCalc", &nSelJets_CommonCalc, &b_nSelJets_CommonCalc);
//    fChain->SetBranchAddress("nTightMuons_CommonCalc", &nTightMuons_CommonCalc, &b_nTightMuons_CommonCalc);
// 
   fChain->SetBranchAddress("trigEE_DileptonCalc", &trigEE, &b_trigEE_DileptonCalc);
   fChain->SetBranchAddress("trigEM_DileptonCalc", &trigEM, &b_trigEM_DileptonCalc);
   fChain->SetBranchAddress("trigMM_DileptonCalc", &trigMM, &b_trigMM_DileptonCalc);

   fChain->SetBranchAddress("corr_met_DileptonCalc", &corr_met, &b_corr_met_DileptonCalc);
   fChain->SetBranchAddress("corr_met_phi_DileptonCalc", &corr_met_phi, &b_corr_met_phi_DileptonCalc);

   fChain->SetBranchAddress("met_DileptonCalc", &PF_met_pt, &b_met_DileptonCalc);
   fChain->SetBranchAddress("met_phi_DileptonCalc", &PF_met_phi, &b_met_phi_DileptonCalc);

   fChain->SetBranchAddress("weight_PU_PileUpCalc", &weight_PU, &b_weight_PU_PileUpCalc);
// 
// //    fChain->SetBranchAddress("CA8DaughterMotherIndex_DileptonCalc", &CA8DaughterMotherIndex_DileptonCalc, &b_CA8DaughterMotherIndex_DileptonCalc);
// //    fChain->SetBranchAddress("CA8JetIndex_DileptonCalc", &CA8JetIndex_DileptonCalc, &b_CA8JetIndex_DileptonCalc);
// //    fChain->SetBranchAddress("CA8JetnDaughters_DileptonCalc", &CA8JetnDaughters_DileptonCalc, &b_CA8JetnDaughters_DileptonCalc);
// //    fChain->SetBranchAddress("CATopDaughterMotherIndex_DileptonCalc", &CATopDaughterMotherIndex_DileptonCalc, &b_CATopDaughterMotherIndex_DileptonCalc);
// //    fChain->SetBranchAddress("CATopJetIndex_DileptonCalc", &CATopJetIndex_DileptonCalc, &b_CATopJetIndex_DileptonCalc);
// //    fChain->SetBranchAddress("CATopJetnDaughters_DileptonCalc", &CATopJetnDaughters_DileptonCalc, &b_CATopJetnDaughters_DileptonCalc);

//    fChain->SetBranchAddress("CA8DaughterEnergy_DileptonCalc", &CA8DaughterEnergy_DileptonCalc, &b_CA8DaughterEnergy_DileptonCalc);
//    fChain->SetBranchAddress("CA8DaughterEta_DileptonCalc", &CA8DaughterEta_DileptonCalc, &b_CA8DaughterEta_DileptonCalc);
//    fChain->SetBranchAddress("CA8DaughterPhi_DileptonCalc", &CA8DaughterPhi_DileptonCalc, &b_CA8DaughterPhi_DileptonCalc);
//    fChain->SetBranchAddress("CA8DaughterPt_DileptonCalc", &CA8DaughterPt_DileptonCalc, &b_CA8DaughterPt_DileptonCalc);
//    fChain->SetBranchAddress("CA8JetEnergy_DileptonCalc", &CA8JetEnergy_DileptonCalc, &b_CA8JetEnergy_DileptonCalc);
//    fChain->SetBranchAddress("CA8JetEta_DileptonCalc", &CA8JetEta_DileptonCalc, &b_CA8JetEta_DileptonCalc);
//    fChain->SetBranchAddress("CA8JetMass_DileptonCalc", &CA8JetMass_DileptonCalc, &b_CA8JetMass_DileptonCalc);
//    fChain->SetBranchAddress("CA8JetPhi_DileptonCalc", &CA8JetPhi_DileptonCalc, &b_CA8JetPhi_DileptonCalc);
//    fChain->SetBranchAddress("CA8JetPt_DileptonCalc", &CA8JetPt_DileptonCalc, &b_CA8JetPt_DileptonCalc);
//    fChain->SetBranchAddress("CATopDaughterEnergy_DileptonCalc", &CATopDaughterEnergy_DileptonCalc, &b_CATopDaughterEnergy_DileptonCalc);
//    fChain->SetBranchAddress("CATopDaughterEta_DileptonCalc", &CATopDaughterEta_DileptonCalc, &b_CATopDaughterEta_DileptonCalc);
//    fChain->SetBranchAddress("CATopDaughterPhi_DileptonCalc", &CATopDaughterPhi_DileptonCalc, &b_CATopDaughterPhi_DileptonCalc);
//    fChain->SetBranchAddress("CATopDaughterPt_DileptonCalc", &CATopDaughterPt_DileptonCalc, &b_CATopDaughterPt_DileptonCalc);
//    fChain->SetBranchAddress("CATopJetEnergy_DileptonCalc", &CATopJetEnergy_DileptonCalc, &b_CATopJetEnergy_DileptonCalc);
//    fChain->SetBranchAddress("CATopJetEta_DileptonCalc", &CATopJetEta_DileptonCalc, &b_CATopJetEta_DileptonCalc);
//    fChain->SetBranchAddress("CATopJetMinPairMass_DileptonCalc", &CATopJetMinPairMass_DileptonCalc, &b_CATopJetMinPairMass_DileptonCalc);
//    fChain->SetBranchAddress("CATopJetPhi_DileptonCalc", &CATopJetPhi_DileptonCalc, &b_CATopJetPhi_DileptonCalc);
//    fChain->SetBranchAddress("CATopJetPt_DileptonCalc", &CATopJetPt_DileptonCalc, &b_CATopJetPt_DileptonCalc);
//    fChain->SetBranchAddress("CATopJetTopMass_DileptonCalc", &CATopJetTopMass_DileptonCalc, &b_CATopJetTopMass_DileptonCalc);


   fChain->SetBranchAddress("elChargeConsistent_DileptonCalc", &elChargeConsistent, &b_elChargeConsistent_DileptonCalc);
   fChain->SetBranchAddress("elCharge_DileptonCalc", &elCharge, &b_elCharge_DileptonCalc);
   fChain->SetBranchAddress("elIsEBEE_DileptonCalc", &elIsEBEE, &b_elIsEBEE_DileptonCalc);
   fChain->SetBranchAddress("elMHits_DileptonCalc", &elMHits, &b_elMHits_DileptonCalc);
   fChain->SetBranchAddress("elNotConversion_DileptonCalc", &elNotConversion, &b_elNotConversion_DileptonCalc);
   fChain->SetBranchAddress("elQuality_DileptonCalc", &elQuality, &b_elQuality_DileptonCalc);
   fChain->SetBranchAddress("elVtxFitConv_DileptonCalc", &elVtxFitConv, &b_elVtxFitConv_DileptonCalc);
   fChain->SetBranchAddress("elD0_DileptonCalc", &elD0, &b_elD0_DileptonCalc);
   fChain->SetBranchAddress("elDZ_DileptonCalc", &elDZ, &b_elDZ_DileptonCalc);
   fChain->SetBranchAddress("elDeta_DileptonCalc", &elDeta, &b_elDeta_DileptonCalc);
   fChain->SetBranchAddress("elDphi_DileptonCalc", &elDphi, &b_elDphi_DileptonCalc);
   fChain->SetBranchAddress("elDxy_DileptonCalc", &elDxy, &b_elDxy_DileptonCalc);
   fChain->SetBranchAddress("elEnergy_DileptonCalc", &elEnergy, &b_elEnergy_DileptonCalc);
   fChain->SetBranchAddress("elEta_DileptonCalc", &elEta, &b_elEta_DileptonCalc);
   fChain->SetBranchAddress("elHoE_DileptonCalc", &elHoE, &b_elHoE_DileptonCalc);
   fChain->SetBranchAddress("elOoemoop_DileptonCalc", &elOoemoop, &b_elOoemoop_DileptonCalc);
   fChain->SetBranchAddress("elPhi_DileptonCalc", &elPhi, &b_elPhi_DileptonCalc);
   fChain->SetBranchAddress("elPt_DileptonCalc", &elPt, &b_elPt_DileptonCalc);
   fChain->SetBranchAddress("elRelIso_DileptonCalc", &elRelIso, &b_elRelIso_DileptonCalc);
   fChain->SetBranchAddress("elSihih_DileptonCalc", &elSihih, &b_elSihih_DileptonCalc);
// 
// //    fChain->SetBranchAddress("genID_DileptonCalc", &genID_DileptonCalc, &b_genID_DileptonCalc);
// //    fChain->SetBranchAddress("genIndex_DileptonCalc", &genIndex_DileptonCalc, &b_genIndex_DileptonCalc);
// //    fChain->SetBranchAddress("genMotherID_DileptonCalc", &genMotherID_DileptonCalc, &b_genMotherID_DileptonCalc);
// //    fChain->SetBranchAddress("genMotherIndex_DileptonCalc", &genMotherIndex_DileptonCalc, &b_genMotherIndex_DileptonCalc);
// //    fChain->SetBranchAddress("genStatus_DileptonCalc", &genStatus_DileptonCalc, &b_genStatus_DileptonCalc);
// 
   fChain->SetBranchAddress("muCharge_DileptonCalc", &muCharge, &b_muCharge_DileptonCalc);
   fChain->SetBranchAddress("muGlobal_DileptonCalc", &muGlobal, &b_muGlobal_DileptonCalc);
   fChain->SetBranchAddress("muNMatchedStations_DileptonCalc", &muNMatchedStations, &b_muNMatchedStations_DileptonCalc);
   fChain->SetBranchAddress("muNTrackerLayers_DileptonCalc", &muNTrackerLayers, &b_muNTrackerLayers_DileptonCalc);
   fChain->SetBranchAddress("muNValMuHits_DileptonCalc", &muNValMuHits, &b_muNValMuHits_DileptonCalc);
   fChain->SetBranchAddress("muNValPixelHits_DileptonCalc", &muNValPixelHits, &b_muNValPixelHits_DileptonCalc);
   fChain->SetBranchAddress("muChi2_DileptonCalc", &muChi2, &b_muChi2_DileptonCalc);
   fChain->SetBranchAddress("muDxy_DileptonCalc", &muDxy, &b_muDxy_DileptonCalc);
   fChain->SetBranchAddress("muDz_DileptonCalc", &muDz, &b_muDz_DileptonCalc);
   fChain->SetBranchAddress("muEnergy_DileptonCalc", &muEnergy, &b_muEnergy_DileptonCalc);
   fChain->SetBranchAddress("muEta_DileptonCalc", &muEta, &b_muEta_DileptonCalc);
   fChain->SetBranchAddress("muPhi_DileptonCalc", &muPhi, &b_muPhi_DileptonCalc);
   fChain->SetBranchAddress("muPt_DileptonCalc", &muPt, &b_muPt_DileptonCalc);
   fChain->SetBranchAddress("muRelIso_DileptonCalc", &muRelIso, &b_muRelIso_DileptonCalc);

   fChain->SetBranchAddress("AK5JetTBag_DileptonCalc", &AK5JetTBag, &b_AK5JetTBag_DileptonCalc);
   fChain->SetBranchAddress("AK5JetEnergy_DileptonCalc", &AK5JetEnergy, &b_AK5JetEnergy_DileptonCalc);
   fChain->SetBranchAddress("AK5JetEta_DileptonCalc", &AK5JetEta, &b_AK5JetEta_DileptonCalc);
   fChain->SetBranchAddress("AK5JetPhi_DileptonCalc", &AK5JetPhi, &b_AK5JetPhi_DileptonCalc);
   fChain->SetBranchAddress("AK5JetPt_DileptonCalc", &AK5JetPt, &b_AK5JetPt_DileptonCalc);
   //matching:
   //electrons:
   fChain->SetBranchAddress("elMother_id_DileptonCalc", &elMother_id, &b_elMother_id_DileptonCalc);
   fChain->SetBranchAddress("elMother_status_DileptonCalc", &elMother_status, &b_elMother_status_DileptonCalc);
   fChain->SetBranchAddress("elMother_energy_DileptonCalc", &elMother_energy, &b_elMother_energy_DileptonCalc);
   fChain->SetBranchAddress("elMother_eta_DileptonCalc", &elMother_eta, &b_elMother_eta_DileptonCalc);
   fChain->SetBranchAddress("elMother_phi_DileptonCalc", &elMother_phi, &b_elMother_phi_DileptonCalc);
   fChain->SetBranchAddress("elMother_pt_DileptonCalc", &elMother_pt, &b_elMother_pt_DileptonCalc);
   fChain->SetBranchAddress("elGen_Reco_dr_DileptonCalc", &elGen_Reco_dr, &b_elGen_Reco_dr_DileptonCalc);
   fChain->SetBranchAddress("elMatched_DileptonCalc", &elMatched, &b_elMatched_DileptonCalc);
   fChain->SetBranchAddress("elPdgId_DileptonCalc", &elPdgId, &b_elPdgId_DileptonCalc);
   fChain->SetBranchAddress("elStatus_DileptonCalc", &elStatus, &b_elStatus_DileptonCalc);
   fChain->SetBranchAddress("elNumberOfMothers_DileptonCalc", &elNumberOfMothers, &b_elNumberOfMothers_DileptonCalc);
   //muons:
   fChain->SetBranchAddress("muMother_id_DileptonCalc", &muMother_id, &b_muMother_id_DileptonCalc);
   fChain->SetBranchAddress("muMother_status_DileptonCalc", &muMother_status, &b_muMother_status_DileptonCalc);
   fChain->SetBranchAddress("muMother_energy_DileptonCalc", &muMother_energy, &b_muMother_energy_DileptonCalc);
   fChain->SetBranchAddress("muMother_eta_DileptonCalc", &muMother_eta, &b_muMother_eta_DileptonCalc);
   fChain->SetBranchAddress("muMother_phi_DileptonCalc", &muMother_phi, &b_muMother_phi_DileptonCalc);
   fChain->SetBranchAddress("muMother_pt_DileptonCalc", &muMother_pt, &b_muMother_pt_DileptonCalc);
   fChain->SetBranchAddress("muGen_Reco_dr_DileptonCalc", &muGen_Reco_dr, &b_muGen_Reco_dr_DileptonCalc);
   fChain->SetBranchAddress("muMatched_DileptonCalc", &muMatched, &b_muMatched_DileptonCalc);
   fChain->SetBranchAddress("muPdgId_DileptonCalc", &muPdgId, &b_muPdgId_DileptonCalc);
   fChain->SetBranchAddress("muStatus_DileptonCalc", &muStatus, &b_muStatus_DileptonCalc);
   fChain->SetBranchAddress("muNumberOfMothers_DileptonCalc", &muNumberOfMothers, &b_muNumberOfMothers_DileptonCalc);
//    fChain->SetBranchAddress("genEnergy_DileptonCalc", &genEnergy_DileptonCalc, &b_genEnergy_DileptonCalc);
//    fChain->SetBranchAddress("genEta_DileptonCalc", &genEta_DileptonCalc, &b_genEta_DileptonCalc);
//    fChain->SetBranchAddress("genPhi_DileptonCalc", &genPhi_DileptonCalc, &b_genPhi_DileptonCalc);
//    fChain->SetBranchAddress("genPt_DileptonCalc", &genPt_DileptonCalc, &b_genPt_DileptonCalc);


//   for (int i = 0;i<4;++i ) {
//     sprintf(str,"muon%i", i);
//     TString m(str);
//     fChain->SetBranchAddress(m+"_Matched_"+treeSuf, &muon[i].matched);
//     fChain->SetBranchAddress(m+"_energy_Matched_"+treeSuf, &muon[i].matchedLepton.energy);
//     fChain->SetBranchAddress(m+"_eta_Matched_"+treeSuf, &muon[i].matchedLepton.eta);
//     fChain->SetBranchAddress(m+"_phi_Matched_"+treeSuf, &muon[i].matchedLepton.phi);
//     fChain->SetBranchAddress(m+"_pt_Matched_"+treeSuf,  &muon[i].matchedLepton.pt);
//     fChain->SetBranchAddress(m+"_gen_reco_DR_"+treeSuf, &muon[i].gen_reco_DR);
//     
//     for (int j = 0;j<10;++j ) {
//       sprintf(str,"muon%i_mother_%i", i,j);
//       TString mother(str);
//       fChain->SetBranchAddress(mother+"_pdgId_"+treeSuf, 	&muon[i].mother[j].pdgID);
//       fChain->SetBranchAddress(mother+"_energy_"+treeSuf, 	&muon[i].mother[j].energy);
//       fChain->SetBranchAddress(mother+"_eta_"+treeSuf, 		&muon[i].mother[j].eta);
//       fChain->SetBranchAddress(mother+"_phi_"+treeSuf, 		&muon[i].mother[j].phi);
//       fChain->SetBranchAddress(mother+"_pt_"+treeSuf, 		&muon[i].mother[j].pt);
//     }*/
//   }
//   
//   //electron
//   for (int i = 0;i<4;++i ) {
//     sprintf(str,"electron%i", i);
//     TString e(str);
//   /*  fChain->SetBranchAddress(e+"_Matched_"+treeSuf, &elec[i].matched);
//     fChain->SetBranchAddress(e+"_energy_Matched_"+treeSuf, &elec[i].matchedLepton.energy);
//     fChain->SetBranchAddress(e+"_eta_Matched_"+treeSuf, &elec[i].matchedLepton.eta);
//     fChain->SetBranchAddress(e+"_phi_Matched_"+treeSuf, &elec[i].matchedLepton.phi);
//     fChain->SetBranchAddress(e+"_pt_Matched_"+treeSuf,  &elec[i].matchedLepton.pt);
//     fChain->SetBranchAddress(e+"_gen_reco_DR_"+treeSuf, &elec[i].gen_reco_DR);
//     
//     for (int j = 0;j<10;++j ) {
//       sprintf(str,"elec%i_mother_%i", i,j);
//       TString mother(str);
//       fChain->SetBranchAddress(mother+"_pdgId_"+treeSuf, 	&elec[i].mother[j].pdgID);
//       fChain->SetBranchAddress(mother+"_energy_"+treeSuf, 	&elec[i].mother[j].energy);
//       fChain->SetBranchAddress(mother+"_eta_"+treeSuf, 		&elec[i].mother[j].eta);
//       fChain->SetBranchAddress(mother+"_phi_"+treeSuf, 		&elec[i].mother[j].phi);
//       fChain->SetBranchAddress(mother+"_pt_"+treeSuf, 		&elec[i].mother[j].pt);
//     }*/
//   }
// // ??    fChain->SetBranchAddress(e+"_pt_Matched_"+treeSuf,  &elec[i].matchedLepton.pt);
// // ??      TString mother("elec"+TString(i)+"_mother_"+TString(j))
  Notify();
}

Bool_t treetop::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.
  
  return kTRUE;
}

void treetop::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t treetop::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
