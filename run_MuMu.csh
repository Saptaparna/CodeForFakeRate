echo "


*****TTbar MadGraph****

" > TTJets_MuMu.txt
echo "

*****Matched to l-hadrons*****" >> TTJets_MuMu.txt
./GetFakeRate MuMu 2012 FakeRate_Data TTJets_Nov20_FullGenInfo_all.root 1 >> TTJets_MuMu.txt
echo "

*****Matched to c-hadrons******" >> TTJets_MuMu.txt
./GetFakeRate MuMu 2012 FakeRate_Data TTJets_Nov20_FullGenInfo_all.root 4 >> TTJets_MuMu.txt
echo "

*****Matched to b-hadrons******" >> TTJets_MuMu.txt
./GetFakeRate MuMu 2012 FakeRate_Data TTJets_Nov20_FullGenInfo_all.root 5 >> TTJets_MuMu.txt
echo "

*****Matched to Ws******" >> TTJets_MuMu.txt
./GetFakeRate MuMu 2012 FakeRate_Data TTJets_Nov20_FullGenInfo_all.root 24 >> TTJets_MuMu.txt
echo "

****unMatched*****" >> TTJets_MuMu.txt
./GetFakeRate MuMu 2012 FakeRate_Data TTJets_Nov20_FullGenInfo_all.root 0 >> TTJets_MuMu.txt

mkdir TTJets_MadGraph_MuMu
mv  gfOutFile_FakeRate_Data_MuMu_1.root TTJets_MadGraph_MuMu
mv  gfOutFile_FakeRate_Data_MuMu_4.root TTJets_MadGraph_MuMu
mv  gfOutFile_FakeRate_Data_MuMu_5.root TTJets_MadGraph_MuMu
mv  gfOutFile_FakeRate_Data_MuMu_24.root TTJets_MadGraph_MuMu
mv  gfOutFile_FakeRate_Data_MuMu_0.root TTJets_MadGraph_MuMu


echo "


*****TTbar POWHEG****

" >> TTJets_MuMu.txt

echo " 

*****Matched to l-hadrons*****" >> TTJets_MuMu.txt
./GetFakeRate MuMu 2012 FakeRate_Data TTJets_POWHEG_FullGenInfo_all.root 1 >> TTJets_MuMu.txt
echo "

*****Matched to c-hadrons******" >> TTJets_MuMu.txt
./GetFakeRate MuMu 2012 FakeRate_Data TTJets_POWHEG_FullGenInfo_all.root 4 >> TTJets_MuMu.txt
echo "

*****Matched to b-hadrons******" >> TTJets_MuMu.txt
./GetFakeRate MuMu 2012 FakeRate_Data TTJets_POWHEG_FullGenInfo_all.root 5 >> TTJets_MuMu.txt
echo "

*****Matched to Ws******" >> TTJets_MuMu.txt
./GetFakeRate MuMu 2012 FakeRate_Data TTJets_POWHEG_FullGenInfo_all.root 24 >> TTJets_MuMu.txt
echo "

****unMatched*****" >> TTJets_MuMu.txt
./GetFakeRate MuMu 2012 FakeRate_Data TTJets_POWHEG_FullGenInfo_all.root 0 >> TTJets_MuMu.txt

mkdir TTJets_POWHEG_MuMu
mv  gfOutFile_FakeRate_Data_MuMu_1.root TTJets_POWHEG_MuMu
mv  gfOutFile_FakeRate_Data_MuMu_4.root TTJets_POWHEG_MuMu
mv  gfOutFile_FakeRate_Data_MuMu_5.root TTJets_POWHEG_MuMu
mv  gfOutFile_FakeRate_Data_MuMu_24.root TTJets_POWHEG_MuMu
mv  gfOutFile_FakeRate_Data_MuMu_0.root TTJets_POWHEG_MuMu
