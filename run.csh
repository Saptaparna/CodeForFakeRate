echo "


*****TTbar MadGraph****

" > TTJets_1.txt
echo "

*****Matched to l-hadrons*****" >> TTJets_1.txt
./GetFakeRate ElEl 2012 FakeRate_Data TTJets_Nov20_FullGenInfo_all.root 1 >> TTJets_1.txt
echo "

*****Matched to c-hadrons******" >> TTJets_1.txt
./GetFakeRate ElEl 2012 FakeRate_Data TTJets_Nov20_FullGenInfo_all.root 4 >> TTJets_1.txt
echo "

*****Matched to b-hadrons******" >> TTJets_1.txt
./GetFakeRate ElEl 2012 FakeRate_Data TTJets_Nov20_FullGenInfo_all.root 5 >> TTJets_1.txt
echo "

*****Matched to Ws******" >> TTJets_1.txt
./GetFakeRate ElEl 2012 FakeRate_Data TTJets_Nov20_FullGenInfo_all.root 24 >> TTJets_1.txt
echo "

****unMatched*****" >> TTJets_1.txt
./GetFakeRate ElEl 2012 FakeRate_Data TTJets_Nov20_FullGenInfo_all.root 0 >> TTJets_1.txt

mkdir TTJets_MadGraph_ElEl
mv  gfOutFile_FakeRate_Data_ElEl_1.root TTJets_MadGraph_ElEl
mv  gfOutFile_FakeRate_Data_ElEl_4.root TTJets_MadGraph_ElEl
mv  gfOutFile_FakeRate_Data_ElEl_5.root TTJets_MadGraph_ElEl
mv  gfOutFile_FakeRate_Data_ElEl_24.root TTJets_MadGraph_ElEl
mv  gfOutFile_FakeRate_Data_ElEl_0.root TTJets_MadGraph_ElEl
echo "

*****TTbar POWHEG****

" >> TTJets_1.txt


echo " 

*****Matched to l-hadrons*****" >> TTJets_1.txt
./GetFakeRate ElEl 2012 FakeRate_Data TTJets_POWHEG_FullGenInfo_all.root 1 >> TTJets_1.txt
echo "

*****Matched to c-hadrons******" >> TTJets_1.txt
./GetFakeRate ElEl 2012 FakeRate_Data TTJets_POWHEG_FullGenInfo_all.root 4 >> TTJets_1.txt
echo "

*****Matched to b-hadrons******" >> TTJets_1.txt
./GetFakeRate ElEl 2012 FakeRate_Data TTJets_POWHEG_FullGenInfo_all.root 5 >> TTJets_1.txt
echo "

*****Matched to Ws******" >> TTJets_1.txt
./GetFakeRate ElEl 2012 FakeRate_Data TTJets_POWHEG_FullGenInfo_all.root 24 >> TTJets_1.txt
echo "

****unMatched*****" >> TTJets_1.txt
./GetFakeRate ElEl 2012 FakeRate_Data TTJets_POWHEG_FullGenInfo_all.root 0 >> TTJets_1.txt

mkdir TTJets_POWHEG_ElEl
mv  gfOutFile_FakeRate_Data_ElEl_1.root TTJets_POWHEG_ElEl
mv  gfOutFile_FakeRate_Data_ElEl_4.root TTJets_POWHEG_ElEl
mv  gfOutFile_FakeRate_Data_ElEl_5.root TTJets_POWHEG_ElEl
mv  gfOutFile_FakeRate_Data_ElEl_24.root TTJets_POWHEG_ElEl
mv  gfOutFile_FakeRate_Data_ElEl_0.root TTJets_POWHEG_ElEl
