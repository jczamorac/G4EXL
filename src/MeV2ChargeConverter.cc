 // $Id: MeV2ChargeConverter.cc 25 2010-01-05 17:18:05Z adotti $
 /**
  * @file MeV2ChargeConverter.cc
  * @brief Converter class MeV2ChargeConverter implementation.
  *
  * @date 10 Dec 2009
  * @author adotti
  */
 
 #include "MeV2ChargeConverter.hh"
 
 MeV2ChargeConverter::MeV2ChargeConverter(const G4double& value) : MeV2Q(value)
 {
 }
 
 G4double MeV2ChargeConverter::operator()( G4double input ) const
 {
   /* Very simple!
    */
   return input*MeV2Q;
 }