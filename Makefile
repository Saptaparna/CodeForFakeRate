CXX=g++

ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs)

ROOTIL      = $(ROOTCFLAGS) $(ROOTLIBS)

LIBS            = libObjects.so

TopPartnersv4:
	$(CXX) $(ROOTIL) -L /data1/sapta/Code_from_Thomas_nov27/tools/lib  -l Objects -l MassAMWT -l LHAPDF -l JetMETObjects -I /data1/sapta/Code_from_Thomas_nov27/tools -I /data1/speer/tblsm/tools/lhapdf585_64/include -O2 -Wall -o TopPartnersv4 TopPartnersv4.C

PrintEfficiencies:
	$(CXX) $(ROOTIL) -O2 -Wall -o PrintEfficiencies PrintEfficiencies.C

DataDrivenOS:
	$(CXX) $(ROOTIL) -O2 -Wall -o DataDrivenOS DataDrivenOS.C

CrossCheckMCv2:
	$(CXX) $(ROOTIL) -O2 -Wall -o CrossCheckMCv2 CrossCheckMCv2.C

DrawOneHisto:
	$(CXX) $(ROOTIL) -O2 -Wall -o DrawOneHisto DrawOneHisto.C

DrawOneHistoFR:
	$(CXX) $(ROOTIL) -O2 -Wall -o DrawOneHistoFR DrawOneHistoFR.C

DrawOneHistoDDB:
	$(CXX) $(ROOTIL) -O2 -Wall -o DrawOneHistoDDB DrawOneHistoDDB.C

DrawOneHistoWithSyst:
	$(CXX) $(ROOTIL) -O2 -Wall -o DrawOneHistoWithSyst DrawOneHistoWithSyst.C

EventYields:
	$(CXX) $(ROOTIL) -O2 -Wall -o EventYields EventYields.C

Systematics:
	$(CXX) $(ROOTIL) -O2 -Wall -o Systematics Systematics.C

PromptLnTProb:
	$(CXX) $(ROOTIL) -O2 -Wall -o PromptLnTProb PromptLnTProb.C

GetFakeRate:
	$(CXX) $(ROOTIL) -L /data1/sapta/Code_from_Thomas_nov29/tools/lib  -l Objects -l MassAMWT -l LHAPDF -l JetMETObjects -I /data1/sapta/Code_from_Thomas_nov29/tools -O2 -Wall -o GetFakeRate GetFakeRate.C

ClosureTest:
	$(CXX) $(ROOTIL) -L /data1/sapta/Code_from_Thomas_nov29/tools/lib  -l Objects -l MassAMWT -l LHAPDF -l JetMETObjects -I /data1/sapta/Code_from_Thomas_nov29/tools -O2 -Wall -o ClosureTest ClosureTest.C

LooseTopPartnersv4:
	$(CXX) $(ROOTIL) -L /data1/sapta/Code_from_Thomas_nov29/tools/lib  -l Objects -l MassAMWT -l LHAPDF -l JetMETObjects -I /data1/sapta/Code_from_Thomas_nov29/tools -O2 -Wall -o LooseTopPartnersv4 LooseTopPartnersv4.C

IsoCheck:
	$(CXX) $(ROOTIL) -O2 -Wall -o IsoCheck IsoCheck.C

ErrorPropagation:
	$(CXX) $(ROOTIL) -O2 -Wall -o ErrorPropagation ErrorPropagation.C

clean: 
	rm *.o *.so *.d


all: GetFakeRate ClosureTest LooseTopPartnersv4

.PHONY: TopPartnersv4
.PHONY: PrintEfficiencies
.PHONY: DataDrivenOS
.PHONY: CrossCheckMCv2
.PHONY: DrawOneHisto
.PHONY: DrawOneHistoFR
.PHONY: DrawOneHistoDDB
.PHONY: DrawOneHistoWithSyst
.PHONY: EventYields
.PHONY: Systematics
.PHONY: PromptLnTProb
.PHONY: LooseTopPartnersv4
.PHONY: GetFakeRate
.PHONY: IsoCheck
.PHONY: ErrorPropagation
.PHONY: ClosureTest
