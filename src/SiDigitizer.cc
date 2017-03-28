 // $Id: SiDigitizer.cc 94 2010-01-26 13:18:30Z adotti $
 /**
  * @file  SiDigitizer.cc
  * @brief Implements SiDigitizer class, i.e. the digitization process.
  *
  * @date 10 Dec 2009
  * @author adotti
  */
 
 #include "G4DigiManager.hh"
 #include "SiDigitizer.hh"
 #include "SiDigi.hh"
 #include "NoiseGenerator.hh"
 #include "MeV2ChargeConverter.hh"
 //#include "CrosstalkGenerator.hh"
 #include "SiHit.hh"
 #include "G4SystemOfUnits.hh"
 #include <assert.h>
 #include <list>
 #include <map>

 
 SiDigitizer::SiDigitizer(G4String aName) :
   G4VDigitizerModule(aName) ,
   //These two are names for digits and hits collections
   digiCollectionName("SiDigitCollection") ,
   hitsCollName("SiHitCollection") ,
   //Digitization requires several components:
   //1- A pedestal level
   pedestal(0.) ,
   //2- A noise generator: a simple gaussian noise
   //Noise standard deviation is 1000 e
   //To turn it off put a value <0
   noise( 11.75 ) ,
   //3- MeV2Charge converter: converts energy deposits from MeV to Q
   //It needs a parameter: the MeV2Q conversion factor: 3.6 eV/e.
   convert( 1./(1.0*keV) ) ,
   //4- Crosstalk Generator:
   //Crosstalk needs two parameters: number of strips in each module
   //and fraction of charge that leaks.
   //To turn off crosstalk put 0.0
   //crosstalk( 0.05 , 1 ),
   //UI cmds
   messenger(this)
 {
         collectionName.push_back( digiCollectionName );
 }
 
 void SiDigitizer::Digitize()
 {
   //First we create a digits collection...
   SiDigiCollection * digiCollection = new SiDigiCollection("SiDigitizer",digiCollectionName);
   //Create a empty collection with one digits for each strip
   const G4int numPlanes = 736;  //Number of Si detectors
   const G4int numStrips = 1; //Number of strip per plane
 
   //The following matrix is used to map: (plane,strip) to
   //its corresponding digit.
   //Example plane = 1 , strip = 10
   //Digi* theDigi = digitsMap[plane][strip]
   //Initialize with NULL pointers
   std::vector< std::vector<SiDigi*> > digitsMap(numPlanes);
   for ( G4int i = 0 ; i < numPlanes ; ++i )
   {
           digitsMap[i].resize(numStrips,static_cast<SiDigi*>(0));
   }
 
 
   //Create empty digits
   for ( G4int plane = 0 ; plane < numPlanes ; ++plane ) {
     for ( G4int strip = 0 ; strip < numStrips ; ++strip )
       {
         SiDigi* newDigi = new SiDigi(plane,strip);
         //Remember the hit so we can find it by plane,strip
         digitsMap[plane][strip] = newDigi;
         //Now insert the digit in the digit collection
         digiCollection->insert(newDigi);
       }
   }
   //We can now simulate the electronic circuit.
 
   //We search and retrieve the hits collection
   G4DigiManager* digMan = G4DigiManager::GetDMpointer();
   G4int SiHitCollID = digMan->GetHitsCollectionID( hitsCollName );//Number associated to hits collection names hitsCollName
   const SiHitCollection* hitCollection = static_cast<const SiHitCollection*>(digMan->GetHitsCollection(SiHitCollID));
 
   if ( hitCollection )
     {
           //G4cout<<"-------------"<<G4endl;
           //G4cout<<"Number of hits: "<<hitCollection->entries()<<G4endl;
           for ( G4int i = 0 ; i < hitCollection->entries() ; ++i )
         {
           //For each Hit we now get to which strip it belongs
           //And convert its edep in charge units
           SiHit* aHit = (*hitCollection)[i];
           //Un-comment this line if you want to record only
           //primary energy depositions
           //if ( hit->GetIsPrimary() == false ) continue;
           G4int hitPlane = aHit->GetPlaneNumber();
           G4int hitStrip = aHit->GetStripNumber();
           G4double edep = aHit->GetEdep();
           //Converter object accept MeV unit as input
           G4double charge = convert( edep/MeV );
 
           digitsMap[hitPlane][hitStrip]->Add(charge);
         }
     }
   else //Something really bad happened...
     {
       G4cerr<<"Could not found SiHit collection with name:"<<hitsCollName<<G4endl;
     }
 
   //We can now proceed simulating the crosstalk
   //MakeCrosstalk( digitsMap );
 
   //We can now add, for each strip the noise
   for ( size_t d = 0 ; d < digiCollection->GetSize(); ++d )
   {
           SiDigi* digi = static_cast< SiDigi* >( digiCollection->GetDigi(d) );
           //First we add a pedestal
           digi->Add( pedestal );
 
           //Then we smear for the noise
           digi->Add( noise() );
 
           //Debug Output!!!!
           //G4cout<<"Digit :"<<d<<" ";
           //digi->Print();
 
   }
 
   //This line is very important,
   //differently from hits we need to store the digits
   //each event explicitly.
   //This actually gives us quite a lot of flexibility
   //For example it is possible to simulate a malfunctioning
   //detector: you can comment this line and the digits
   //will not be available. Actually this example can be useful
   //for example if you want to study the effect of "dead" channels
   //in the physics measurement you perform.
   StoreDigiCollection(digiCollection);
 }
 /*
 void SiDigitizer::MakeCrosstalk(std::vector< std::vector< SiDigi* > >& digitsMap )
 {
         //We have to make some conversions:
         //1- Take the digits of plane 2: we make crosstalk only for the second plane
         //2- Make a HepVector of the collected charges, ordered by Strip number
         //3- Apply transformation
         //4- Update digits with the new charge
         int plane = 1;//xtalk only on middle plane (DUT)
         std::vector< SiDigi* >& thisPlane = digitsMap[plane];
         size_t numStrips = thisPlane.size();
         size_t strip = 0;
         CLHEP::HepVector in(numStrips);
         for ( ; strip<numStrips;++strip )
         {
                 in[strip] = thisPlane[strip]->GetCharge();
         }
         CLHEP::HepVector out = crosstalk( in );
         for ( strip=0; strip < numStrips ; ++strip )
         {
                 thisPlane[strip]->SetCharge( out[strip] );
         }
 }
 */
