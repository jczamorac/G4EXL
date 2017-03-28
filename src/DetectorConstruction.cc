 // $Id: DetectorConstruction.cc 94 2010-01-26 13:18:30Z adotti $
 /**
  * @file
  * @brief Implements mandatory user class DetectorConstruction.
  */
 
 #include "DetectorConstruction.hh"
 #include "DetectorMessenger.hh"
 
 #include "G4Material.hh"
 #include "G4Box.hh"
#include "G4Tubs.hh"
 #include "G4LogicalVolume.hh"
 #include "G4PVPlacement.hh"
 #include "G4PVReplica.hh"
#include "G4SystemOfUnits.hh"

 
 #include "G4GeometryTolerance.hh"
 #include "G4GeometryManager.hh"
 #include "G4NistManager.hh"
 
 #include "G4VisAttributes.hh"
 #include "G4Colour.hh"
 
 #include "SensitiveDetector.hh"
 #include "G4SDManager.hh"
//nuevo detector
#include "Crystal.hh"
#include "G4VSensitiveDetector.hh"


#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4Polyhedra.hh"
#include  "G4Trd.hh"
#include "CrystalParameterisation.hh"
#include "G4Sphere.hh"
#include "G4Cons.hh"



#include <fstream>
#include <cstring>

 DetectorConstruction::DetectorConstruction()
 {
   //Create a messanger (defines custom UI commands)
   messenger = new DetectorMessenger(this);
 
   //--------- Material definition ---------
   DefineMaterials();
 
   //--------- Sizes of the principal geometrical components (solids)  ---------
   ComputeParameters();
 }
  
 DetectorConstruction::~DetectorConstruction()
 {
   delete messenger;             
 }
  
 void DetectorConstruction::DefineMaterials() 
 {

   G4double a, z, density;            // z=mean number of protons;
   G4double temperature, pressure;
   G4int ncomponents, natoms;
   G4String name, symbol;             // a=mass of a mole;

   // define Elements
   a = 1.01*g/mole;
   G4Element* elH  = new G4Element(name="Hydrogen",symbol="H" , z= 1., a);
   density     = 1.33e-11*g/cm3;
   pressure    = 1.0913e-10*atmosphere;
   temperature = 200.*kelvin;
   H2 = new G4Material(name="Hydrogen gas", density, ncomponents=1,
                                     kStateGas,temperature,pressure);
   H2->AddElement(elH, natoms=2);


    //define the AlN
    G4Element* elAl  = new G4Element(name="Aluminum",symbol="Al" , z= 13., a=26.98*g/mole);
    G4Element* elN  = new G4Element(name="Nitrogen",symbol="N" , z= 7., a=14.00*g/mole);
    density     = 3.26*g/cm3;
    AlN = new G4Material(name="Aluminum Nitrode", density, ncomponents=2);
    AlN->AddElement(elAl, natoms=1);
    AlN->AddElement(elN, natoms=1);
    

   //Get Materials from NIST database
   G4NistManager* man = G4NistManager::Instance();
   man->SetVerbose(0);
 
   // define NIST materials
   air     = man->FindOrBuildMaterial("G4_AIR");
   silicon = man->FindOrBuildMaterial("G4_Si");
   vacuum  = man->FindOrBuildMaterial("G4_Galactic");
   steel  = man->FindOrBuildMaterial("G4_STAINLESS-STEEL");
   tungsten  = man->FindOrBuildMaterial("G4_W");
   CsI  = man->FindOrBuildMaterial("G4_CESIUM_IODIDE");
   tantalum  = man->FindOrBuildMaterial("G4_Ta");

    
   
 }
  
 void DetectorConstruction::ComputeParameters() 
 {
   //This function defines the defaults
   //of the geometry construction
 
   // ** world **
   halfWorldLength = 1.3* m;
 
   // ** Esta simulacion ya no tiene strips (sub-det dentro de los volumenes) **
  // por eso el tamanho de strip es el mismo del detector
   noOfSensorStrips = 1;
   Lengthy_sili = 90.*mm;
   Thickness_sili = 6.5*mm;
   Lengthx_sili  = 90.*mm; 

   Lengthy_dssd_t1 = 90.*mm;
   Thickness_dssd_t1 = 100.0*um;
   Lengthx_dssd_t1  = 90. * mm; 

   Lengthy_dssd_t2 = 90.*mm;
   Thickness_dssd_t2 = 300.0*um;
   Lengthx_dssd_t2  = 90. * mm; 
	
   Lengthy_dssd_t3 = 90.*mm;
   Thickness_dssd_t3 = 300.0*um;
   Lengthx_dssd_t3  = 60. * mm; 

   Lengthy_sili2 = 90.*mm;
   Thickness_sili2 = 6.5*mm;
   Lengthx_sili2  = 60.*mm; 


   Lengthy_dssd_t4 = 50.*mm;
   Thickness_dssd_t4 = 300.0*um;
   Lengthx_dssd_t4  = 50. * mm; 

   Lengthy_sili3 = 50.*mm;
   Thickness_sili3 = 6.5*mm;
   Lengthx_sili3  = 50.*mm; 


      // ** Device under test (DUT) **
   isSecondPlaneDUT = true; //By default construct a SiTelescope
   fwhm_beam = 3.1*mm;
   fwhm_target = 5.5*mm;
  


   theta_D_0_0 = 15.71059*deg;	
   theta_D_0_1 = 15.71059*deg;
   theta_D_0_2 = 15.71059*deg;

    // ** RingD00
    coorx_D_0_0 = -(450.*mm)*cos(-(90.- 15.71059)*3.141562/180.);
    coory_D_0_0 = 0.*mm;	
    coorz_D_0_0 = -(450.*mm)*sin(-(90.- 15.71059)*3.141562/180.);

    coorx_D_0_0_e = -(450.*mm + 1*mm)*cos(-(90.- 15.71059)*3.141562/180.);
    coory_D_0_0_e = 0.*mm;	
    coorz_D_0_0_e = -(450.*mm + 1*mm)*sin(-(90.- 15.71059)*3.141562/180.);

   // ** RingD01
    coorx_D_0_1 = -(550.*mm)*cos(-(90.- 15.71059)*3.141562/180.);
    coory_D_0_1 = 0.*mm;	
    coorz_D_0_1 = -(550.*mm)*sin(-(90.- 15.71059)*3.141562/180.);

    coorx_D_0_1_e = -(550.*mm + 1*mm)*cos(-(90.- 15.71059)*3.141562/180.);
    coory_D_0_1_e = 0.*mm;	
    coorz_D_0_1_e = -(550.*mm + 1*mm)*sin(-(90.- 15.71059)*3.141562/180.);


     // ** RingD02
    coorx_D_0_2 = -(560.*mm)*cos(-(90.- 15.71059)*3.141562/180.);
    coory_D_0_2 = 0.*mm;	
    coorz_D_0_2 = -(560.*mm)*sin(-(90.- 15.71059)*3.141562/180.);

    coorx_D_0_2_e = -(560.*mm + 10*mm)*cos(-(90.- 15.71059)*3.141562/180.);
    coory_D_0_2_e = 0.*mm;	
    coorz_D_0_2_e = -(560.*mm + 10*mm)*sin(-(90.- 15.71059)*3.141562/180.);


   theta_D_1_0 = 27.5184*deg;	
   theta_D_1_1 = 27.5184*deg;
   theta_D_1_2 = 27.5184*deg;

 // ** RingD10
    coorx_D_1_0 = -(450.*mm - 10*mm)*cos(-(90.- 27.5184)*3.141562/180.);
    coory_D_1_0 = 0.*mm;	
    coorz_D_1_0 = -(450.*mm - 10*mm)*sin(-(90.- 27.5184)*3.141562/180.);

    coorx_D_1_0_e = -(450.*mm + 1*mm - 10*mm)*cos(-(90.- 27.5184)*3.141562/180.);
    coory_D_1_0_e = 0.*mm;	
    coorz_D_1_0_e = -(450.*mm + 1*mm - 10*mm)*sin(-(90.- 27.5184)*3.141562/180.);

   // ** RingD11
    coorx_D_1_1 = -(550.*mm - 10*mm)*cos(-(90.- 27.5184)*3.141562/180.);
    coory_D_1_1 = 0.*mm;	
    coorz_D_1_1 = -(550.*mm - 10*mm)*sin(-(90.- 27.5184)*3.141562/180.);

    coorx_D_1_1_e = -(550.*mm + 1*mm - 10*mm)*cos(-(90.- 27.5184)*3.141562/180.);
    coory_D_1_1_e = 0.*mm;	
    coorz_D_1_1_e = -(550.*mm + 1*mm - 10*mm)*sin(-(90.- 27.5184)*3.141562/180.);


     // ** RingD12
    coorx_D_1_2 = -(560.*mm - 10*mm)*cos(-(90.- 27.5184)*3.141562/180.);
    coory_D_1_2 = 0.*mm;	
    coorz_D_1_2 = -(560.*mm - 10*mm)*sin(-(90.- 27.5184)*3.141562/180.);

    coorx_D_1_2_e = -(560.*mm + 10*mm - 10*mm)*cos(-(90.- 27.5184)*3.141562/180.);
    coory_D_1_2_e = 0.*mm;	
    coorz_D_1_2_e = -(560.*mm + 10*mm - 10*mm)*sin(-(90.- 27.5184)*3.141562/180.);




   theta_D_2_0 = 38.55529*deg;	
   theta_D_2_1 = 38.55529*deg;
   theta_D_2_2 = 38.55529*deg;

 // ** RingD10
    coorx_D_2_0 = -(450.*mm )*cos(-(90.- 38.55529)*3.141562/180.);
    coory_D_2_0 = 0.*mm;	
    coorz_D_2_0 = -(450.*mm )*sin(-(90.- 38.55529)*3.141562/180.);

    coorx_D_2_0_e = -(450.*mm + 1*mm )*cos(-(90.- 38.55529)*3.141562/180.);
    coory_D_2_0_e = 0.*mm;	
    coorz_D_2_0_e = -(450.*mm + 1*mm )*sin(-(90.- 38.55529)*3.141562/180.);

   // ** RingD11
    coorx_D_2_1 = -(550.*mm )*cos(-(90.- 38.55529)*3.141562/180.);
    coory_D_2_1 = 0.*mm;	
    coorz_D_2_1 = -(550.*mm )*sin(-(90.- 38.55529)*3.141562/180.);

    coorx_D_2_1_e = -(550.*mm + 1*mm )*cos(-(90.- 38.55529)*3.141562/180.);
    coory_D_2_1_e = 0.*mm;	
    coorz_D_2_1_e = -(550.*mm + 1*mm )*sin(-(90.- 38.55529)*3.141562/180.);


     // ** RingD12
    coorx_D_2_2 = -(560.*mm )*cos(-(90.- 38.55529)*3.141562/180.);
    coory_D_2_2 = 0.*mm;	
    coorz_D_2_2 = -(560.*mm )*sin(-(90.- 38.55529)*3.141562/180.);

    coorx_D_2_2_e = -(560.*mm + 10*mm )*cos(-(90.- 38.55529)*3.141562/180.);
    coory_D_2_2_e = 0.*mm;	
    coorz_D_2_2_e = -(560.*mm + 10*mm )*sin(-(90.- 38.55529)*3.141562/180.);



   theta_C_0_0 = 48.75*deg;	
   theta_C_0_1 = 48.75*deg;
   theta_C_1_0 = 56.25*deg;	
   theta_C_1_1 = 56.25*deg;
   theta_C_2_0 = 63.75*deg;	
   theta_C_2_1 = 63.75*deg;
   theta_C_3_0 = 71.25*deg;	
   theta_C_3_1 = 71.25*deg;

 // ** RingC00
    coorx_C_0_0 = -(450.*mm )*cos(-(90.- 48.75)*3.141562/180.);
    coory_C_0_0 = 0.*mm;	
    coorz_C_0_0 = -(450.*mm )*sin(-(90.- 48.75)*3.141562/180.);


    coorx_C_0_0_e = -(450.*mm + 1*mm)*cos(-(90.- 48.75)*3.141562/180.);
    coory_C_0_0_e = 0.*mm;	
    coorz_C_0_0_e = -(450.*mm + 1*mm)*sin(-(90.- 48.75)*3.141562/180.);

// ** RingC01
    coorx_C_0_1 = -(580.*mm )*cos(-(90.- 48.75)*3.141562/180.);
    coory_C_0_1 = 0.*mm;	
    coorz_C_0_1 = -(580.*mm )*sin(-(90.- 48.75)*3.141562/180.);


    coorx_C_0_1_e = -(580.*mm + 1*mm)*cos(-(90.- 48.75)*3.141562/180.);
    coory_C_0_1_e = 0.*mm;	
    coorz_C_0_1_e = -(580.*mm + 1*mm)*sin(-(90.- 48.75)*3.141562/180.);


// ** RingC10
    coorx_C_1_0 = -(450.*mm -5.5*mm )*cos(-(90.- 56.25)*3.141562/180.);
    coory_C_1_0 = 0.*mm;	
    coorz_C_1_0 = -(450.*mm -5.5*mm)*sin(-(90.- 56.25)*3.141562/180.);


    coorx_C_1_0_e = -(450.*mm + 1*mm -5.5*mm)*cos(-(90.- 56.25)*3.141562/180.);
    coory_C_1_0_e = 0.*mm;	
    coorz_C_1_0_e = -(450.*mm + 1*mm -5.5*mm)*sin(-(90.- 56.25)*3.141562/180.);

// ** RingC11
    coorx_C_1_1 = -(580.*mm -5.5*mm)*cos(-(90.- 56.25)*3.141562/180.);
    coory_C_1_1 = 0.*mm;	
    coorz_C_1_1 = -(580.*mm -5.5*mm)*sin(-(90.- 56.25)*3.141562/180.);


    coorx_C_1_1_e = -(580.*mm + 1*mm -5.5*mm)*cos(-(90.- 56.25)*3.141562/180.);
    coory_C_1_1_e = 0.*mm;	
    coorz_C_1_1_e = -(580.*mm + 1*mm -5.5*mm)*sin(-(90.- 56.25)*3.141562/180.);


// ** RingC20
    coorx_C_2_0 = -(450.*mm )*cos(-(90.- 63.75)*3.141562/180.);
    coory_C_2_0 = 0.*mm;	
    coorz_C_2_0 = -(450.*mm )*sin(-(90.- 63.75)*3.141562/180.);


    coorx_C_2_0_e = -(450.*mm + 1*mm)*cos(-(90.- 63.75)*3.141562/180.);
    coory_C_2_0_e = 0.*mm;	
    coorz_C_2_0_e = -(450.*mm + 1*mm)*sin(-(90.- 63.75)*3.141562/180.);

// ** RingC21
    coorx_C_2_1 = -(580.*mm )*cos(-(90.- 63.75)*3.141562/180.);
    coory_C_2_1 = 0.*mm;	
    coorz_C_2_1 = -(580.*mm )*sin(-(90.- 63.75)*3.141562/180.);


    coorx_C_2_1_e = -(580.*mm + 1*mm)*cos(-(90.- 63.75)*3.141562/180.);
    coory_C_2_1_e = 0.*mm;	
    coorz_C_2_1_e = -(580.*mm + 1*mm)*sin(-(90.- 63.75)*3.141562/180.);


// ** RingC30
    coorx_C_3_0 = -(450.*mm -5.5*mm )*cos(-(90.- 71.25)*3.141562/180.);
    coory_C_3_0 = 0.*mm;	
    coorz_C_3_0 = -(450.*mm -5.5*mm)*sin(-(90.- 71.25)*3.141562/180.);


    coorx_C_3_0_e = -(450.*mm + 1*mm -5.5*mm)*cos(-(90.- 71.25)*3.141562/180.);
    coory_C_3_0_e = 0.*mm;	
    coorz_C_3_0_e = -(450.*mm + 1*mm -5.5*mm)*sin(-(90.- 71.25)*3.141562/180.);

// ** RingC11
    coorx_C_3_1 = -(580.*mm -5.5*mm)*cos(-(90.- 71.25)*3.141562/180.);
    coory_C_3_1 = 0.*mm;	
    coorz_C_3_1 = -(580.*mm -5.5*mm)*sin(-(90.- 71.25)*3.141562/180.);


    coorx_C_3_1_e = -(580.*mm + 1*mm -5.5*mm)*cos(-(90.- 71.25)*3.141562/180.);
    coory_C_3_1_e = 0.*mm;	
    coorz_C_3_1_e = -(580.*mm + 1*mm -5.5*mm)*sin(-(90.- 71.25)*3.141562/180.);


   theta_B_0_0 = 77.5*deg;
   theta_B_0_1 = 77.5*deg;	
   theta_B_0_2 = 77.5*deg;	
   theta_B_0_3 = 77.5*deg;		
// ** RingB00
    coorx_B_0_0 = -(450.*mm )*cos(-(90.- 77.5)*3.141562/180.);
    coory_B_0_0 = 0.*mm;	
    coorz_B_0_0 = -(450.*mm )*sin(-(90.- 77.5)*3.141562/180.);


    coorx_B_0_0_e = -(450.*mm + 1*mm )*cos(-(90.- 77.5)*3.141562/180.);
    coory_B_0_0_e = 0.*mm;	
    coorz_B_0_0_e = -(450.*mm + 1*mm )*sin(-(90.- 77.5)*3.141562/180.);

// ** RingB01
    coorx_B_0_1 = -(468.*mm )*cos(-(90.- 77.5)*3.141562/180.);
    coory_B_0_1 = 0.*mm;	
    coorz_B_0_1 = -(468.*mm )*sin(-(90.- 77.5)*3.141562/180.);


    coorx_B_0_1_e = -(468.*mm + 1*mm )*cos(-(90.- 77.5)*3.141562/180.);
    coory_B_0_1_e = 0.*mm;	
    coorz_B_0_1_e = -(468.*mm + 1*mm )*sin(-(90.- 77.5)*3.141562/180.);
// ** RingB02
    coorx_B_0_2 = -(525.*mm )*cos(-(90.- 77.5)*3.141562/180.);
    coory_B_0_2 = 0.*mm;	
    coorz_B_0_2 = -(525.*mm )*sin(-(90.- 77.5)*3.141562/180.);


    coorx_B_0_2_e = -(525.*mm + 1*mm )*cos(-(90.- 77.5)*3.141562/180.);
    coory_B_0_2_e = 0.*mm;	
    coorz_B_0_2_e = -(525.*mm + 1*mm )*sin(-(90.- 77.5)*3.141562/180.);
// ** RingB03
    coorx_B_0_3 = -(560.*mm )*cos(-(90.- 77.5)*3.141562/180.);
    coory_B_0_3 = 0.*mm;	
    coorz_B_0_3 = -(560.*mm )*sin(-(90.- 77.5)*3.141562/180.);


    coorx_B_0_3_e = -(560.*mm + 1*mm )*cos(-(90.- 77.5)*3.141562/180.);
    coory_B_0_3_e = 0.*mm;	
    coorz_B_0_3_e = -(560.*mm + 1*mm )*sin(-(90.- 77.5)*3.141562/180.);


   theta_A_0_0 = 84.5*deg;
   theta_A_0_1 = 84.5*deg;	

// ** RingA00
    coorx_A_0_0 = -(580.*mm )*cos(-(90.- 84.5)*3.141562/180.);
    coory_A_0_0 = 0.*mm;	
    coorz_A_0_0 = -(580.*mm )*sin(-(90.- 84.5)*3.141562/180.);


    coorx_A_0_0_e = -(580.*mm + 1*mm )*cos(-(90.- 84.5)*3.141562/180.);
    coory_A_0_0_e = 0.*mm;	
    coorz_A_0_0_e = -(580.*mm + 1*mm )*sin(-(90.- 84.5)*3.141562/180.);
// ** RingA01
    coorx_A_0_1 = -(599.*mm )*cos(-(90.- 84.5)*3.141562/180.);
    coory_A_0_1 = 0.*mm;	
    coorz_A_0_1 = -(599.*mm )*sin(-(90.- 84.5)*3.141562/180.);


    coorx_A_0_1_e = -(599.*mm + 1*mm )*cos(-(90.- 84.5)*3.141562/180.);
    coory_A_0_1_e = 0.*mm;	
    coorz_A_0_1_e = -(599.*mm + 1*mm )*sin(-(90.- 84.5)*3.141562/180.);



    theta_E_0_0 = 95.0*deg;
    theta_E_0_1 = 95.0*deg;
    theta_E_1_0 = 105.0*deg;
    theta_E_1_1 = 105.0*deg;
    theta_E_2_0 = 115.0*deg;
    theta_E_2_1 = 115.0*deg;

// ** RingE00
    coorx_E_0_0 = -(580.*mm -5.5*mm)*cos(-(90.- 95.0)*3.141562/180.);
    coory_E_0_0 = 0.*mm;	
    coorz_E_0_0 = -(580.*mm -5.5*mm)*sin(-(90.- 95.0)*3.141562/180.);

    coorx_E_0_0_e = -(580.*mm + 1*mm -5.5*mm)*cos(-(90.- 95.0)*3.141562/180.);
    coory_E_0_0_e = 0.*mm;	
    coorz_E_0_0_e = -(580.*mm + 1*mm -5.5*mm)*sin(-(90.- 95.0)*3.141562/180.);

// ** RingE01
    coorx_E_0_1 = -(599.*mm -5.5*mm)*cos(-(90.- 95.0)*3.141562/180.);
    coory_E_0_1 = 0.*mm;	
    coorz_E_0_1 = -(599.*mm -5.5*mm)*sin(-(90.- 95.0)*3.141562/180.);

    coorx_E_0_1_e = -(599.*mm + 1*mm -5.5*mm)*cos(-(90.- 95.0)*3.141562/180.);
    coory_E_0_1_e = 0.*mm;	
    coorz_E_0_1_e = -(599.*mm + 1*mm -5.5*mm)*sin(-(90.- 95.0)*3.141562/180.);


// ** RingE10
    coorx_E_1_0 = -(580.*mm )*cos(-(90.- 105.0)*3.141562/180.);
    coory_E_1_0 = 0.*mm;	
    coorz_E_1_0 = -(580.*mm )*sin(-(90.- 105.0)*3.141562/180.);

    coorx_E_1_0_e = -(580.*mm + 1*mm )*cos(-(90.- 105.0)*3.141562/180.);
    coory_E_1_0_e = 0.*mm;	
    coorz_E_1_0_e = -(580.*mm + 1*mm )*sin(-(90.- 105.0)*3.141562/180.);

// ** RingE11
    coorx_E_1_1 = -(599.*mm )*cos(-(90.- 105.0)*3.141562/180.);
    coory_E_1_1 = 0.*mm;	
    coorz_E_1_1 = -(599.*mm )*sin(-(90.- 105.0)*3.141562/180.);

    coorx_E_1_1_e = -(599.*mm + 1*mm )*cos(-(90.- 105.0)*3.141562/180.);
    coory_E_1_1_e = 0.*mm;	
    coorz_E_1_1_e = -(599.*mm + 1*mm )*sin(-(90.- 105.0)*3.141562/180.);


// ** RingE20
    coorx_E_2_0 = -(580.*mm -5.5*mm)*cos(-(90.- 115.0)*3.141562/180.);
    coory_E_2_0 = 0.*mm;	
    coorz_E_2_0 = -(580.*mm -5.5*mm)*sin(-(90.- 115.0)*3.141562/180.);

    coorx_E_2_0_e = -(580.*mm + 1*mm -5.5*mm)*cos(-(90.- 115.0)*3.141562/180.);
    coory_E_2_0_e = 0.*mm;	
    coorz_E_2_0_e = -(580.*mm + 1*mm -5.5*mm)*sin(-(90.- 115.0)*3.141562/180.);

// ** RingE21
    coorx_E_2_1 = -(599.*mm -5.5*mm)*cos(-(90.- 115.0)*3.141562/180.);
    coory_E_2_1 = 0.*mm;	
    coorz_E_2_1 = -(599.*mm -5.5*mm)*sin(-(90.- 115.0)*3.141562/180.);

    coorx_E_2_1_e = -(599.*mm + 1*mm -5.5*mm)*cos(-(90.- 115.0)*3.141562/180.);
    coory_E_2_1_e = 0.*mm;	
    coorz_E_2_1_e = -(599.*mm + 1*mm -5.5*mm)*sin(-(90.- 115.0)*3.141562/180.);



    theta_F_0_0 = 125.71*deg;
    theta_F_0_1 = 125.71*deg;
    theta_F_1_0 = 137.13*deg;
    theta_F_1_1 = 137.13*deg;
    theta_F_2_0 = 148.55*deg;
    theta_F_2_1 = 148.55*deg;
    theta_F_3_0 = 159.97*deg;
    theta_F_3_1 = 159.97*deg;

// ** RingF00
    coorx_F_0_0 = -(250.*mm )*cos(-(90.- 125.71)*3.141562/180.);
    coory_F_0_0 = 0.*mm;	
    coorz_F_0_0 = -(250.*mm )*sin(-(90.- 125.71)*3.141562/180.);

    coorx_F_0_0_e = -(250.*mm + 1*mm )*cos(-(90.- 125.71)*3.141562/180.);
    coory_F_0_0_e = 0.*mm;	
    coorz_F_0_0_e = -(250.*mm + 1*mm )*sin(-(90.- 125.71)*3.141562/180.);

// ** RingF01
    coorx_F_0_1 = -(260.*mm )*cos(-(90.- 125.71)*3.141562/180.);
    coory_F_0_1 = 0.*mm;	
    coorz_F_0_1 = -(260.*mm )*sin(-(90.- 125.71)*3.141562/180.);

    coorx_F_0_1_e = -(260.*mm + 1*mm )*cos(-(90.- 125.71)*3.141562/180.);
    coory_F_0_1_e = 0.*mm;	
    coorz_F_0_1_e = -(260.*mm + 1*mm )*sin(-(90.- 125.71)*3.141562/180.);

// ** RingF10
    coorx_F_1_0 = -(250.*mm -5.5*mm)*cos(-(90.- 137.13)*3.141562/180.);
    coory_F_1_0 = 0.*mm;	
    coorz_F_1_0 = -(250.*mm -5.5*mm)*sin(-(90.- 137.13)*3.141562/180.);

    coorx_F_1_0_e = -(250.*mm + 1*mm -5.5*mm)*cos(-(90.- 137.13)*3.141562/180.);
    coory_F_1_0_e = 0.*mm;	
    coorz_F_1_0_e = -(250.*mm + 1*mm -5.5*mm)*sin(-(90.- 137.13)*3.141562/180.);

// ** RingF11
    coorx_F_1_1 = -(260.*mm -5.5*mm)*cos(-(90.- 137.13)*3.141562/180.);
    coory_F_1_1 = 0.*mm;	
    coorz_F_1_1 = -(260.*mm -5.5*mm)*sin(-(90.- 137.13)*3.141562/180.);

    coorx_F_1_1_e = -(260.*mm + 1*mm -5.5*mm)*cos(-(90.- 137.13)*3.141562/180.);
    coory_F_1_1_e = 0.*mm;	
    coorz_F_1_1_e = -(260.*mm + 1*mm -5.5*mm)*sin(-(90.- 137.13)*3.141562/180.);

// ** RingF20
    coorx_F_2_0 = -(250.*mm )*cos(-(90.- 148.55)*3.141562/180.);
    coory_F_2_0 = 0.*mm;	
    coorz_F_2_0 = -(250.*mm )*sin(-(90.- 148.55)*3.141562/180.);

    coorx_F_2_0_e = -(250.*mm + 1*mm )*cos(-(90.- 148.55)*3.141562/180.);
    coory_F_2_0_e = 0.*mm;	
    coorz_F_2_0_e = -(250.*mm + 1*mm )*sin(-(90.- 148.55)*3.141562/180.);

// ** RingF21
    coorx_F_2_1 = -(260.*mm )*cos(-(90.- 148.55)*3.141562/180.);
    coory_F_2_1 = 0.*mm;	
    coorz_F_2_1 = -(260.*mm )*sin(-(90.- 148.55)*3.141562/180.);

    coorx_F_2_1_e = -(260.*mm + 1*mm )*cos(-(90.- 148.55)*3.141562/180.);
    coory_F_2_1_e = 0.*mm;	
    coorz_F_2_1_e = -(260.*mm + 1*mm )*sin(-(90.- 148.55)*3.141562/180.);

// ** RingF30
    coorx_F_3_0 = -(250.*mm -5.5*mm)*cos(-(90.- 159.97)*3.141562/180.);
    coory_F_3_0 = 0.*mm;	
    coorz_F_3_0 = -(250.*mm -5.5*mm)*sin(-(90.- 159.97)*3.141562/180.);

    coorx_F_3_0_e = -(250.*mm + 1*mm -5.5*mm)*cos(-(90.- 159.97)*3.141562/180.);
    coory_F_3_0_e = 0.*mm;	
    coorz_F_3_0_e = -(250.*mm + 1*mm -5.5*mm)*sin(-(90.- 159.97)*3.141562/180.);

// ** RingF31
    coorx_F_3_1 = -(260.*mm -5.5*mm)*cos(-(90.- 159.97)*3.141562/180.);
    coory_F_3_1 = 0.*mm;	
    coorz_F_3_1 = -(260.*mm -5.5*mm)*sin(-(90.- 159.97)*3.141562/180.);

    coorx_F_3_1_e = -(260.*mm + 1*mm -5.5*mm)*cos(-(90.- 159.97)*3.141562/180.);
    coory_F_3_1_e = 0.*mm;	
    coorz_F_3_1_e = -(260.*mm + 1*mm -5.5*mm)*sin(-(90.- 159.97)*3.141562/180.);



   //--------------------ponemos algunos mensajes----------------------------
   //slit_z = GetSlit_z();
   //slit_x = GetSlit_x();
  
   //pocket_x = GetPocket1_x();

   
  //-------------------------------------------------------------------------
   
 }
  
 G4VPhysicalVolume* DetectorConstruction::Construct()
 {
   //This function is called by G4 when the detector has to be created
   //--------- Definitions of Solids, Logical Volumes, Physical Volumes ---------

   
   //------------------------------
   // World
   //------------------------------
  
   G4GeometryManager::GetInstance()->SetWorldMaximumExtent(2.*halfWorldLength);
   G4cout << "Computed tolerance = "
          << G4GeometryTolerance::GetInstance()->GetSurfaceTolerance()/mm
          << " mm" << G4endl;
 
 
   G4Box * solidWorld= new G4Box("world",halfWorldLength,halfWorldLength,halfWorldLength);
   logicWorld= new G4LogicalVolume( solidWorld, vacuum, "World", 0, 0, 0);
   
   //  Must place the World Physical volume unrotated at (0,0,0).
   //
   G4VPhysicalVolume * physiWorld = new G4PVPlacement(0,               // no rotation
                                                      G4ThreeVector(), // at (0,0,0)
                                                      logicWorld,      // its logical volume
                                                      "World",         // its name
                                                      0,               // its mother  volume
                                                      false,           // no boolean operations
                                                      0);              // copy number
                                  
 
 
   //The construction of the three si plane is actually done here

//--------------------------valores que se recargan del mensaje-----------
   G4double el_x_pocket1 = -(250.*mm)*cos(-9.5*3.141562/180.) -pocket_x*sin(-9.5*3.141562/180.);
   G4double el_z_pocket1 = -(250.*mm)*sin(-9.5*3.141562/180.) +pocket_x*cos(-9.5*3.141562/180.);

   posSecondSensor = G4ThreeVector( el_x_pocket1, 0.*mm,  el_z_pocket1); // DSSD
//------------------------------------------------------------------------

   ConstructRings();
   ConstructCrystals(); 


  //--------- jet-gas target -------------------------------

 //a cylindrical target
  /*G4RotationMatrix *x_rotM = new G4RotationMatrix();
  x_rotM->rotateX(90*deg);
   G4Tubs * solidTarget = new G4Tubs("target",0.,3*fwhm_target/2.35,4*fwhm_beam/2.35,0.,360.*deg); 
   logicTarget = new G4LogicalVolume(solidTarget,H2,"target");
  physiTarget = new G4PVPlacement(x_rotM,G4ThreeVector(0,0,0),logicTarget,"target",logicWorld,false,0);
*/


   //--------- Visualization attributes -------------------------------

/*
// --------------------------- Scintillator
//	

  G4double innerRadius = 650.0*mm;
  G4double outerRadius = 850.0*mm;
 
  

  G4VSolid* sphereSolid = new G4Sphere("Sphere_Solid",   // Name
                                         innerRadius,    // Inner radius
                                         outerRadius,    // Outer radius
                                         0.*deg,         // Starting phi
                                         360.0*deg,       // Delta phi
                                         10.*deg,         // Starting theta
                                         120.0*deg);      // Delta theta
 
 


  G4VSolid*  cono1Solid = new G4Cons("cono_arriba",
             		0*mm,
             		0*mm,
             		0*mm,
             		tan(45*3.141592/180.)*850*mm,
             		 425*mm,
             		  0*deg,
             		   360*deg); 

  G4ThreeVector yTrans(0, 425*mm, 0);
  G4RotationMatrix * rota = new G4RotationMatrix;
	rota->rotateX(90*deg);
    	
  G4SubtractionSolid* subtraction1 =
    new G4SubtractionSolid("Esferapartearriba", sphereSolid, cono1Solid, rota, yTrans);

  
  G4ThreeVector yTrans2(0, -425*mm, 0);
  G4RotationMatrix * rota2 = new G4RotationMatrix;
	rota2->rotateX(-90*deg);
    	
  G4SubtractionSolid* subtraction2 =
    new G4SubtractionSolid("Esferaabajo", subtraction1, cono1Solid, rota2, yTrans2);
 
    
    G4LogicalVolume* sphereLogical =
    new G4LogicalVolume(subtraction2, vacuum, "Sphere_Logical");
 
 
  new G4PVPlacement(0, G4ThreeVector(), sphereLogical, "Sphere_Physical_E",
                     logicWorld, false, 0);




//-------------------volumen parametrizado
G4double deltaPhi = 2.647*deg; 
G4double deltaTheta = 8.79*deg;
//definimos una madre
G4VSolid* madre1 = new G4Sphere("madre1",   // Name
                                         innerRadius,    // Inner radius
                                         outerRadius,    // Outer radius
                                          15.27*deg,         // Starting phi
                                         15.27*deg,       // Delta phi
                                         10.*deg,         // Starting theta
                                         110*deg);      // Delta theta

    G4LogicalVolume* madre1Logical =
    new G4LogicalVolume(madre1, vacuum, "Madre1_Logical");

    new G4PVPlacement(0, G4ThreeVector(), madre1Logical, "Madre_Physical",
                     logicWorld, false, 0);

*/
/*//un cristal
G4VSolid* scoreSolid = new G4Sphere("Score_Solid",   // Name
                                        innerRadius,   // Inner radius
                                        outerRadius,   // Outer radius
                                        0.*deg,        // Starting phi
                                        deltaPhi,      // Delta phi    
                                        0.*deg,        // Starting theta
                                        deltaTheta);   // Delta theta
 
  G4LogicalVolume* fScoreLogical = 
    new G4LogicalVolume(scoreSolid, vacuum, "scoreLog");
 //parametrizacion
  CrystalParameterisation* param =
    new CrystalParameterisation(innerRadius, outerRadius, 10.*deg, 15.65*deg);
 
  new G4PVParameterised("scorePhys",   // Name
                         fScoreLogical, // Logical volume
                         madre1Logical, // Mother volume
                         kZAxis,        // Axis
                         23,            // Number of replicas
                         param);        // Parameterisation

*/



/*
 G4LogicalVolume* fScoreLogical2 = 
    new G4LogicalVolume(scoreSolid, vacuum, "scoreLog2");
 
  CrystalParameterisation* param2 =
    new CrystalParameterisation(innerRadius, outerRadius, 18.8*deg, 8.18*deg);
 
  new G4PVParameterised("scorePhys2",   // Name
                         fScoreLogical2, // Logical volume
                         sphereLogical, // Mother volume
                         kZAxis,        // Axis
                         44,            // Number of replicas
                         param2);        // Parameterisation

*/


//--------------------------otro anillo de cristales


/*
  G4VSolid* scintillator_solid =  new   G4Trd("Scintillator_solid",                        
					    2.0*cm,   //x mitad mayor
					    1.0*cm,    //x mitad menor
					    1.0*cm,   //y mitad mayor
					    1.0*cm,   //y mitad menor
					    5.5*cm );  //z mitad largo

  
  G4LogicalVolume* scintillator_log
    = new G4LogicalVolume(scintillator_solid,CsI,"Scintillator_log");

    G4RotationMatrix *rot = new G4RotationMatrix();   // me define una rotacion
    rot->rotateX(180.*deg);
    //rot->rotateY(-10.30*deg);

  CrystalParameterisation* paramdelta =
    new CrystalParameterisation(150*cm, 150*cm+11*cm, 10.*deg);    

	parametro = new G4PVParameterised("scorePhysdelta",   // Name
                         scintillator_log, // Logical volume
                         sphereLogical, // Mother volume
                         kZAxis,        // Axis
                         50,            // Number of replicas
                         paramdelta);        // Parameterisation

*/
/*
  scintillator_phys
    = new G4PVPlacement(rot,G4ThreeVector(0*cm,-0.1*cm,100.0*cm),scintillator_log,"Scintillator_phy",
                        logicWorld,false,0);
*/
  //----------------------------------------------------------------------------------------
  




   G4Color
     green(0.0,1.0,0.0),
     blue(0.0,0.0,1.0),
     brown(0.4,0.4,0.1),	
     white(1.0,1.0,1.0);
 
   //sphereLogical-> SetVisAttributes(G4VisAttributes::Invisible); 
   logicWorld -> SetVisAttributes(new G4VisAttributes(white));
   logicWorld -> SetVisAttributes(G4VisAttributes::Invisible);
   //sphereLogical -> SetVisAttributes(G4VisAttributes::Invisible);
  

   return physiWorld;
 }
 
 G4VPhysicalVolume* DetectorConstruction::ConstructRings()
 {
   //
   // 1st Plane of Si Beam Telescope
   //
   
     G4cout<<"Construyendo el Sector D"<<G4endl;
     ConstructRing_D_0_0();
     ConstructRing_D_0_1();
    ConstructRing_D_0_2();
 
    ConstructRing_D_1_0();
    ConstructRing_D_1_1();
    ConstructRing_D_1_2();
 
    ConstructRing_D_2_0();
    ConstructRing_D_2_1();
    ConstructRing_D_2_2();

    ConstructRing_C_0_0();
    ConstructRing_C_0_1();

    ConstructRing_C_1_0();
    ConstructRing_C_1_1();

    ConstructRing_C_2_0();
    ConstructRing_C_2_1();

    ConstructRing_C_3_0();
    ConstructRing_C_3_1();

    ConstructRing_B_0_0();
    ConstructRing_B_0_1();
    ConstructRing_B_0_2();
    ConstructRing_B_0_3();

    ConstructRing_A_0_0();
    ConstructRing_A_0_1();

   ConstructRing_E_0_0();
   ConstructRing_E_0_1();
   ConstructRing_E_1_0();
   ConstructRing_E_1_1();
   ConstructRing_E_2_0();
   ConstructRing_E_2_1();

   ConstructRing_F_0_0();
   ConstructRing_F_0_1();
   ConstructRing_F_1_0();
   ConstructRing_F_1_1();
   ConstructRing_F_2_0();
   ConstructRing_F_2_1();
   ConstructRing_F_3_0();
   ConstructRing_F_3_1(); 

   //ConstructCrystals();
   // ----------------------------------------------------------
   // -- Binding SensitiveDetector code to sensor strip volume:
   // -- Note that it is possible to set the sensitive detector
   // -- at construction of the G4LogicalVolume (fith argument
   // -- is a G4VSensitiveDetector*).
   // ----------------------------------------------------------
   //Every time the /det/update command is executed this
   //method is called since geometry is recomputed.
   //However we do not need to create a new SD, but reuse the
   //already existing one
   static SensitiveDetector* sensitive = 0;
   if ( !sensitive) {
     sensitive = new SensitiveDetector("/myDet/SiStripSD");
     //We register now the SD with the manager
     G4SDManager::GetSDMpointer()->AddNewDetector(sensitive);
 
   }
  

//******* dos lineas para anexar un detector diferente en una replica de detectores

   //if ( isSecondPlaneDUT ) {
     //With DUT we need to attach to the logical volume of the strips the
     //sensitive detector, since we only have a pointer to the physical volume
     //of the second plane we need to do some gymnastic:
     //1- First we get the logical volume associated to the second plane
     const G4LogicalVolume* log = physiSensorRing_D_0_0->GetLogicalVolume();
     //2- Then we get the first daughter associated to it: the strip
     // since strip is a replicated volume (G4PVReplica) there is
     // a single G4PhysicalVolume representing all replicas.
     // We actually need the LogicalVolume.
     // Thus we ask the first daughter ::GetDaughter(0) and ask the
     // associated logical volume
     log->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);
   //}
     
	//adjuntamos el D como sensitive
   const G4LogicalVolume* ring_sen_D01 = physiSensorRing_D_0_1->GetLogicalVolume();	
   ring_sen_D01->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);
 
   const G4LogicalVolume* ring_sen_D02 = physiSensorRing_D_0_2->GetLogicalVolume();	
   ring_sen_D02->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_D10 = physiSensorRing_D_1_0->GetLogicalVolume();	
   ring_sen_D10->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_D11 = physiSensorRing_D_1_1->GetLogicalVolume();	
   ring_sen_D11->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);
 
   const G4LogicalVolume* ring_sen_D12 = physiSensorRing_D_1_2->GetLogicalVolume();	
   ring_sen_D12->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);


    const G4LogicalVolume* ring_sen_D20 = physiSensorRing_D_2_0->GetLogicalVolume();	
   ring_sen_D20->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_D21 = physiSensorRing_D_2_1->GetLogicalVolume();	
   ring_sen_D21->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);
 
   const G4LogicalVolume* ring_sen_D22 = physiSensorRing_D_2_2->GetLogicalVolume();	
   ring_sen_D22->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

	//adjuntamos el D como sensitive
   const G4LogicalVolume* ring_sen_C00 = physiSensorRing_C_0_0->GetLogicalVolume();	
   ring_sen_C00->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_C01 = physiSensorRing_C_0_1->GetLogicalVolume();	
   ring_sen_C01->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_C10 = physiSensorRing_C_1_0->GetLogicalVolume();	
   ring_sen_C10->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_C11 = physiSensorRing_C_1_1->GetLogicalVolume();	
   ring_sen_C11->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_C20 = physiSensorRing_C_2_0->GetLogicalVolume();	
   ring_sen_C20->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_C21 = physiSensorRing_C_2_1->GetLogicalVolume();	
   ring_sen_C21->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_C30 = physiSensorRing_C_3_0->GetLogicalVolume();	
   ring_sen_C30->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_C31 = physiSensorRing_C_3_1->GetLogicalVolume();	
   ring_sen_C31->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);


   //adjuntamos el B como sensitive
   const G4LogicalVolume* ring_sen_B00 = physiSensorRing_B_0_0->GetLogicalVolume();	
   ring_sen_B00->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_B01 = physiSensorRing_B_0_1->GetLogicalVolume();	
   ring_sen_B01->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_B02 = physiSensorRing_B_0_2->GetLogicalVolume();	
   ring_sen_B02->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_B03 = physiSensorRing_B_0_3->GetLogicalVolume();	
   ring_sen_B03->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);


   //adjuntamos el A como sensitive
   const G4LogicalVolume* ring_sen_A00 = physiSensorRing_A_0_0->GetLogicalVolume();	
   ring_sen_A00->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_A01 = physiSensorRing_A_0_1->GetLogicalVolume();	
   ring_sen_A01->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);



   //adjuntamos el E como sensitive
   const G4LogicalVolume* ring_sen_E00 = physiSensorRing_E_0_0->GetLogicalVolume();	
   ring_sen_E00->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_E01 = physiSensorRing_E_0_1->GetLogicalVolume();	
   ring_sen_E01->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_E10 = physiSensorRing_E_1_0->GetLogicalVolume();	
   ring_sen_E10->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_E11 = physiSensorRing_E_1_1->GetLogicalVolume();	
   ring_sen_E11->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_E20 = physiSensorRing_E_2_0->GetLogicalVolume();	
   ring_sen_E20->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_E21 = physiSensorRing_E_2_1->GetLogicalVolume();	
   ring_sen_E21->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);



   //adjuntamos el F como sensitive
   const G4LogicalVolume* ring_sen_F00 = physiSensorRing_F_0_0->GetLogicalVolume();	
   ring_sen_F00->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_F01 = physiSensorRing_F_0_1->GetLogicalVolume();	
   ring_sen_F01->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_F10 = physiSensorRing_F_1_0->GetLogicalVolume();	
   ring_sen_F10->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_F11 = physiSensorRing_F_1_1->GetLogicalVolume();	
   ring_sen_F11->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_F20 = physiSensorRing_F_2_0->GetLogicalVolume();	
   ring_sen_F20->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_F21 = physiSensorRing_F_2_1->GetLogicalVolume();	
   ring_sen_F21->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_F30 = physiSensorRing_F_3_0->GetLogicalVolume();	
   ring_sen_F30->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   const G4LogicalVolume* ring_sen_F31 = physiSensorRing_F_3_1->GetLogicalVolume();	
   ring_sen_F31->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensitive);

   

   //static Crystal* sensiCrystal = 0;
   //if ( !sensiCrystal) {
   
     //We register now the SD with the manager
     //G4SDManager::GetSDMpointer()->AddNewDetector(sensiCrystal);
 
   //}
  
    //  G4VSensitiveDetector*  sensiCrystal = new Crystal("CrystalHitsCollection");
      //G4SDManager::GetSDMpointer()->AddNewDetector(  );

      //  G4SDManager::GetSDMpointer()->AddNewDetector(sensiCrystal);
       //logicCrystal->SetSensitiveDetector( sensiCrystal );
      //logicCrystal->SetSensitiveDetector(sensiCrystal);
      //const G4LogicalVolume* crystal = scintillator_phys->GetLogicalVolume();	
      //crystal->GetDaughter(0)->GetLogicalVolume()->SetSensitiveDetector(sensiCrystal);


   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0);
  
 
   return physiSensorRing_D_0_0;
 }
 
//-------------------------------------------------------------Layer D0

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_D_0_0()
 {
   
	double *ring_D_0_0; 

   G4Box * solidSensor_D_0_0 = new G4Box("SensorD_0_0",
                                   noOfSensorStrips*Lengthx_dssd_t1/2.,Lengthy_dssd_t1/2.,Thickness_dssd_t1/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_D_0_0, // its solid
                                                            silicon,     //its material
                                                            "SensorL_D_0_0");   //its name

   

   for(int jd00=0;jd00<12;jd00++){

	G4RotationMatrix * rot_D_0_0 = new G4RotationMatrix;
	phi_D_0_0 = (-(360./12.)*jd00); 
	rot_D_0_0->rotateZ(phi_D_0_0*deg);
    	rot_D_0_0->rotateY(theta_D_0_0);
    
	 
	if(jd00 % 2 == 0){ ring_D_0_0 = rotacion(coorx_D_0_0, coory_D_0_0, coorz_D_0_0, -phi_D_0_0);}	
	else{ring_D_0_0 = rotacion(coorx_D_0_0_e, coory_D_0_0_e, coorz_D_0_0_e, -phi_D_0_0);} 
	
	vector_D_0_0 = G4ThreeVector(*(ring_D_0_0), *(ring_D_0_0+1), *(ring_D_0_0+2));


	std::ostringstream nombre_d_0_0;
   	nombre_d_0_0 << "D_0_0_" << jd00 ;

	//G4cout<<phi_D_0_0*deg/deg<<"  "<<vector_D_0_0<<G4endl;
	G4cout<<jd00<<"  "<<theta_D_0_0/deg<<"  "<<-phi_D_0_0*deg/deg<<"  "<<sqrt(coorx_D_0_0*coorx_D_0_0 + coorz_D_0_0*coorz_D_0_0)<<G4endl;
    	physiSensorRing_D_0_0 =
    	 	new G4PVPlacement(rot_D_0_0,
                       		vector_D_0_0,
                       		logicSensorPlane,
                       		nombre_d_0_0.str().data(),
                       		logicWorld,
                       		false,
                       		jd00);
	}

 //
   // Strips
   
   G4Box * solidSensorStripD00 = 
     new G4Box("SensorStripD00",              
               Lengthx_dssd_t1/2.,Lengthy_dssd_t1/2.,Thickness_dssd_t1/2.);
 
   G4LogicalVolume * logicSensorStripD00 = 
     new G4LogicalVolume(solidSensorStripD00,silicon,"SensorStripD00");
 
   physiSensorStripD_0_0 = 
     new G4PVReplica("SensorStripD00",           //its name
                     logicSensorStripD00,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t1);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripD00 -> SetVisAttributes(new G4VisAttributes(yellow));
 
   return physiSensorRing_D_0_0;
 }



G4VPhysicalVolume* DetectorConstruction::ConstructRing_D_0_1()
 {
   double *ring_D_0_1; 

   G4Box * solidSensor_D_0_1 = new G4Box("SensorD_0_1",
                                   noOfSensorStrips*Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_D_0_1, // its solid
                                                            silicon,     //its material
                                                            "SensorL_D_0_1");   //its name

   

   for(int jd01=0;jd01<12;jd01++){

	G4RotationMatrix * rot_D_0_1 = new G4RotationMatrix;
	phi_D_0_1 = (-(360./12.)*jd01); 
	rot_D_0_1->rotateZ(phi_D_0_1*deg);
    	rot_D_0_1->rotateY(theta_D_0_1);
    
	 if(jd01 % 2 == 0){ ring_D_0_1 = rotacion(coorx_D_0_1, coory_D_0_1, coorz_D_0_1, -phi_D_0_1);}	
         else{ring_D_0_1 = rotacion(coorx_D_0_1_e, coory_D_0_1_e, coorz_D_0_1_e, -phi_D_0_1);} 

	 vector_D_0_1 = G4ThreeVector(*(ring_D_0_1), *(ring_D_0_1+1), *(ring_D_0_1+2));

	std::ostringstream nombre_d_0_1;
   	nombre_d_0_1 << "D_0_1_" << jd01 ;

	//G4cout<<phi_D_0_1*deg/deg<<"  "<<vector_D_0_1<<G4endl;
	G4cout<<jd01+12<<"  "<<theta_D_0_1/deg<<"  "<<-phi_D_0_1*deg/deg<<"  "<<sqrt(coorx_D_0_1*coorx_D_0_1 + coorz_D_0_1*coorz_D_0_1)<<G4endl;
    	physiSensorRing_D_0_1 =
    	 	new G4PVPlacement(rot_D_0_1,
                       		vector_D_0_1,
                       		logicSensorPlane,
                       		nombre_d_0_1.str().data(),
                       		logicWorld,
                       		false,
                       		jd01 + 12);
	}

 //
   // Strips
   
   G4Box * solidSensorStripD01 = 
     new G4Box("SensorStripD01",              
               Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorStripD01 = 
     new G4LogicalVolume(solidSensorStripD01,silicon,"SensorStripD01");
 
   physiSensorStripD_0_1 = 
     new G4PVReplica("SensorStripD01",           //its name
                     logicSensorStripD01,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t2);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripD01 -> SetVisAttributes(new G4VisAttributes(yellow));
 
   return physiSensorRing_D_0_1;
 }



G4VPhysicalVolume* DetectorConstruction::ConstructRing_D_0_2()
 {
   double *ring_D_0_2; 

   G4Box * solidSensor_D_0_2 = new G4Box("SensorD_0_2",
                                   noOfSensorStrips*Lengthx_sili/2.,Lengthy_sili/2.,Thickness_sili/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_D_0_2, // its solid
                                                            silicon,     //its material
                                                            "SensorL_D_0_2");   //its name

   

   for(int jd02=0;jd02<12;jd02++){

	G4RotationMatrix * rot_D_0_2 = new G4RotationMatrix;
	phi_D_0_2 = (-(360./12.)*jd02); 
	rot_D_0_2->rotateZ(phi_D_0_2*deg);
    	rot_D_0_2->rotateY(theta_D_0_2);
    
	 if(jd02 % 2 == 0){ ring_D_0_2 = rotacion(coorx_D_0_2, coory_D_0_2, coorz_D_0_2, -phi_D_0_2);}	
         else{ring_D_0_2 = rotacion(coorx_D_0_2_e, coory_D_0_2_e, coorz_D_0_2_e, -phi_D_0_2);} 

	 vector_D_0_2 = G4ThreeVector(*(ring_D_0_2), *(ring_D_0_2+1), *(ring_D_0_2+2));

	std::ostringstream nombre_d_0_2;
   	nombre_d_0_2 << "D_0_2_" << jd02 ;

	//G4cout<<phi_D_0_2*deg/deg<<"  "<<vector_D_0_2<<G4endl;
	G4cout<<jd02+24<<"  "<<theta_D_0_2/deg<<"  "<<-phi_D_0_2*deg/deg<<"  "<<sqrt(coorx_D_0_2*coorx_D_0_2 + coorz_D_0_2*coorz_D_0_2)<<G4endl;
    	physiSensorRing_D_0_2 =
    	 	new G4PVPlacement(rot_D_0_2,
                       		vector_D_0_2,
                       		logicSensorPlane,
                       		nombre_d_0_2.str().data(),
                       		logicWorld,
                       		false,
                       		jd02 + 12 + 12);
	}

 //
   // Strips
   
   G4Box * solidSensorStripD02 = 
     new G4Box("SensorStripD02",              
               Lengthx_sili/2.,Lengthy_sili/2.,Thickness_sili/2.);
 
   G4LogicalVolume * logicSensorStripD02 = 
     new G4LogicalVolume(solidSensorStripD02,silicon,"SensorStripD02");
 
   physiSensorStripD_0_2 = 
     new G4PVReplica("SensorStripD02",           //its name
                     logicSensorStripD02,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_sili);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), cyan(0.0, 1.0, 1.0) , blue(0.0, 0.0, 1.0), orange(1.0, 1.0, 0.5);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripD02 -> SetVisAttributes(new G4VisAttributes(yellow));
 
   return physiSensorRing_D_0_2;
 }

////-------------------------------------------------------------Layer D1
G4VPhysicalVolume* DetectorConstruction::ConstructRing_D_1_0()
 {
   
	double *ring_D_1_0; 

   G4Box * solidSensor_D_1_0 = new G4Box("SensorD_1_0",
                                   noOfSensorStrips*Lengthx_dssd_t1/2.,Lengthy_dssd_t1/2.,Thickness_dssd_t1/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_D_1_0, // its solid
                                                            silicon,     //its material
                                                            "SensorL_D_1_0");   //its name

   

   for(int jd10=0;jd10<20;jd10++){

	G4RotationMatrix * rot_D_1_0 = new G4RotationMatrix;
	phi_D_1_0 = (-(360./20.)*jd10); 
	rot_D_1_0->rotateZ(phi_D_1_0*deg);
    	rot_D_1_0->rotateY(theta_D_1_0);
    
	 
	if(jd10 % 2 == 0){ ring_D_1_0 = rotacion(coorx_D_1_0, coory_D_1_0, coorz_D_1_0, -phi_D_1_0);}	
	else{ring_D_1_0 = rotacion(coorx_D_1_0_e, coory_D_1_0_e, coorz_D_1_0_e, -phi_D_1_0);} 
	
	vector_D_1_0 = G4ThreeVector(*(ring_D_1_0), *(ring_D_1_0+1), *(ring_D_1_0+2));


	std::ostringstream nombre_d_1_0;
   	nombre_d_1_0 << "D_1_0_" << jd10 ;

	//G4cout<<phi_D_1_0*deg/deg<<"  "<<vector_D_1_0<<G4endl;
	G4cout<<jd10+36<<"  "<<theta_D_1_0/deg<<"  "<<-phi_D_1_0*deg/deg<<"  "<<sqrt(coorx_D_1_0*coorx_D_1_0 + coorz_D_1_0*coorz_D_1_0)<<G4endl;
    	physiSensorRing_D_1_0 =
    	 	new G4PVPlacement(rot_D_1_0,
                       		vector_D_1_0,
                       		logicSensorPlane,
                       		nombre_d_1_0.str().data(),
                       		logicWorld,
                       		false,
                       		jd10+36);
	}

 //
   // Strips
   
   G4Box * solidSensorStripD10 = 
     new G4Box("SensorStripD10",              
               Lengthx_dssd_t1/2.,Lengthy_dssd_t1/2.,Thickness_dssd_t1/2.);
 
   G4LogicalVolume * logicSensorStripD10 = 
     new G4LogicalVolume(solidSensorStripD10,silicon,"SensorStripD10");
 
   physiSensorStripD_1_0 = 
     new G4PVReplica("SensorStripD10",           //its name
                     logicSensorStripD10,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t1);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), cyan(0.0, 1.0, 1.0) , blue(0.0, 0.0, 1.0), orange(1.0, 1.0, 0.5);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripD10 -> SetVisAttributes(new G4VisAttributes(yellow));
 
   return physiSensorRing_D_1_0;
 }



G4VPhysicalVolume* DetectorConstruction::ConstructRing_D_1_1()
 {
   double *ring_D_1_1; 

   G4Box * solidSensor_D_1_1 = new G4Box("SensorD_1_1",
                                   noOfSensorStrips*Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_D_1_1, // its solid
                                                            silicon,     //its material
                                                            "SensorL_D_1_1");   //its name

   

   for(int jd11=0;jd11<20;jd11++){

	G4RotationMatrix * rot_D_1_1 = new G4RotationMatrix;
	phi_D_1_1 = (-(360./20.)*jd11); 
	rot_D_1_1->rotateZ(phi_D_1_1*deg);
    	rot_D_1_1->rotateY(theta_D_1_1);
    
	 if(jd11 % 2 == 0){ ring_D_1_1 = rotacion(coorx_D_1_1, coory_D_1_1, coorz_D_1_1, -phi_D_1_1);}	
         else{ring_D_1_1 = rotacion(coorx_D_1_1_e, coory_D_1_1_e, coorz_D_1_1_e, -phi_D_1_1);} 

	 vector_D_1_1 = G4ThreeVector(*(ring_D_1_1), *(ring_D_1_1+1), *(ring_D_1_1+2));

	std::ostringstream nombre_d_1_1;
   	nombre_d_1_1 << "D_1_1_" << jd11 ;

	//G4cout<<phi_D_1_1*deg/deg<<"  "<<vector_D_1_1<<G4endl;
	G4cout<<jd11+56<<"  "<<theta_D_1_1/deg<<"  "<<-phi_D_1_1*deg/deg<<"  "<<sqrt(coorx_D_1_1*coorx_D_1_1 + coorz_D_1_0*coorz_D_1_1)<<G4endl;
    	physiSensorRing_D_1_1 =
    	 	new G4PVPlacement(rot_D_1_1,
                       		vector_D_1_1,
                       		logicSensorPlane,
                       		nombre_d_1_1.str().data(),
                       		logicWorld,
                       		false,
                       		jd11 + 56);
	}

 //
   // Strips
   
   G4Box * solidSensorStripD11 = 
     new G4Box("SensorStripD11",              
               Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorStripD11 = 
     new G4LogicalVolume(solidSensorStripD11,silicon,"SensorStripD11");
 
   physiSensorStripD_1_1 = 
     new G4PVReplica("SensorStripD11",           //its name
                     logicSensorStripD11,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t2);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), cyan(0.0, 1.0, 1.0) , blue(0.0, 0.0, 1.0), orange(1.0, 1.0, 0.5);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripD11 -> SetVisAttributes(new G4VisAttributes(yellow));
 
   return physiSensorRing_D_1_1;
 }



G4VPhysicalVolume* DetectorConstruction::ConstructRing_D_1_2()
 {
   double *ring_D_1_2; 

   G4Box * solidSensor_D_1_2 = new G4Box("SensorD_1_2",
                                   noOfSensorStrips*Lengthx_sili/2.,Lengthy_sili/2.,Thickness_sili/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_D_1_2, // its solid
                                                            silicon,     //its material
                                                            "SensorL_D_1_2");   //its name

   

   for(int jd12=0;jd12<20;jd12++){

	G4RotationMatrix * rot_D_1_2 = new G4RotationMatrix;
	phi_D_1_2 = (-(360./20.)*jd12); 
	rot_D_1_2->rotateZ(phi_D_1_2*deg);
    	rot_D_1_2->rotateY(theta_D_1_2);
    
	 if(jd12 % 2 == 0){ ring_D_1_2 = rotacion(coorx_D_1_2, coory_D_1_2, coorz_D_1_2, -phi_D_1_2);}	
         else{ring_D_1_2 = rotacion(coorx_D_1_2_e, coory_D_1_2_e, coorz_D_1_2_e, -phi_D_1_2);} 

	 vector_D_1_2 = G4ThreeVector(*(ring_D_1_2), *(ring_D_1_2+1), *(ring_D_1_2+2));

	std::ostringstream nombre_d_1_2;
   	nombre_d_1_2 << "D_1_2_" << jd12 ;

	//G4cout<<phi_D_1_2*deg/deg<<"  "<<vector_D_1_2<<G4endl;
	G4cout<<jd12+76<<"  "<<theta_D_1_2/deg<<"  "<<-phi_D_1_2*deg/deg<<"  "<<sqrt(coorx_D_1_2*coorx_D_1_2 + coorz_D_1_2*coorz_D_1_2)<<G4endl;
    	physiSensorRing_D_1_2 =
    	 	new G4PVPlacement(rot_D_1_2,
                       		vector_D_1_2,
                       		logicSensorPlane,
                       		nombre_d_1_2.str().data(),
                       		logicWorld,
                       		false,
                       		jd12 + 76);
	}

 //
   // Strips
   
   G4Box * solidSensorStripD12 = 
     new G4Box("SensorStripD12",              
               Lengthx_sili/2.,Lengthy_sili/2.,Thickness_sili/2.);
 
   G4LogicalVolume * logicSensorStripD12 = 
     new G4LogicalVolume(solidSensorStripD12,silicon,"SensorStripD12");
 
   physiSensorStripD_1_2 = 
     new G4PVReplica("SensorStripD12",           //its name
                     logicSensorStripD12,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_sili);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), cyan(0.0, 1.0, 1.0) , blue(0.0, 0.0, 1.0), orange(1.0, 1.0, 0.5);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripD12 -> SetVisAttributes(new G4VisAttributes(yellow));
 
   return physiSensorRing_D_1_2;
 }

////-------------------------------------------------------------Layer D2
G4VPhysicalVolume* DetectorConstruction::ConstructRing_D_2_0()
 {
   
	double *ring_D_2_0; 

   G4Box * solidSensor_D_2_0 = new G4Box("SensorD_2_0",
                                   noOfSensorStrips*Lengthx_dssd_t1/2.,Lengthy_dssd_t1/2.,Thickness_dssd_t1/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_D_2_0, // its solid
                                                            silicon,     //its material
                                                            "SensorL_D_2_0");   //its name

   

   for(int jd20=0;jd20<24;jd20++){

	G4RotationMatrix * rot_D_2_0 = new G4RotationMatrix;
	phi_D_2_0 = (-(360./24.)*jd20); 
	rot_D_2_0->rotateZ(phi_D_2_0*deg);
    	rot_D_2_0->rotateY(theta_D_2_0);
    
	 
	if(jd20 % 2 == 0){ ring_D_2_0 = rotacion(coorx_D_2_0, coory_D_2_0, coorz_D_2_0, -phi_D_2_0);}	
	else{ring_D_2_0 = rotacion(coorx_D_2_0_e, coory_D_2_0_e, coorz_D_2_0_e, -phi_D_2_0);} 
	
	vector_D_2_0 = G4ThreeVector(*(ring_D_2_0), *(ring_D_2_0+1), *(ring_D_2_0+2));


	std::ostringstream nombre_D_2_0;
   	nombre_D_2_0 << "D_2_0_" << jd20 ;

	//G4cout<<phi_D_2_0*deg/deg<<"  "<<vector_D_2_0<<G4endl;
	G4cout<<jd20+96<<"  "<<theta_D_2_0/deg<<"  "<<-phi_D_2_0*deg/deg<<"  "<<sqrt(coorx_D_2_0*coorx_D_2_0 + coorz_D_2_0*coorz_D_2_0)<<G4endl;
    	physiSensorRing_D_2_0 =
    	 	new G4PVPlacement(rot_D_2_0,
                       		vector_D_2_0,
                       		logicSensorPlane,
                       		nombre_D_2_0.str().data(),
                       		logicWorld,
                       		false,
                       		jd20+96);
	}

 //
   // Strips
   
   G4Box * solidSensorStripD20 = 
     new G4Box("SensorStripD20",              
               Lengthx_dssd_t1/2.,Lengthy_dssd_t1/2.,Thickness_dssd_t1/2.);
 
   G4LogicalVolume * logicSensorStripD20 = 
     new G4LogicalVolume(solidSensorStripD20,silicon,"SensorStripD20");
 
   physiSensorStripD_2_0 = 
     new G4PVReplica("SensorStripD20",           //its name
                     logicSensorStripD20,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t1);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), cyan(0.0, 1.0, 1.0) , blue(0.0, 0.0, 1.0), orange(1.0, 1.0, 0.5);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripD20 -> SetVisAttributes(new G4VisAttributes(yellow));
 
   return physiSensorRing_D_2_0;
 }



G4VPhysicalVolume* DetectorConstruction::ConstructRing_D_2_1()
 {
   double *ring_D_2_1; 

   G4Box * solidSensor_D_2_1 = new G4Box("SensorD_2_1",
                                   noOfSensorStrips*Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_D_2_1, // its solid
                                                            silicon,     //its material
                                                            "SensorL_D_2_1");   //its name

   

   for(int jd21=0;jd21<24;jd21++){

	G4RotationMatrix * rot_D_2_1 = new G4RotationMatrix;
	phi_D_2_1 = (-(360./24.)*jd21); 
	rot_D_2_1->rotateZ(phi_D_2_1*deg);
    	rot_D_2_1->rotateY(theta_D_2_1);
    
	 if(jd21 % 2 == 0){ ring_D_2_1 = rotacion(coorx_D_2_1, coory_D_2_1, coorz_D_2_1, -phi_D_2_1);}	
         else{ring_D_2_1 = rotacion(coorx_D_2_1_e, coory_D_2_1_e, coorz_D_2_1_e, -phi_D_2_1);} 

	 vector_D_2_1 = G4ThreeVector(*(ring_D_2_1), *(ring_D_2_1+1), *(ring_D_2_1+2));

	std::ostringstream nombre_D_2_1;
   	nombre_D_2_1 << "D_2_1_" << jd21 ;

	//G4cout<<phi_D_2_1*deg/deg<<"  "<<vector_D_2_1<<G4endl;
	G4cout<<jd21+120<<"  "<<theta_D_2_1/deg<<"  "<<-phi_D_2_1*deg/deg<<"  "<<sqrt(coorx_D_2_1*coorx_D_2_1 + coorz_D_2_1*coorz_D_2_1)<<G4endl;
    	physiSensorRing_D_2_1 =
    	 	new G4PVPlacement(rot_D_2_1,
                       		vector_D_2_1,
                       		logicSensorPlane,
                       		nombre_D_2_1.str().data(),
                       		logicWorld,
                       		false,
                       		jd21 + 120);
	}

 //
   // Strips
   
   G4Box * solidSensorStripD21 = 
     new G4Box("SensorStripD21",              
               Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorStripD21 = 
     new G4LogicalVolume(solidSensorStripD21,silicon,"SensorStripD21");
 
   physiSensorStripD_2_1 = 
     new G4PVReplica("SensorStripD11",           //its name
                     logicSensorStripD21,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t2);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), cyan(0.0, 1.0, 1.0) , blue(0.0, 0.0, 1.0), orange(1.0, 1.0, 0.5);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripD21 -> SetVisAttributes(new G4VisAttributes(yellow));
 
   return physiSensorRing_D_2_1;
 }



G4VPhysicalVolume* DetectorConstruction::ConstructRing_D_2_2()
 {
   double *ring_D_2_2; 

   G4Box * solidSensor_D_2_2 = new G4Box("SensorD_2_2",
                                   noOfSensorStrips*Lengthx_sili/2.,Lengthy_sili/2.,Thickness_sili/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_D_2_2, // its solid
                                                            silicon,     //its material
                                                            "SensorL_D_2_2");   //its name

   

   for(int jd22=0;jd22<24;jd22++){

	G4RotationMatrix * rot_D_2_2 = new G4RotationMatrix;
	phi_D_2_2 = (-(360./24.)*jd22); 
	rot_D_2_2->rotateZ(phi_D_2_2*deg);
    	rot_D_2_2->rotateY(theta_D_2_2);
    
	 if(jd22 % 2 == 0){ ring_D_2_2 = rotacion(coorx_D_2_2, coory_D_2_2, coorz_D_2_2, -phi_D_2_2);}	
         else{ring_D_2_2 = rotacion(coorx_D_2_2_e, coory_D_2_2_e, coorz_D_2_2_e, -phi_D_2_2);} 

	 vector_D_2_2 = G4ThreeVector(*(ring_D_2_2), *(ring_D_2_2+1), *(ring_D_2_2+2));

	std::ostringstream nombre_D_2_2;
   	nombre_D_2_2 << "D_2_2_" << jd22 ;

	//G4cout<<phi_D_2_2*deg/deg<<"  "<<vector_D_2_2<<G4endl;
	G4cout<<jd22+144<<"  "<<theta_D_2_2/deg<<"  "<<-phi_D_2_2*deg/deg<<"  "<<sqrt(coorx_D_2_2*coorx_D_2_2 + coorz_D_2_2*coorz_D_2_2)<<G4endl;
    	physiSensorRing_D_2_2 =
    	 	new G4PVPlacement(rot_D_2_2,
                       		vector_D_2_2,
                       		logicSensorPlane,
                       		nombre_D_2_2.str().data(),
                       		logicWorld,
                       		false,
                       		jd22 + 144);
	}

 //
   // Strips
   
   G4Box * solidSensorStripD22 = 
     new G4Box("SensorStripD22",              
               Lengthx_sili/2.,Lengthy_sili/2.,Thickness_sili/2.);
 
   G4LogicalVolume * logicSensorStripD22 = 
     new G4LogicalVolume(solidSensorStripD22,silicon,"SensorStripD22");
 
   physiSensorStripD_2_2 = 
     new G4PVReplica("SensorStripD22",           //its name
                     logicSensorStripD22,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_sili);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), cyan(0.0, 1.0, 1.0) , blue(0.0, 0.0, 1.0), orange(1.0, 1.0, 0.5);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripD22 -> SetVisAttributes(new G4VisAttributes(yellow));
 
   return physiSensorRing_D_2_2;
 }



//-------------------------------------------------------------RING C

//-------------------------------------------------------------Layer C00

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_C_0_0()
 {
   
	double *ring_C_0_0; 
	int flagC_0_0 = 0;

   G4Box * solidSensor_C_0_0 = new G4Box("SensorC_0_0",
                                   noOfSensorStrips*Lengthx_dssd_t1/2.,Lengthy_dssd_t1/2.,Thickness_dssd_t1/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_C_0_0, // its solid
                                                            silicon,     //its material
                                                            "SensorL_C_0_0");   //its name

   

   for(int jc00=0;jc00<31;jc00++){

	
	G4RotationMatrix * rot_C_0_0 = new G4RotationMatrix;
	phi_C_0_0 = (-(360./31.)*jc00); 
	rot_C_0_0->rotateZ(phi_C_0_0*deg);
    	rot_C_0_0->rotateY(theta_C_0_0);
    
	if((-phi_C_0_0 > 65. && -phi_C_0_0 < 118.) || (-phi_C_0_0 > 245. && -phi_C_0_0 < 295.) ){flagC_0_0++; continue;}
	 
	if(jc00 % 2 == 0){ ring_C_0_0 = rotacion(coorx_C_0_0, coory_C_0_0, coorz_C_0_0, -phi_C_0_0);}	
	else{ring_C_0_0 = rotacion(coorx_C_0_0_e, coory_C_0_0_e, coorz_C_0_0_e, -phi_C_0_0);} 
	
	vector_C_0_0 = G4ThreeVector(*(ring_C_0_0), *(ring_C_0_0+1), *(ring_C_0_0+2));
	//G4cout<<flagC_0_0<<"  "<<jc00<<G4endl;

	std::ostringstream nombre_C_0_0;
   	nombre_C_0_0 << "C_0_0_" << jc00-flagC_0_0 ;

	//G4cout<<phi_C_0_0*deg/deg<<"  "<<vector_C_0_0<<G4endl;
	G4cout<<jc00+168-flagC_0_0<<"  "<<theta_C_0_0/deg<<"  "<<-phi_C_0_0*deg/deg<<"  "<<sqrt(coorx_C_0_0*coorx_C_0_0 + coorz_C_0_0*coorz_C_0_0)<<G4endl;
    	physiSensorRing_C_0_0 =
    	 	new G4PVPlacement(rot_C_0_0,
                       		vector_C_0_0,
                       		logicSensorPlane,
                       		nombre_C_0_0.str().data(),
                       		logicWorld,
                       		false,
                       		jc00 + 168 - flagC_0_0);
	}

 //
   // Strips
   
   G4Box * solidSensorStripC00 = 
     new G4Box("SensorStripC00",              
               Lengthx_dssd_t1/2.,Lengthy_dssd_t1/2.,Thickness_dssd_t1/2.);
 
   G4LogicalVolume * logicSensorStripC00 = 
     new G4LogicalVolume(solidSensorStripC00,silicon,"SensorStripC00");
 
   physiSensorStripC_0_0 = 
     new G4PVReplica("SensorStripC00",           //its name
                     logicSensorStripC00,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t1);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), cyan(0.0, 1.0, 1.0) , blue(0.0, 0.0, 1.0), orange(1.0, 1.0, 0.5);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripC00 -> SetVisAttributes(new G4VisAttributes(blue));
 
   return physiSensorRing_C_0_0;
 }


//-------------------------------------------------------------Layer C01

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_C_0_1()
 {
   
	double *ring_C_0_1; 
	int flagC_0_1 = 0;

   G4Box * solidSensor_C_0_1 = new G4Box("SensorC_0_1",
                                   noOfSensorStrips*Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_C_0_1, // its solid
                                                            silicon,     //its material
                                                            "SensorL_C_0_1");   //its name

   

   for(int jc01=0;jc01<31;jc01++){

	
	G4RotationMatrix * rot_C_0_1 = new G4RotationMatrix;
	phi_C_0_1 = (-(360./31.)*jc01); 
	rot_C_0_1->rotateZ(phi_C_0_1*deg);
    	rot_C_0_1->rotateY(theta_C_0_1);
    
	if((-phi_C_0_1 > 65. && -phi_C_0_1 < 118.) || (-phi_C_0_1 > 245. && -phi_C_0_1 < 295.)){flagC_0_1++; continue;}
	 
	if(jc01 % 2 == 0){ ring_C_0_1 = rotacion(coorx_C_0_1, coory_C_0_1, coorz_C_0_1, -phi_C_0_1);}	
	else{ring_C_0_1 = rotacion(coorx_C_0_1_e, coory_C_0_1_e, coorz_C_0_1_e, -phi_C_0_1);} 
	
	vector_C_0_1 = G4ThreeVector(*(ring_C_0_1), *(ring_C_0_1+1), *(ring_C_0_1+2));
	//G4cout<<flagC_0_1<<"  "<<jc00<<G4endl;

	std::ostringstream nombre_C_0_1;
   	nombre_C_0_1 << "C_0_1_" << jc01-flagC_0_1 ;

	//G4cout<<phi_C_0_1*deg/deg<<"  "<<vector_C_0_1<<G4endl;
	G4cout<<jc01+190-flagC_0_1<<"  "<<theta_C_0_1/deg<<"  "<<-phi_C_0_1*deg/deg<<"  "<<sqrt(coorx_C_0_1*coorx_C_0_1 + coorz_C_0_1*coorz_C_0_1)<<G4endl;
    	physiSensorRing_C_0_1 =
    	 	new G4PVPlacement(rot_C_0_1,
                       		vector_C_0_1,
                       		logicSensorPlane,
                       		nombre_C_0_1.str().data(),
                       		logicWorld,
                       		false,
                       		jc01 + 190 - flagC_0_1);
	}

 //
   // Strips
   
   G4Box * solidSensorStripC01 = 
     new G4Box("SensorStripC01",              
               Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorStripC01 = 
     new G4LogicalVolume(solidSensorStripC01,silicon,"SensorStripC01");
 
   physiSensorStripC_0_1 = 
     new G4PVReplica("SensorStripC01",           //its name
                     logicSensorStripC01,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t2);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), cyan(0.0, 1.0, 1.0) , blue(0.0, 0.0, 1.0), orange(1.0, 1.0, 0.5);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripC01 -> SetVisAttributes(new G4VisAttributes(blue));
 
   return physiSensorRing_C_0_1;
 }


//-------------------------------------------------------------Layer C10

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_C_1_0()
 {
   
	double *ring_C_1_0; 
	int flagC_1_0 = 0;

   G4Box * solidSensor_C_1_0 = new G4Box("SensorC_1_0",
                                   noOfSensorStrips*Lengthx_dssd_t1/2.,Lengthy_dssd_t1/2.,Thickness_dssd_t1/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_C_1_0, // its solid
                                                            silicon,     //its material
                                                            "SensorL_C_1_0");   //its name

   

   for(int jc10=0;jc10<31;jc10++){

	
	G4RotationMatrix * rot_C_1_0 = new G4RotationMatrix;
	phi_C_1_0 = (-(360./31.)*jc10); 
	rot_C_1_0->rotateZ(phi_C_1_0*deg);
    	rot_C_1_0->rotateY(theta_C_1_0);
    
	if((-phi_C_1_0 > 65. && -phi_C_1_0 < 118.) || (-phi_C_1_0 > 245. && -phi_C_1_0 < 295.) ){flagC_1_0++; continue;}
	 
	if(jc10 % 2 == 0){ ring_C_1_0 = rotacion(coorx_C_1_0, coory_C_1_0, coorz_C_1_0, -phi_C_1_0);}	
	else{ring_C_1_0 = rotacion(coorx_C_1_0_e, coory_C_1_0_e, coorz_C_1_0_e, -phi_C_1_0);} 
	
	vector_C_1_0 = G4ThreeVector(*(ring_C_1_0), *(ring_C_1_0+1), *(ring_C_1_0+2));
	//G4cout<<flagC_1_0<<"  "<<jc10<<G4endl;

	std::ostringstream nombre_C_1_0;
   	nombre_C_1_0 << "C_1_0_" << jc10-flagC_1_0 ;

	//G4cout<<phi_C_1_0*deg/deg<<"  "<<vector_C_1_0<<G4endl;
	G4cout<<jc10+212-flagC_1_0<<"  "<<theta_C_1_0/deg<<"  "<<-phi_C_1_0*deg/deg<<"  "<<sqrt(coorx_C_1_0*coorx_C_1_0 + coorz_C_1_0*coorz_C_1_0)<<G4endl;
    	physiSensorRing_C_1_0 =
    	 	new G4PVPlacement(rot_C_1_0,
                       		vector_C_1_0,
                       		logicSensorPlane,
                       		nombre_C_1_0.str().data(),
                       		logicWorld,
                       		false,
                       		jc10 + 212 - flagC_1_0);
	}

 //
   // Strips
   
   G4Box * solidSensorStripC10 = 
     new G4Box("SensorStripC10",              
               Lengthx_dssd_t1/2.,Lengthy_dssd_t1/2.,Thickness_dssd_t1/2.);
 
   G4LogicalVolume * logicSensorStripC10 = 
     new G4LogicalVolume(solidSensorStripC10,silicon,"SensorStripC10");
 
   physiSensorStripC_1_0 = 
     new G4PVReplica("SensorStripC10",           //its name
                     logicSensorStripC10,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t1);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), cyan(0.0, 1.0, 1.0) , blue(0.0, 0.0, 1.0), orange(1.0, 1.0, 0.5);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripC10 -> SetVisAttributes(new G4VisAttributes(blue));
 
   return physiSensorRing_C_1_0;
 }


//-------------------------------------------------------------Layer C11

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_C_1_1()
 {
   
	double *ring_C_1_1; 
	int flagC_1_1 = 0;

   G4Box * solidSensor_C_1_1 = new G4Box("SensorC_1_1",
                                   noOfSensorStrips*Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_C_1_1, // its solid
                                                            silicon,     //its material
                                                            "SensorL_C_1_1");   //its name

   

   for(int jc11=0;jc11<31;jc11++){

	
	G4RotationMatrix * rot_C_1_1 = new G4RotationMatrix;
	phi_C_1_1 = (-(360./31.)*jc11); 
	rot_C_1_1->rotateZ(phi_C_1_1*deg);
    	rot_C_1_1->rotateY(theta_C_1_1);
    
	if((-phi_C_1_1 > 65. && -phi_C_1_1 < 118.) || (-phi_C_1_1 > 245. && -phi_C_1_1 < 295.)){flagC_1_1++; continue;}
	 
	if(jc11 % 2 == 0){ ring_C_1_1 = rotacion(coorx_C_1_1, coory_C_1_1, coorz_C_1_1, -phi_C_1_1);}	
	else{ring_C_1_1 = rotacion(coorx_C_1_1_e, coory_C_1_1_e, coorz_C_1_1_e, -phi_C_1_1);} 
	
	vector_C_1_1 = G4ThreeVector(*(ring_C_1_1), *(ring_C_1_1+1), *(ring_C_1_1+2));
	//G4cout<<flagC_1_1<<"  "<<jc00<<G4endl;

	std::ostringstream nombre_C_1_1;
   	nombre_C_1_1 << "C_1_1_" << jc11-flagC_1_1 ;

	//G4cout<<phi_C_1_1*deg/deg<<"  "<<vector_C_1_1<<G4endl;
	G4cout<<jc11+234-flagC_1_1<<"  "<<theta_C_1_1/deg<<"  "<<-phi_C_1_1*deg/deg<<"  "<<sqrt(coorx_C_1_1*coorx_C_1_1 + coorz_C_1_1*coorz_C_1_1)<<G4endl;
    	physiSensorRing_C_1_1 =
    	 	new G4PVPlacement(rot_C_1_1,
                       		vector_C_1_1,
                       		logicSensorPlane,
                       		nombre_C_1_1.str().data(),
                       		logicWorld,
                       		false,
                       		jc11 + 234 - flagC_1_1);
	}

 //
   // Strips
   
   G4Box * solidSensorStripC11 = 
     new G4Box("SensorStripC11",              
               Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorStripC11 = 
     new G4LogicalVolume(solidSensorStripC11,silicon,"SensorStripC11");
 
   physiSensorStripC_1_1 = 
     new G4PVReplica("SensorStripC11",           //its name
                     logicSensorStripC11,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t2);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), cyan(0.0, 1.0, 1.0) , blue(0.0, 0.0, 1.0), orange(1.0, 1.0, 0.5);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripC11 -> SetVisAttributes(new G4VisAttributes(blue));
 
   return physiSensorRing_C_1_1;
 }


//-------------------------------------------------------------Layer C20

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_C_2_0()
 {
   
	double *ring_C_2_0; 
	int flagC_2_0 = 0;

   G4Box * solidSensor_C_2_0 = new G4Box("SensorC_2_0",
                                   noOfSensorStrips*Lengthx_dssd_t1/2.,Lengthy_dssd_t1/2.,Thickness_dssd_t1/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_C_2_0, // its solid
                                                            silicon,     //its material
                                                            "SensorL_C_2_0");   //its name

   

   for(int jc20=0;jc20<31;jc20++){

	
	G4RotationMatrix * rot_C_2_0 = new G4RotationMatrix;
	phi_C_2_0 = (-(360./31.)*jc20); 
	rot_C_2_0->rotateZ(phi_C_2_0*deg);
    	rot_C_2_0->rotateY(theta_C_2_0);
    
	if((-phi_C_2_0 > 65. && -phi_C_2_0 < 118.) || (-phi_C_2_0 > 245. && -phi_C_2_0 < 295.) ){flagC_2_0++; continue;}
	 
	if(jc20 % 2 == 0){ ring_C_2_0 = rotacion(coorx_C_2_0, coory_C_2_0, coorz_C_2_0, -phi_C_2_0);}	
	else{ring_C_2_0 = rotacion(coorx_C_2_0_e, coory_C_2_0_e, coorz_C_2_0_e, -phi_C_2_0);} 
	
	vector_C_2_0 = G4ThreeVector(*(ring_C_2_0), *(ring_C_2_0+1), *(ring_C_2_0+2));
	//G4cout<<flagC_2_0<<"  "<<jc20<<G4endl;

	std::ostringstream nombre_C_2_0;
   	nombre_C_2_0 << "C_2_0_" << jc20-flagC_2_0 ;

	//G4cout<<phi_C_2_0*deg/deg<<"  "<<vector_C_2_0<<G4endl;
	G4cout<<jc20+256-flagC_2_0<<"  "<<theta_C_2_0/deg<<"  "<<-phi_C_2_0*deg/deg<<"  "<<sqrt(coorx_C_2_0*coorx_C_2_0 + coorz_C_2_0*coorz_C_2_0)<<G4endl;
    	physiSensorRing_C_2_0 =
    	 	new G4PVPlacement(rot_C_2_0,
                       		vector_C_2_0,
                       		logicSensorPlane,
                       		nombre_C_2_0.str().data(),
                       		logicWorld,
                       		false,
                       		jc20 + 256 - flagC_2_0);
	}

 //
   // Strips
   
   G4Box * solidSensorStripC20 = 
     new G4Box("SensorStripC20",              
               Lengthx_dssd_t1/2.,Lengthy_dssd_t1/2.,Thickness_dssd_t1/2.);
 
   G4LogicalVolume * logicSensorStripC20 = 
     new G4LogicalVolume(solidSensorStripC20,silicon,"SensorStripC20");
 
   physiSensorStripC_2_0 = 
     new G4PVReplica("SensorStripC20",           //its name
                     logicSensorStripC20,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t1);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), cyan(0.0, 1.0, 1.0) , blue(0.0, 0.0, 1.0), orange(1.0, 1.0, 0.5);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripC20 -> SetVisAttributes(new G4VisAttributes(blue));
 
   return physiSensorRing_C_2_0;
 }


//-------------------------------------------------------------Layer C21

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_C_2_1()
 {
   
	double *ring_C_2_1; 
	int flagC_2_1 = 0;

   G4Box * solidSensor_C_2_1 = new G4Box("SensorC_2_1",
                                   noOfSensorStrips*Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_C_2_1, // its solid
                                                            silicon,     //its material
                                                            "SensorL_C_2_1");   //its name

   

   for(int jc21=0;jc21<31;jc21++){

	
	G4RotationMatrix * rot_C_2_1 = new G4RotationMatrix;
	phi_C_2_1 = (-(360./31.)*jc21); 
	rot_C_2_1->rotateZ(phi_C_2_1*deg);
    	rot_C_2_1->rotateY(theta_C_2_1);
    
	if((-phi_C_2_1 > 65. && -phi_C_2_1 < 118.) || (-phi_C_2_1 > 245. && -phi_C_2_1 < 295.)){flagC_2_1++; continue;}
	 
	if(jc21 % 2 == 0){ ring_C_2_1 = rotacion(coorx_C_2_1, coory_C_2_1, coorz_C_2_1, -phi_C_2_1);}	
	else{ring_C_2_1 = rotacion(coorx_C_2_1_e, coory_C_2_1_e, coorz_C_2_1_e, -phi_C_2_1);} 
	
	vector_C_2_1 = G4ThreeVector(*(ring_C_2_1), *(ring_C_2_1+1), *(ring_C_2_1+2));
	//G4cout<<flagC_2_1<<"  "<<jc00<<G4endl;

	std::ostringstream nombre_C_2_1;
   	nombre_C_2_1 << "C_2_1_" << jc21-flagC_2_1 ;

	//G4cout<<phi_C_2_1*deg/deg<<"  "<<vector_C_2_1<<G4endl;
	G4cout<<jc21+278-flagC_2_1<<"  "<<theta_C_2_1/deg<<"  "<<-phi_C_2_1*deg/deg<<"  "<<sqrt(coorx_C_2_1*coorx_C_2_1 + coorz_C_2_1*coorz_C_2_1)<<G4endl;
    	physiSensorRing_C_2_1 =
    	 	new G4PVPlacement(rot_C_2_1,
                       		vector_C_2_1,
                       		logicSensorPlane,
                       		nombre_C_2_1.str().data(),
                       		logicWorld,
                       		false,
                       		jc21 + 278 - flagC_2_1);
	}

 //
   // Strips
   
   G4Box * solidSensorStripC21 = 
     new G4Box("SensorStripC21",              
               Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorStripC21 = 
     new G4LogicalVolume(solidSensorStripC21,silicon,"SensorStripC21");
 
   physiSensorStripC_2_1 = 
     new G4PVReplica("SensorStripC21",           //its name
                     logicSensorStripC21,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t2);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), cyan(0.0, 1.0, 1.0) , blue(0.0, 0.0, 1.0), orange(1.0, 1.0, 0.5);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripC21 -> SetVisAttributes(new G4VisAttributes(blue));
 
   return physiSensorRing_C_2_1;
 }


//-------------------------------------------------------------Layer C30

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_C_3_0()
 {
   
	double *ring_C_3_0; 
	int flagC_3_0 = 0;

   G4Box * solidSensor_C_3_0 = new G4Box("SensorC_3_0",
                                   noOfSensorStrips*Lengthx_dssd_t1/2.,Lengthy_dssd_t1/2.,Thickness_dssd_t1/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_C_3_0, // its solid
                                                            silicon,     //its material
                                                            "SensorL_C_3_0");   //its name

   

   for(int jc30=0;jc30<31;jc30++){

	
	G4RotationMatrix * rot_C_3_0 = new G4RotationMatrix;
	phi_C_3_0 = (-(360./31.)*jc30); 
	rot_C_3_0->rotateZ(phi_C_3_0*deg);
    	rot_C_3_0->rotateY(theta_C_3_0);
    
	if((-phi_C_3_0 > 65. && -phi_C_3_0 < 118.) || (-phi_C_3_0 > 245. && -phi_C_3_0 < 295.) ){flagC_3_0++; continue;}
	 
	if(jc30 % 2 == 0){ ring_C_3_0 = rotacion(coorx_C_3_0, coory_C_3_0, coorz_C_3_0, -phi_C_3_0);}	
	else{ring_C_3_0 = rotacion(coorx_C_3_0_e, coory_C_3_0_e, coorz_C_3_0_e, -phi_C_3_0);} 
	
	vector_C_3_0 = G4ThreeVector(*(ring_C_3_0), *(ring_C_3_0+1), *(ring_C_3_0+2));
	//G4cout<<flagC_3_0<<"  "<<jc30<<G4endl;

	std::ostringstream nombre_C_3_0;
   	nombre_C_3_0 << "C_3_0_" << jc30-flagC_3_0 ;

	//G4cout<<phi_C_3_0*deg/deg<<"  "<<vector_C_3_0<<G4endl;
	G4cout<<jc30+300-flagC_3_0<<"  "<<theta_C_3_0/deg<<"  "<<-phi_C_3_0*deg/deg<<"  "<<sqrt(coorx_C_3_0*coorx_C_3_0 + coorz_C_3_0*coorz_C_3_0)<<G4endl;
    	physiSensorRing_C_3_0 =
    	 	new G4PVPlacement(rot_C_3_0,
                       		vector_C_3_0,
                       		logicSensorPlane,
                       		nombre_C_3_0.str().data(),
                       		logicWorld,
                       		false,
                       		jc30 + 300 - flagC_3_0);
	}

 //
   // Strips
   
   G4Box * solidSensorStripC30 = 
     new G4Box("SensorStripC30",              
               Lengthx_dssd_t1/2.,Lengthy_dssd_t1/2.,Thickness_dssd_t1/2.);
 
   G4LogicalVolume * logicSensorStripC30 = 
     new G4LogicalVolume(solidSensorStripC30,silicon,"SensorStripC30");
 
   physiSensorStripC_3_0 = 
     new G4PVReplica("SensorStripC30",           //its name
                     logicSensorStripC30,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t1);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), cyan(0.0, 1.0, 1.0) , blue(0.0, 0.0, 1.0), orange(1.0, 1.0, 0.5);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripC30 -> SetVisAttributes(new G4VisAttributes(blue));
 
   return physiSensorRing_C_3_0;
 }


//-------------------------------------------------------------Layer C31

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_C_3_1()
 {
   
	double *ring_C_3_1; 
	int flagC_3_1 = 0;

   G4Box * solidSensor_C_3_1 = new G4Box("SensorC_3_1",
                                   noOfSensorStrips*Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_C_3_1, // its solid
                                                            silicon,     //its material
                                                            "SensorL_C_3_1");   //its name

   

   for(int jc31=0;jc31<31;jc31++){

	
	G4RotationMatrix * rot_C_3_1 = new G4RotationMatrix;
	phi_C_3_1 = (-(360./31.)*jc31); 
	rot_C_3_1->rotateZ(phi_C_3_1*deg);
    	rot_C_3_1->rotateY(theta_C_3_1);
    
	if((-phi_C_3_1 > 65. && -phi_C_3_1 < 118.) || (-phi_C_3_1 > 245. && -phi_C_3_1 < 295.)){flagC_3_1++; continue;}
	 
	if(jc31 % 2 == 0){ ring_C_3_1 = rotacion(coorx_C_3_1, coory_C_3_1, coorz_C_3_1, -phi_C_3_1);}	
	else{ring_C_3_1 = rotacion(coorx_C_3_1_e, coory_C_3_1_e, coorz_C_3_1_e, -phi_C_3_1);} 
	
	vector_C_3_1 = G4ThreeVector(*(ring_C_3_1), *(ring_C_3_1+1), *(ring_C_3_1+2));
	//G4cout<<flagC_3_1<<"  "<<jc00<<G4endl;

	std::ostringstream nombre_C_3_1;
   	nombre_C_3_1 << "C_3_1_" << jc31-flagC_3_1 ;

	//G4cout<<phi_C_3_1*deg/deg<<"  "<<vector_C_3_1<<G4endl;
	G4cout<<jc31+322-flagC_3_1<<"  "<<theta_C_3_1/deg<<"  "<<-phi_C_3_1*deg/deg<<"  "<<sqrt(coorx_C_3_1*coorx_C_3_1 + coorz_C_3_1*coorz_C_3_1)<<G4endl;
    	physiSensorRing_C_3_1 =
    	 	new G4PVPlacement(rot_C_3_1,
                       		vector_C_3_1,
                       		logicSensorPlane,
                       		nombre_C_3_1.str().data(),
                       		logicWorld,
                       		false,
                       		jc31 + 322 - flagC_3_1);
	}

 //
   // Strips
   
   G4Box * solidSensorStripC31 = 
     new G4Box("SensorStripC31",              
               Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorStripC31 = 
     new G4LogicalVolume(solidSensorStripC31,silicon,"SensorStripC31");
 
   physiSensorStripC_3_1 = 
     new G4PVReplica("SensorStripC31",           //its name
                     logicSensorStripC31,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t2);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), cyan(0.0, 1.0, 1.0) , blue(0.0, 0.0, 1.0), orange(1.0, 1.0, 0.5);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripC31 -> SetVisAttributes(new G4VisAttributes(blue));
 
   return physiSensorRing_C_3_1;
 }



//-------------------------------------------------------------RING B

//-------------------------------------------------------------Layer B00

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_B_0_0()
 {
   
	double *ring_B_0_0; 
	int flagB_0_0 = 0;

   G4Box * solidSensor_B_0_0 = new G4Box("SensorB_0_0",
                                   noOfSensorStrips*Lengthx_dssd_t3/2.,Lengthy_dssd_t3/2.,Thickness_dssd_t3/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_B_0_0, // its solid
                                                            silicon,     //its material
                                                            "SensorL_B_0_0");   //its name

   

   for(int jb00=0;jb00<31;jb00++){

	
	G4RotationMatrix * rot_B_0_0 = new G4RotationMatrix;
	phi_B_0_0 = (-(360./31.)*jb00); 
	rot_B_0_0->rotateZ(phi_B_0_0*deg);
    	rot_B_0_0->rotateY(theta_B_0_0);
    
	if((-phi_B_0_0 > 65. && -phi_B_0_0 < 118.) || (-phi_B_0_0 > 245. && -phi_B_0_0 < 295.) ){flagB_0_0++; continue;}
	 
	if(jb00 % 2 == 0){ ring_B_0_0 = rotacion(coorx_B_0_0, coory_B_0_0, coorz_B_0_0, -phi_B_0_0);}	
	else{ring_B_0_0 = rotacion(coorx_B_0_0_e, coory_B_0_0_e, coorz_B_0_0_e, -phi_B_0_0);} 
	
	vector_B_0_0 = G4ThreeVector(*(ring_B_0_0), *(ring_B_0_0+1), *(ring_B_0_0+2));
	//G4cout<<flagB_0_0<<"  "<<jb00<<G4endl;

	std::ostringstream nombre_B_0_0;
   	nombre_B_0_0 << "B_0_0_" << jb00-flagB_0_0 ;

	//G4cout<<phi_B_0_0*deg/deg<<"  "<<vector_B_0_0<<G4endl;
	G4cout<<jb00+344-flagB_0_0<<"  "<<theta_B_0_0/deg<<"  "<<-phi_B_0_0*deg/deg<<"  "<<sqrt(coorx_B_0_0*coorx_B_0_0 + coorz_B_0_0*coorz_B_0_0)<<G4endl;
    	physiSensorRing_B_0_0 =
    	 	new G4PVPlacement(rot_B_0_0,
                       		vector_B_0_0,
                       		logicSensorPlane,
                       		nombre_B_0_0.str().data(),
                       		logicWorld,
                       		false,
                       		jb00 + 344 - flagB_0_0);
	}

 //
   // Strips
   
   G4Box * solidSensorStripB00 = 
     new G4Box("SensorStripB00",              
               Lengthx_dssd_t3/2.,Lengthy_dssd_t3/2.,Thickness_dssd_t3/2.);
 
   G4LogicalVolume * logicSensorStripB00 = 
     new G4LogicalVolume(solidSensorStripB00,silicon,"SensorStripB00");
 
   physiSensorStripB_0_0 = 
     new G4PVReplica("SensorStripB00",           //its name
                     logicSensorStripB00,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t3);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripB00 -> SetVisAttributes(new G4VisAttributes(green));
 
   return physiSensorRing_B_0_0;
 }


//-------------------------------------------------------------Layer B01

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_B_0_1()
 {
   
	double *ring_B_0_1; 
	int flagB_0_1 = 0;

   G4Box * solidSensor_B_0_1 = new G4Box("SensorB_0_1",
                                   noOfSensorStrips*Lengthx_sili2/2.,Lengthy_sili2/2.,Thickness_sili2/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_B_0_1, // its solid
                                                            silicon,     //its material
                                                            "SensorL_B_0_1");   //its name

   

   for(int jb01=0;jb01<31;jb01++){

	
	G4RotationMatrix * rot_B_0_1 = new G4RotationMatrix;
	phi_B_0_1 = (-(360./31.)*jb01); 
	rot_B_0_1->rotateZ(phi_B_0_1*deg);
    	rot_B_0_1->rotateY(theta_B_0_1);
    
	if((-phi_B_0_1 > 65. && -phi_B_0_1 < 118.) || (-phi_B_0_1 > 245. && -phi_B_0_1 < 295.) ){flagB_0_1++; continue;}
	 
	if(jb01 % 2 == 0){ ring_B_0_1 = rotacion(coorx_B_0_1, coory_B_0_1, coorz_B_0_1, -phi_B_0_1);}	
	else{ring_B_0_1 = rotacion(coorx_B_0_1_e, coory_B_0_1_e, coorz_B_0_1_e, -phi_B_0_1);} 
	
	vector_B_0_1 = G4ThreeVector(*(ring_B_0_1), *(ring_B_0_1+1), *(ring_B_0_1+2));
	//G4cout<<flagB_0_1<<"  "<<jb01<<G4endl;

	std::ostringstream nombre_B_0_1;
   	nombre_B_0_1 << "B_0_1_" << jb01-flagB_0_1 ;

	//G4cout<<phi_B_0_1*deg/deg<<"  "<<vector_B_0_1<<G4endl;
	G4cout<<jb01+366-flagB_0_1<<"  "<<theta_B_0_1/deg<<"  "<<-phi_B_0_1*deg/deg<<"  "<<sqrt(coorx_B_0_1*coorx_B_0_1 + coorz_B_0_1*coorz_B_0_1)<<G4endl;
    	physiSensorRing_B_0_1 =
    	 	new G4PVPlacement(rot_B_0_1,
                       		vector_B_0_1,
                       		logicSensorPlane,
                       		nombre_B_0_1.str().data(),
                       		logicWorld,
                       		false,
                       		jb01 + 366 - flagB_0_1);
	}

 //
   // Strips
   
   G4Box * solidSensorStripB01 = 
     new G4Box("SensorStripB01",              
               Lengthx_sili2/2.,Lengthy_sili2/2.,Thickness_sili2/2.);
 
   G4LogicalVolume * logicSensorStripB01 = 
     new G4LogicalVolume(solidSensorStripB01,silicon,"SensorStripB01");
 
   physiSensorStripB_0_1 = 
     new G4PVReplica("SensorStripB01",           //its name
                     logicSensorStripB01,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_sili2);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripB01 -> SetVisAttributes(new G4VisAttributes(green));
 
   return physiSensorRing_B_0_1;
 }


//-------------------------------------------------------------Layer B02

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_B_0_2()
 {
   
	double *ring_B_0_2; 
	int flagB_0_2 = 0;

   G4Box * solidSensor_B_0_2 = new G4Box("SensorB_0_2",
                                   noOfSensorStrips*Lengthx_sili2/2.,Lengthy_sili2/2.,Thickness_sili2/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_B_0_2, // its solid
                                                            silicon,     //its material
                                                            "SensorL_B_0_2");   //its name

   

   for(int jb02=0;jb02<31;jb02++){

	
	G4RotationMatrix * rot_B_0_2 = new G4RotationMatrix;
	phi_B_0_2 = (-(360./31.)*jb02); 
	rot_B_0_2->rotateZ(phi_B_0_2*deg);
    	rot_B_0_2->rotateY(theta_B_0_2);
    
	if((-phi_B_0_2 > 65. && -phi_B_0_2 < 118.) || (-phi_B_0_2 > 245. && -phi_B_0_2 < 295.) ){flagB_0_2++; continue;}
	 
	if(jb02 % 2 == 0){ ring_B_0_2 = rotacion(coorx_B_0_2, coory_B_0_2, coorz_B_0_2, -phi_B_0_2);}	
	else{ring_B_0_2 = rotacion(coorx_B_0_2_e, coory_B_0_2_e, coorz_B_0_2_e, -phi_B_0_2);} 
	
	vector_B_0_2 = G4ThreeVector(*(ring_B_0_2), *(ring_B_0_2+1), *(ring_B_0_2+2));
	//G4cout<<flagB_0_2<<"  "<<jb02<<G4endl;

	std::ostringstream nombre_B_0_2;
   	nombre_B_0_2 << "B_0_2_" << jb02-flagB_0_2 ;

	//G4cout<<phi_B_0_2*deg/deg<<"  "<<vector_B_0_2<<G4endl;
	G4cout<<jb02+388-flagB_0_2<<"  "<<theta_B_0_2/deg<<"  "<<-phi_B_0_2*deg/deg<<"  "<<sqrt(coorx_B_0_2*coorx_B_0_2 + coorz_B_0_2*coorz_B_0_2)<<G4endl;
    	physiSensorRing_B_0_2 =
    	 	new G4PVPlacement(rot_B_0_2,
                       		vector_B_0_2,
                       		logicSensorPlane,
                       		nombre_B_0_2.str().data(),
                       		logicWorld,
                       		false,
                       		jb02 + 388 - flagB_0_2);
	}

 //
   // Strips
   
   G4Box * solidSensorStripB02 = 
     new G4Box("SensorStripB02",              
               Lengthx_sili2/2.,Lengthy_sili2/2.,Thickness_sili2/2.);
 
   G4LogicalVolume * logicSensorStripB02 = 
     new G4LogicalVolume(solidSensorStripB02,silicon,"SensorStripB02");
 
   physiSensorStripB_0_2 = 
     new G4PVReplica("SensorStripB02",           //its name
                     logicSensorStripB02,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_sili2);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripB02 -> SetVisAttributes(new G4VisAttributes(green));
 
   return physiSensorRing_B_0_2;
 }

//-------------------------------------------------------------Layer B03

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_B_0_3()
 {
   
	double *ring_B_0_3; 
	int flagB_0_3 = 0;

   G4Box * solidSensor_B_0_3 = new G4Box("SensorB_0_3",
                                   noOfSensorStrips*Lengthx_sili2/2.,Lengthy_sili2/2.,Thickness_sili2/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_B_0_3, // its solid
                                                            silicon,     //its material
                                                            "SensorL_B_0_3");   //its name

   

   for(int jb03=0;jb03<31;jb03++){

	
	G4RotationMatrix * rot_B_0_3 = new G4RotationMatrix;
	phi_B_0_3 = (-(360./31.)*jb03); 
	rot_B_0_3->rotateZ(phi_B_0_3*deg);
    	rot_B_0_3->rotateY(theta_B_0_3);
    
	if((-phi_B_0_3 > 65. && -phi_B_0_3 < 118.) || (-phi_B_0_3 > 245. && -phi_B_0_3 < 295.) ){flagB_0_3++; continue;}
	 
	if(jb03 % 2 == 0){ ring_B_0_3 = rotacion(coorx_B_0_3, coory_B_0_3, coorz_B_0_3, -phi_B_0_3);}	
	else{ring_B_0_3 = rotacion(coorx_B_0_3_e, coory_B_0_3_e, coorz_B_0_3_e, -phi_B_0_3);} 
	
	vector_B_0_3 = G4ThreeVector(*(ring_B_0_3), *(ring_B_0_3+1), *(ring_B_0_3+2));
	//G4cout<<flagB_0_3<<"  "<<jb03<<G4endl;

	std::ostringstream nombre_B_0_3;
   	nombre_B_0_3 << "B_0_3_" << jb03-flagB_0_3 ;

	//G4cout<<phi_B_0_3*deg/deg<<"  "<<vector_B_0_3<<G4endl;
	G4cout<<jb03+410-flagB_0_3<<"  "<<theta_B_0_3/deg<<"  "<<-phi_B_0_3*deg/deg<<"  "<<sqrt(coorx_B_0_3*coorx_B_0_3 + coorz_B_0_3*coorz_B_0_3)<<G4endl;
    	physiSensorRing_B_0_3 =
    	 	new G4PVPlacement(rot_B_0_3,
                       		vector_B_0_3,
                       		logicSensorPlane,
                       		nombre_B_0_3.str().data(),
                       		logicWorld,
                       		false,
                       		jb03 + 410 - flagB_0_3);
	}

 //
   // Strips
   
   G4Box * solidSensorStripB03 = 
     new G4Box("SensorStripB03",              
               Lengthx_sili2/2.,Lengthy_sili2/2.,Thickness_sili2/2.);
 
   G4LogicalVolume * logicSensorStripB03 = 
     new G4LogicalVolume(solidSensorStripB03,silicon,"SensorStripB03");
 
   physiSensorStripB_0_3 = 
     new G4PVReplica("SensorStripB03",           //its name
                     logicSensorStripB03,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_sili2);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripB03 -> SetVisAttributes(new G4VisAttributes(green));
 
   return physiSensorRing_B_0_3;
 }


//-------------------------------------------------------------RING A
//-------------------------------------------------------------Layer A00

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_A_0_0()
 {
   
	double *ring_A_0_0; 
	int flagA_0_0 = 0;

   G4Box * solidSensor_A_0_0 = new G4Box("SensorA_0_0",
                                   noOfSensorStrips*Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_A_0_0, // its solid
                                                            silicon,     //its material
                                                            "SensorL_A_0_0");   //its name

   

   for(int ja00=0;ja00<31;ja00++){

	
	G4RotationMatrix * rot_A_0_0 = new G4RotationMatrix;
	phi_A_0_0 = (-(360./31.)*ja00); 
	rot_A_0_0->rotateZ(phi_A_0_0*deg);
    	rot_A_0_0->rotateY(theta_A_0_0);
    
	if((-phi_A_0_0 > 65. && -phi_A_0_0 < 118.) || (-phi_A_0_0 > 245. && -phi_A_0_0 < 295.) ){flagA_0_0++; continue;}
	 
	if(ja00 % 2 == 0){ ring_A_0_0 = rotacion(coorx_A_0_0, coory_A_0_0, coorz_A_0_0, -phi_A_0_0);}	
	else{ring_A_0_0 = rotacion(coorx_A_0_0_e, coory_A_0_0_e, coorz_A_0_0_e, -phi_A_0_0);} 
	
	vector_A_0_0 = G4ThreeVector(*(ring_A_0_0), *(ring_A_0_0+1), *(ring_A_0_0+2));
	//G4cout<<flagA_0_0<<"  "<<ja00<<G4endl;

	std::ostringstream nombre_A_0_0;
   	nombre_A_0_0 << "A_0_0_" << ja00-flagA_0_0 ;

	//G4cout<<phi_A_0_0*deg/deg<<"  "<<vector_A_0_0<<G4endl;
	G4cout<<ja00+432-flagA_0_0<<"  "<<theta_A_0_0/deg<<"  "<<-phi_A_0_0*deg/deg<<"  "<<sqrt(coorx_A_0_0*coorx_A_0_0 + coorz_A_0_0*coorz_A_0_0)<<G4endl;
    	physiSensorRing_A_0_0 =
    	 	new G4PVPlacement(rot_A_0_0,
                       		vector_A_0_0,
                       		logicSensorPlane,
                       		nombre_A_0_0.str().data(),
                       		logicWorld,
                       		false,
                       		ja00 + 432 - flagA_0_0);
	}

 //
   // Strips
   
   G4Box * solidSensorStripA00 = 
     new G4Box("SensorStripA00",              
               Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorStripA00 = 
     new G4LogicalVolume(solidSensorStripA00,silicon,"SensorStripA00");
 
   physiSensorStripA_0_0 = 
     new G4PVReplica("SensorStripA00",           //its name
                     logicSensorStripA00,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t2);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripA00 -> SetVisAttributes(new G4VisAttributes(red));
 
   return physiSensorRing_A_0_0;
 }

//-------------------------------------------------------------Layer A01

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_A_0_1()
 {
   
	double *ring_A_0_1; 
	int flagA_0_1 = 0;

   G4Box * solidSensor_A_0_1 = new G4Box("SensorA_0_1",
                                   noOfSensorStrips*Lengthx_sili/2.,Lengthy_sili/2.,Thickness_sili/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_A_0_1, // its solid
                                                            silicon,     //its material
                                                            "SensorL_A_0_1");   //its name

   

   for(int ja01=0;ja01<31;ja01++){

	
	G4RotationMatrix * rot_A_0_1 = new G4RotationMatrix;
	phi_A_0_1 = (-(360./31.)*ja01); 
	rot_A_0_1->rotateZ(phi_A_0_1*deg);
    	rot_A_0_1->rotateY(theta_A_0_1);
    
	if((-phi_A_0_1 > 65. && -phi_A_0_1 < 118.) || (-phi_A_0_1 > 245. && -phi_A_0_1 < 295.) ){flagA_0_1++; continue;}
	 
	if(ja01 % 2 == 0){ ring_A_0_1 = rotacion(coorx_A_0_1, coory_A_0_1, coorz_A_0_1, -phi_A_0_1);}	
	else{ring_A_0_1 = rotacion(coorx_A_0_1_e, coory_A_0_1_e, coorz_A_0_1_e, -phi_A_0_1);} 
	
	vector_A_0_1 = G4ThreeVector(*(ring_A_0_1), *(ring_A_0_1+1), *(ring_A_0_1+2));
	//G4cout<<flagA_0_1<<"  "<<ja01<<G4endl;

	std::ostringstream nombre_A_0_1;
   	nombre_A_0_1 << "A_0_1_" << ja01-flagA_0_1 ;

	//G4cout<<phi_A_0_1*deg/deg<<"  "<<vector_A_0_1<<G4endl;
	G4cout<<ja01+454-flagA_0_1<<"  "<<theta_A_0_1/deg<<"  "<<-phi_A_0_1*deg/deg<<"  "<<sqrt(coorx_A_0_1*coorx_A_0_1 + coorz_A_0_1*coorz_A_0_1)<<G4endl;
    	physiSensorRing_A_0_1 =
    	 	new G4PVPlacement(rot_A_0_1,
                       		vector_A_0_1,
                       		logicSensorPlane,
                       		nombre_A_0_1.str().data(),
                       		logicWorld,
                       		false,
                       		ja01 + 454 - flagA_0_1);
	}

 //
   // Strips
   
   G4Box * solidSensorStripA01 = 
     new G4Box("SensorStripA01",              
               Lengthx_sili/2.,Lengthy_sili/2.,Thickness_sili/2.);
 
   G4LogicalVolume * logicSensorStripA01 = 
     new G4LogicalVolume(solidSensorStripA01,silicon,"SensorStripA01");
 
   physiSensorStripA_0_1 = 
     new G4PVReplica("SensorStripA01",           //its name
                     logicSensorStripA01,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_sili);
   //                Lengthx_sili);            //witdth of replica
 
  G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(0.70, 0.50, 0.0), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripA01 -> SetVisAttributes(new G4VisAttributes(red));
 
   return physiSensorRing_A_0_1;
 }


//-------------------------------------------------------------RING E
//-------------------------------------------------------------Layer E00

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_E_0_0()
 {
   
	double *ring_E_0_0; 
	int flagE_0_0 = 0;

   G4Box * solidSensor_E_0_0 = new G4Box("SensorE_0_0",
                                   noOfSensorStrips*Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_E_0_0, // its solid
                                                            silicon,     //its material
                                                            "SensorL_E_0_0");   //its name

   

   for(int je00=0;je00<31;je00++){

	
	G4RotationMatrix * rot_E_0_0 = new G4RotationMatrix;
	phi_E_0_0 = (-(360./31.)*je00); 
	rot_E_0_0->rotateZ(phi_E_0_0*deg);
    	rot_E_0_0->rotateY(theta_E_0_0);
    
	if((-phi_E_0_0 > 65. && -phi_E_0_0 < 118.) || (-phi_E_0_0 > 245. && -phi_E_0_0 < 295.) ){flagE_0_0++; continue;}
	 
	if(je00 % 2 == 0){ ring_E_0_0 = rotacion(coorx_E_0_0, coory_E_0_0, coorz_E_0_0, -phi_E_0_0);}	
	else{ring_E_0_0 = rotacion(coorx_E_0_0_e, coory_E_0_0_e, coorz_E_0_0_e, -phi_E_0_0);} 
	
	vector_E_0_0 = G4ThreeVector(*(ring_E_0_0), *(ring_E_0_0+1), *(ring_E_0_0+2));
	//G4cout<<flagE_0_0<<"  "<<je00<<G4endl;

	std::ostringstream nombre_E_0_0;
   	nombre_E_0_0 << "E_0_0_" << je00-flagE_0_0 ;

	//G4cout<<phi_E_0_0*deg/deg<<"  "<<vector_E_0_0<<G4endl;
	G4cout<<je00+476-flagE_0_0<<"  "<<theta_E_0_0/deg<<"  "<<-phi_E_0_0*deg/deg<<"  "<<sqrt(coorx_E_0_0*coorx_E_0_0 + coorz_E_0_0*coorz_E_0_0)<<G4endl;
    	physiSensorRing_E_0_0 =
    	 	new G4PVPlacement(rot_E_0_0,
                       		vector_E_0_0,
                       		logicSensorPlane,
                       		nombre_E_0_0.str().data(),
                       		logicWorld,
                       		false,
                       		je00 + 476 - flagE_0_0);
	}

 //
   // Strips
   
   G4Box * solidSensorStripE00 = 
     new G4Box("SensorStripE00",              
               Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorStripE00 = 
     new G4LogicalVolume(solidSensorStripE00,silicon,"SensorStripE00");
 
   physiSensorStripE_0_0 = 
     new G4PVReplica("SensorStripE00",           //its name
                     logicSensorStripE00,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t2);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripE00 -> SetVisAttributes(new G4VisAttributes(orange));
 
   return physiSensorRing_E_0_0;
 }

//-------------------------------------------------------------Layer E01

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_E_0_1()
 {
   
	double *ring_E_0_1; 
	int flagE_0_1 = 0;

   G4Box * solidSensor_E_0_1 = new G4Box("SensorE_0_1",
                                   noOfSensorStrips*Lengthx_sili/2.,Lengthy_sili/2.,Thickness_sili/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_E_0_1, // its solid
                                                            silicon,     //its material
                                                            "SensorL_E_0_1");   //its name

   

   for(int je01=0;je01<31;je01++){

	
	G4RotationMatrix * rot_E_0_1 = new G4RotationMatrix;
	phi_E_0_1 = (-(360./31.)*je01); 
	rot_E_0_1->rotateZ(phi_E_0_1*deg);
    	rot_E_0_1->rotateY(theta_E_0_1);
    
	if((-phi_E_0_1 > 65. && -phi_E_0_1 < 118.) || (-phi_E_0_1 > 245. && -phi_E_0_1 < 295.) ){flagE_0_1++; continue;}
	 
	if(je01 % 2 == 0){ ring_E_0_1 = rotacion(coorx_E_0_1, coory_E_0_1, coorz_E_0_1, -phi_E_0_1);}	
	else{ring_E_0_1 = rotacion(coorx_E_0_1_e, coory_E_0_1_e, coorz_E_0_1_e, -phi_E_0_1);} 
	
	vector_E_0_1 = G4ThreeVector(*(ring_E_0_1), *(ring_E_0_1+1), *(ring_E_0_1+2));
	//G4cout<<flagE_0_1<<"  "<<je01<<G4endl;

	std::ostringstream nombre_E_0_1;
   	nombre_E_0_1 << "E_0_1_" << je01-flagE_0_1 ;

	//G4cout<<phi_E_0_1*deg/deg<<"  "<<vector_E_0_1<<G4endl;
	G4cout<<je01+498-flagE_0_1<<"  "<<theta_E_0_1/deg<<"  "<<-phi_E_0_1*deg/deg<<"  "<<sqrt(coorx_E_0_1*coorx_E_0_1 + coorz_E_0_1*coorz_E_0_1)<<G4endl;
    	physiSensorRing_E_0_1 =
    	 	new G4PVPlacement(rot_E_0_1,
                       		vector_E_0_1,
                       		logicSensorPlane,
                       		nombre_E_0_1.str().data(),
                       		logicWorld,
                       		false,
                       		je01 + 498 - flagE_0_1);
	}

 //
   // Strips
   
   G4Box * solidSensorStripE01 = 
     new G4Box("SensorStripE01",              
               Lengthx_sili/2.,Lengthy_sili/2.,Thickness_sili/2.);
 
   G4LogicalVolume * logicSensorStripE01 = 
     new G4LogicalVolume(solidSensorStripE01,silicon,"SensorStripE01");
 
   physiSensorStripE_0_1 = 
     new G4PVReplica("SensorStripE01",           //its name
                     logicSensorStripE01,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_sili);
   //                Lengthx_sili);            //witdth of replica
 
  G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(0.70, 0.50, 0.0), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripE01 -> SetVisAttributes(new G4VisAttributes(orange));
 
   return physiSensorRing_E_0_1;
 }


//-------------------------------------------------------------Layer E10

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_E_1_0()
 {
   
	double *ring_E_1_0; 
	int flagE_1_0 = 0;

   G4Box * solidSensor_E_1_0 = new G4Box("SensorE_1_0",
                                   noOfSensorStrips*Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_E_1_0, // its solid
                                                            silicon,     //its material
                                                            "SensorL_E_1_0");   //its name

   

   for(int je10=0;je10<31;je10++){

	
	G4RotationMatrix * rot_E_1_0 = new G4RotationMatrix;
	phi_E_1_0 = (-(360./31.)*je10); 
	rot_E_1_0->rotateZ(phi_E_1_0*deg);
    	rot_E_1_0->rotateY(theta_E_1_0);
    
	if((-phi_E_1_0 > 65. && -phi_E_1_0 < 118.) || (-phi_E_1_0 > 245. && -phi_E_1_0 < 295.) ){flagE_1_0++; continue;}
	 
	if(je10 % 2 == 0){ ring_E_1_0 = rotacion(coorx_E_1_0, coory_E_1_0, coorz_E_1_0, -phi_E_1_0);}	
	else{ring_E_1_0 = rotacion(coorx_E_1_0_e, coory_E_1_0_e, coorz_E_1_0_e, -phi_E_1_0);} 
	
	vector_E_1_0 = G4ThreeVector(*(ring_E_1_0), *(ring_E_1_0+1), *(ring_E_1_0+2));
	//G4cout<<flagE_1_0<<"  "<<je10<<G4endl;

	std::ostringstream nombre_E_1_0;
   	nombre_E_1_0 << "E_1_0_" << je10-flagE_1_0 ;

	//G4cout<<phi_E_1_0*deg/deg<<"  "<<vector_E_1_0<<G4endl;
	G4cout<<je10+520-flagE_1_0<<"  "<<theta_E_1_0/deg<<"  "<<-phi_E_1_0*deg/deg<<"  "<<sqrt(coorx_E_1_0*coorx_E_1_0 + coorz_E_1_0*coorz_E_1_0)<<G4endl;
    	physiSensorRing_E_1_0 =
    	 	new G4PVPlacement(rot_E_1_0,
                       		vector_E_1_0,
                       		logicSensorPlane,
                       		nombre_E_1_0.str().data(),
                       		logicWorld,
                       		false,
                       		je10 + 520 - flagE_1_0);
	}

 //
   // Strips
   
   G4Box * solidSensorStripE10 = 
     new G4Box("SensorStripE10",              
               Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorStripE10 = 
     new G4LogicalVolume(solidSensorStripE10,silicon,"SensorStripE10");
 
   physiSensorStripE_1_0 = 
     new G4PVReplica("SensorStripE10",           //its name
                     logicSensorStripE10,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t2);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripE10 -> SetVisAttributes(new G4VisAttributes(orange));
 
   return physiSensorRing_E_1_0;
 }

//-------------------------------------------------------------Layer E11

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_E_1_1()
 {
   
	double *ring_E_1_1; 
	int flagE_1_1 = 0;

   G4Box * solidSensor_E_1_1 = new G4Box("SensorE_1_1",
                                   noOfSensorStrips*Lengthx_sili/2.,Lengthy_sili/2.,Thickness_sili/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_E_1_1, // its solid
                                                            silicon,     //its material
                                                            "SensorL_E_1_1");   //its name

   

   for(int je11=0;je11<31;je11++){

	
	G4RotationMatrix * rot_E_1_1 = new G4RotationMatrix;
	phi_E_1_1 = (-(360./31.)*je11); 
	rot_E_1_1->rotateZ(phi_E_1_1*deg);
    	rot_E_1_1->rotateY(theta_E_1_1);
    
	if((-phi_E_1_1 > 65. && -phi_E_1_1 < 118.) || (-phi_E_1_1 > 245. && -phi_E_1_1 < 295.) ){flagE_1_1++; continue;}
	 
	if(je11 % 2 == 0){ ring_E_1_1 = rotacion(coorx_E_1_1, coory_E_1_1, coorz_E_1_1, -phi_E_1_1);}	
	else{ring_E_1_1 = rotacion(coorx_E_1_1_e, coory_E_1_1_e, coorz_E_1_1_e, -phi_E_1_1);} 
	
	vector_E_1_1 = G4ThreeVector(*(ring_E_1_1), *(ring_E_1_1+1), *(ring_E_1_1+2));
	//G4cout<<flagE_1_1<<"  "<<je11<<G4endl;

	std::ostringstream nombre_E_1_1;
   	nombre_E_1_1 << "E_1_1_" << je11-flagE_1_1 ;

	//G4cout<<phi_E_1_1*deg/deg<<"  "<<vector_E_1_1<<G4endl;
	G4cout<<je11+542-flagE_1_1<<"  "<<theta_E_1_1/deg<<"  "<<-phi_E_1_1*deg/deg<<"  "<<sqrt(coorx_E_1_1*coorx_E_1_1 + coorz_E_1_1*coorz_E_1_1)<<G4endl;
    	physiSensorRing_E_1_1 =
    	 	new G4PVPlacement(rot_E_1_1,
                       		vector_E_1_1,
                       		logicSensorPlane,
                       		nombre_E_1_1.str().data(),
                       		logicWorld,
                       		false,
                       		je11 + 542 - flagE_1_1);
	}

 //
   // Strips
   
   G4Box * solidSensorStripE11 = 
     new G4Box("SensorStripE11",              
               Lengthx_sili/2.,Lengthy_sili/2.,Thickness_sili/2.);
 
   G4LogicalVolume * logicSensorStripE11 = 
     new G4LogicalVolume(solidSensorStripE11,silicon,"SensorStripE11");
 
   physiSensorStripE_1_1 = 
     new G4PVReplica("SensorStripE11",           //its name
                     logicSensorStripE11,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_sili);
   //                Lengthx_sili);            //witdth of replica
 
  G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(0.70, 0.50, 0.0), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripE11 -> SetVisAttributes(new G4VisAttributes(orange));
 
   return physiSensorRing_E_1_1;
 }


//-------------------------------------------------------------Layer E20

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_E_2_0()
 {
   
	double *ring_E_2_0; 
	int flagE_2_0 = 0;

   G4Box * solidSensor_E_2_0 = new G4Box("SensorE_2_0",
                                   noOfSensorStrips*Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_E_2_0, // its solid
                                                            silicon,     //its material
                                                            "SensorL_E_2_0");   //its name

   

   for(int je20=0;je20<31;je20++){

	
	G4RotationMatrix * rot_E_2_0 = new G4RotationMatrix;
	phi_E_2_0 = (-(360./31.)*je20); 
	rot_E_2_0->rotateZ(phi_E_2_0*deg);
    	rot_E_2_0->rotateY(theta_E_2_0);
    
	if((-phi_E_2_0 > 65. && -phi_E_2_0 < 118.) || (-phi_E_2_0 > 245. && -phi_E_2_0 < 295.) ){flagE_2_0++; continue;}
	 
	if(je20 % 2 == 0){ ring_E_2_0 = rotacion(coorx_E_2_0, coory_E_2_0, coorz_E_2_0, -phi_E_2_0);}	
	else{ring_E_2_0 = rotacion(coorx_E_2_0_e, coory_E_2_0_e, coorz_E_2_0_e, -phi_E_2_0);} 
	
	vector_E_2_0 = G4ThreeVector(*(ring_E_2_0), *(ring_E_2_0+1), *(ring_E_2_0+2));
	//G4cout<<flagE_2_0<<"  "<<je20<<G4endl;

	std::ostringstream nombre_E_2_0;
   	nombre_E_2_0 << "E_2_0_" << je20-flagE_2_0 ;

	//G4cout<<phi_E_2_0*deg/deg<<"  "<<vector_E_2_0<<G4endl;
	G4cout<<je20+546-flagE_2_0<<"  "<<theta_E_2_0/deg<<"  "<<-phi_E_2_0*deg/deg<<"  "<<sqrt(coorx_E_2_0*coorx_E_2_0 + coorz_E_2_0*coorz_E_2_0)<<G4endl;
    	physiSensorRing_E_2_0 =
    	 	new G4PVPlacement(rot_E_2_0,
                       		vector_E_2_0,
                       		logicSensorPlane,
                       		nombre_E_2_0.str().data(),
                       		logicWorld,
                       		false,
                       		je20 + 564 - flagE_2_0);
	}

 //
   // Strips
   
   G4Box * solidSensorStripE20 = 
     new G4Box("SensorStripE20",              
               Lengthx_dssd_t2/2.,Lengthy_dssd_t2/2.,Thickness_dssd_t2/2.);
 
   G4LogicalVolume * logicSensorStripE20 = 
     new G4LogicalVolume(solidSensorStripE20,silicon,"SensorStripE20");
 
   physiSensorStripE_2_0 = 
     new G4PVReplica("SensorStripE20",           //its name
                     logicSensorStripE20,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t2);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripE20 -> SetVisAttributes(new G4VisAttributes(orange));
 
   return physiSensorRing_E_2_0;
 }

//-------------------------------------------------------------Layer E21

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_E_2_1()
 {
   
	double *ring_E_2_1; 
	int flagE_2_1 = 0;

   G4Box * solidSensor_E_2_1 = new G4Box("SensorE_2_1",
                                   noOfSensorStrips*Lengthx_sili/2.,Lengthy_sili/2.,Thickness_sili/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_E_2_1, // its solid
                                                            silicon,     //its material
                                                            "SensorL_E_2_1");   //its name

   

   for(int je21=0;je21<31;je21++){

	
	G4RotationMatrix * rot_E_2_1 = new G4RotationMatrix;
	phi_E_2_1 = (-(360./31.)*je21); 
	rot_E_2_1->rotateZ(phi_E_2_1*deg);
    	rot_E_2_1->rotateY(theta_E_2_1);
    
	if((-phi_E_2_1 > 65. && -phi_E_2_1 < 118.) || (-phi_E_2_1 > 245. && -phi_E_2_1 < 295.) ){flagE_2_1++; continue;}
	 
	if(je21 % 2 == 0){ ring_E_2_1 = rotacion(coorx_E_2_1, coory_E_2_1, coorz_E_2_1, -phi_E_2_1);}	
	else{ring_E_2_1 = rotacion(coorx_E_2_1_e, coory_E_2_1_e, coorz_E_2_1_e, -phi_E_2_1);} 
	
	vector_E_2_1 = G4ThreeVector(*(ring_E_2_1), *(ring_E_2_1+1), *(ring_E_2_1+2));
	//G4cout<<flagE_2_1<<"  "<<je21<<G4endl;

	std::ostringstream nombre_E_2_1;
   	nombre_E_2_1 << "E_2_1_" << je21-flagE_2_1 ;

	//G4cout<<phi_E_2_1*deg/deg<<"  "<<vector_E_2_1<<G4endl;
	G4cout<<je21+586-flagE_2_1<<"  "<<theta_E_2_1/deg<<"  "<<-phi_E_2_1*deg/deg<<"  "<<sqrt(coorx_E_2_1*coorx_E_2_1 + coorz_E_2_1*coorz_E_2_1)<<G4endl;
    	physiSensorRing_E_2_1 =
    	 	new G4PVPlacement(rot_E_2_1,
                       		vector_E_2_1,
                       		logicSensorPlane,
                       		nombre_E_2_1.str().data(),
                       		logicWorld,
                       		false,
                       		je21 + 586 - flagE_2_1);
	}

 //
   // Strips
   
   G4Box * solidSensorStripE21 = 
     new G4Box("SensorStripE21",              
               Lengthx_sili/2.,Lengthy_sili/2.,Thickness_sili/2.);
 
   G4LogicalVolume * logicSensorStripE21 = 
     new G4LogicalVolume(solidSensorStripE21,silicon,"SensorStripE21");
 
   physiSensorStripE_2_1 = 
     new G4PVReplica("SensorStripE21",           //its name
                     logicSensorStripE21,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_sili);
   //                Lengthx_sili);            //witdth of replica
 
  G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(0.70, 0.50, 0.0), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripE21 -> SetVisAttributes(new G4VisAttributes(orange));
 
   return physiSensorRing_E_2_1;
 }


//-------------------------------------------------------------RING F
//-------------------------------------------------------------Layer F00

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_F_0_0()
 {
   
	double *ring_F_0_0; 

   G4Box * solidSensor_F_0_0 = new G4Box("SensorF_0_0",
                                   noOfSensorStrips*Lengthx_dssd_t4/2.,Lengthy_dssd_t4/2.,Thickness_dssd_t4/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_F_0_0, // its solid
                                                            silicon,     //its material
                                                            "SensorL_F_0_0");   //its name

   

   for(int jf00=0;jf00<17;jf00++){

	G4RotationMatrix * rot_F_0_0 = new G4RotationMatrix;
	phi_F_0_0 = (-(360./17.)*jf00); 
	rot_F_0_0->rotateZ(phi_F_0_0*deg);
    	rot_F_0_0->rotateY(theta_F_0_0);
    
	 
	if(jf00 % 2 == 0){ ring_F_0_0 = rotacion(coorx_F_0_0, coory_F_0_0, coorz_F_0_0, -phi_F_0_0);}	
	else{ring_F_0_0 = rotacion(coorx_F_0_0_e, coory_F_0_0_e, coorz_F_0_0_e, -phi_F_0_0);} 
	
	vector_F_0_0 = G4ThreeVector(*(ring_F_0_0), *(ring_F_0_0+1), *(ring_F_0_0+2));


	std::ostringstream nombre_F_0_0;
   	nombre_F_0_0 << "F_0_0_" << jf00 ;

	//G4cout<<phi_F_0_0*deg/deg<<"  "<<vector_F_0_0<<G4endl;
	G4cout<<jf00+608<<"  "<<theta_F_0_0/deg<<"  "<<-phi_F_0_0*deg/deg<<"  "<<sqrt(coorx_F_0_0*coorx_F_0_0 + coorz_F_0_0*coorz_F_0_0)<<G4endl;
    	physiSensorRing_F_0_0 =
    	 	new G4PVPlacement(rot_F_0_0,
                       		vector_F_0_0,
                       		logicSensorPlane,
                       		nombre_F_0_0.str().data(),
                       		logicWorld,
                       		false,
                       		jf00 + 608);
	}

 //
   // Strips
   
   G4Box * solidSensorStripF00 = 
     new G4Box("SensorStripF00",              
               Lengthx_dssd_t4/2.,Lengthy_dssd_t4/2.,Thickness_dssd_t4/2.);
 
   G4LogicalVolume * logicSensorStripF00 = 
     new G4LogicalVolume(solidSensorStripF00,silicon,"SensorStripF00");
 
   physiSensorStripF_0_0 = 
     new G4PVReplica("SensorStripF00",           //its name
                     logicSensorStripF00,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t4);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripF00 -> SetVisAttributes(new G4VisAttributes(orange));
 
   return physiSensorRing_F_0_0;
 }



//-------------------------------------------------------------Layer F01

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_F_0_1()
 {
   
	double *ring_F_0_1; 

   G4Box * solidSensor_F_0_1 = new G4Box("SensorF_0_1",
                                   noOfSensorStrips*Lengthx_sili3/2.,Lengthy_sili3/2.,Thickness_sili3/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_F_0_1, // its solid
                                                            silicon,     //its material
                                                            "SensorL_F_0_1");   //its name

   

   for(int jf01=0;jf01<17;jf01++){

	G4RotationMatrix * rot_F_0_1 = new G4RotationMatrix;
	phi_F_0_1 = (-(360./17.)*jf01); 
	rot_F_0_1->rotateZ(phi_F_0_1*deg);
    	rot_F_0_1->rotateY(theta_F_0_1);
    
	 
	if(jf01 % 2 == 0){ ring_F_0_1 = rotacion(coorx_F_0_1, coory_F_0_1, coorz_F_0_1, -phi_F_0_1);}	
	else{ring_F_0_1 = rotacion(coorx_F_0_1_e, coory_F_0_1_e, coorz_F_0_1_e, -phi_F_0_1);} 
	
	vector_F_0_1 = G4ThreeVector(*(ring_F_0_1), *(ring_F_0_1+1), *(ring_F_0_1+2));


	std::ostringstream nombre_F_0_1;
   	nombre_F_0_1 << "F_0_1_" << jf01 ;

	//G4cout<<phi_F_0_1*deg/deg<<"  "<<vector_F_0_1<<G4endl;
	G4cout<<jf01+625<<"  "<<theta_F_0_1/deg<<"  "<<-phi_F_0_1*deg/deg<<"  "<<sqrt(coorx_F_0_1*coorx_F_0_1 + coorz_F_0_1*coorz_F_0_1)<<G4endl;
    	physiSensorRing_F_0_1 =
    	 	new G4PVPlacement(rot_F_0_1,
                       		vector_F_0_1,
                       		logicSensorPlane,
                       		nombre_F_0_1.str().data(),
                       		logicWorld,
                       		false,
                       		jf01 + 625);
	}

 //
   // Strips
   
   G4Box * solidSensorStripF01 = 
     new G4Box("SensorStripF01",              
               Lengthx_sili3/2.,Lengthy_sili3/2.,Thickness_sili3/2.);
 
   G4LogicalVolume * logicSensorStripF01 = 
     new G4LogicalVolume(solidSensorStripF01,silicon,"SensorStripF01");
 
   physiSensorStripF_0_1 = 
     new G4PVReplica("SensorStripF01",           //its name
                     logicSensorStripF01,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_sili3);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripF01 -> SetVisAttributes(new G4VisAttributes(orange));
 
   return physiSensorRing_F_0_1;
 }


//-------------------------------------------------------------Layer F10

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_F_1_0()
 {
   
	double *ring_F_1_0; 

   G4Box * solidSensor_F_1_0 = new G4Box("SensorF_1_0",
                                   noOfSensorStrips*Lengthx_dssd_t4/2.,Lengthy_dssd_t4/2.,Thickness_dssd_t4/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_F_1_0, // its solid
                                                            silicon,     //its material
                                                            "SensorL_F_1_0");   //its name

   

   for(int jf10=0;jf10<17;jf10++){

	G4RotationMatrix * rot_F_1_0 = new G4RotationMatrix;
	phi_F_1_0 = (-(360./17.)*jf10); 
	rot_F_1_0->rotateZ(phi_F_1_0*deg);
    	rot_F_1_0->rotateY(theta_F_1_0);
    
	 
	if(jf10 % 2 == 0){ ring_F_1_0 = rotacion(coorx_F_1_0, coory_F_1_0, coorz_F_1_0, -phi_F_1_0);}	
	else{ring_F_1_0 = rotacion(coorx_F_1_0_e, coory_F_1_0_e, coorz_F_1_0_e, -phi_F_1_0);} 
	
	vector_F_1_0 = G4ThreeVector(*(ring_F_1_0), *(ring_F_1_0+1), *(ring_F_1_0+2));


	std::ostringstream nombre_F_1_0;
   	nombre_F_1_0 << "F_1_0_" << jf10 ;

	//G4cout<<phi_F_1_0*deg/deg<<"  "<<vector_F_1_0<<G4endl;
	G4cout<<jf10+642<<"  "<<theta_F_1_0/deg<<"  "<<-phi_F_1_0*deg/deg<<"  "<<sqrt(coorx_F_1_0*coorx_F_1_0 + coorz_F_1_0*coorz_F_1_0)<<G4endl;
    	physiSensorRing_F_1_0 =
    	 	new G4PVPlacement(rot_F_1_0,
                       		vector_F_1_0,
                       		logicSensorPlane,
                       		nombre_F_1_0.str().data(),
                       		logicWorld,
                       		false,
                       		jf10 + 642);
	}

 //
   // Strips
   
   G4Box * solidSensorStripF10 = 
     new G4Box("SensorStripF10",              
               Lengthx_dssd_t4/2.,Lengthy_dssd_t4/2.,Thickness_dssd_t4/2.);
 
   G4LogicalVolume * logicSensorStripF10 = 
     new G4LogicalVolume(solidSensorStripF10,silicon,"SensorStripF10");
 
   physiSensorStripF_1_0 = 
     new G4PVReplica("SensorStripF10",           //its name
                     logicSensorStripF10,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t4);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripF10 -> SetVisAttributes(new G4VisAttributes(orange));
 
   return physiSensorRing_F_1_0;
 }



//-------------------------------------------------------------Layer F11

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_F_1_1()
 {
   
	double *ring_F_1_1; 

   G4Box * solidSensor_F_1_1 = new G4Box("SensorF_1_1",
                                   noOfSensorStrips*Lengthx_sili3/2.,Lengthy_sili3/2.,Thickness_sili3/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_F_1_1, // its solid
                                                            silicon,     //its material
                                                            "SensorL_F_1_1");   //its name

   

   for(int jf11=0;jf11<17;jf11++){

	G4RotationMatrix * rot_F_1_1 = new G4RotationMatrix;
	phi_F_1_1 = (-(360./17.)*jf11); 
	rot_F_1_1->rotateZ(phi_F_1_1*deg);
    	rot_F_1_1->rotateY(theta_F_1_1);
    
	 
	if(jf11 % 2 == 0){ ring_F_1_1 = rotacion(coorx_F_1_1, coory_F_1_1, coorz_F_1_1, -phi_F_1_1);}	
	else{ring_F_1_1 = rotacion(coorx_F_1_1_e, coory_F_1_1_e, coorz_F_1_1_e, -phi_F_1_1);} 
	
	vector_F_1_1 = G4ThreeVector(*(ring_F_1_1), *(ring_F_1_1+1), *(ring_F_1_1+2));


	std::ostringstream nombre_F_1_1;
   	nombre_F_1_1 << "F_1_1_" << jf11 ;

	//G4cout<<phi_F_1_1*deg/deg<<"  "<<vector_F_1_1<<G4endl;
	G4cout<<jf11+659<<"  "<<theta_F_1_1/deg<<"  "<<-phi_F_1_1*deg/deg<<"  "<<sqrt(coorx_F_1_1*coorx_F_1_1 + coorz_F_1_1*coorz_F_1_1)<<G4endl;
    	physiSensorRing_F_1_1 =
    	 	new G4PVPlacement(rot_F_1_1,
                       		vector_F_1_1,
                       		logicSensorPlane,
                       		nombre_F_1_1.str().data(),
                       		logicWorld,
                       		false,
                       		jf11 + 659);
	}

 //
   // Strips
   
   G4Box * solidSensorStripF11 = 
     new G4Box("SensorStripF11",              
               Lengthx_sili3/2.,Lengthy_sili3/2.,Thickness_sili3/2.);
 
   G4LogicalVolume * logicSensorStripF11 = 
     new G4LogicalVolume(solidSensorStripF11,silicon,"SensorStripF11");
 
   physiSensorStripF_1_1 = 
     new G4PVReplica("SensorStripF11",           //its name
                     logicSensorStripF11,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_sili3);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripF11 -> SetVisAttributes(new G4VisAttributes(orange));
 
   return physiSensorRing_F_1_1;
 }


//-------------------------------------------------------------Layer F20

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_F_2_0()
 {
   
	double *ring_F_2_0; 

   G4Box * solidSensor_F_2_0 = new G4Box("SensorF_2_0",
                                   noOfSensorStrips*Lengthx_dssd_t4/2.,Lengthy_dssd_t4/2.,Thickness_dssd_t4/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_F_2_0, // its solid
                                                            silicon,     //its material
                                                            "SensorL_F_2_0");   //its name

   

   for(int jf20=0;jf20<15;jf20++){

	G4RotationMatrix * rot_F_2_0 = new G4RotationMatrix;
	phi_F_2_0 = (-(360./15.)*jf20); 
	rot_F_2_0->rotateZ(phi_F_2_0*deg);
    	rot_F_2_0->rotateY(theta_F_2_0);
    
	 
	if(jf20 % 2 == 0){ ring_F_2_0 = rotacion(coorx_F_2_0, coory_F_2_0, coorz_F_2_0, -phi_F_2_0);}	
	else{ring_F_2_0 = rotacion(coorx_F_2_0_e, coory_F_2_0_e, coorz_F_2_0_e, -phi_F_2_0);} 
	
	vector_F_2_0 = G4ThreeVector(*(ring_F_2_0), *(ring_F_2_0+1), *(ring_F_2_0+2));


	std::ostringstream nombre_F_2_0;
   	nombre_F_2_0 << "F_2_0_" << jf20 ;

	//G4cout<<phi_F_2_0*deg/deg<<"  "<<vector_F_2_0<<G4endl;
	G4cout<<jf20+676<<"  "<<theta_F_2_0/deg<<"  "<<-phi_F_2_0*deg/deg<<"  "<<sqrt(coorx_F_2_0*coorx_F_2_0 + coorz_F_2_0*coorz_F_2_0)<<G4endl;
    	physiSensorRing_F_2_0 =
    	 	new G4PVPlacement(rot_F_2_0,
                       		vector_F_2_0,
                       		logicSensorPlane,
                       		nombre_F_2_0.str().data(),
                       		logicWorld,
                       		false,
                       		jf20 + 676);
	}

 //
   // Strips
   
   G4Box * solidSensorStripF20 = 
     new G4Box("SensorStripF20",              
               Lengthx_dssd_t4/2.,Lengthy_dssd_t4/2.,Thickness_dssd_t4/2.);
 
   G4LogicalVolume * logicSensorStripF20 = 
     new G4LogicalVolume(solidSensorStripF20,silicon,"SensorStripF20");
 
   physiSensorStripF_2_0 = 
     new G4PVReplica("SensorStripF20",           //its name
                     logicSensorStripF20,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t4);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripF20 -> SetVisAttributes(new G4VisAttributes(orange));
 
   return physiSensorRing_F_2_0;
 }



//-------------------------------------------------------------Layer F21

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_F_2_1()
 {
   
	double *ring_F_2_1; 

   G4Box * solidSensor_F_2_1 = new G4Box("SensorF_2_1",
                                   noOfSensorStrips*Lengthx_sili3/2.,Lengthy_sili3/2.,Thickness_sili3/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_F_2_1, // its solid
                                                            silicon,     //its material
                                                            "SensorL_F_2_1");   //its name

   

   for(int jf21=0;jf21<15;jf21++){

	G4RotationMatrix * rot_F_2_1 = new G4RotationMatrix;
	phi_F_2_1 = (-(360./15.)*jf21); 
	rot_F_2_1->rotateZ(phi_F_2_1*deg);
    	rot_F_2_1->rotateY(theta_F_2_1);
    
	 
	if(jf21 % 2 == 0){ ring_F_2_1 = rotacion(coorx_F_2_1, coory_F_2_1, coorz_F_2_1, -phi_F_2_1);}	
	else{ring_F_2_1 = rotacion(coorx_F_2_1_e, coory_F_2_1_e, coorz_F_2_1_e, -phi_F_2_1);} 
	
	vector_F_2_1 = G4ThreeVector(*(ring_F_2_1), *(ring_F_2_1+1), *(ring_F_2_1+2));


	std::ostringstream nombre_F_2_1;
   	nombre_F_2_1 << "F_2_1_" << jf21 ;

	//G4cout<<phi_F_2_1*deg/deg<<"  "<<vector_F_2_1<<G4endl;
	G4cout<<jf21+691<<"  "<<theta_F_2_1/deg<<"  "<<-phi_F_2_1*deg/deg<<"  "<<sqrt(coorx_F_2_1*coorx_F_2_1 + coorz_F_2_1*coorz_F_2_1)<<G4endl;
    	physiSensorRing_F_2_1 =
    	 	new G4PVPlacement(rot_F_2_1,
                       		vector_F_2_1,
                       		logicSensorPlane,
                       		nombre_F_2_1.str().data(),
                       		logicWorld,
                       		false,
                       		jf21 + 691);
	}

 //
   // Strips
   
   G4Box * solidSensorStripF21 = 
     new G4Box("SensorStripF21",              
               Lengthx_sili3/2.,Lengthy_sili3/2.,Thickness_sili3/2.);
 
   G4LogicalVolume * logicSensorStripF21 = 
     new G4LogicalVolume(solidSensorStripF21,silicon,"SensorStripF21");
 
   physiSensorStripF_2_1 = 
     new G4PVReplica("SensorStripF21",           //its name
                     logicSensorStripF21,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_sili3);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripF21 -> SetVisAttributes(new G4VisAttributes(orange));
 
   return physiSensorRing_F_2_1;
 }


//-------------------------------------------------------------Layer F30

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_F_3_0()
 {
   
	double *ring_F_3_0; 

   G4Box * solidSensor_F_3_0 = new G4Box("SensorF_3_0",
                                   noOfSensorStrips*Lengthx_dssd_t4/2.,Lengthy_dssd_t4/2.,Thickness_dssd_t4/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_F_3_0, // its solid
                                                            silicon,     //its material
                                                            "SensorL_F_3_0");   //its name

   

   for(int jf30=0;jf30<15;jf30++){

	G4RotationMatrix * rot_F_3_0 = new G4RotationMatrix;
	phi_F_3_0 = (-(360./15.)*jf30); 
	rot_F_3_0->rotateZ(phi_F_3_0*deg);
    	rot_F_3_0->rotateY(theta_F_3_0);
    
	 
	if(jf30 % 2 == 0){ ring_F_3_0 = rotacion(coorx_F_3_0, coory_F_3_0, coorz_F_3_0, -phi_F_3_0);}	
	else{ring_F_3_0 = rotacion(coorx_F_3_0_e, coory_F_3_0_e, coorz_F_3_0_e, -phi_F_3_0);} 
	
	vector_F_3_0 = G4ThreeVector(*(ring_F_3_0), *(ring_F_3_0+1), *(ring_F_3_0+2));


	std::ostringstream nombre_F_3_0;
   	nombre_F_3_0 << "F_3_0_" << jf30 ;

	//G4cout<<phi_F_3_0*deg/deg<<"  "<<vector_F_3_0<<G4endl;
	G4cout<<jf30+706<<"  "<<theta_F_3_0/deg<<"  "<<-phi_F_3_0*deg/deg<<"  "<<sqrt(coorx_F_3_0*coorx_F_3_0 + coorz_F_3_0*coorz_F_3_0)<<G4endl;
    	physiSensorRing_F_3_0 =
    	 	new G4PVPlacement(rot_F_3_0,
                       		vector_F_3_0,
                       		logicSensorPlane,
                       		nombre_F_3_0.str().data(),
                       		logicWorld,
                       		false,
                       		jf30 + 706);
	}

 //
   // Strips
   
   G4Box * solidSensorStripF30 = 
     new G4Box("SensorStripF30",              
               Lengthx_dssd_t4/2.,Lengthy_dssd_t4/2.,Thickness_dssd_t4/2.);
 
   G4LogicalVolume * logicSensorStripF30 = 
     new G4LogicalVolume(solidSensorStripF30,silicon,"SensorStripF30");
 
   physiSensorStripF_3_0 = 
     new G4PVReplica("SensorStripF30",           //its name
                     logicSensorStripF30,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_dssd_t4);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripF30 -> SetVisAttributes(new G4VisAttributes(orange));
 
   return physiSensorRing_F_3_0;
 }



//-------------------------------------------------------------Layer F31

 G4VPhysicalVolume* DetectorConstruction::ConstructRing_F_3_1()
 {
   
	double *ring_F_3_1; 

   G4Box * solidSensor_F_3_1 = new G4Box("SensorF_3_1",
                                   noOfSensorStrips*Lengthx_sili3/2.,Lengthy_sili3/2.,Thickness_sili3/2.);
 
   G4LogicalVolume * logicSensorPlane = new G4LogicalVolume(solidSensor_F_3_1, // its solid
                                                            silicon,     //its material
                                                            "SensorL_F_3_1");   //its name

   

   for(int jf31=0;jf31<15;jf31++){

	G4RotationMatrix * rot_F_3_1 = new G4RotationMatrix;
	phi_F_3_1 = (-(360./15.)*jf31); 
	rot_F_3_1->rotateZ(phi_F_3_1*deg);
    	rot_F_3_1->rotateY(theta_F_3_1);
    
	 
	if(jf31 % 2 == 0){ ring_F_3_1 = rotacion(coorx_F_3_1, coory_F_3_1, coorz_F_3_1, -phi_F_3_1);}	
	else{ring_F_3_1 = rotacion(coorx_F_3_1_e, coory_F_3_1_e, coorz_F_3_1_e, -phi_F_3_1);} 
	
	vector_F_3_1 = G4ThreeVector(*(ring_F_3_1), *(ring_F_3_1+1), *(ring_F_3_1+2));


	std::ostringstream nombre_F_3_1;
   	nombre_F_3_1 << "F_3_1_" << jf31 ;

	//G4cout<<phi_F_3_1*deg/deg<<"  "<<vector_F_3_1<<G4endl;
	G4cout<<jf31+721<<"  "<<theta_F_3_1/deg<<"  "<<-phi_F_3_1*deg/deg<<"  "<<sqrt(coorx_F_3_1*coorx_F_3_1 + coorz_F_3_1*coorz_F_3_1)<<G4endl;
    	physiSensorRing_F_3_1 =
    	 	new G4PVPlacement(rot_F_3_1,
                       		vector_F_3_1,
                       		logicSensorPlane,
                       		nombre_F_3_1.str().data(),
                       		logicWorld,
                       		false,
                       		jf31 + 721);
	}

 //
   // Strips
   
   G4Box * solidSensorStripF31 = 
     new G4Box("SensorStripF31",              
               Lengthx_sili3/2.,Lengthy_sili3/2.,Thickness_sili3/2.);
 
   G4LogicalVolume * logicSensorStripF31 = 
     new G4LogicalVolume(solidSensorStripF31,silicon,"SensorStripF31");
 
   physiSensorStripF_3_1 = 
     new G4PVReplica("SensorStripF31",           //its name
                     logicSensorStripF31,           //its logical volume
                     logicSensorPlane,           //its mother
                     kXAxis,                     //axis of replication
                     noOfSensorStrips,           //number of replica
                     Lengthx_sili3);
   //                Lengthx_sili);            //witdth of replica
 
   G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   logicSensorPlane -> SetVisAttributes(new G4VisAttributes(yellow));
   logicSensorStripF31 -> SetVisAttributes(new G4VisAttributes(orange));
 
   return physiSensorRing_F_3_1;
 }




//-------------------------------------------------------------Crystals

 G4VPhysicalVolume* DetectorConstruction::ConstructCrystals()
 {
   
	// --------------------------- Scintillator
//	

  G4double innerRadius = 650.0*mm;
  G4double outerRadius = 850.0*mm;
 
  

  G4VSolid* sphereSolid = new G4Sphere("Sphere_Solid",   // Name
                                         innerRadius,    // Inner radius
                                         outerRadius,    // Outer radius
                                         0.*deg,         // Starting phi
                                         360.0*deg,       // Delta phi
                                         10.*deg,         // Starting theta
                                         120.0*deg);      // Delta theta
 
 


  G4VSolid*  cono1Solid = new G4Cons("cono_arriba",
             		0*mm,
             		0*mm,
             		0*mm,
             		tan(45*3.141592/180.)*850*mm,
             		 425*mm,
             		  0*deg,
             		   360*deg); 

  G4ThreeVector yTrans(0, 425*mm, 0);
  G4RotationMatrix * rota = new G4RotationMatrix;
	rota->rotateX(90*deg);
    	
  G4SubtractionSolid* subtraction1 =
    new G4SubtractionSolid("Esferapartearriba", sphereSolid, cono1Solid, rota, yTrans);

  
  G4ThreeVector yTrans2(0, -425*mm, 0);
  G4RotationMatrix * rota2 = new G4RotationMatrix;
	rota2->rotateX(-90*deg);
    	
  G4SubtractionSolid* subtraction2 =
    new G4SubtractionSolid("Esferaabajo", subtraction1, cono1Solid, rota2, yTrans2);
 
    
     logicCrystal =
    new G4LogicalVolume(subtraction2, CsI, "Sphere_Logical");

 scintillator_phys =
  new G4PVPlacement(0, G4ThreeVector(), logicCrystal, "Sphere_Physical_E",
    	                 logicWorld, false, 0);


    /*
G4LogicalVolume * logicSensorStripCrys =
    new G4LogicalVolume(subtraction2, CsI, "Sphere_Logical_Strip");

   scintillator_phys_strips=
   new G4PVReplica("SensorCrystal",           //its name
                     logicSensorStripCrys,           //its logical volume
                     logicSensorPlane,           //its mother
                     kPhi,                     //axis of replication
                     1,           //number of replica
                     0*deg);
   //                Lengthx_sili);            //witdth of replica

*/
  //G4Color red(1.0,0.0,0.0),yellow(1.0,1.0,0.0), orange(1.0, 1.0, 0.5), blue(0.0, 0.0, 1.0), green(0.0, 1.0, 0.0);
   //logicSensorStripCrys -> SetVisAttributes(new G4VisAttributes(yellow));

   //---------------------------- test sensible

  G4SDManager *sdm = G4SDManager::GetSDMpointer();
  Crystal* sd = dynamic_cast<Crystal*>(sdm->FindSensitiveDetector("CrystalHitsCollection",false));
  if ( !sd ) {
      sd = new Crystal("CrystalHitsCollection");
      sdm->AddNewDetector(sd);
  }
  logicCrystal->SetSensitiveDetector(sd);
      
//--------------------------------

   return scintillator_phys;
 }




 G4double* DetectorConstruction::rotacion(G4double dx , G4double dy, G4double dz, G4double angulo)
{
	static G4double valores[3];
	 valores[0] = dx*cos(angulo*3.141562/180.) - dy*sin(angulo*3.141562/180.);
    	 valores[1] = dx*sin(angulo*3.141562/180.) + dy*cos(angulo*3.141562/180.);
    	 valores[2] = dz;

	return valores;
}
 

 #include "G4RunManager.hh"
 #include "G4PhysicalVolumeStore.hh"
 #include "G4LogicalVolumeStore.hh"
 #include "G4SolidStore.hh"
 
 void DetectorConstruction::UpdateGeometry()
 {
   // Cleanup old geometry
   G4GeometryManager::GetInstance()->OpenGeometry();
   G4PhysicalVolumeStore::GetInstance()->Clean();
   G4LogicalVolumeStore::GetInstance()->Clean();
   G4SolidStore::GetInstance()->Clean();
 
   G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
 
 
 }
