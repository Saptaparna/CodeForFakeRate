#include "../interface/TopMassVariables.h"
#include "../interface/Constants.h"

using namespace std;
TopMassVariables::TopMassVariables()
{
  hasMassSolution_ = false;
  hasMassWeightHisto_ = false;
  peakMass_ = 0.;
  weight_ = 0.;
  top1Pt_  = SENTINEL;
  top2Pt_  = SENTINEL;
  tTbarPt_ = SENTINEL;
}

void TopMassVariables::setLeptons(const TLorentzVector & lvp, const TLorentzVector & lvm)
{
  lep_p = lvp;
  lep_m = lvm;
  lep_sum = lep_m + lep_p;
}

void TopMassVariables::setMET(double x, double y)
{
  v_met.Set(x,y);
}
void TopMassVariables::setJets(const TLorentzVector & j1, const TLorentzVector & j2)
{
  if (ptComparator(j1,j2)){
    jet1 = j1;
    jet2 = j2;
  } else {
    jet1 = j2;
    jet2 = j1;
  }
}

//   b_good_EE = false;
//   b_good_EM = false;
//   b_good_MM = false;
//       candPairType = "ee";


//   v_jets  = sel.GetJetsForAna();
//   sort(v_jets.begin(), v_jets.end(), ptComparator);
//   if (!sel.isData()) sel.randomBTag();
//   vector <NTJet> b_jets = sel.GetBJetsForAna();
//   nBjets = 0;
// 
//   if (v_jets.size()>1) {
//     sel_jet1 = 0; sel_jet2 = 1;
// 
//     for (unsigned int i = 0; i < v_jets.size(); i++){
// 
//       bool tagged = false;
//       for (unsigned int j = 0; j < b_jets.size(); j++){
// 	if (v_jets[i].p4 == b_jets[j].p4) {
// 	  tagged = true;
// 	  break;
// 	}
//       }
// 
//       jetTagged.push_back(tagged);
//       if (tagged){
// 	++ nBjets;
// 	if ( nBjets == 1){
// 	  sel_jet1 = i;
// 	  if (sel_jet1 != 0) sel_jet2 = 0;
// 	} else if ( nBjets == 2) sel_jet2 = i;
//       }
//     }
// 
// //   for (unsigned int ijet = 0; ijet < v_jets.size(); ijet++){
// //     if (ijet == sel_jet1 || ijet == sel_jet2) cout<<"Selected ";
// //     else                                      cout<<"         ";
// //     cout<<"Jet "<<ijet<<": ";
// //     cout << (jetTagged[ijet]?"Tag   ":"NoTag ");
// //     Print4Vector(v_jets[ijet].p4);
// //     cout << " <";
// //       for (unsigned int ibjet = 0; ibjet < b_jets.size(); ibjet++){
// //       NTJet & a = v_jets[ijet];
// //       NTJet & b = b_jets[ibjet];
// //       if ((a.p4) == b.p4) cout <<"T";
// //       else cout <<"-";
// //       }
// //     
// //     cout << "<"<<endl;
// //   }
// 
//     if (v_jets[sel_jet2].p4.Pt() > v_jets[sel_jet1].p4.Pt()) {
//       int temp = sel_jet1;
//       sel_jet1 = sel_jet2;
//       sel_jet2 = temp;
//     }
// 
//     jet1 = v_jets[sel_jet1].p4;
//     jet2 = v_jets[sel_jet2].p4;
// 
//   } else {
//     sel_jet1 = -1; sel_jet2 = -1;
//     if (v_jets.size()==1) jetTagged.push_back(sel.passBtagSelection(v_jets[0]));
//   }
// 
//   HT =  lep_p.Pt() + lep_m.Pt();
// 
// // 	 for(unsigned int i=0; i<candElec.size(); i++){
// // 	   HT+=candElec[i].p4.Pt();
// // 	 }
// // 	 for(unsigned int i=0; i<candMuon.size(); i++){
// // 	   HT+=candMuon[i].p4.Pt();
// // 	 }
//   for(unsigned int i=0; i<v_jets.size(); i++){
//     HT+=v_jets[i].p4.Pt();
//   }
//   HT+=v_met.Mod();
//   unclusteredMET = sel.GetUnclusMET().Mod();
//   top1Pt_  = SENTINEL;
//   top2Pt_  = SENTINEL;
//   tTbarPt_ = SENTINEL;
//   nVertex_ = sel.GetSelectedVertex().size();
// }

TopMassVariables::~TopMassVariables()
{
  if (hasMassSolution_) delete massWeightHisto_;
}

void TopMassVariables::setMass(TH1F* histo)
{
  massWeightHisto_ = histo;
  hasMassWeightHisto_ = true;
  hasMassSolution_ = true;
  weight_ = histo->GetBinContent(histo->GetMaximumBin());
  peakMass_  =   histo->GetXaxis()->GetBinLowEdge(histo->GetMaximumBin());
}

void TopMassVariables::printAll() const
{
//   cout << "Got a "<<candPairType<<endl;
  Print4Vector(lep_p);cout <<endl;
  Print4Vector(lep_m);cout <<endl;
  cout << "Dilpeton invariant mass: "<< lep_sum.M()<<endl;
//   cout << "Jets  / bJets: " << nJets() <<" / "<<nBJets()<<endl;
  Print4Vector(jet1);cout <<endl;
  Print4Vector(jet2);cout <<endl;
  
//   for (unsigned int ijet = 0; ijet < v_jets.size(); ijet++){
//     if (ijet == sel_jet1 || ijet == sel_jet2) cout<<"Selected ";
//     else                                      cout<<"         ";
//     cout<<"Jet "<<ijet<<": ";
//     cout << (jetTagged[ijet]?"Tag   ":"NoTag ");
//     Print4Vector(v_jets[ijet].p4);
//     cout << endl;
//   }
  cout << "MET: " << v_met.Mod()<<endl;

  if (hasMassSolution_) {
    cout <<"ttbar candidate with Mtop = "
      <<peakMass_<<" GeV with weight "
      <<weight_<<endl;
  }
}

void TopMassVariables::printSmall() const
{
//   cout <<" , "<< candPairType;
  cout <<" , "<<lep_p.Pt();
  cout <<" , "<<lep_m.Pt();
  cout <<" , "<<jet1.Pt();
  cout <<" , "<<jet1.Eta();
  cout <<" , "<<jet2.Pt();
  cout <<" , "<<jet2.Eta();
  cout <<" , "<< v_met.Mod();
//   cout <<" , "<< unclusteredMET;

  
  if (hasMassSolution_) cout <<" , "<< peakMass_<<" , "<<weight_;
}

void TopMassVariables::Print4Vector(const TLorentzVector & v1) const
{
  printf("| %8.2f | %8.2f | %8.2f | %8.2f |", v1.Pt(), v1.Eta(), v1.Phi(), v1.M());
}

