#ifndef TopMassVariables_h
#define TopMassVariables_h

// #include "../../Selection/interface/DiLeptonSelection.h"
#include <TLorentzVector.h>
#include <vector>
#include <map>
#include <TH1F.h>
#include <iostream>

struct ComparePt{
  bool operator()(const TLorentzVector & v1, const TLorentzVector & v2) const {
    return v1.Pt() > v2.Pt();
  }
//   bool operator()(const NTJet & v1, const NTJet & v2) const {
//     return v1.p4.Pt() > v2.p4.Pt();
//   }
};

// struct CompareCSV{
//   bool operator()(const NTJet & v1, const NTJet & v2) const {
//     return v1.GetDiscri(string("combinedSecondaryVertexBJetTags")) > v2.GetDiscri(string("combinedSecondaryVertexBJetTags"));
//   }
// };

class TopMassVariables{

public:

  TopMassVariables();
  ~TopMassVariables();

  void setLeptons(const TLorentzVector & lvp, const TLorentzVector & lvn);
  void setMET(double x, double y);
  void setJets(const TLorentzVector & j1, const TLorentzVector & j2);

  void setMass(TH1F* massWeightHisto);

  void printAll() const;
  void printSmall() const;

  float peakMass() const {return peakMass_;}
  float peakWeight() const {return weight_;}
  TH1F* massWeightHisto() {return massWeightHisto_;}
  bool hasMassWeightHisto() const {return hasMassWeightHisto_;}
  bool hasMassSolution() const {return hasMassSolution_;}

  TLorentzVector const& posLeptonLV() const {return lep_p;}
  TLorentzVector const& negLeptonLV() const {return lep_m;}
  TLorentzVector const& diLeptonLV()  const {return lep_sum;}

  /**
   *   Get LV of selected jet -- starts at 0
   */
  TLorentzVector const& selectedJetLV(const int i) const {return (i==0?jet1:jet2);}
//   bool selectedJetTag(const int i) const {return (i==0?jetTagged[sel_jet1]:jetTagged[sel_jet2]);}
//   unsigned int nJets() const {return v_jets.size();}
//   unsigned int nBJets() const {return nBjets;}
  

  TVector2 const& metV()  const {return v_met;}
//   float hT() const {return HT;}
// 
//   bool isEE() const {return b_good_EE;}
//   bool isEM() const {return b_good_EM;}
//   bool isMM() const {return b_good_MM;}

//   std::string const& dileptonType() const {return candPairType;}

  float top1Pt() const {return top1Pt_;}
  float top2Pt() const {return top2Pt_;}
  float tTbarPt() const {return tTbarPt_;}
  void setTopPt(float top1Pt, float top2Pt, float tTbarPt)
	{top1Pt_ = top1Pt; top2Pt_ = top2Pt; tTbarPt_ = tTbarPt;}

  int nVertex() const {return nVertex_;}

private:

  void Print4Vector(const TLorentzVector & v1) const;

  ComparePt ptComparator;
//  CompareCSV csvComparator;
  float peakMass_;
  float weight_;
  TH1F* massWeightHisto_;
  bool hasMassWeightHisto_, hasMassSolution_;
//   unsigned int sel_jet1, sel_jet2;

  TLorentzVector lep_p;
  TLorentzVector lep_m;
  TLorentzVector lep_sum;

  TLorentzVector jet1, jet2;

  TVector2 v_met;
//   float HT;
//   int nBjets;

//   bool b_good_EE;
//   bool b_good_EM;
//   bool b_good_MM;

//   std::string candPairType;

  float top1Pt_;
  float top2Pt_;
  float tTbarPt_;
  int nVertex_;

};
#endif
