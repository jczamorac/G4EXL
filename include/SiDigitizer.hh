 // $Id: SiDigitizer.hh 33 2010-01-14 17:08:18Z adotti $
 /**
  * @file   SiDigitizer.hh
  *
  * @date   10 Dec 2009
  * @author adotti
  *
  * @brief Defines the digitization process
  */
 
 #ifndef SIDIGITIZER_HH_
 #define SIDIGITIZER_HH_
 
 
 #include "G4VDigitizerModule.hh"
 #include "SiDigi.hh"
 #include "NoiseGenerator.hh"
 #include "MeV2ChargeConverter.hh"
 //#include "CrosstalkGenerator.hh"
 #include "SiDigitizerMessenger.hh"
 
 /*!
  * \brief Simulation of the digitization process
  *
  * This class is responsible of the simulation of the ditis creation. i.e. it is responsible
  * to simulate the read-out of the detector.
  * Geant4 provides hits in the sensitive detector (i.e. energy depositions and position in
  * elements of the detector that have been declared sensitive),
  * this class is responsible to convert these hits in the electronic read-out format.
  * \sa SiDigi
  * 
  * Digitization consists of the following steps:
  *  -# converting the energy deposit in charge
  *  -# simulate the strip cross talk
  *  -# for each strip add a pedestal
  *  -# smear the collected charge with electronic noise
  *  -# add cross talk
  * 
  * All relevant methods are virtual, you can inherit from
  * this base class to overwrite behaviour.
  * This classes uses two support classes to simulate noise and
  * convert energy deposit (in MeV) to the appropriate units.
  * \sa MeV2ChargeConverter and \sa NoiseGenerator
  */
 class SiDigitizer : public G4VDigitizerModule
 {
 public:
   /*! \brief constructor
    *
    * Creates a digitization module
    * @param aName The name of the module
    */
   SiDigitizer(G4String aName);
 
   //! Empty destructor
   virtual ~SiDigitizer() {};
 
   /*! \brief Perform digitization
    *
    * This method is declared pure virtual in the base class
    * and thus must be implemented
    */
   virtual void Digitize();
 protected:
   //! \name simulate electronics
   //@{
   /*! \brief Simulate crosstalk between strips
    *
    * The charge collected by one strip "leaks" to the adjacent strips
    * Thus the charge collected by the strip that has been "hit"
    * is reduced and part of this goes to the adjacent strips
    * @param digitsMap : the digits collection digitsMap[ planeNumber ][ stripNumber ]
    * Important: crosstalk should be simulated before noise and bedestal
    * is added. \sa Digitize
    */
   //virtual void MakeCrosstalk(std::vector< std::vector< SiDigi* > >& digitsMap);
   //@}
 public:
   //! \name some simple set & get functions
   //@{
   //TODO: Add setters for the other noise parameters?
   //TODO: make a messanger to set parameters?
   inline void     SetPedestal( const G4double& aValue )         { pedestal = aValue; }
   inline void     SetNoise( const G4double& aValue )            { noise = NoiseGenerator(aValue); }
   //inline void     SetCrosstalk( const G4double& aValue )        { crosstalk = CrosstalkGenerator(aValue,48); }
   inline void     SetConversionFactor( const G4double& aValue ) { convert = MeV2ChargeConverter(aValue); }
   inline void     SetCollectionName( const G4String& aName )    { digiCollectionName = aName; }
   inline void     SetHitsCollectionName( const G4String& aName ){ hitsCollName = aName; }
   //@}
 private:
   //! Name of the digits collection
   G4String digiCollectionName;
   //! Name of the hits collection. Should match what has been used in \sa SensitiveDetector
   G4String hitsCollName;
   //! Pedestal level
   G4double pedestal;
   //! The object responsible to generate the electronic noise
   NoiseGenerator noise;
   //! The object that converts the energy deposit in collected charge
   MeV2ChargeConverter convert;
   //! The object that handles cross talk
   //CrosstalkGenerator crosstalk;
   //! Messenger to implement some UI commands
   SiDigitizerMessenger messenger;
 };
 
 #endif /* SIDIGITIZER_HH_ */
