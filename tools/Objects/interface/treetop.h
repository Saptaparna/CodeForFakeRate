//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Aug 13 03:17:52 2012 by ROOT version 5.27/06b
// from TTree treetop/treetop
// found on file: TTbar_Aug13_all.root
//////////////////////////////////////////////////////////

#ifndef treetop_h
#define treetop_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include "TLepton.h"
#include <stdio.h>


class treetop {
 public :
   struct SortByPt {
       bool operator()(const TLepton *e1, const TLepton *e2) {
           return (e1->lv.Pt() < e1->lv.Pt());
       }
   };


  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  vector <TLepton*> allMuons, allElecs, goodMuons, goodElecs, looseMuons, looseElecs, lntMuons, lntElecs;
  vector<TJet *> allJets;
  // The goodLeptons is orderd in pT and overlaps are cleaned (dR<0.1)
  vector <TLepton*> goodLeptons, looseLeptons;
  
  vector <TJet*> goodJets(const vector <TLepton*> & leptons);
  //int goodLeptons();
  
  
  //to remove:
  Int_t goodLumi;
//
  Int_t           run, lumi, event;
  
  Int_t           nPV;
  Int_t           nPFjet;
  Int_t           nElectrons;
  Int_t           nMuons;

  Int_t           event_flavor; // Flavour of the leading jet
  Int_t           n_Bjets, n_Cjets, n_Lightjets;
  
// Pile-up reqeighting: 
  Double_t        weight_PU_3D_73mb;
  Double_t        weight_PU_3D;
  Double_t        weight_PU_3D_shiftDown_73mb;
  Double_t        weight_PU_3D_shiftDown;
  Double_t        weight_PU_3D_shiftUp_73mb;
  Double_t        weight_PU_3D_shiftUp;
  Double_t        weight_PU_RootFile;
  Double_t        weight_PU;

// MET
  Double_t        PF_met_phi;
  Double_t        PF_met_pt;
  Double_t        PF_met_px;
  Double_t        PF_met_py;
//   Double_t        PF_met_sumEt;
   Double_t        corr_met;
   Double_t        corr_met_phi;


// Primary vertex
  Double_t        Nchi2PV;
  Double_t        PV1Z;
  Double_t        PV2Z;
  Double_t        PV3Z;
  Double_t        PV4Z;
  Double_t        chi2PV;
  Double_t        ndofPV;

   // Declaration of leaf types
   Int_t           bunchXing;
   Int_t           dataEE;
   Int_t           dataEM;
   Int_t           dataMM;
   Int_t           event_CommonCalc;
   Int_t           nAllJets_CommonCalc;
   Int_t           nInteractions, nTrueInteractions;
   Int_t           nLooseMuons_CommonCalc;
   Int_t           nSelBtagJets_CommonCalc;
   Int_t           nSelElectrons_CommonCalc;
   Int_t           nSelJets_CommonCalc;
   Int_t           nTightMuons_CommonCalc;
   Int_t           run_CommonCalc;
   Int_t           trigEE;
   Int_t           trigEM;
   Int_t           trigMM;
   vector<int>     *AK5JetTBag;
   vector<int>     *CA8DaughterMotherIndex;
   vector<int>     *CA8JetIndex;
   vector<int>     *CA8JetnDaughters;
   vector<int>     *CATopDaughterMotherIndex;
   vector<int>     *CATopJetIndex;
   vector<int>     *CATopJetnDaughters;
   vector<int>     *elChargeConsistent;
   vector<int>     *elCharge;
   vector<int>     *elIsEBEE;
   vector<int>     *elMHits;
   vector<int>     *elNotConversion;
   vector<int>     *elQuality;
   vector<int>     *elVtxFitConv;
   vector<int>     *genID;
   vector<int>     *genIndex;
   vector<int>     *genMotherID;
   vector<int>     *genMotherIndex;
   vector<int>     *genStatus;
   vector<int>     *muCharge;
   vector<int>     *muGlobal;
   vector<int>     *muNMatchedStations;
   vector<int>     *muNTrackerLayers;
   vector<int>     *muNValMuHits;
   vector<int>     *muNValPixelHits;
   vector<double>  *AK5JetEnergy;
   vector<double>  *AK5JetEta;
   vector<double>  *AK5JetPhi;
   vector<double>  *AK5JetPt;
   vector<double>  *CA8DaughterEnergy;
   vector<double>  *CA8DaughterEta;
   vector<double>  *CA8DaughterPhi;
   vector<double>  *CA8DaughterPt;
   vector<double>  *CA8JetEnergy;
   vector<double>  *CA8JetEta;
   vector<double>  *CA8JetMass;
   vector<double>  *CA8JetPhi;
   vector<double>  *CA8JetPt;
   vector<double>  *CATopDaughterEnergy;
   vector<double>  *CATopDaughterEta;
   vector<double>  *CATopDaughterPhi;
   vector<double>  *CATopDaughterPt;
   vector<double>  *CATopJetEnergy;
   vector<double>  *CATopJetEta;
   vector<double>  *CATopJetMinPairMass;
   vector<double>  *CATopJetPhi;
   vector<double>  *CATopJetPt;
   vector<double>  *CATopJetTopMass;
   vector<double>  *elD0;
   vector<double>  *elDZ;
   vector<double>  *elDeta;
   vector<double>  *elDphi;
   vector<double>  *elDxy;
   vector<double>  *elEnergy;
   vector<double>  *elEta;
   vector<double>  *elHoE;
   vector<double>  *elOoemoop;
   vector<double>  *elPhi;
   vector<double>  *elPt;
   vector<double>  *elRelIso;
   vector<double>  *elSihih;
   vector<double>  *genEnergy;
   vector<double>  *genEta;
   vector<double>  *genPhi;
   vector<double>  *genPt;
   vector<double>  *muChi2;
   vector<double>  *muDxy;
   vector<double>  *muDz;
   vector<double>  *muEnergy;
   vector<double>  *muEta;
   vector<double>  *muPhi;
   vector<double>  *muPt;
   vector<double>  *muRelIso;
   //mother information:
   //muon gen information:
   vector<double>  *muGen_Reco_dr;  
   vector<double>  *muMother_energy; 
   vector<double>  *muMother_eta;
   vector<double>  *muMother_phi;
   vector<double>  *muMother_pt;
   vector<int>     *muMatched;
   vector<int>     *muMother_id;
   vector<int>     *muMother_status;
   vector<int>     *muPdgId;
   vector<int>     *muStatus;
   vector<int>     *muNumberOfMothers;
   //electron gen information: 
   vector<double>  *elGen_Reco_dr;
   vector<double>  *elMother_energy;
   vector<double>  *elMother_eta;
   vector<double>  *elMother_phi;
   vector<double>  *elMother_pt;
   vector<int>     *elMatched;
   vector<int>     *elMother_id;
   vector<int>     *elMother_status;
   vector<int>     *elPdgId;
   vector<int>     *elStatus;
   vector<int>     *elNumberOfMothers;

   // List of branches
   TBranch        *b_bunchXing_PileUpCalc;   //!
   TBranch        *b_dataEE_DileptonCalc;   //!
   TBranch        *b_dataEM_DileptonCalc;   //!
   TBranch        *b_dataMM_DileptonCalc;   //!
   TBranch        *b_event_CommonCalc;   //!
   TBranch        *b_jet_0_flavor_WprimeCalc;   //!
   TBranch        *b_jet_0_tag_WprimeCalc;   //!
   TBranch        *b_jet_1_flavor_WprimeCalc;   //!
   TBranch        *b_jet_1_tag_WprimeCalc;   //!
   TBranch        *b_jet_2_flavor_WprimeCalc;   //!
   TBranch        *b_jet_2_tag_WprimeCalc;   //!
   TBranch        *b_jet_3_flavor_WprimeCalc;   //!
   TBranch        *b_jet_3_tag_WprimeCalc;   //!
   TBranch        *b_jet_4_flavor_WprimeCalc;   //!
   TBranch        *b_jet_4_tag_WprimeCalc;   //!
   TBranch        *b_jet_5_flavor_WprimeCalc;   //!
   TBranch        *b_jet_5_tag_WprimeCalc;   //!
   TBranch        *b_jet_6_flavor_WprimeCalc;   //!
   TBranch        *b_jet_6_tag_WprimeCalc;   //!
   TBranch        *b_jet_7_flavor_WprimeCalc;   //!
   TBranch        *b_jet_7_tag_WprimeCalc;   //!
   TBranch        *b_jet_8_flavor_WprimeCalc;   //!
   TBranch        *b_jet_8_tag_WprimeCalc;   //!
   TBranch        *b_jet_9_flavor_WprimeCalc;   //!
   TBranch        *b_jet_9_tag_WprimeCalc;   //!
   TBranch        *b_lumi_CommonCalc;   //!
   TBranch        *b_nAllJets_CommonCalc;   //!
   TBranch        *b_nInteractions_PileUpCalc;   //!
   TBranch        *b_nLooseMuons_CommonCalc;   //!
   TBranch        *b_nPV_WprimeCalc;   //!
   TBranch        *b_nSelBtagJets_CommonCalc;   //!
   TBranch        *b_nSelElectrons_CommonCalc;   //!
   TBranch        *b_nSelJets_CommonCalc;   //!
   TBranch        *b_nTightMuons_CommonCalc;   //!
   TBranch        *b_n_Bjets_WprimeCalc;   //!
   TBranch        *b_n_Cjets_WprimeCalc;   //!
   TBranch        *b_n_btags_WprimeCalc;   //!
   TBranch        *b_run_CommonCalc;   //!
   TBranch        *b_trigEE_DileptonCalc;   //!
   TBranch        *b_trigEM_DileptonCalc;   //!
   TBranch        *b_trigMM_DileptonCalc;   //!
   TBranch        *b_bjet_1_pt_StopCalc;   //!
   TBranch        *b_bjet_2_pt_StopCalc;   //!
   TBranch        *b_corr_met_DileptonCalc;   //!
   TBranch        *b_corr_met_WprimeCalc;   //!
   TBranch        *b_corr_met_phi_DileptonCalc;   //!
   TBranch        *b_corr_met_phi_WprimeCalc;   //!
   TBranch        *b_elec_1_RelIso_WprimeCalc;   //!
   TBranch        *b_elec_1_eta_WprimeCalc;   //!
   TBranch        *b_elec_1_phi_WprimeCalc;   //!
   TBranch        *b_elec_1_pt_WprimeCalc;   //!
   TBranch        *b_ht_StopCalc;   //!
   TBranch        *b_jet_0_eta_WprimeCalc;   //!
   TBranch        *b_jet_0_phi_WprimeCalc;   //!
   TBranch        *b_jet_0_pt_WprimeCalc;   //!
   TBranch        *b_jet_1_eta_WprimeCalc;   //!
   TBranch        *b_jet_1_phi_WprimeCalc;   //!
   TBranch        *b_jet_1_pt_StopCalc;   //!
   TBranch        *b_jet_1_pt_WprimeCalc;   //!
   TBranch        *b_jet_2_eta_WprimeCalc;   //!
   TBranch        *b_jet_2_phi_WprimeCalc;   //!
   TBranch        *b_jet_2_pt_StopCalc;   //!
   TBranch        *b_jet_2_pt_WprimeCalc;   //!
   TBranch        *b_jet_3_eta_WprimeCalc;   //!
   TBranch        *b_jet_3_phi_WprimeCalc;   //!
   TBranch        *b_jet_3_pt_StopCalc;   //!
   TBranch        *b_jet_3_pt_WprimeCalc;   //!
   TBranch        *b_jet_4_eta_WprimeCalc;   //!
   TBranch        *b_jet_4_phi_WprimeCalc;   //!
   TBranch        *b_jet_4_pt_StopCalc;   //!
   TBranch        *b_jet_4_pt_WprimeCalc;   //!
   TBranch        *b_jet_5_eta_WprimeCalc;   //!
   TBranch        *b_jet_5_phi_WprimeCalc;   //!
   TBranch        *b_jet_5_pt_WprimeCalc;   //!
   TBranch        *b_jet_6_eta_WprimeCalc;   //!
   TBranch        *b_jet_6_phi_WprimeCalc;   //!
   TBranch        *b_jet_6_pt_WprimeCalc;   //!
   TBranch        *b_jet_7_eta_WprimeCalc;   //!
   TBranch        *b_jet_7_phi_WprimeCalc;   //!
   TBranch        *b_jet_7_pt_WprimeCalc;   //!
   TBranch        *b_jet_8_eta_WprimeCalc;   //!
   TBranch        *b_jet_8_phi_WprimeCalc;   //!
   TBranch        *b_jet_8_pt_WprimeCalc;   //!
   TBranch        *b_jet_9_eta_WprimeCalc;   //!
   TBranch        *b_jet_9_phi_WprimeCalc;   //!
   TBranch        *b_jet_9_pt_WprimeCalc;   //!
   TBranch        *b_met_DileptonCalc;   //!
   TBranch        *b_met_StopCalc;   //!
   TBranch        *b_met_WprimeCalc;   //!
   TBranch        *b_met_phi_DileptonCalc;   //!
   TBranch        *b_met_phi_StopCalc;   //!
   TBranch        *b_met_phi_WprimeCalc;   //!
   TBranch        *b_mlb1_StopCalc;   //!
   TBranch        *b_mlb2_StopCalc;   //!
   TBranch        *b_mt_StopCalc;   //!
   TBranch        *b_muon_1_RelIso_WprimeCalc;   //!
   TBranch        *b_muon_1_eta_WprimeCalc;   //!
   TBranch        *b_muon_1_phi_StopCalc;   //!
   TBranch        *b_muon_1_phi_WprimeCalc;   //!
   TBranch        *b_muon_1_pt_StopCalc;   //!
   TBranch        *b_muon_1_pt_WprimeCalc;   //!
   TBranch        *b_type1corrmet_WprimeCalc;   //!
   TBranch        *b_type1corrmet_phi_WprimeCalc;   //!
   TBranch        *b_weight_MuonEff_WprimeCalc;   //!
   TBranch        *b_weight_PU_PileUpCalc;   //!
   TBranch        *b_weight_WJets_WprimeCalc;   //!
   TBranch        *b_AK5JetTBag_DileptonCalc;   //!
   TBranch        *b_CA8DaughterMotherIndex_DileptonCalc;   //!
   TBranch        *b_CA8JetIndex_DileptonCalc;   //!
   TBranch        *b_CA8JetnDaughters_DileptonCalc;   //!
   TBranch        *b_CATopDaughterMotherIndex_DileptonCalc;   //!
   TBranch        *b_CATopJetIndex_DileptonCalc;   //!
   TBranch        *b_CATopJetnDaughters_DileptonCalc;   //!
   TBranch        *b_elChargeConsistent_DileptonCalc;   //!
   TBranch        *b_elCharge_DileptonCalc;   //!
   TBranch        *b_elIsEBEE_DileptonCalc;   //!
   TBranch        *b_elMHits_DileptonCalc;   //!
   TBranch        *b_elNotConversion_DileptonCalc;   //!
   TBranch        *b_elQuality_DileptonCalc;   //!
   TBranch        *b_elVtxFitConv_DileptonCalc;   //!
   TBranch        *b_genID_DileptonCalc;   //!
   TBranch        *b_genIndex_DileptonCalc;   //!
   TBranch        *b_genMotherID_DileptonCalc;   //!
   TBranch        *b_genMotherIndex_DileptonCalc;   //!
   TBranch        *b_genStatus_DileptonCalc;   //!
   TBranch        *b_muCharge_DileptonCalc;   //!
   TBranch        *b_muGlobal_DileptonCalc;   //!
   TBranch        *b_muNMatchedStations_DileptonCalc;   //!
   TBranch        *b_muNTrackerLayers_DileptonCalc;   //!
   TBranch        *b_muNValMuHits_DileptonCalc;   //!
   TBranch        *b_muNValPixelHits_DileptonCalc;   //!
   TBranch        *b_AK5JetEnergy_DileptonCalc;   //!
   TBranch        *b_AK5JetEta_DileptonCalc;   //!
   TBranch        *b_AK5JetPhi_DileptonCalc;   //!
   TBranch        *b_AK5JetPt_DileptonCalc;   //!
   TBranch        *b_CA8DaughterEnergy_DileptonCalc;   //!
   TBranch        *b_CA8DaughterEta_DileptonCalc;   //!
   TBranch        *b_CA8DaughterPhi_DileptonCalc;   //!
   TBranch        *b_CA8DaughterPt_DileptonCalc;   //!
   TBranch        *b_CA8JetEnergy_DileptonCalc;   //!
   TBranch        *b_CA8JetEta_DileptonCalc;   //!
   TBranch        *b_CA8JetMass_DileptonCalc;   //!
   TBranch        *b_CA8JetPhi_DileptonCalc;   //!
   TBranch        *b_CA8JetPt_DileptonCalc;   //!
   TBranch        *b_CATopDaughterEnergy_DileptonCalc;   //!
   TBranch        *b_CATopDaughterEta_DileptonCalc;   //!
   TBranch        *b_CATopDaughterPhi_DileptonCalc;   //!
   TBranch        *b_CATopDaughterPt_DileptonCalc;   //!
   TBranch        *b_CATopJetEnergy_DileptonCalc;   //!
   TBranch        *b_CATopJetEta_DileptonCalc;   //!
   TBranch        *b_CATopJetMinPairMass_DileptonCalc;   //!
   TBranch        *b_CATopJetPhi_DileptonCalc;   //!
   TBranch        *b_CATopJetPt_DileptonCalc;   //!
   TBranch        *b_CATopJetTopMass_DileptonCalc;   //!
   TBranch        *b_elD0_DileptonCalc;   //!
   TBranch        *b_elDZ_DileptonCalc;   //!
   TBranch        *b_elDeta_DileptonCalc;   //!
   TBranch        *b_elDphi_DileptonCalc;   //!
   TBranch        *b_elDxy_DileptonCalc;   //!
   TBranch        *b_elEnergy_DileptonCalc;   //!
   TBranch        *b_elEta_DileptonCalc;   //!
   TBranch        *b_elHoE_DileptonCalc;   //!
   TBranch        *b_elOoemoop_DileptonCalc;   //!
   TBranch        *b_elPhi_DileptonCalc;   //!
   TBranch        *b_elPt_DileptonCalc;   //!
   TBranch        *b_elRelIso_DileptonCalc;   //!
   TBranch        *b_elSihih_DileptonCalc;   //!
   TBranch        *b_genEnergy_DileptonCalc;   //!
   TBranch        *b_genEta_DileptonCalc;   //!
   TBranch        *b_genPhi_DileptonCalc;   //!
   TBranch        *b_genPt_DileptonCalc;   //!
   TBranch        *b_muChi2_DileptonCalc;   //!
   TBranch        *b_muDxy_DileptonCalc;   //!
   TBranch        *b_muDz_DileptonCalc;   //!
   TBranch        *b_muEnergy_DileptonCalc;   //!
   TBranch        *b_muEta_DileptonCalc;   //!
   TBranch        *b_muPhi_DileptonCalc;   //!
   TBranch        *b_muPt_DileptonCalc;   //!
   TBranch        *b_muRelIso_DileptonCalc;   //!
   //mother information:
   //muon gen information:
   TBranch        *b_muGen_Reco_dr_DileptonCalc;
   TBranch        *b_muMother_energy_DileptonCalc;
   TBranch        *b_muMother_eta_DileptonCalc;
   TBranch        *b_muMother_phi_DileptonCalc;
   TBranch        *b_muMother_pt_DileptonCalc;
   TBranch        *b_muMatched_DileptonCalc;
   TBranch        *b_muMother_id_DileptonCalc;
   TBranch        *b_muMother_status_DileptonCalc;
   TBranch        *b_muPdgId_DileptonCalc;
   TBranch        *b_muStatus_DileptonCalc;
   TBranch        *b_muNumberOfMothers_DileptonCalc;
   //electron gen information: 
   TBranch        *b_elGen_Reco_dr_DileptonCalc;
   TBranch        *b_elMother_energy_DileptonCalc;
   TBranch        *b_elMother_eta_DileptonCalc;
   TBranch        *b_elMother_phi_DileptonCalc;
   TBranch        *b_elMother_pt_DileptonCalc;
   TBranch        *b_elMatched_DileptonCalc;
   TBranch        *b_elMother_id_DileptonCalc;
   TBranch        *b_elMother_status_DileptonCalc;
   TBranch        *b_elPdgId_DileptonCalc;
   TBranch        *b_elStatus_DileptonCalc;
   TBranch        *b_elNumberOfMothers_DileptonCalc;


  // Declaration of leaf types
//   Double_t        JER;
//   Double_t        JES;
//   
//   Double_t        qScale;
//   Double_t        smallestDeltaZ;
//   Double_t        weightQCD;
//   Double_t        weight_BTag_0_tags_DOWN;
//   Double_t        weight_BTag_0_tags_UP;
//   Double_t        weight_BTag_0_tags;
//   Double_t        weight_BTag_1_tags_DOWN;
//   Double_t        weight_BTag_1_tags_UP;
//   Double_t        weight_BTag_1_tags;
//   Double_t        weight_BTag_2_tags_DOWN;
//   Double_t        weight_BTag_2_tags_UP;
//   Double_t        weight_BTag_2_tags;
//   Double_t        weight_BTag_GE1_tags_DOWN;
//   Double_t        weight_BTag_GE1_tags_UP;
//   Double_t        weight_BTag_GE1_tags;
//   Double_t        weight_BTag_GE2_tags_DOWN;
//   Double_t        weight_BTag_GE2_tags_UP;
//   Double_t        weight_BTag_GE2_tags;
//   Double_t        weight_LeptonIso;
//   Double_t        weight_PU_3D_73mb;
//   Double_t        weight_PU_3D;
//   Double_t        weight_PU_3D_shiftDown_73mb;
//   Double_t        weight_PU_3D_shiftDown;
//   Double_t        weight_PU_3D_shiftUp_73mb;
//   Double_t        weight_PU_3D_shiftUp;
//   Double_t        weight_PU_RootFile;
//   Double_t        weight_PU;
//   Double_t        weight_Total;
//   Double_t        weight_TriggEff;
//   Double_t        weight_WxsecNoLight_comb;
//   Double_t        weight_WxsecNoLight_comb_down;
//   Double_t        weight_WxsecNoLight_comb_up;
//   Double_t        weight_WxsecNoLight_el;
//   Double_t        weight_WxsecNoLight_el_down;
//   Double_t        weight_WxsecNoLight_el_up;
//   Double_t        weight_WxsecNoLight_mu;
//   Double_t        weight_WxsecNoLight_mu_down;
//   Double_t        weight_WxsecNoLight_mu_up;
//   Double_t        weight_Wxsec_comb;
//   Double_t        weight_Wxsec_comb_down;
//   Double_t        weight_Wxsec_comb_up;
//   Double_t        weight_Wxsec_el;
//   Double_t        weight_Wxsec_el_down;
//   Double_t        weight_Wxsec_el_up;
//   Double_t        weight_Wxsec;
//   Double_t        weight_Wxsec_mu;
//   Double_t        weight_Wxsec_mu_down;
//   Double_t        weight_Wxsec_mu_up;
  
  
  treetop(TTree *tree);
  treetop(const TString &filename);
  virtual ~treetop();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  double getEntries();
  void printEvent(int jentry);
  void printEvent();
  void checkLeptons();
  double entries;
};

#endif

#ifdef treetop_cxx

#endif // #ifdef treetop_cxx
