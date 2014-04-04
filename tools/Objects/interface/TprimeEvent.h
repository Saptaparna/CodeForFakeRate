#ifndef TprimeEvent_h
#define TprimeEvent_h
#include <TString.h>
#include "TLepton.h"

class TprimeEvent{

public:

  TString suffix;

  unsigned int isam;

  double weight;
  int    nPV;
 
  TLepton* lepton1;
  TLepton* lepton2;
  vector <TLepton *> theLeptons;
  TLorentzVector leptonSum;

  vector <TJet*> vGoodJets;
  vector <unsigned int>   vGoodCsvs;

  double ht;
  double met;
  double met_phi;
  double mt;
  
  int nBTags;
  
  TprimeEvent()  { clearEvent(); }

  void clearEvent();
  void printEvent();

  double dRlepton() const;

  vector<double> drBJetLepton () const;
  double mindrBJetLepton() const;

  vector<double> mlb () const;
  double minMlb() const;
  
  vector <TJet*> selectJetsForMass();
  float amwtPeakMass, amwtPeakWeight;

};

#endif
