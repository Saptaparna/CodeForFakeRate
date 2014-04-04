#include "../interface/TLepton.h"

TLepton::TLepton(int chargeTemp, double ptTemp, double etaTemp, double phiTemp, double energyTemp, 
	double relIsoTemp, double ipXYTemp, double ipzTemp, int muonTypeTemp, 
	int innerTrackLayersTemp, double nChi2Temp, int MuonHitsTemp, int PixelHitsTemp, int nMatchTemp) :
  charge(chargeTemp), pt(ptTemp), eta(etaTemp), phi(phiTemp), energy(energyTemp),
  relIso(relIsoTemp), ipXY(ipXYTemp), ipZ(ipzTemp), 
  isElectron_(false), isMuon_(true),
  innerTrackLayers(innerTrackLayersTemp), 
  nChi2(nChi2Temp), MuonHits(MuonHitsTemp), PixelHits(PixelHitsTemp), 
  nMatch(nMatchTemp)
//, relPtUnc(relPtUncTemp), 
{

  defaults();
  if (muonTypeTemp==8) {
    GlobalMuon = true;
    TrackerMuon= true;
  } else {
    GlobalMuon = muonTypeTemp&0x2>>1;
    TrackerMuon= muonTypeTemp&0x1;
  }
  setLV();
}

TLepton::TLepton(int chargeTemp, double ptTemp, double etaTemp, double phiTemp, double energyTemp, 
	double relIsoTemp, double ipXYTemp, double ipzTemp,
	int eEEBtypes, int elQuality, int chargeConsistencyTemp, int notConvTemp,
	double elDeta, double elDphi,
	double elSihih, double elHoE, double elD0, double elOoemoop,
	int elMHits, int elVtxFitConv):
  charge(chargeTemp), pt(ptTemp), eta(etaTemp), phi(phiTemp), energy(energyTemp),
  relIso(relIsoTemp), ipXY(ipXYTemp), ipZ(ipzTemp), 
  isElectron_(true), isMuon_(false),
  chargeConsistency(chargeConsistencyTemp), notConv(notConvTemp),
  deltaEtaSuperClusterTrackAtVtx(elDeta), deltaPhiSuperClusterTrackAtVtx(elDphi),
  sigmaIetaIeta(elSihih), hadronicOverEm(elHoE), dB(elD0), ooemoop(elOoemoop),
  trackerExpectedHitsInner(elMHits), passConversionVeto(elVtxFitConv)
{
  defaults();
  notEEEBGap_ = eEEBtypes&0x4>>2;
  isEE_ =  eEEBtypes&0x2>>1;
  isEB_ =  eEEBtypes&0x1;
  elQualityT_ = elQuality&0x4>>2;
  elQualityM_ = elQuality&0x2>>1;
  elQualityL_ = elQuality&0x1;
  setLV();
}

void TLepton::SetMatching(int numberOfMothersTemp, std::vector<double>::iterator & mptTemp, std::vector<double>::iterator & metaTemp, std::vector<double>::iterator
& mphiTemp, std::vector<double>::iterator & menergyTemp, std::vector<int>::iterator & mpdgIdTemp,  std::vector<int>::iterator & mstatusTemp, int pdgIdTemp, int statusTemp, int matchedTemp, double deltaRTemp ){

matchedLepton.pdgID = pdgIdTemp;
matchedLepton.status = statusTemp;
matched = matchedTemp;

for (int i = 0; i<numberOfMothersTemp;++i)
{
  mother.push_back(MCLepton());
  mother[i].pt  =(*mptTemp); 
  mother[i].eta =(*metaTemp);
  mother[i].phi =(*mphiTemp);
  mother[i].energy =(*menergyTemp);
  mother[i].pdgID = (*mpdgIdTemp);
  mother[i].status = (*mstatusTemp);
  mptTemp++;
  metaTemp++;
  mphiTemp++;
  menergyTemp++;
  mpdgIdTemp++;
  mstatusTemp++;
  }

//cout << "mother.size() = " << mother.size() << endl; 
//cout << "numberOfMothersTemp = " << numberOfMothersTemp << endl;
}


int TLepton::origin() const
{

  //cout << "mother.size() = " << mother.size() << endl;
  //cout << "matched = " << matched << endl;
  if (!matched) return 0;
  int i = 0;
  while (i<mother.size()) {
    if (abs(mother[i].pdgID)==24) return 24; // The mother is a W    
    if ((abs(mother[i].pdgID)!=11) && (abs(mother[i].pdgID)!=13) && (abs(mother[i].pdgID)!=15)) break; 
    ++i; // The mother is a lepton, continue checking whether the next mother is a W.
  }
  // So it is not a W
  for (i = 0;i<mother.size();++i ) {
    if ((thousand(fabs(mother[i].pdgID))== 5) || (hundred(fabs(mother[i].pdgID))== 5)) return 5;
  }
  for (i = 0;i<mother.size();++i ) {
    if ((thousand(fabs(mother[i].pdgID))== 4) || (hundred(fabs(mother[i].pdgID))== 4)) return 4;
  }
  for (i = 0;i<mother.size();++i ) {
    int t = thousand(fabs(mother[i].pdgID));
    int h = hundred(fabs(mother[i].pdgID));
    if ((t==1)||(t==2)|| (t==3) || (h==1)||(h==2)|| (h==3)) return 1;
  }
  //cout << "origin function closed" << endl;
  return -1;
}

void TLepton::setLV() {
  lv.SetPxPyPzE(pt*cos(phi), pt*sin(phi), pt*TMath::SinH(eta), energy);
//     if (matched) {
//       matchedLepton.setLV();
//       for (int i = 0;i<10;++i ) if (mother[i].pdgID!=0) mother[i].setLV();
//     }

}
bool TLepton::goodLepton(double minPt){
 if(isMuon_) return goodMuon(20.0);
 if(isElectron_) return goodElectron(20.0);
 }

bool TLepton::looseLepton(double minPt){
 if(isMuon_) return looseMuon(20.0);
 if(isElectron_) return looseElectron(20.0);
 }


bool TLepton::goodElectron(double minPt){
  if (isMuon_) return false;

  if (lv.Pt() < minPt)             return false;
  if (fabs(lv.Eta()) > MAX_EL_ETA) return false;
  if (isEB_ and deltaEtaSuperClusterTrackAtVtx > 4.0e-03) return false;
  if (isEB_ and deltaPhiSuperClusterTrackAtVtx > 3.0e-02) return false;
  if (isEB_ and sigmaIetaIeta > 1.0e-02) return false;
  if (isEB_ and hadronicOverEm > 1.2e-01) return false;
  if (isEB_ and fabs(ipZ) > 0.1 ) return false;
  if (isEB_ and fabs(dB) > 0.02 ) return false;
  if (isEB_ and ooemoop > 5e-02) return false;
  if (isEE_ and deltaEtaSuperClusterTrackAtVtx > 5.0e-03) return false;
  if (isEE_ and deltaPhiSuperClusterTrackAtVtx > 2.0e-02) return false;
  if (isEE_ and sigmaIetaIeta > 3.0e-02) return false;
  if (isEE_ and hadronicOverEm > 1.0e-01) return false;
  if (isEE_ and fabs(ipZ) > 0.1 ) return false;
  if (isEE_ and fabs(dB) > 0.02 ) return false;
  if (isEE_ and ooemoop > 5.0e-02) return false;
  if (not passConversionVeto) return false;
  if (not chargeConsistency) return false;
  if (trackerExpectedHitsInner) return false;
  if (relIso > MAX_EL_ISO)   return false;  
   
  return true;
  //return elQualityT_;

//     int CiC = (int) (hyperTightID + 0.01);
// 
//     if (not notEEEBGap_)            return false;
//     if (fabs(ipXY) > 0.02)             return false;
//     if (not (CiC & EID_VAL))              return false;
//     if (not chargeConsistency)       return false;
//     if (not notConv)                 return false;
//     if (relIso > MAX_EL_ISO)         return false;

}

bool TLepton::looseElectron(double minPt){
  //cout << "isEB_ = " << isEB_ << endl;
  if (isMuon_) return false;
  if (lv.Pt() < minPt)             return false;
  if (fabs(lv.Eta()) > MAX_EL_ETA) return false;
  if (isEB_ and deltaEtaSuperClusterTrackAtVtx > 7.0e-03) return false;
  if (isEB_ and deltaPhiSuperClusterTrackAtVtx > 1.5e-01) return false;
  if (isEB_ and sigmaIetaIeta > 1.0e-02) return false;
  if (isEB_ and hadronicOverEm > 1.2e-01) return false;
  //if (isEB_ or fabs(ipZ) > 0.2 ) return false;
  //if (isEB_ or fabs(dB) > 0.2 ) return false;
  if (isEB_ and ooemoop > 5e-02) return false;
  if (isEE_ and deltaEtaSuperClusterTrackAtVtx > 9.0e-03) return false;
  if (isEE_ and deltaPhiSuperClusterTrackAtVtx > 1.0e-01) return false;
  if (isEE_ and sigmaIetaIeta > 3.0e-02) return false;
  if (isEE_ and hadronicOverEm > 1.0e-01) return false;
  //if (isEE_ or fabs(ipXY) > 0.2 ) return false;
  //if (isEE_ or fabs(dB) > 0.2 ) return false;
  if (isEE_ and ooemoop > 5e-02) return false;
  //if (not passConversionVeto) return false;
  if (trackerExpectedHitsInner) return false;
  if (not chargeConsistency) return false;
  if (relIso > MAX_EL_ISO_LOOSE)   return false;
  //return elQualityL_;

//     int CiC = (int) (hyperTightID + 0.01);
// 
//     if (not notEEEBGap_)            return false;
//   //   if (fabs(ipXY) > 0.02)             return false;
//     if (not (CiC & EID_VAL))              return false;
//     if (not chargeConsistency)       return false;
//     // if (not notConv)                 return false;
//     if (relIso > MAX_EL_ISO_LOOSE)   return false;
  return true;
}

bool TLepton::goodMuon(double minPt){
  if (isElectron_)		     return false;
  if (lv.Pt() < minPt)             return false;
  if (fabs(lv.Eta()) > MAX_MU_ETA) return false; 
  if (!(GlobalMuon &&  TrackerMuon))return false;
  if (innerTrackLayers <= 5)        return false;
  if (nChi2 >= 10)                  return false;
  if (MuonHits < 1)                 return false;
  if (fabs(ipXY) > 0.2)             return false;
  if (fabs(ipZ)  > 0.5)             return false;
  if (PixelHits < 1)                return false;
  if (nMatch < 2)                   return false;
  if (relIso > MAX_MU_ISO)          return false;
  return true;
}

bool TLepton::looseMuon(double minPt){
  if (isElectron_) return false;
  if (lv.Pt() < minPt)             return false;
  if (fabs(lv.Eta()) > MAX_MU_ETA) return false;
  if (not GlobalMuon)              return false;
  if (not TrackerMuon)             return false;
  //if (innerTrackLayers <= 10)        return false; 
  if (nChi2 >= 50)                 return false;
  if (MuonHits < 1)                return false;
  if (PixelHits < 1)               return false;
  // if (nMatch < 2)                  return false;
  if (fabs(ipXY) > 2)             return false;
//   if (fabs(relPtUnc) > 0.1)        return false;
  if (relIso > MAX_MU_ISO_LOOSE)   return false;

  return true;
}

// float TLepton::leptonIDsfLoose(int run)
// {
//   if (isElectron_){
//   } else {
//     if (run < 198000) { // 2012 A & B
//       if (fabs(eta)< 0.9) {
//         return 0.9988;
//       } else if (fabs(eta)< 1.2) {
//         return 0.9993;
//       } else {
//         return 0.9982;
//       }
//     } else {		// 2012 C
//       if (fabs(eta)< 0.9) {
//         return 0.9985;
//       } else if (fabs(eta)< 1.2) {
//         return 0.9992;
//       } else {
//         return 0.9986;
//       }
//     }
//   }
// }

void TLepton::printLepton(bool fullMatching){

  if (lv.Pt() < 1){
    cout<<"Lepton with pT < 1"<<endl;
//      return;
  }

  cout<<"pt: "<<lv.Pt()<<" eta: "<<lv.Eta()<<" phi: "<<lv.Phi()<<endl;
  cout<<"charge:            "<<charge<<endl;
  cout<<"iso:               "<<relIso<<endl;
  cout<<"ipXY / ipZ:        "<<ipXY<<" / "<< ipZ<<  endl;

  if (isElectron_){
    //Electrons only
    cout<<"EE/EB/notGap:        "<<isEE_<<" / "<< isEB_<<" / "<<  notEEEBGap_<<endl;
    cout<<"Cut based-id L/M/T   "<<elQualityL_<<" / "<< elQualityM_<<" / "<<  elQualityT_<<endl;

//     cout<<"hyperTightID:      "<<hyperTightID<<endl;
    cout<<"chargeConsistency:   "<<chargeConsistency<<endl;
    cout<<"Conversion veto:     "<<passConversionVeto<<endl;
    cout<<"trackerExpectedHitsInner:   "<<trackerExpectedHitsInner<<endl;
    cout<<"chargeConsistency:   "<<chargeConsistency<<endl;
    cout<<"delta Eta/Phi SuperClusterTrackAtVtx: "<<
	deltaEtaSuperClusterTrackAtVtx<<" / "<< deltaPhiSuperClusterTrackAtVtx<<endl;
    cout<<"sigmaIetaIeta:   "<<sigmaIetaIeta<<endl;
    cout<<"hadronicOverEm:   "<<hadronicOverEm<<endl;
    cout<<"dB:   "<<dB<<endl;
    cout<<"ooemoop:   "<<ooemoop<<endl;

  }
  else{
    //Muons only
    cout<<"Global / Tracker   "<<GlobalMuon<<" / "<< TrackerMuon<<endl;
    cout<<"innerTrackLayers:    "<<innerTrackLayers<<endl;
    cout<<"NormalizedChi2:    "<<nChi2<<endl;
    cout<<"MuonHits:          "<<MuonHits<<endl;
    cout<<"PixelHits:         "<<PixelHits<<endl;
    cout<<"nMatch:            "<<nMatch<<endl;

    if (goodMuon(MIN_LEP_PT)) cout << "Good muon\n";
    else if (looseMuon(MIN_LEP_PT)) cout << "Loose muon\n";
  }

  cout<<"MC match:          "<<matched<<" "<< origin()<<endl;
  if (fullMatching && matched) {
    cout<<"Matched lepton pt: "<<matchedLepton.lv.Pt()<<" eta: "<<matchedLepton.lv.Eta()
        <<" phi: "<<matchedLepton.lv.Phi()<<endl;
    cout <<"Mothers\n";
    for (int i = 0;i<10;++i )
      if (mother[i].pdgID!=0) cout<<i<<" : pdgID: "<< mother[i].pdgID<<" pt: "
	<< mother[i].lv.Pt()<<" eta: "<<mother[i].lv.Eta()
        <<" phi: "<<mother[i].lv.Phi()<<endl;
  }
  cout<<endl;
}

void TLepton::defaults(){
  //MIN_LEP_PT	 = 30.;
  //MIN_LEP_PT_FR  = 30.;

  MIN_LEP_PT   = 20.;//using the new lepton ID definition
  MIN_LEP_PT_FR  = 20.; //using the new lepton ID definition

  /*
  MAX_EL_ISO  = 0.15;//10.0; //0.15;//0.15;
  MAX_MU_ISO  = 0.20;//10.0; //0.20;//0.10;//0.20;
*/
  MAX_EL_ISO_LOOSE  = 0.60;//10.0;//0.60;//0.60;
  MAX_MU_ISO_LOOSE  = 0.40;//10.0;//0.40;//1.0;//1.0;//0.40;//0.60;//1.0; //0.40;

  //changing the isolation to what we use now (April 1st -- this is not a joke.)
  MAX_EL_ISO  = 0.10;//10.0; //0.15;//0.15;
  MAX_MU_ISO  = 0.12;//10.0; //0.20;//0.10;//0.20;
  
  MAX_EL_ETA  = 2.4;
  MAX_MU_ETA  = 2.4;

  FR_MU = 0.285;
  FR_EL = 0.112;

  PR_MU = 1.0;
  PR_EL = 1.0;

}

// void TLepton::initLepton(){
//   lv.SetPxPyPzE(0,0,0,0);
//   relIso = SEN_HIGH;
//   ipXY = SEN_HIGH;
//   ipZ = SEN_HIGH;
//   charge = 0;
// 
//   //Electrons only
//   notEEEBGap_ = true;
//   chargeConsistency = false;
//   notConv = false;
// 
//   //Muons only
//   GlobalMuon = false;
//   TrackerMuon = false;
//   innerTrackLayers = SEN_LOW;
//   nChi2 = SEN_HIGH;
//   MuonHits = SEN_LOW;
//   PixelHits = SEN_LOW;
//   nMatch = SEN_LOW;
// //     relPtUnc = SEN_HIGH;
// }

TJet::TJet(double ptTemp, double etaTemp, double phiTemp, double energyTemp, bool bTagTemp) :
  pt(ptTemp), eta(etaTemp), phi(phiTemp), energy(energyTemp), csvMedium(bTagTemp)
{
  setLV();
  MIN_JET_PT  = 30.;
  MAX_JET_ETA = 2.4;
  MIN_LEP_PT	 = 20.; //30
}


TJet::TJet()
{
  MIN_JET_PT  = 30.;
  MAX_JET_ETA = 2.4;
  MIN_LEP_PT	 = 20.; //30.0
}

void TJet::setLV() {
  lv.SetPxPyPzE(pt*cos(phi), pt*sin(phi), pt*TMath::SinH(eta), energy);
}

void TJet::printJet(){

  if (lv.Pt() < 1){
    cout<<"Jet with pT < 1"<<endl;
//      return;
  }

  cout<<"pt: "<<lv.Pt()<<" eta: "<<lv.Eta()<<" phi: "<<lv.Phi()<<" energy: "<<lv.E()<<endl;
  cout<<"CSV:       "<<csvMedium  <<endl;
  cout<<endl;
}


bool TJet::checkJetLeptondR(const TLepton & lep1, const TLepton & lep2){

  bool dRcut = true; 

  if (lv.Pt() < MIN_JET_PT) return false; 

  if (lep1.lv.Pt() > MIN_LEP_PT){
    if (lep1.lv.DeltaR(lv) < 0.3) dRcut = false;
  }

  if (lep2.lv.Pt() > MIN_LEP_PT){
    if (lep2.lv.DeltaR(lv) < 0.3) dRcut = false;
  }

  return dRcut;
}

bool TJet::checkJetLeptondR(const TLepton & lep1){

  bool dRcut = true; 

  if ((lv.Pt() < MIN_JET_PT) || fabs(lv.Eta()) > MAX_JET_ETA) return false; 

  if (lep1.lv.Pt() > MIN_LEP_PT){
    if (lep1.lv.DeltaR(lv) < 0.3) dRcut = false;
  }

  return dRcut;
}

