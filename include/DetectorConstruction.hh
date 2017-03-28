 // $Id: DetectorConstruction.hh 33 2010-01-14 17:08:18Z adotti $
 #ifndef DetectorConstruction_h
 #define DetectorConstruction_h 1
 
 /**
  * @file
  * @brief Defines mandatory user class DetectorConstruction.
  */
 
 #include "globals.hh"
 #include "G4VUserDetectorConstruction.hh"
 #include "G4ThreeVector.hh"
 #include "G4PVParameterised.hh"
 
 class G4LogicalVolume;
 class G4VPhysicalVolume;
 class G4Material;
 class DetectorMessenger;
 
 //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
 /*!
 \brief This mandatory user class defines the geometry.
 
 It is responsible for
  - Definition of material, and
  - Construction of geometry
 
 \sa Construct()
  */
 class DetectorConstruction : public G4VUserDetectorConstruction
 {
 public:
   //! Constructor
   DetectorConstruction();
   //! Destructor
   ~DetectorConstruction();
 public:
   //! Construct geometry of the setup
   G4VPhysicalVolume* Construct();
 
   //! Update geometry
   void UpdateGeometry();
 
   //! \name some simple set & get functions
   //@{

// funciones mariconas del messenger
   G4ThreeVector FirstSensorPosition() const  { return posFirstSensor; }
   G4ThreeVector SecondSensorPosition() const { return posSecondSensor; }
   G4ThreeVector ThirdSensorPosition() const { return posThirdSensor; }
   G4ThreeVector CuartoSensorPosition() const { return posCuartoSensor; }
 
   G4ThreeVector SetFirstSensorPosition(const G4ThreeVector & pos) { return posFirstSensor=pos; }
   G4ThreeVector SetSecondSensorPosition(const G4ThreeVector & pos) { return posSecondSensor=pos; }
   G4ThreeVector SetThirdSensorPosition(const G4ThreeVector & pos) { return posThirdSensor=pos; }
   G4ThreeVector SetCuartoSensorPosition(const G4ThreeVector & pos) { return posCuartoSensor=pos; }
 
   G4bool   IsDUTSetup() const { return isSecondPlaneDUT; }
   G4bool   SetDUTSetup( const G4bool& flag ) { return isSecondPlaneDUT=flag; }
   G4double DUTangle() const { return theta_D_0_0; }
   G4double SetDUTangle(const G4double theta)  { return theta_D_0_0=theta; }

//-------------------------algunos mensajes------------------------------
   G4double GetSlit_z() const { return slit_z; }
   G4double SetSlit_z(const G4double el_z)  { return slit_z=el_z; }

   G4double GetSlit_x() const { return slit_x; }
   G4double SetSlit_x(const G4double el_x)  { return slit_x=el_x; }

   G4double GetPocket1_x() const { return pocket_x; }
   G4double SetPocket1_x(const G4double el_x_pocket)  { return pocket_x=el_x_pocket; }
//-----------------------------------------------------------------------

   G4bool   Is2PocketSetup() const { return isCuartoPlane2Pocket; }
   G4bool   Set2PocketSetup( const G4bool& flag2Pocket ) { return isCuartoPlane2Pocket=flag2Pocket; }
   G4double SPocketangle() const { return theta_D_0_1; }
   G4double Set2Pocketangle(const G4double theta2)  { return theta_D_0_1=theta2; }
   //@}
 private:
   //! define needed materials
   void DefineMaterials();
   //! initialize geometry parameters
   void ComputeParameters();
   //! Construct geometry of the Beam Telescope
   G4VPhysicalVolume* ConstructRings();
   //! Construct geometry of the Device-under-test
   G4VPhysicalVolume* ConstructRing_D_0_0();
   //! Construct geometry of the 2Pocket
   G4VPhysicalVolume* ConstructRing_D_0_1();

   G4VPhysicalVolume* ConstructRing_D_0_2();

   G4VPhysicalVolume* ConstructRing_D_1_0();
   G4VPhysicalVolume* ConstructRing_D_1_1();
   G4VPhysicalVolume* ConstructRing_D_1_2();

   G4VPhysicalVolume* ConstructRing_D_2_0();
   G4VPhysicalVolume* ConstructRing_D_2_1();
   G4VPhysicalVolume* ConstructRing_D_2_2();

   G4VPhysicalVolume* ConstructRing_C_0_0();
   G4VPhysicalVolume* ConstructRing_C_0_1();
   G4VPhysicalVolume* ConstructRing_C_1_0();
   G4VPhysicalVolume* ConstructRing_C_1_1();
   G4VPhysicalVolume* ConstructRing_C_2_0();
   G4VPhysicalVolume* ConstructRing_C_2_1();
   G4VPhysicalVolume* ConstructRing_C_3_0();
   G4VPhysicalVolume* ConstructRing_C_3_1();

   G4VPhysicalVolume* ConstructRing_B_0_0();
   G4VPhysicalVolume* ConstructRing_B_0_1();
   G4VPhysicalVolume* ConstructRing_B_0_2();
   G4VPhysicalVolume* ConstructRing_B_0_3();

   G4VPhysicalVolume* ConstructRing_A_0_0();
   G4VPhysicalVolume* ConstructRing_A_0_1();

   G4VPhysicalVolume* ConstructRing_E_0_0();
   G4VPhysicalVolume* ConstructRing_E_0_1();
   G4VPhysicalVolume* ConstructRing_E_1_0();
   G4VPhysicalVolume* ConstructRing_E_1_1();
   G4VPhysicalVolume* ConstructRing_E_2_0();
   G4VPhysicalVolume* ConstructRing_E_2_1();

   G4VPhysicalVolume* ConstructRing_F_0_0();
   G4VPhysicalVolume* ConstructRing_F_0_1();
   G4VPhysicalVolume* ConstructRing_F_1_0();
   G4VPhysicalVolume* ConstructRing_F_1_1();
   G4VPhysicalVolume* ConstructRing_F_2_0();
   G4VPhysicalVolume* ConstructRing_F_2_1();
   G4VPhysicalVolume* ConstructRing_F_3_0();
   G4VPhysicalVolume* ConstructRing_F_3_1();


   G4VPhysicalVolume* ConstructCrystals();

   G4VPhysicalVolume* scintillator_phys;
   G4VPhysicalVolume* scintillator_phys_strips;
  //G4VPhysicalVolume* ConstructElSlit();

    G4LogicalVolume * logicTarget;

    G4double* rotacion(G4double dx , G4double dy, G4double dz, G4double angulo);
 
 private:
 
   //! \name Materials
   //@{
   G4Material* air;
   G4Material* silicon;
   G4Material* vacuum;
   G4Material* H2;
   G4Material* AlN;
   G4Material* steel;
   G4Material* tungsten;
   G4Material* CsI;
   G4Material* tantalum;
   
   //@}
 
   //! \name Geometry
   //@{
 
   //! global mother volume
   G4LogicalVolume * logicWorld;
 
   //! 1st telescope plane
  // G4VPhysicalVolume* physiFirstSensor;
   //! 2nd telescope plane
   
   
   //! subdivisions of the DUT in sensor strips
  
   //G4VPhysicalVolume * physiSensorStrip2Pocket; 

    //G4VPhysicalVolume * physiSensorslit;

   G4VPhysicalVolume * physiTarget; 
   
   //@}
 
   //! \name Parameters
   //@{
   G4double halfWorldLength;
 
   G4int noOfSensorStrips;
   G4double Lengthy_sili;
   G4double Thickness_sili;
 
   G4double Lengthx_sili;

   G4double Lengthy_dssd_t1;
   G4double Thickness_dssd_t1;
   G4double Lengthx_dssd_t1;

   G4double Lengthy_dssd_t2;
   G4double Thickness_dssd_t2;
   G4double Lengthx_dssd_t2;


   G4double Lengthy_dssd_t3;
   G4double Thickness_dssd_t3;
   G4double Lengthx_dssd_t3;


   G4double Lengthy_sili2;
   G4double Thickness_sili2;
   G4double Lengthx_sili2;

   G4double Lengthy_dssd_t4;
   G4double Thickness_dssd_t4;
   G4double Lengthx_dssd_t4;


   G4double Lengthy_sili3;
   G4double Thickness_sili3;
   G4double Lengthx_sili3;


//-------------------variable solo para el messenger, no olvidar cambiarlas en un futuro!!
   G4ThreeVector posFirstSensor;
   G4ThreeVector posSecondSensor;
   G4ThreeVector posThirdSensor;
   G4ThreeVector posCuartoSensor;
   G4bool isSecondPlaneDUT;
   G4bool isCuartoPlane2Pocket;
   G4double slit_x;
   G4double slit_z;
   G4double pocket_x;
//------------------------------------------------


   G4PVParameterised * parametro;
   
   G4double fwhm_beam;
   G4double fwhm_target;

//------------ring D_0_0
     G4VPhysicalVolume * physiSensorStripD_0_0; 
     G4VPhysicalVolume* physiSensorRing_D_0_0;
     G4ThreeVector vector_D_0_0;
     G4double phi_D_0_0;
     G4double coorx_D_0_0;	
     G4double coory_D_0_0;	
     G4double coorz_D_0_0;
     G4double coorx_D_0_0_e;	
     G4double coory_D_0_0_e;	
     G4double coorz_D_0_0_e;
     G4double theta_D_0_0;
   

   //------------ring D_0_1
     G4VPhysicalVolume* physiSensorStripD_0_1;
     G4VPhysicalVolume* physiSensorRing_D_0_1;
     G4ThreeVector vector_D_0_1;
     G4double phi_D_0_1;     
     G4double coorx_D_0_1;	
     G4double coory_D_0_1;	
     G4double coorz_D_0_1;
     G4double coorx_D_0_1_e;	
     G4double coory_D_0_1_e;	
     G4double coorz_D_0_1_e;
     G4double theta_D_0_1;	
     
     
    //------------ring D_0_2
     G4VPhysicalVolume* physiSensorStripD_0_2;
     G4VPhysicalVolume* physiSensorRing_D_0_2;
     G4ThreeVector vector_D_0_2;
     G4double phi_D_0_2;     
     G4double coorx_D_0_2;	
     G4double coory_D_0_2;	
     G4double coorz_D_0_2;
     G4double coorx_D_0_2_e;	
     G4double coory_D_0_2_e;	
     G4double coorz_D_0_2_e;
     G4double theta_D_0_2;	


//------------ring D_1_0
     G4VPhysicalVolume * physiSensorStripD_1_0; 
     G4VPhysicalVolume* physiSensorRing_D_1_0;
     G4ThreeVector vector_D_1_0;
     G4double phi_D_1_0;
     G4double coorx_D_1_0;	
     G4double coory_D_1_0;	
     G4double coorz_D_1_0;
     G4double coorx_D_1_0_e;	
     G4double coory_D_1_0_e;	
     G4double coorz_D_1_0_e;
     G4double theta_D_1_0;
   

   //------------ring D_1_1
     G4VPhysicalVolume* physiSensorStripD_1_1;
     G4VPhysicalVolume* physiSensorRing_D_1_1;
     G4ThreeVector vector_D_1_1;
     G4double phi_D_1_1;     
     G4double coorx_D_1_1;	
     G4double coory_D_1_1;	
     G4double coorz_D_1_1;
     G4double coorx_D_1_1_e;	
     G4double coory_D_1_1_e;	
     G4double coorz_D_1_1_e;
     G4double theta_D_1_1;	
     
     
    //------------ring D_1_2
     G4VPhysicalVolume* physiSensorStripD_1_2;
     G4VPhysicalVolume* physiSensorRing_D_1_2;
     G4ThreeVector vector_D_1_2;
     G4double phi_D_1_2;     
     G4double coorx_D_1_2;	
     G4double coory_D_1_2;	
     G4double coorz_D_1_2;
     G4double coorx_D_1_2_e;	
     G4double coory_D_1_2_e;	
     G4double coorz_D_1_2_e;
     G4double theta_D_1_2;	


//------------ring D_2_0
     G4VPhysicalVolume * physiSensorStripD_2_0; 
     G4VPhysicalVolume* physiSensorRing_D_2_0;
     G4ThreeVector vector_D_2_0;
     G4double phi_D_2_0;
     G4double coorx_D_2_0;	
     G4double coory_D_2_0;	
     G4double coorz_D_2_0;
     G4double coorx_D_2_0_e;	
     G4double coory_D_2_0_e;	
     G4double coorz_D_2_0_e;
     G4double theta_D_2_0;
   

   //------------ring D_2_1
     G4VPhysicalVolume* physiSensorStripD_2_1;
     G4VPhysicalVolume* physiSensorRing_D_2_1;
     G4ThreeVector vector_D_2_1;
     G4double phi_D_2_1;     
     G4double coorx_D_2_1;	
     G4double coory_D_2_1;	
     G4double coorz_D_2_1;
     G4double coorx_D_2_1_e;	
     G4double coory_D_2_1_e;	
     G4double coorz_D_2_1_e;
     G4double theta_D_2_1;	
     
     
    //------------ring D_2_2
     G4VPhysicalVolume* physiSensorStripD_2_2;
     G4VPhysicalVolume* physiSensorRing_D_2_2;
     G4ThreeVector vector_D_2_2;
     G4double phi_D_2_2;     
     G4double coorx_D_2_2;	
     G4double coory_D_2_2;	
     G4double coorz_D_2_2;
     G4double coorx_D_2_2_e;	
     G4double coory_D_2_2_e;	
     G4double coorz_D_2_2_e;
     G4double theta_D_2_2;	


//------------ring C_0_0
     G4VPhysicalVolume * physiSensorStripC_0_0; 
     G4VPhysicalVolume* physiSensorRing_C_0_0;
     G4ThreeVector vector_C_0_0;
     G4double phi_C_0_0;
     G4double coorx_C_0_0;	
     G4double coory_C_0_0;	
     G4double coorz_C_0_0;
     G4double coorx_C_0_0_e;	
     G4double coory_C_0_0_e;	
     G4double coorz_C_0_0_e;
     G4double theta_C_0_0;



//------------ring C_0_1
     G4VPhysicalVolume * physiSensorStripC_0_1; 
     G4VPhysicalVolume* physiSensorRing_C_0_1;
     G4ThreeVector vector_C_0_1;
     G4double phi_C_0_1;
     G4double coorx_C_0_1;	
     G4double coory_C_0_1;	
     G4double coorz_C_0_1;
     G4double coorx_C_0_1_e;	
     G4double coory_C_0_1_e;	
     G4double coorz_C_0_1_e;
     G4double theta_C_0_1;


//------------ring C_1_0
     G4VPhysicalVolume * physiSensorStripC_1_0; 
     G4VPhysicalVolume* physiSensorRing_C_1_0;
     G4ThreeVector vector_C_1_0;
     G4double phi_C_1_0;
     G4double coorx_C_1_0;	
     G4double coory_C_1_0;	
     G4double coorz_C_1_0;
     G4double coorx_C_1_0_e;	
     G4double coory_C_1_0_e;	
     G4double coorz_C_1_0_e;
     G4double theta_C_1_0;



//------------ring C_1_1
     G4VPhysicalVolume * physiSensorStripC_1_1; 
     G4VPhysicalVolume* physiSensorRing_C_1_1;
     G4ThreeVector vector_C_1_1;
     G4double phi_C_1_1;
     G4double coorx_C_1_1;	
     G4double coory_C_1_1;	
     G4double coorz_C_1_1;
     G4double coorx_C_1_1_e;	
     G4double coory_C_1_1_e;	
     G4double coorz_C_1_1_e;
     G4double theta_C_1_1;



//------------ring C_2_0
     G4VPhysicalVolume * physiSensorStripC_2_0; 
     G4VPhysicalVolume* physiSensorRing_C_2_0;
     G4ThreeVector vector_C_2_0;
     G4double phi_C_2_0;
     G4double coorx_C_2_0;	
     G4double coory_C_2_0;	
     G4double coorz_C_2_0;
     G4double coorx_C_2_0_e;	
     G4double coory_C_2_0_e;	
     G4double coorz_C_2_0_e;
     G4double theta_C_2_0;



//------------ring C_2_1
     G4VPhysicalVolume * physiSensorStripC_2_1; 
     G4VPhysicalVolume* physiSensorRing_C_2_1;
     G4ThreeVector vector_C_2_1;
     G4double phi_C_2_1;
     G4double coorx_C_2_1;	
     G4double coory_C_2_1;	
     G4double coorz_C_2_1;
     G4double coorx_C_2_1_e;	
     G4double coory_C_2_1_e;	
     G4double coorz_C_2_1_e;
     G4double theta_C_2_1;


//------------ring C_3_0
     G4VPhysicalVolume * physiSensorStripC_3_0; 
     G4VPhysicalVolume* physiSensorRing_C_3_0;
     G4ThreeVector vector_C_3_0;
     G4double phi_C_3_0;
     G4double coorx_C_3_0;	
     G4double coory_C_3_0;	
     G4double coorz_C_3_0;
     G4double coorx_C_3_0_e;	
     G4double coory_C_3_0_e;	
     G4double coorz_C_3_0_e;
     G4double theta_C_3_0;



//------------ring C_3_1
     G4VPhysicalVolume * physiSensorStripC_3_1; 
     G4VPhysicalVolume* physiSensorRing_C_3_1;
     G4ThreeVector vector_C_3_1;
     G4double phi_C_3_1;
     G4double coorx_C_3_1;	
     G4double coory_C_3_1;	
     G4double coorz_C_3_1;
     G4double coorx_C_3_1_e;	
     G4double coory_C_3_1_e;	
     G4double coorz_C_3_1_e;
     G4double theta_C_3_1;


//------------ring B_0_0
     G4VPhysicalVolume * physiSensorStripB_0_0; 
     G4VPhysicalVolume* physiSensorRing_B_0_0;
     G4ThreeVector vector_B_0_0;
     G4double phi_B_0_0;
     G4double coorx_B_0_0;	
     G4double coory_B_0_0;	
     G4double coorz_B_0_0;
     G4double coorx_B_0_0_e;	
     G4double coory_B_0_0_e;	
     G4double coorz_B_0_0_e;
     G4double theta_B_0_0;

//------------ring B_0_1
     G4VPhysicalVolume * physiSensorStripB_0_1; 
     G4VPhysicalVolume* physiSensorRing_B_0_1;
     G4ThreeVector vector_B_0_1;
     G4double phi_B_0_1;
     G4double coorx_B_0_1;	
     G4double coory_B_0_1;	
     G4double coorz_B_0_1;
     G4double coorx_B_0_1_e;	
     G4double coory_B_0_1_e;	
     G4double coorz_B_0_1_e;
     G4double theta_B_0_1;

//------------ring B_0_2
     G4VPhysicalVolume * physiSensorStripB_0_2; 
     G4VPhysicalVolume* physiSensorRing_B_0_2;
     G4ThreeVector vector_B_0_2;
     G4double phi_B_0_2;
     G4double coorx_B_0_2;	
     G4double coory_B_0_2;	
     G4double coorz_B_0_2;
     G4double coorx_B_0_2_e;	
     G4double coory_B_0_2_e;	
     G4double coorz_B_0_2_e;
     G4double theta_B_0_2;

//------------ring B_0_3
     G4VPhysicalVolume * physiSensorStripB_0_3; 
     G4VPhysicalVolume* physiSensorRing_B_0_3;
     G4ThreeVector vector_B_0_3;
     G4double phi_B_0_3;
     G4double coorx_B_0_3;	
     G4double coory_B_0_3;	
     G4double coorz_B_0_3;
     G4double coorx_B_0_3_e;	
     G4double coory_B_0_3_e;	
     G4double coorz_B_0_3_e;
     G4double theta_B_0_3;



//------------ring A_0_0
     G4VPhysicalVolume * physiSensorStripA_0_0; 
     G4VPhysicalVolume* physiSensorRing_A_0_0;
     G4ThreeVector vector_A_0_0;
     G4double phi_A_0_0;
     G4double coorx_A_0_0;	
     G4double coory_A_0_0;	
     G4double coorz_A_0_0;
     G4double coorx_A_0_0_e;	
     G4double coory_A_0_0_e;	
     G4double coorz_A_0_0_e;
     G4double theta_A_0_0;

//------------ring A_0_1
     G4VPhysicalVolume * physiSensorStripA_0_1; 
     G4VPhysicalVolume* physiSensorRing_A_0_1;
     G4ThreeVector vector_A_0_1;
     G4double phi_A_0_1;
     G4double coorx_A_0_1;	
     G4double coory_A_0_1;	
     G4double coorz_A_0_1;
     G4double coorx_A_0_1_e;	
     G4double coory_A_0_1_e;	
     G4double coorz_A_0_1_e;
     G4double theta_A_0_1;

//------------ring E_0_0
     G4VPhysicalVolume * physiSensorStripE_0_0; 
     G4VPhysicalVolume* physiSensorRing_E_0_0;
     G4ThreeVector vector_E_0_0;
     G4double phi_E_0_0;
     G4double coorx_E_0_0;	
     G4double coory_E_0_0;	
     G4double coorz_E_0_0;
     G4double coorx_E_0_0_e;	
     G4double coory_E_0_0_e;	
     G4double coorz_E_0_0_e;
     G4double theta_E_0_0;

//------------ring E_0_1
     G4VPhysicalVolume * physiSensorStripE_0_1; 
     G4VPhysicalVolume* physiSensorRing_E_0_1;
     G4ThreeVector vector_E_0_1;
     G4double phi_E_0_1;
     G4double coorx_E_0_1;	
     G4double coory_E_0_1;	
     G4double coorz_E_0_1;
     G4double coorx_E_0_1_e;	
     G4double coory_E_0_1_e;	
     G4double coorz_E_0_1_e;
     G4double theta_E_0_1;

//------------ring E_1_0
     G4VPhysicalVolume * physiSensorStripE_1_0; 
     G4VPhysicalVolume* physiSensorRing_E_1_0;
     G4ThreeVector vector_E_1_0;
     G4double phi_E_1_0;
     G4double coorx_E_1_0;	
     G4double coory_E_1_0;	
     G4double coorz_E_1_0;
     G4double coorx_E_1_0_e;	
     G4double coory_E_1_0_e;	
     G4double coorz_E_1_0_e;
     G4double theta_E_1_0;

//------------ring E_1_1
     G4VPhysicalVolume * physiSensorStripE_1_1; 
     G4VPhysicalVolume* physiSensorRing_E_1_1;
     G4ThreeVector vector_E_1_1;
     G4double phi_E_1_1;
     G4double coorx_E_1_1;	
     G4double coory_E_1_1;	
     G4double coorz_E_1_1;
     G4double coorx_E_1_1_e;	
     G4double coory_E_1_1_e;	
     G4double coorz_E_1_1_e;
     G4double theta_E_1_1;

//------------ring E_2_0
     G4VPhysicalVolume * physiSensorStripE_2_0; 
     G4VPhysicalVolume* physiSensorRing_E_2_0;
     G4ThreeVector vector_E_2_0;
     G4double phi_E_2_0;
     G4double coorx_E_2_0;	
     G4double coory_E_2_0;	
     G4double coorz_E_2_0;
     G4double coorx_E_2_0_e;	
     G4double coory_E_2_0_e;	
     G4double coorz_E_2_0_e;
     G4double theta_E_2_0;

//------------ring E_2_1
     G4VPhysicalVolume * physiSensorStripE_2_1; 
     G4VPhysicalVolume* physiSensorRing_E_2_1;
     G4ThreeVector vector_E_2_1;
     G4double phi_E_2_1;
     G4double coorx_E_2_1;	
     G4double coory_E_2_1;	
     G4double coorz_E_2_1;
     G4double coorx_E_2_1_e;	
     G4double coory_E_2_1_e;	
     G4double coorz_E_2_1_e;
     G4double theta_E_2_1;


//------------ring F_0_0
     G4VPhysicalVolume * physiSensorStripF_0_0; 
     G4VPhysicalVolume* physiSensorRing_F_0_0;
     G4ThreeVector vector_F_0_0;
     G4double phi_F_0_0;
     G4double coorx_F_0_0;	
     G4double coory_F_0_0;	
     G4double coorz_F_0_0;
     G4double coorx_F_0_0_e;	
     G4double coory_F_0_0_e;	
     G4double coorz_F_0_0_e;
     G4double theta_F_0_0;

//------------ring F_0_1
     G4VPhysicalVolume * physiSensorStripF_0_1; 
     G4VPhysicalVolume* physiSensorRing_F_0_1;
     G4ThreeVector vector_F_0_1;
     G4double phi_F_0_1;
     G4double coorx_F_0_1;	
     G4double coory_F_0_1;	
     G4double coorz_F_0_1;
     G4double coorx_F_0_1_e;	
     G4double coory_F_0_1_e;	
     G4double coorz_F_0_1_e;
     G4double theta_F_0_1;

//------------ring F_1_0
     G4VPhysicalVolume * physiSensorStripF_1_0; 
     G4VPhysicalVolume* physiSensorRing_F_1_0;
     G4ThreeVector vector_F_1_0;
     G4double phi_F_1_0;
     G4double coorx_F_1_0;	
     G4double coory_F_1_0;	
     G4double coorz_F_1_0;
     G4double coorx_F_1_0_e;	
     G4double coory_F_1_0_e;	
     G4double coorz_F_1_0_e;
     G4double theta_F_1_0;

//------------ring F_1_1
     G4VPhysicalVolume * physiSensorStripF_1_1; 
     G4VPhysicalVolume* physiSensorRing_F_1_1;
     G4ThreeVector vector_F_1_1;
     G4double phi_F_1_1;
     G4double coorx_F_1_1;	
     G4double coory_F_1_1;	
     G4double coorz_F_1_1;
     G4double coorx_F_1_1_e;	
     G4double coory_F_1_1_e;	
     G4double coorz_F_1_1_e;
     G4double theta_F_1_1;

//------------ring F_2_0
     G4VPhysicalVolume * physiSensorStripF_2_0; 
     G4VPhysicalVolume* physiSensorRing_F_2_0;
     G4ThreeVector vector_F_2_0;
     G4double phi_F_2_0;
     G4double coorx_F_2_0;	
     G4double coory_F_2_0;	
     G4double coorz_F_2_0;
     G4double coorx_F_2_0_e;	
     G4double coory_F_2_0_e;	
     G4double coorz_F_2_0_e;
     G4double theta_F_2_0;

//------------ring F_2_1
     G4VPhysicalVolume * physiSensorStripF_2_1; 
     G4VPhysicalVolume* physiSensorRing_F_2_1;
     G4ThreeVector vector_F_2_1;
     G4double phi_F_2_1;
     G4double coorx_F_2_1;	
     G4double coory_F_2_1;	
     G4double coorz_F_2_1;
     G4double coorx_F_2_1_e;	
     G4double coory_F_2_1_e;	
     G4double coorz_F_2_1_e;
     G4double theta_F_2_1;

//------------ring F_3_0
     G4VPhysicalVolume * physiSensorStripF_3_0; 
     G4VPhysicalVolume* physiSensorRing_F_3_0;
     G4ThreeVector vector_F_3_0;
     G4double phi_F_3_0;
     G4double coorx_F_3_0;	
     G4double coory_F_3_0;	
     G4double coorz_F_3_0;
     G4double coorx_F_3_0_e;	
     G4double coory_F_3_0_e;	
     G4double coorz_F_3_0_e;
     G4double theta_F_3_0;

//------------ring F_3_1
     G4VPhysicalVolume * physiSensorStripF_3_1; 
     G4VPhysicalVolume* physiSensorRing_F_3_1;
     G4ThreeVector vector_F_3_1;
     G4double phi_F_3_1;
     G4double coorx_F_3_1;	
     G4double coory_F_3_1;	
     G4double coorz_F_3_1;
     G4double coorx_F_3_1_e;	
     G4double coory_F_3_1_e;	
     G4double coorz_F_3_1_e;
     G4double theta_F_3_1;


     G4LogicalVolume * logicCrystal;
     
   //@}
 

   //! \name UI Messenger 
   //@{
   DetectorMessenger * messenger;
   //@}
 };
 
 //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
 #endif
