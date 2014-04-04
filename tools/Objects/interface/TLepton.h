#ifndef ObjectID_cxx
#define ObjectID_cxx

#include <TLorentzVector.h>
#include <cmath>
#include <iostream>



using namespace std;


class MCLepton{

public:

  TLorentzVector lv;

  int pdgID; 
  int status;
  double pt;
  double phi;
  double eta;
  double energy;  
  
  void setLV() {
    lv.SetPxPyPzE(pt*cos(phi), pt*sin(phi), pt*TMath::SinH(eta), energy);
  }

};

class TLepton{

public:
  
  TLepton(int chargeTemp, double ptTemp, double etaTemp, double phiTemp, double energyTemp, 
	double relIsoTemp, double ipXYTemp, double ipzTemp,
	int muonTypeTempm,
	int innerTrackLayersTemp, double nChi2Temp, int MuonHitsTemp, int PixelHitsTemp, int nMatchTemp);

  TLepton(int chargeTemp, double ptTemp, double etaTemp, double phiTemp, double energyTemp, 
	double relIsoTemp, double ipXYTemp, double ipzTemp,
	int eEEBtypes, int elQuality, int chargeConsistencyTemp, int notConvTemp,
	double elDeta, double elDphi, 
	double elSihih, double elHoE, double elD0, double elOoemoop,
	int elMHits, int elVtxFitConv);

  bool isElectron() { return isElectron_;}
  bool isMuon(){ return isMuon_;}
  
  TLorentzVector lv;
  int charge;
  double pt;
  double eta;
  double phi;
  double energy;
  double relIso;
  double ipXY, ipZ;
  bool   isElectron_, isMuon_;

  //Electrons only
  bool notEEEBGap_, isEE_, isEB_;
  bool elQualityT_, elQualityM_, elQualityL_;
  int    chargeConsistency;
  int    notConv;
  double deltaEtaSuperClusterTrackAtVtx, deltaPhiSuperClusterTrackAtVtx;
  double sigmaIetaIeta, hadronicOverEm, dB, ooemoop; 
  int trackerExpectedHitsInner;
  int passConversionVeto;


  //Muons only
  int    GlobalMuon;
  int    TrackerMuon;
  double nChi2;
  int    MuonHits; // number of valid muon hits
  int    PixelHits;
  int    nMatch;
  int    innerTrackLayers;

  int nMuons;

//   double relPtUnc;
  //mc
  void SetMatching(int numberOfMothersTemp,std::vector<double>::iterator & mptTemp, std::vector<double>::iterator & metaTemp, std::vector<double>::iterator &
  mphiTemp, std::vector<double>::iterator & menergyTemp, std::vector<int>::iterator &  mpdgIdTemp, std::vector<int>::iterator & mstatusTemp, int pdgIdTemp, int statusTemp, int matchedTemp, double deltaRTemp );
   
  int origin() const;
  bool goodElectron(double minPt = 30.0);
  bool looseElectron(double minPt = 30.0);
  bool goodMuon(double minPt = 30.0);
  bool looseMuon(double minPt = 30.0);
  bool looseLepton(double minPt=30.0);
  bool goodLepton(double minPt=30.0);
  void printLepton(bool fullMatching = false);

  vector<MCLepton> mother;
  MCLepton matchedLepton;
  bool matched;
  double gen_reco_DR;


  inline int hundred (int i) const
  {
    int j = (int) i % 1000;
    return (int) j/100;
  }
  inline int thousand (int i) const
  {
    int j = (int) i % 10000;
    return (int) j/1000;
  }

//public members for fake contribution
  double FR_MU;
  double FR_EL;

  double PR_MU;
  double PR_EL;


private :

  void setLV() ;
  
  double MIN_LEP_PT    ;
  double MIN_LEP_PT_FR ;

  double MAX_EL_ISO;
  double MAX_MU_ISO;

  double MAX_EL_ISO_LOOSE;
  double MAX_MU_ISO_LOOSE;

  double MAX_EL_ETA;
  double MAX_MU_ETA;
  
  TLepton(){defaults();}
  void defaults();
//   void initLepton();
};

class TJet{

public:
  
  TJet(double ptTemp, double etaTemp, double phiTemp, double energyTemp, bool bTagTemp);

  TLorentzVector lv;

  double pt;
  double eta;
  double phi;
  double energy;
  
  int csvMedium;//, csvLoose;
//   double combinedSecondaryVertexBJetTags, combinedSecondaryVertexMVABJetTags,
// 	jetBProbabilityBJetTags, jetProbabilityBJetTags, simpleSecondaryVertexBJetTags,
// 	simpleSecondaryVertexHighEffBJetTags, simpleSecondaryVertexHighPurBJetTags,
// 	trackCountingHighEffBJetTags, trackCountingHighPurBJetTags;
  int partonFlavour;

  void setLV();
  void printJet();
  bool checkJetLeptondR(const TLepton & lep1, const TLepton & lep2);
  bool checkJetLeptondR(const TLepton & lep1);
private:
  double MIN_LEP_PT;
  double MIN_JET_PT;
  double MAX_JET_ETA;

  TJet();
};




#endif