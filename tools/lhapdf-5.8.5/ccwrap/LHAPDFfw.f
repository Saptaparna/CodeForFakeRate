! -*- F90 -*-
!
! A simple Fortran wrapper around LHAPDF for interfacing to C++
! By Stefan Gieseke 2004                                            
! Adapted for LHAPDFv4 by Mike Whalley                              
! Adapted for LHAPDFv5 by Craig Group/Mike Whalley                  
! Improved string passing by Andy Buckley 

subroutine finitpdfset(name) 
  character name*(*) 
  ! print *, "@@@", name, "@@@"                                       
  ! print *, len_trim(name)                                           
  ! print *, len(name)                                                
  call InitPDFset(name) 
end subroutine finitpdfset
                                                                       
subroutine finitpdfsetm(nset,name) 
  character name*(*) 
  integer nset 
  call InitPDFsetM(nset,name) 
end subroutine finitpdfsetm
 
subroutine finitpdfsetbyname(name) 
  character name*(*) 
  ! print *, "@@@", name, "@@@"                                       
  ! print *, len_trim(name)                                           
  ! print *, len(name)                                                
  call InitPDFsetByName(name) 
end subroutine finitpdfsetbyname

subroutine finitpdfsetbynameM(nset,name) 
  character name*(*) 
  integer nset 
  call InitPDFsetByNameM(nset,name) 
end subroutine finitpdfsetbynameM
 
subroutine finitpdf(mem) 
  integer mem 
  call InitPDF(mem) 
end subroutine finitpdf
 
subroutine finitpdfM(nset,mem) 
  integer nset,mem 
  call InitPDFM(nset,mem) 
end subroutine finitpdfM

subroutine fhasphoton(haspho) 
  implicit none
  integer haspho
  logical has_photon
  haspho = 0
  if (has_photon()) then
     haspho = 1
  end if
end subroutine fhasphoton
 
subroutine fnumberpdf(set) 
  integer set 
  call numberPDF(set) 
end subroutine fnumberpdf

subroutine fnumberpdfM(nset,set) 
  integer nset,set 
  call numberPDFM(nset,set) 
end subroutine fnumberpdfM

subroutine fevolvepdf(x,Q,f) 
  real*8 x,Q 
  real*8 f(-6:6) 
  call evolvePDF(x,Q,f) 
end subroutine fevolvepdf

subroutine fevolvepdfm(nset,x,Q,f) 
  real*8 x,Q 
  real*8 f(-6:6) 
  integer nset 
  call evolvePDFM(nset,x,Q,f) 
end subroutine fevolvepdfm

subroutine fevolvepdfp(x,Q,P2,ip,f) 
  real*8 x,Q,P2 
  real*8 f(-6:6) 
  integer ip 
  call evolvePDFp(x,Q,P2,ip,f) 
end subroutine fevolvepdfp

subroutine fevolvepdfpM(nset,x,Q,P2,ip,f) 
  real*8 x,Q,P2 
  real*8 f(-6:6) 
  integer ip,nset 
  call evolvePDFpM(nset,x,Q,P2,ip,f) 
end subroutine fevolvepdfpM

subroutine fevolvepdfa(x,Q,a,f) 
  real*8 x,Q,a 
  real*8 f(-6:6) 
  call evolvePDFa(x,Q,a,f) 
end subroutine fevolvepdfa

subroutine fevolvepdfaM(nset,x,Q,a,f) 
  real*8 x,Q,a 
  real*8 f(-6:6) 
  integer nset 
  call evolvePDFaM(nset,x,Q,a,f) 
end subroutine fevolvepdfaM

subroutine fevolvepdfphoton(x,Q,f,photon) 
  real*8 x,Q,photon 
  real*8 f(-6:6) 
  call evolvePDFphoton(x,Q,f,photon) 
end subroutine fevolvepdfphoton

subroutine fevolvepdfphotonM(nset,x,Q,f,photon) 
  real*8 x,Q,photon 
  real*8 f(-6:6) 
  integer nset 
  call evolvePDFphotonM(nset,x,Q,f,photon) 
end subroutine fevolvepdfphotonM

subroutine falphaspdfm(nset,Q,ans) 
  real*8 ans,Q,alphasPDFM 
  integer nset 
  ans=alphasPDFM(nset,Q) 
end subroutine falphaspdfm

subroutine falphaspdf(Q,ans) 
  real*8 ans,Q,alphasPDF 
  ans=alphasPDF(Q) 
end subroutine falphaspdf

subroutine fgetorderpdf(order) 
  integer order 
  call getorderpdf(order) 
end subroutine fgetorderpdf

subroutine fgetorderpdfm(nset,order) 
  integer nset,order 
  call getorderpdfM(nset,order) 
end subroutine fgetorderpdfm

subroutine fgetorderas(order) 
  integer order 
  call getorderas(order) 
end subroutine fgetorderas

subroutine fgetorderasm(nset,order) 
  integer nset,order 
  call getorderasm(nset,order) 
end subroutine fgetorderasm

subroutine fgetdesc() 
  call getdesc() 
end subroutine fgetdesc

subroutine fgetdescm(nset) 
  integer nset 
  call getdescm(nset) 
end subroutine fgetdescm

subroutine fgetqmass(nf,mass) 
  integer nf 
  real*8 mass 
  call getqmass(nf,mass) 
end subroutine fgetqmass

subroutine fgetqmassm(nset,nf,mass) 
  integer nset,nf 
  real*8 mass 
  call getqmassm(nset,nf,mass) 
end subroutine fgetqmassm

subroutine fgetthreshold(nf,Q) 
  integer nf 
  real*8 Q 
  call getthreshold(nf,Q) 
end subroutine fgetthreshold

subroutine fgetthresholdm(nset,nf,Q) 
  integer nset,nf 
  real*8 Q 
  call getthresholdm(nset,nf,Q) 
end subroutine fgetthresholdm

subroutine fgetnf(nfmax) 
  integer nfmax 
  call getnf(nfmax) 
end subroutine fgetnf

subroutine fgetnfm(nset,nfmax) 
  integer nset,nfmax 
  call getnfm(nset,nfmax) 
end subroutine fgetnfm

subroutine fgetlam4(mem,xlam4) 
  integer mem 
  real*8 xlam4 
  call getlam4(mem,xlam4) 
end subroutine fgetlam4

subroutine fgetlam4m(nset,mem,xlam4) 
  integer nset,mem 
  real*8 xlam4 
  call getlam4m(nset,mem,xlam4) 
end subroutine fgetlam4m

subroutine fgetlam5(mem,xlam5) 
  integer mem 
  real*8 xlam5 
  call getlam5(mem,xlam5) 
end subroutine fgetlam5

subroutine fgetlam5m(nset,mem,xlam5) 
  integer nset,mem 
  real*8 xlam5 
  call getlam5m(nset,mem,xlam5) 
end subroutine fgetlam5m

subroutine fgetXmin(mem,xmin) 
  integer mem 
  real*8 xmin 
  call getXmin(mem,xmin) 
end subroutine fgetXmin

subroutine fgetXmax(mem,xmax) 
  integer mem 
  real*8 xmax 
  call getXmax(mem,xmax) 
end subroutine fgetXmax

subroutine fgetQ2min(mem,q2min) 
  integer mem 
  real*8 q2min 
  call getQ2min(mem,q2min) 
end subroutine fgetQ2min

subroutine fgetQ2max(mem,q2max) 
  integer mem 
  real*8 q2max 
  call getQ2max(mem,q2max) 
end subroutine fgetQ2max

subroutine fgetXminM(nset,mem,xmin) 
  integer nset,mem 
  real*8 xmin 
  call getXminM(nset,mem,xmin) 
end subroutine fgetXminM

subroutine fgetXmaxM(nset,mem,xmax) 
  integer nset,mem 
  real*8 xmax 
  call getXmaxM(nset,mem,xmax) 
end subroutine fgetXmaxM

subroutine fgetQ2minM(nset,mem,q2min) 
  integer nset,mem 
  real*8 q2min 
  call getQ2minM(nset,mem,q2min) 
end subroutine fgetQ2minM

subroutine fgetQ2maxM(nset,mem,q2max) 
  integer nset,mem 
  real*8 q2max 
  call getQ2maxM(nset,mem,q2max) 
end subroutine fgetQ2maxM

subroutine fgetMinMax(mem,xmin,xmax,q2min,q2max) 
  integer mem 
  real*8 xmin,xmax,q2min,q2max 
  call getMinMax(mem,xmin,xmax,q2min,q2max) 
end subroutine fgetMinMax

subroutine fgetMinMaxM(nset,mem,xmin,xmax,q2min,q2max) 
  integer nset,mem 
  real*8 xmin,xmax,q2min,q2max 
  call getMinMaxM(nset,mem,xmin,xmax,q2min,q2max) 
end subroutine fgetMinMaxM

subroutine fextrapolateon() 
  call SetLHAPARM('EXTRAPOLATE') 
end subroutine fextrapolateon

subroutine fextrapolateoff() 
  call SetLHAPARM('18') 
end subroutine fextrapolateoff

subroutine fsilent() 
  call SetLHAPARM('SILENT') 
end subroutine fsilent

subroutine flowkey() 
  call SetLHAPARM('LOWKEY') 
end subroutine flowkey

subroutine fdefaultverb() 
  call SetLHAPARM('19') 
end subroutine fdefaultverb

subroutine fsetpdfpath(path) 
  character path*(*)
  call SetPDFPath(path) 
end subroutine fsetpdfpath
