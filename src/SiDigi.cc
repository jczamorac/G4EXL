 // $Id: SiDigi.cc 94 2010-01-26 13:18:30Z adotti $
 /**
  * @file SiDigi.cc
  * @brief implements SiDigi detector output class
  *
  * @date 10 Dec 2009
  * @author adotti
  */
 
 #include "SiDigi.hh"
#include "G4SystemOfUnits.hh" 
 // -- one more nasty trick for new and delete operator overloading:
 G4Allocator<SiDigi> SiDigiAllocator;
 
 SiDigi::SiDigi(const int& pn,const int& sn) :
                 charge(0) ,
                 stripNumber(sn) ,
                 planeNumber(pn) ,
                 isPrimary(false)
 {
 
 }
 
 void SiDigi::Print()
 {
   G4cout<<"Digit: Plane= "<<planeNumber<<" Strip= "<<stripNumber<<" with Charge= "<<charge<<G4endl;
 }
