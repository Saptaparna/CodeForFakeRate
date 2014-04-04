#!/bin/tcsh
# Parameters of the script:
# directory
# output file name

make DrawOneHistoWithSyst
set startDir=$cwd
cd $argv[1]
set rootFile=$cwd/$argv[2]
echo $cwd

#$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B MET     1 "MET [GeV]" 2
#$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsAS MuMu 2L_AS Lep1Pt  1 "Leading lepton p_{T} [GeV/c]" 5
#cd ..
#exit(1)
#
#DrawOneHisto parameter list:
#1: Input directory in root file
#2: Channel (ElEl, ElMu or MuMu   
#3: Prefix for histograms 
#4: Name of histogram
#5: Log or not log 
#6: x-Axis name
#7: Optional: rebin by this number

#mkdir 8TeV_test_SS/
#mkdir AllPDF


##Two good leptons only -- no charge requirement
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS Lep1Pt  1 "Leading lepton p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS Lep2Pt  1 "Second lepton p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS Lep3Pt  1 "Third lepton p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS Jet1Pt  1 "Leading jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS Jet2Pt  1 "Second jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS LepInvM 1 "Invariant Mass of Lepton Pair [GeV/c^{2}]" 4
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS nJets   1 "Number of Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS nBJets  1 "Number of b-tagged jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS HT      1 "H_{T} [GeV]" 20
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS MET     1 "MET [GeV]"
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS nLept   1 "Number of Leptons"
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS sumPtL  1 "Sum of lepton p_{T} [GeV/c]" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS sumPtJ  1 "Sum of jet p_{T} [GeV/c]" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS minMlb  1 "Min(m_{lb}})" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS Mlb     1 "m_{lb}}" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS dRlept  1 "#delta R (l1,l2)" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS MinLepCATopdR	1 "Min (#delta R (l,top-jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS MinLepCA8dR	1 "Min (#delta R (l,CA8 Jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS MinLepAK5dR	1 "Min (#delta R (l,AK5 jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS MinLepJetdR 	1 "Min (#delta R (l,jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS MinLepBJetdR	1 "Min (#delta R (l,b-jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS CA8Jet1Pt  1 "Leading CA8 Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS CA8Jet2Pt  1 "Second CA8 Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS nCA8Jets   1 "Number of CA8 Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS CA8Btag    1 "CA8 Jet CSV discriminant"
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS CATopJet1Pt  1 "Leading CATop Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS CATopJet2Pt  1 "Second CATop Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS nCATopJets   1 "Number of CATop Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS CATopBtag    1 "CATop Jet CSV discriminant"
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsSS All 2L_SS amwt    1 "AMWT mass" 5
#
#
mkdir TwoLeptonsSS
mv  *_2L_SS*.pdf *_2L_SS*.png            TwoLeptonsSS
cd TwoLeptonsSS
## diowroot.pl -o index.html -t 'Two leptons, without charge requirements'
cd ..
##cp indexFiles/i2L_AS.html TwoLeptons/index.html
##mv h_2L_AS*pdf            AllPDF/

#Two same-sign/opposite-sign leptons, with eventual vetos
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV Lep1Pt  1 "Leading lepton p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV Lep2Pt  1 "Second lepton p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV Lep3Pt  1 "Third lepton p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV Jet1Pt  1 "Leading jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV Jet2Pt  1 "Second jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV LepInvM 1 "Invariant Mass of Lepton Pair [GeV/c^{2}]" 4
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV nJets   1 "Number of Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV nBJets  1 "Number of b-tagged jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV HT      1 "H_{T} [GeV]" 20
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV MET     1 "MET [GeV]"

$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV nLept   1 "Number of Leptons"
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV sumPtL  1 "Sum of lepton p_{T} [GeV/c]" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV sumPtJ  1 "Sum of jet p_{T} [GeV/c]" 2

$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV minMlb  1 "Min(m_{lb}})" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV Mlb     1 "m_{lb}}" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV dRlept  1 "#delta R (l1,l2)" 2

$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV MinLepCATopdR	1 "Min (#delta R (l,top-jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV MinLepCA8dR	1 "Min (#delta R (l,CA8 Jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV MinLepAK5dR	1 "Min (#delta R (l,AK5 jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV MinLepJetdR 	1 "Min (#delta R (l,jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV MinLepBJetdR	1 "Min (#delta R (l,b-jet))" 2

$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV CA8Jet1Pt  1 "Leading CA8 Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV CA8Jet2Pt  1 "Second CA8 Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV nCA8Jets   1 "Number of CA8 Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV CA8Btag    1 "CA8 Jet CSV discriminant"

$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV CATopJet1Pt  1 "Leading CATop Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV CATopJet2Pt  1 "Second CATop Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV nCATopJets   1 "Number of CATop Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV CATopBtag    1 "CATop Jet CSV discriminant"

#$startDir/DrawOneHistoWithSyst $rootFile TwoLeptonsZQV All 2L_ZQV amwt    1 "AMWT mass" 5

mkdir                     TwoLeptonsSigned

mv *_2L_ZQV*.eps *_2L_ZQV*.p*            TwoLeptonsSigned
cd  TwoLeptonsSigned
# diowroot.pl -o index.html -t 'Two leptons, with charge requirements'
cd ..

# Two same-sign/opposite-sign leptons, with eventual vetos, and 2 jets
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J Lep1Pt  1 "Leading lepton p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J Lep2Pt  1 "Second lepton p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J Lep3Pt  1 "Third lepton p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J Jet1Pt  1 "Leading jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J Jet2Pt  1 "Second jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J LepInvM 1 "Invariant Mass of Lepton Pair [GeV/c^{2}]" 4
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J nJets   1 "Number of Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J nBJets  1 "Number of b-tagged jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J HT      1 "H_{T} [GeV]" 20
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J MET     1 "MET [GeV]"

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J nLept   1 "Number of Leptons"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J sumPtL  1 "Sum of lepton p_{T} [GeV/c]" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J sumPtJ  1 "Sum of jet p_{T} [GeV/c]" 2

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J minMlb  1 "Min(m_{lb}})" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J Mlb     1 "m_{lb}}" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J dRlept  1 "#delta R (l1,l2)" 2

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J MinLepCATopdR	1 "Min (#delta R (l,top-jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J MinLepCA8dR	1 "Min (#delta R (l,CA8 Jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J MinLepAK5dR	1 "Min (#delta R (l,AK5 jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J MinLepJetdR 	1 "Min (#delta R (l,jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J MinLepBJetdR	1 "Min (#delta R (l,b-jet))" 2

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J CA8Jet1Pt  1 "Leading CA8 Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J CA8Jet2Pt  1 "Second CA8 Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J nCA8Jets   1 "Number of CA8 Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J CA8Btag    1 "CA8 Jet CSV discriminant"

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J CATopJet1Pt  1 "Leading CATop Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J CATopJet2Pt  1 "Second CATop Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J nCATopJets   1 "Number of CATop Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J CATopBtag    1 "CATop Jet CSV discriminant"

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ All 2L_2J amwt    1 "AMWT mass" 10


mkdir                     TwoLeptonsSigned2Jets
mv *_2L_2J*.p* *_2L_2J*.eps            TwoLeptonsSigned2Jets
cd  TwoLeptonsSigned2Jets
# diowroot.pl -o index.html -t 'Two leptons, with charge requirements, and 2 jets'
cd ..

# Two same-sign/opposite-sign leptons, with eventual vetos, and 2 b-jets
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet Lep1Pt  1 "Leading lepton p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet Lep2Pt  1 "Second lepton p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet Lep3Pt  1 "Third lepton p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet Jet1Pt  1 "Leading jet p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet Jet2Pt  1 "Second jet p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet LepInvM 1 "Invariant Mass of Lepton Pair [GeV/c^{2}]" 4
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet nJets   1 "Number of Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet nBJets  1 "Number of b-tagged jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet HT      1 "H_{T} [GeV]" 20
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet MET     1 "MET [GeV]" 2

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet nLept   1 "Number of Leptons"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet sumPtL  1 "Sum of lepton p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet sumPtJ  1 "Sum of jet p_{T} [GeV/c]" 5

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet minMlb  1 "Min(m_{lb}})" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet Mlb     1 "m_{lb}}" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet dRlept  1 "#delta R (l1,l2)" 2

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet MinLepCATopdR	1 "Min (#delta R (l,top-jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet MinLepCA8dR	1 "Min (#delta R (l,CA8 Jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet MinLepAK5dR	1 "Min (#delta R (l,AK5 jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet MinLepJetdR 	1 "Min (#delta R (l,jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet MinLepBJetdR	1 "Min (#delta R (l,b-jet))" 2

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet CA8Jet1Pt  1 "Leading CA8 Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet CA8Jet2Pt  1 "Second CA8 Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet nCA8Jets   1 "Number of CA8 Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet CA8Btag    1 "CA8 Jet CSV discriminant"

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet CATopJet1Pt  1 "Leading CATop Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet CATopJet2Pt  1 "Second CATop Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet nCATopJets   1 "Number of CATop Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet CATopBtag    1 "CATop Jet CSV discriminant"

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJmet All 2L_2Jmet amwt    1 "AMWT mass" 10



mkdir                     TwoLeptonsSigned2JetsMET
mv *_2L_2Jmet*.p* *_2L_2Jmet*.eps            TwoLeptonsSigned2JetsMET
cd  TwoLeptonsSigned2JetsMET
# diowroot.pl -o index.html -t 'Two leptons, with charge requirements, and 2 jets, and MET'
cd ..


# Two same-sign/opposite-sign leptons, with eventual vetos, and 2 b-jets
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B Lep1Pt  1 "Leading lepton p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B Lep2Pt  1 "Second lepton p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B Lep3Pt  1 "Third lepton p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B Jet1Pt  1 "Leading jet p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B Jet2Pt  1 "Second jet p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B LepInvM 1 "Invariant Mass of Lepton Pair [GeV/c^{2}]" 4
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B nJets   1 "Number of Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B nBJets  1 "Number of b-tagged jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B HT      1 "H_{T} [GeV]" 20
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B MET     1 "MET [GeV]" 2

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B nLept   1 "Number of Leptons"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B sumPtL  1 "Sum of lepton p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B sumPtJ  1 "Sum of jet p_{T} [GeV/c]" 5

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B minMlb  1 "Min(m_{lb}})" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B Mlb     1 "m_{lb}}" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B dRlept  1 "#delta R (l1,l2)" 2

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B MinLepCATopdR	1 "Min (#delta R (l,top-jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B MinLepCA8dR	1 "Min (#delta R (l,CA8 Jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B MinLepAK5dR	1 "Min (#delta R (l,AK5 jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B MinLepJetdR 	1 "Min (#delta R (l,jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B MinLepBJetdR	1 "Min (#delta R (l,b-jet))" 2

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B CA8Jet1Pt  1 "Leading CA8 Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B CA8Jet2Pt  1 "Second CA8 Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B nCA8Jets   1 "Number of CA8 Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B CA8Btag    1 "CA8 Jet CSV discriminant"

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B CATopJet1Pt  1 "Leading CATop Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B CATopJet2Pt  1 "Second CATop Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B nCATopJets   1 "Number of CATop Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B CATopBtag    1 "CATop Jet CSV discriminant"

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2B All 2L_2J2B amwt    1 "AMWT mass" 10



mkdir                     TwoLeptonsSigned2BJets
mv *_2L_2J2B*.p* *_2L_2J2B*.eps            TwoLeptonsSigned2BJets
cd  TwoLeptonsSigned2BJets
# diowroot.pl -o index.html -t 'Two leptons, with charge requirements, and 2 b-jets'
cd ..

# Two same-sign/opposite-sign leptons, with eventual vetos, and 2 b-jets
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B Lep1Pt  1 "Leading lepton p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B Lep2Pt  1 "Second lepton p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B Lep3Pt  1 "Third lepton p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B Jet1Pt  1 "Leading jet p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B Jet2Pt  1 "Second jet p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B LepInvM 1 "Invariant Mass of Lepton Pair [GeV/c^{2}]" 4
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B nJets   1 "Number of Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B nBJets  1 "Number of b-tagged jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B HT      1 "H_{T} [GeV]" 20
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B MET     1 "MET [GeV]" 2

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B nLept   1 "Number of Leptons"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B sumPtL  1 "Sum of lepton p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B sumPtJ  1 "Sum of jet p_{T} [GeV/c]" 5

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B minMlb  1 "Min(m_{lb}})" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B Mlb     1 "m_{lb}}" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B dRlept  1 "#delta R (l1,l2)" 2

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B MinLepCATopdR   1 "Min (#delta R (l,top-jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B MinLepCA8dR     1 "Min (#delta R (l,CA8 Jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B MinLepAK5dR     1 "Min (#delta R (l,AK5 jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B MinLepJetdR     1 "Min (#delta R (l,jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B MinLepBJetdR    1 "Min (#delta R (l,b-jet))" 2

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B CA8Jet1Pt  1 "Leading CA8 Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B CA8Jet2Pt  1 "Second CA8 Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B nCA8Jets   1 "Number of CA8 Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B CA8Btag    1 "CA8 Jet CSV discriminant"

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B CATopJet1Pt  1 "Leading CATop Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B CATopJet2Pt  1 "Second CATop Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B nCATopJets   1 "Number of CATop Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B CATopBtag    1 "CATop Jet CSV discriminant"

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ1B All 2L_2J1B amwt    1 "AMWT mass" 10



mkdir                     TwoLeptonsSigned1BJets
mv *_2L_2J1B*.p* *_2L_2J1B*.eps            TwoLeptonsSigned1BJets
cd  TwoLeptonsSigned2BJets
# diowroot.pl -o index.html -t 'Two leptons, with charge requirements, and 1 b-jet'
cd ..



$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet Lep1Pt  1 "Leading lepton p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet Lep2Pt  1 "Second lepton p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet Lep3Pt  1 "Third lepton p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet Jet1Pt  1 "Leading jet p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet Jet2Pt  1 "Second jet p_{T} [GeV/c]" 10
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet LepInvM 1 "Invariant Mass of Lepton Pair [GeV/c^{2}]" 4
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet nJets   1 "Number of Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet nBJets  1 "Number of b-tagged jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet HT      1 "H_{T} [GeV]" 20
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet MET     1 "MET [GeV]" 2

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet nLept   1 "Number of Leptons"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet sumPtL  1 "Sum of lepton p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet sumPtJ  1 "Sum of jet p_{T} [GeV/c]" 5

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet minMlb  1 "Min(m_{lb}})" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet Mlb     1 "m_{lb}}" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet dRlept  1 "#delta R (l1,l2)" 2

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet MinLepCATopdR	1 "Min (#delta R (l,top-jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet MinLepCA8dR	1 "Min (#delta R (l,CA8 Jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet MinLepAK5dR	1 "Min (#delta R (l,AK5 jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet MinLepJetdR 	1 "Min (#delta R (l,jet))" 2
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet MinLepBJetdR	1 "Min (#delta R (l,b-jet))" 2

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet CA8Jet1Pt  1 "Leading CA8 Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet CA8Jet2Pt  1 "Second CA8 Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet nCA8Jets   1 "Number of CA8 Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet CA8Btag    1 "CA8 Jet CSV discriminant"

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet CATopJet1Pt  1 "Leading CATop Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet CATopJet2Pt  1 "Second CATop Jet p_{T} [GeV/c]" 5
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet nCATopJets   1 "Number of CATop Jets"
$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet CATopBtag    1 "CATop Jet CSV discriminant"

$startDir/DrawOneHistoWithSyst $rootFile TwoLTwoJ2Bmet All 2L_2J2Bmet amwt    1 "AMWT mass" 10


mkdir                     TwoLeptonsSigned2BJetMET
mv *_2L_2J2Bmet*.p* *_2L_2J2Bmet*.eps            TwoLeptonsSigned2BJetMET
cd  TwoLeptonsSigned1BJet
# diowroot.pl -o index.html -t 'Two leptons, with charge requirements, 2 or more jets, 2 or more b-jets and MET'

cd ..


cd $startDir
