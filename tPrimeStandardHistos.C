#ifndef StandardHistos_cxx
#define StandardHistos_cxx

#include "TLorentzVector.h"
#include "TVector2.h"
#include <TMath.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TString.h>

#include <vector>
#include <algorithm>

#include "tools/Objects/interface/TprimeEvent.h"

const unsigned int NHISTOS    = 26;

enum Histos_t {Lep1Pt,  Lep2Pt,  Lep3Pt,
	       ElPt,    MuPt,    ElEta, MuEta, 
	       Jet1Pt,  Jet2Pt,  nJets, HT,     
	       LepInvM, LepJInvM, nBJets, nElec, nMuon, nLept,
	       sumPtL, sumPtJ, MET,
	       mindR, dR, minMlb, Mlb, dRlept, //25
	       amwt
};

const unsigned int NHISTOS_FR = 9;

enum Histos_FR_t {Lep1Pt_FR, Jet1Pt_FR, nJets_FR, nEvents_FR, 
		  nPV_FR,    mJL_FR,    dRJL_FR,  MET_FR,
		  MT_FR
};



class HistoData{

public:

  TString histoName;
  int     nBins;
  double  min;
  double  max;

  HistoData();

  HistoData(TString hn, int nb, double mn, double mx){
    histoName = hn;
    nBins     = nb;
    min       = mn;
    max       = mx;
  }

};

class StandardHistos{
  
public:
  
  StandardHistos(const TString & aName, const TString & aSuffix, const TString & sampleName, const double scale, bool doFakes) :
	hname(aName), suffix(aSuffix), sampleName_(sampleName), scale_(scale), doFakes_(doFakes)//initializer list
  {
    initAllHistos(true);
  }
  void fillVHD(TprimeEvent* teve, treetop* theTree, vector <TH1F*> myHistos){
    
    myHistos.at(Lep1Pt) ->Fill(teve->lepton1->lv.Pt(), teve->weight);
    myHistos.at(Lep2Pt) ->Fill(teve->lepton2->lv.Pt(), teve->weight);
    if (theTree->goodLeptons.size()>2) myHistos.at(Lep3Pt)->Fill(theTree->goodLeptons[2]->lv.Pt(), teve->weight);

    //Fill histos split by lepton flavor
    if (teve->lepton1->isMuon()){
      myHistos.at(MuPt) ->Fill(teve->lepton1->lv.Pt(),  teve->weight);
      myHistos.at(MuEta)->Fill(teve->lepton1->lv.Eta(), teve->weight);
    }
    else{
      myHistos.at(ElPt) ->Fill(teve->lepton1->lv.Pt(),  teve->weight);
      myHistos.at(ElEta)->Fill(teve->lepton1->lv.Eta(), teve->weight);
    }
    if (teve->lepton2->isMuon()){
      myHistos.at(MuPt) ->Fill(teve->lepton2->lv.Pt(),  teve->weight);
      myHistos.at(MuEta)->Fill(teve->lepton2->lv.Eta(), teve->weight);
    }
    else{
      myHistos.at(ElPt) ->Fill(teve->lepton2->lv.Pt(),  teve->weight);
      myHistos.at(ElEta)->Fill(teve->lepton2->lv.Eta(), teve->weight);
    }

    myHistos.at(LepInvM)->Fill(teve->leptonSum.M(), teve->weight);
    myHistos.at(HT)     ->Fill(teve->ht, teve->weight);
    myHistos.at(nJets)  ->Fill(teve->vGoodJets.size(), teve->weight);
    myHistos.at(nBJets)  ->Fill(teve->nBTags, teve->weight);
    double sumpt = 0;
    for (unsigned int j = 0;j<theTree->goodLeptons.size();++j ) sumpt+= theTree->goodLeptons[j]->lv.Pt();
    myHistos.at(sumPtL)  ->Fill(sumpt, teve->weight);

    sumpt = 0;
    for (unsigned int j = 0;j<teve->vGoodJets.size();++j ) sumpt+= teve->vGoodJets[j]->lv.Pt();
    myHistos.at(sumPtJ)  ->Fill(sumpt, teve->weight);
    myHistos.at(MET)  ->Fill(teve->met, teve->weight);
    myHistos.at(nElec)  ->Fill(theTree->goodElecs.size(), teve->weight);
    myHistos.at(nMuon)  ->Fill(theTree->goodMuons.size(), teve->weight);
    myHistos.at(nLept)  ->Fill(theTree->goodLeptons.size(), teve->weight);
    myHistos.at(mindR)  ->Fill( teve->mindrBJetLepton(), teve->weight);
    vector<double> dr(teve->drBJetLepton());
    for (unsigned int j = 0;j<dr.size();++j )     myHistos.at(dR)  ->Fill( dr[j], teve->weight);
    myHistos.at(minMlb)  ->Fill(teve->minMlb(), teve->weight);
    vector<double> m(teve->mlb());
    for (unsigned int j = 0;j<m.size();++j )     myHistos.at(Mlb)  ->Fill( m[j], teve->weight);
    myHistos.at(dRlept)  ->Fill(teve->dRlepton(), teve->weight);
    if (teve->amwtPeakWeight>0.) myHistos.at(amwt)  ->Fill(teve->amwtPeakMass, teve->weight);
    
    if (teve->vGoodJets.size() > 0)  myHistos.at(Jet1Pt)->Fill(teve->vGoodJets.at(0)->lv.Pt(), teve->weight);
    if (teve->vGoodJets.size() > 1)  myHistos.at(Jet2Pt)->Fill(teve->vGoodJets.at(1)->lv.Pt(), teve->weight); 
  }

  void fillAllHistos(TprimeEvent* teve, treetop* theTree, TString type="", bool doFakes=false){
    
    if (not doFakes) fillVHD(teve, theTree, goodHistos);
    else{
      if (type == "Nt00") fillVHD(teve, theTree, Nt00Histos);
      if (type == "Nt01") fillVHD(teve, theTree, Nt01Histos);
      if (type == "Nt10") fillVHD(teve, theTree, Nt10Histos);
      if (type == "Nt11") fillVHD(teve, theTree, Nt11Histos);
    }
  }

  void scaleAllHistos(bool doFakes=false){
    for (unsigned int ih = 0; ih < NHISTOS; ih++){
      goodHistos.at(ih)->Scale(scale_);

      if (doFakes){
	Nt00Histos.at(ih)->Scale(scale_);
	Nt01Histos.at(ih)->Scale(scale_);
	Nt10Histos.at(ih)->Scale(scale_);
	Nt11Histos.at(ih)->Scale(scale_);
      }
    }
  }

  void getTotFakes(double f1, double f2, double p1, double p2){
    for (unsigned int ih = 0; ih < NHISTOS; ih++){

      double det = 1.0 / ((p1 - f1)*(p2 - f2)); 

      TH1F* hNff = (TH1F*)Nt00Histos.at(ih)->Clone("hNff");
      hNff->Scale(p1*p2);
      hNff->Add(Nt10Histos.at(ih), -1*(1-p1)*p2);
      hNff->Add(Nt01Histos.at(ih), -1*p1*(1-p2));
      hNff->Add(Nt11Histos.at(ih), (1-p1)*(1-p2));
      hNff->Scale(det*f1*f2);

      TH1F* hNpf = (TH1F*)Nt00Histos.at(ih)->Clone("hNpf");
      hNpf->Scale(-1*f1*p2);
      hNpf->Add(Nt10Histos.at(ih), (1-f1)*p2);
      hNpf->Add(Nt01Histos.at(ih), f1*(1-p2));
      hNpf->Add(Nt11Histos.at(ih), -1*(1-f1)*(1-p2));
      hNpf->Scale(det*p1*f2);

      TH1F* hNfp = (TH1F*)Nt00Histos.at(ih)->Clone("hNfp");
      hNfp->Scale(-1*p1*f2);
      hNfp->Add(Nt10Histos.at(ih), (1-p1)*f2);
      hNfp->Add(Nt01Histos.at(ih), p1*(1-f2));
      hNfp->Add(Nt11Histos.at(ih), -1*(1-p1)*(1-f2));
      hNfp->Scale(det*f1*p2);

      goodHistos.at(ih)->Add(hNff);
      goodHistos.at(ih)->Add(hNpf);
      goodHistos.at(ih)->Add(hNfp);
    }
  }

private:
  TString hname;
  TString suffix;
  TString sampleName_;
  double scale_;
  bool doFakes_;
  vector <TH1F*> goodHistos;
  vector <TH1F*> Nt00Histos;
  vector <TH1F*> Nt01Histos;
  vector <TH1F*> Nt10Histos;
  vector <TH1F*> Nt11Histos;
  void initAllHistos(bool doFakes=false){

    vector <HistoData*> vhd(NHISTOS);
    vhd.at(Lep1Pt)    = new HistoData("Lep1Pt",   240,  0.,  240.);
    vhd.at(Lep2Pt)    = new HistoData("Lep2Pt",   240,  0.,  240.);
    vhd.at(Lep3Pt)    = new HistoData("Lep3Pt",   240,  0.,  240.);

    vhd.at(ElPt)      = new HistoData("ElPt",     240,  0.,  240.);
    vhd.at(MuPt)      = new HistoData("MuPt",     240,  0.,  240.);

    vhd.at(ElEta)     = new HistoData("ElEta",     60, -2.4, 2.4);
    vhd.at(MuEta)     = new HistoData("MuEta",     60, -2.4, 2.4);

    vhd.at(Jet1Pt)    = new HistoData("Jet1Pt",   480,  0.,  480.);
    vhd.at(Jet2Pt)    = new HistoData("Jet2Pt",   480,  0.,  480.);

    vhd.at(nJets)     = new HistoData("nJets",     9,  -0.5, 8.5);
    vhd.at(nBJets)    = new HistoData("nBJets",   9,  -0.5, 8.5);
    vhd.at(nElec)     = new HistoData("nElec",   9,  -0.5, 8.5);
    vhd.at(nMuon)     = new HistoData("nMuon",   9,  -0.5, 8.5);
    vhd.at(nLept)     = new HistoData("nLept",   9,  -0.5, 8.5);
    vhd.at(sumPtL)    = new HistoData("sumPtL", 300,  0., 600.);
    vhd.at(sumPtJ)    = new HistoData("sumPtJ", 300,  0., 600.);
    vhd.at(MET)       = new HistoData("MET", 60,  0., 300.);

    vhd.at(HT)        = new HistoData("HT",       900,  0.,  900.);

    vhd.at(LepInvM)   = new HistoData("LepInvM",   240,  0.,  240.);
    vhd.at(LepJInvM)  = new HistoData("LepJInvM" , 60,  0.,  240.);



    vhd.at(dRlept)	= new HistoData("dRlept" , 100, 0., 5.);
    vhd.at(mindR)	= new HistoData("mindR" , 100, 0., 5.);
    vhd.at(dR)		= new HistoData("dR" , 100,  0., 5.);
    vhd.at(minMlb)	= new HistoData("minMlb" , 100,  0.,  500.);
    vhd.at(Mlb)		= new HistoData("Mlb" , 100,  0.,  500.);
    vhd.at(amwt)	= new HistoData("amwt" , 600, 100., 700.);
// cout << vhd.size()<< " "<<NHISTOS<<endl;
    if (hname != "") hname = "_"+hname;
    
    goodHistos.resize(NHISTOS);
    
    for (unsigned int ih = 0; ih < NHISTOS; ih++){
//      cout << ih<<" "<<vhd.at(ih)->histoName<<" / "<<hname<<" / "<<sampleName_<<" / "<<suffix<<endl;
      goodHistos.at(ih) = new TH1F(vhd.at(ih)->histoName+hname+"_"+sampleName_+"_"+suffix, vhd.at(ih)->histoName+hname+"_"+sampleName_+"_"+suffix, 
				   vhd.at(ih)->nBins, vhd.at(ih)->min, vhd.at(ih)->max);
      goodHistos.at(ih)->Sumw2();
    }

    if (doFakes){
      Nt00Histos.resize(NHISTOS);
      Nt10Histos.resize(NHISTOS);
      Nt11Histos.resize(NHISTOS);
      Nt01Histos.resize(NHISTOS);

      for (unsigned int ih = 0; ih < NHISTOS; ih++){
	Nt00Histos.at(ih) = new TH1F(vhd.at(ih)->histoName+"Nt00"+hname+"_"+sampleName_+"_"+suffix, vhd.at(ih)->histoName+"Nt00"+hname+"_"+sampleName_+"_"+suffix, 
				     vhd.at(ih)->nBins, vhd.at(ih)->min, vhd.at(ih)->max);
	Nt00Histos.at(ih)->Sumw2();

	Nt01Histos.at(ih) = new TH1F(vhd.at(ih)->histoName+"Nt01"+hname+"_"+sampleName_+"_"+suffix, vhd.at(ih)->histoName+"Nt01"+hname+"_"+sampleName_+"_"+suffix, 
				     vhd.at(ih)->nBins, vhd.at(ih)->min, vhd.at(ih)->max);
	Nt01Histos.at(ih)->Sumw2();

	Nt10Histos.at(ih) = new TH1F(vhd.at(ih)->histoName+"Nt10"+hname+"_"+sampleName_+"_"+suffix, vhd.at(ih)->histoName+"Nt10"+hname+"_"+sampleName_+"_"+suffix, 
				     vhd.at(ih)->nBins, vhd.at(ih)->min, vhd.at(ih)->max);
	Nt10Histos.at(ih)->Sumw2();

	Nt11Histos.at(ih) = new TH1F(vhd.at(ih)->histoName+"Nt11"+hname+"_"+sampleName_+"_"+suffix, vhd.at(ih)->histoName+"Nt11"+hname+"_"+sampleName_+"_"+suffix, 
				     vhd.at(ih)->nBins, vhd.at(ih)->min, vhd.at(ih)->max);
	Nt11Histos.at(ih)->Sumw2();
      }
    }
  }



};

class StandardHistosFR{

public:

  StandardHistosFR(const TString & aName, const TString & aSuffix, const TString & sampleName, const double scale) :
            hname(aName), suffix(aSuffix), sampleName_(sampleName), scale_(scale)
  {
    initAllHistos();
  }


  TString hname;

  TString suffix;
  TString outLabel;
  TString sampleName_;
  double scale_;
  vector <TH1F*> looseHistos;
  vector <TH1F*> tightHistos;
  vector <TH1F*> ratioHistos;
  void initAllHistos(){
    
    vector <HistoData*> vhd(NHISTOS_FR);
    vhd.at(Lep1Pt_FR)   = new HistoData("Lep1Pt",   60,  0.,  240.);
    vhd.at(Jet1Pt_FR)   = new HistoData("Jet1Pt",   60,  0.,  420.);
    vhd.at(nJets_FR)    = new HistoData("nJets",    9,  -0.5, 8.5);
    vhd.at(nEvents_FR)  = new HistoData("nEvents",  1,   0.5, 1.5);
    vhd.at(nPV_FR)      = new HistoData("nPV",      30, -0.5, 29.5);
    vhd.at(mJL_FR)      = new HistoData("mJL",      60,  0.,  240.);
    vhd.at(dRJL_FR)     = new HistoData("dRJL",     50,  0.,  10);
    vhd.at(MET_FR)      = new HistoData("MET",      50,  0.,  250);
    vhd.at(MT_FR)       = new HistoData("MT",       50,  0.,  250);

    looseHistos.resize(NHISTOS_FR);
    tightHistos.resize(NHISTOS_FR);
    ratioHistos.resize(NHISTOS_FR);
  
    for (unsigned int ih = 0; ih < NHISTOS_FR; ih++){
      looseHistos.at(ih) = new TH1F(vhd.at(ih)->histoName+"_loose_"+sampleName_+"_"+suffix, vhd.at(ih)->histoName+"_loose_"+sampleName_+"_"+suffix,
                                    vhd.at(ih)->nBins, vhd.at(ih)->min, vhd.at(ih)->max);
      looseHistos.at(ih)->Sumw2();
      tightHistos.at(ih) = new TH1F(vhd.at(ih)->histoName+"_tight_"+sampleName_+"_"+suffix, vhd.at(ih)->histoName+"_tight_"+sampleName_+"_"+suffix,
                                    vhd.at(ih)->nBins, vhd.at(ih)->min, vhd.at(ih)->max);
      tightHistos.at(ih)->Sumw2();

      ratioHistos.at(ih) = new TH1F(vhd.at(ih)->histoName+"_ratio_"+sampleName_+"_"+suffix, vhd.at(ih)->histoName+"_ratio_"+sampleName_+"_"+suffix,
                                    vhd.at(ih)->nBins, vhd.at(ih)->min, vhd.at(ih)->max);
      ratioHistos.at(ih)->Sumw2();
    }
  }

    void fillLooseHistos(TprimeEvent* teve, treetop* theTree){
    looseHistos.at(Lep1Pt_FR) ->Fill(teve->lepton1->lv.Pt(), teve->weight);
    looseHistos.at(nJets_FR)  ->Fill(teve->vGoodJets.size(), teve->weight);
    looseHistos.at(nEvents_FR)->Fill(1, teve->weight);
    looseHistos.at(nPV_FR)    ->Fill(teve->nPV, teve->weight);
    looseHistos.at(MET_FR)    ->Fill(teve->met, teve->weight);
    looseHistos.at(MT_FR)     ->Fill(teve->mt, teve->weight);
    if (teve->vGoodJets.size() > 0){
      looseHistos.at(Jet1Pt_FR)->Fill(teve->vGoodJets.at(0)->lv.Pt(), teve->weight);
      for (unsigned int ij = 0; ij < teve->vGoodJets.size(); ij++){
        looseHistos.at(mJL_FR)->Fill((teve->lepton1->lv + teve->vGoodJets.at(ij)->lv).M(), teve->weight);
        looseHistos.at(dRJL_FR)->Fill(teve->lepton1->lv.DeltaR(teve->vGoodJets.at(ij)->lv), teve->weight);
      }
    }
  }

   void fillTightHistos(TprimeEvent* teve, treetop* theTree){
    tightHistos.at(Lep1Pt_FR) ->Fill(teve->lepton1->lv.Pt(), teve->weight);
    tightHistos.at(nJets_FR)  ->Fill(teve->vGoodJets.size(), teve->weight);
    tightHistos.at(nEvents_FR)->Fill(1, teve->weight);
    tightHistos.at(nPV_FR)    ->Fill(teve->nPV, teve->weight);
    tightHistos.at(MET_FR)    ->Fill(teve->met, teve->weight);
    tightHistos.at(MT_FR)     ->Fill(teve->mt, teve->weight);
    if (teve->vGoodJets.size() > 0){
      tightHistos.at(Jet1Pt_FR)->Fill(teve->vGoodJets.at(0)->lv.Pt(), teve->weight);
      for (unsigned int ij = 0; ij < teve->vGoodJets.size(); ij++){
        tightHistos.at(mJL_FR)->Fill((teve->lepton1->lv + teve->vGoodJets.at(ij)->lv).M(), teve->weight);
        tightHistos.at(dRJL_FR)->Fill(teve->lepton1->lv.DeltaR(teve->vGoodJets.at(ij)->lv), teve->weight);
      }
    }
  }

    void scaleTLHistos(TprimeEvent* teve){
    for (unsigned int ih = 0; ih < NHISTOS_FR; ih++){
      looseHistos.at(ih)->Scale(scale_);
      tightHistos.at(ih)->Scale(scale_);
    }
  }

  void getRatioHistos(TprimeEvent* teve){
    for (unsigned int ih = 0; ih < NHISTOS_FR; ih++){
      ratioHistos.at(ih)->Add(tightHistos.at(ih));
      ratioHistos.at(ih)->Divide(looseHistos.at(ih));
    }
  } 
    
  void fillTLHistos(TprimeEvent* teve, treetop* theTree, bool b_Tight){
    fillLooseHistos(teve, theTree);
    if (b_Tight) fillTightHistos(teve, theTree);
  } 
};  



/*class StandardHistosFR{
  
private:
  StandardHistosFR(){}
public:
  
  StandardHistosFR(const TString & aName, const TString & aSuffix, const TString & aLabel, const double scale) :
	hname(aName), suffix(aSuffix), outLabel(aLabel), scale_(scale)
  {
    initAllHistos();
  }

  TString hname;
  
  TString suffix;
  TString outLabel;
  double scale_;

  vector <TH1F*> looseHistos;
  vector <TH1F*> tightHistos;
  vector <TH1F*> ratioHistos;
  
  void initAllHistos(){
    
    vector <HistoData*> vhd(NHISTOS_FR);
    vhd.at(Lep1Pt_FR)   = new HistoData("Lep1Pt",   60,  0.,  240.);
    vhd.at(Jet1Pt_FR)   = new HistoData("Jet1Pt",   60,  0.,  420.);
    vhd.at(nJets_FR)    = new HistoData("nJets",    9,  -0.5, 8.5);
    vhd.at(nEvents_FR)  = new HistoData("nEvents",  1,   0.5, 1.5);
    vhd.at(nPV_FR)      = new HistoData("nPV",      30, -0.5, 29.5);
    vhd.at(mJL_FR)      = new HistoData("mJL",      60,  0.,  240.);
    vhd.at(dRJL_FR)     = new HistoData("dRJL",     50,  0.,  10);
    vhd.at(MET_FR)      = new HistoData("MET",      50,  0.,  250);
    vhd.at(MT_FR)       = new HistoData("MT",       50,  0.,  250);

    looseHistos.resize(NHISTOS_FR);
    tightHistos.resize(NHISTOS_FR);
    ratioHistos.resize(NHISTOS_FR);
    
    for (unsigned int ih = 0; ih < NHISTOS_FR; ih++){
      looseHistos.at(ih) = new TH1F(vhd.at(ih)->histoName+"_loose_"+outLabel+"_"+suffix, vhd.at(ih)->histoName+"_loose_"+outLabel+"_"+suffix, 
				    vhd.at(ih)->nBins, vhd.at(ih)->min, vhd.at(ih)->max);
      looseHistos.at(ih)->Sumw2();
      
      tightHistos.at(ih) = new TH1F(vhd.at(ih)->histoName+"_tight_"+outLabel+"_"+suffix, vhd.at(ih)->histoName+"_tight_"+outLabel+"_"+suffix, 
				    vhd.at(ih)->nBins, vhd.at(ih)->min, vhd.at(ih)->max);
      tightHistos.at(ih)->Sumw2();
      
      ratioHistos.at(ih) = new TH1F(vhd.at(ih)->histoName+"_ratio_"+outLabel+"_"+suffix, vhd.at(ih)->histoName+"_ratio_"+outLabel+"_"+suffix, 
				    vhd.at(ih)->nBins, vhd.at(ih)->min, vhd.at(ih)->max);
      ratioHistos.at(ih)->Sumw2();
    }
  }
 
  void fillLooseHistos(TprimeEvent* teve){
    looseHistos.at(Lep1Pt_FR) ->Fill(teve->lepton1->lv.Pt(), teve->weight);
    looseHistos.at(nJets_FR)  ->Fill(teve->vGoodJets.size(), teve->weight);
    looseHistos.at(nEvents_FR)->Fill(1, teve->weight);
    looseHistos.at(nPV_FR)    ->Fill(teve->nPV, teve->weight);
    looseHistos.at(MET_FR)    ->Fill(teve->met, teve->weight);
    looseHistos.at(MT_FR)     ->Fill(teve->mt, teve->weight);
    
    if (teve->vGoodJets.size() > 0){
      looseHistos.at(Jet1Pt_FR)->Fill(teve->vGoodJets.at(0)->lv.Pt(), teve->weight);
      for (unsigned int ij = 0; ij < teve->vGoodJets.size(); ij++){
	looseHistos.at(mJL_FR)->Fill((teve->lepton1->lv + teve->vGoodJets.at(ij)->lv).M(), teve->weight);
	looseHistos.at(dRJL_FR)->Fill(teve->lepton1->lv.DeltaR(teve->vGoodJets.at(ij)->lv), teve->weight);
      }
    }
  }

  void fillTightHistos(TprimeEvent* teve){
    tightHistos.at(Lep1Pt_FR) ->Fill(teve->lepton1->lv.Pt(), teve->weight);
    tightHistos.at(nJets_FR)  ->Fill(teve->vGoodJets.size(), teve->weight);
    tightHistos.at(nEvents_FR)->Fill(1, teve->weight);
    tightHistos.at(nPV_FR)    ->Fill(teve->nPV, teve->weight);
    tightHistos.at(MET_FR)    ->Fill(teve->met, teve->weight);
    tightHistos.at(MT_FR)     ->Fill(teve->mt, teve->weight);

    if (teve->vGoodJets.size() > 0){
      tightHistos.at(Jet1Pt_FR)->Fill(teve->vGoodJets.at(0)->lv.Pt(), teve->weight);
      for (unsigned int ij = 0; ij < teve->vGoodJets.size(); ij++){
	tightHistos.at(mJL_FR)->Fill((teve->lepton1->lv + teve->vGoodJets.at(ij)->lv).M(), teve->weight);
	tightHistos.at(dRJL_FR)->Fill(teve->lepton1->lv.DeltaR(teve->vGoodJets.at(ij)->lv), teve->weight);
      }
    }
  }

  void scaleTLHistos(){
    for (unsigned int ih = 0; ih < NHISTOS_FR; ih++){
      looseHistos.at(ih)->Scale(scale_);
      tightHistos.at(ih)->Scale(scale_);
    }
  }

  void getRatioHistos(){
    for (unsigned int ih = 0; ih < NHISTOS_FR; ih++){
      ratioHistos.at(ih)->Add(tightHistos.at(ih));
      ratioHistos.at(ih)->Divide(looseHistos.at(ih));
    }
  }

  void fillTLHistos(TprimeEvent* teve, bool b_Tight){
    fillLooseHistos(teve);
    if (b_Tight) fillTightHistos(teve);
  }
};

*/

#endif
