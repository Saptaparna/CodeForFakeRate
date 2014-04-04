#include "../interface/TprimeEvent.h"


double TprimeEvent::dRlepton() const {
  return lepton1->lv.DeltaR(lepton2->lv);
}

vector<double> TprimeEvent::drBJetLepton () const {
  vector<double> dr;
  for (unsigned int i=0;i<vGoodJets.size();++i) {
    if (vGoodJets[i]->csvMedium != 0) {
      dr.push_back(lepton1->lv.DeltaR(vGoodJets[i]->lv));
      dr.push_back(lepton2->lv.DeltaR(vGoodJets[i]->lv));
    }
  }
  return dr;
}
double TprimeEvent::mindrBJetLepton() const {
     if (vGoodJets.size()==0) return -1;
     vector<double> dr(drBJetLepton());
     if (dr.size()==0) return -1;
     return *(min_element(dr.begin() ,dr.end()));

}

vector<double> TprimeEvent::mlb () const {
  vector<double> m;
  for (unsigned int i=0;i<vGoodJets.size();++i) {
    if (vGoodJets[i]->csvMedium != 0) {

      m.push_back((lepton1->lv+vGoodJets[i]->lv).M());
      m.push_back((lepton2->lv+vGoodJets[i]->lv).M());
    }
  }
  return m;
}
double TprimeEvent::minMlb() const {
     if (vGoodJets.size()==0) return -1;
     vector<double> m(mlb());
     if (m.size()==0) return -1;
     return *(min_element(m.begin() ,m.end()));

}

void TprimeEvent::clearEvent(){
  weight = -1000.0;
  lepton1=0;
  lepton2=0;
  theLeptons.clear();
  leptonSum.SetPxPyPzE(0,0,0,0);
  vGoodJets.clear();
  vGoodCsvs.clear();
  nBTags = 0;
  ht = 0;
  met = 0;
  mt  = 0;
  amwtPeakMass = 0.0;
  amwtPeakWeight = 0.0;

}

void TprimeEvent::printEvent(){
  for (unsigned int ij = 0; ij < vGoodJets.size(); ij++){
    cout<<"Jet"<<ij<<endl;
    cout<<"Pt: "<<vGoodJets.at(ij)->lv.Pt()<<'\t'<<"Eta: "<<vGoodJets.at(ij)->lv.Eta()<<'\t'<<"Phi: "<<vGoodJets.at(ij)->lv.Phi()<<endl;
  }
  cout<<"HT: "<<ht<<endl<<endl;
  cout<<"InvM: "<<leptonSum.M()<<endl;
}

vector<TJet*> TprimeEvent::selectJetsForMass()
{
  vector <TJet*> jets;
  if (vGoodJets.size()>2) return jets;
  unsigned int j[2];
  
  unsigned int nj=0;
  for (unsigned int ij = 0; ij < vGoodJets.size(); ij++){
    if ((vGoodJets.at(ij)->csvMedium != 0)&&(nj<2)) j[nj++]=ij;
  }
  if (nj<2) {
    for (unsigned int ij = 0; ij < vGoodJets.size(); ij++){
      if ((nj==1)&&(j[0]!=ij)) j[nj++]=ij;
      if (nj==0) j[nj++]=ij;
    }
  }
  jets.push_back(vGoodJets.at(j[0]));
  jets.push_back(vGoodJets.at(j[1]));
  return jets;
}
