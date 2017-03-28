 // $Id: DetectorMessenger.hh 33 2010-01-14 17:08:18Z adotti $
 
 #ifndef DetectorMessenger_h
 #define DetectorMessenger_h 1
 
 /**
  * @file
  * @brief defines class DetectorMessenger
  */
 
 //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
 #include "globals.hh"
 #include "G4UImessenger.hh"
 
 class DetectorConstruction;
 class G4UIdirectory;
 class G4UIcmdWithAString;
 class G4UIcmdWithADoubleAndUnit;
 class G4UIcmdWith3VectorAndUnit;
 class G4UIcmdWithoutParameter;
 class G4UIcmdWithABool;
 
 //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
 /*!
 \brief This class provides the user interface to DetectorConstruction
 
 It allows for
  - change of detector position
  - rotation of the DUT around the y-axis
 
 \sa SetNewValue()
 */
 class DetectorMessenger: public G4UImessenger
 {
 public:
   //! Constructor
   DetectorMessenger(DetectorConstruction* );
   //! Destructor
   ~DetectorMessenger();
     
   //! handle user commands
   void SetNewValue(G4UIcommand*, G4String);
     
 private:
   
   DetectorConstruction*      detector;
     
   G4UIdirectory*             detDir;
   G4UIdirectory*             secondSensorDir;
         
   G4UIcmdWithADoubleAndUnit* xShiftCmd;    
   G4UIcmdWithADoubleAndUnit* yShiftCmd;    
   G4UIcmdWithADoubleAndUnit* thetaCmd;
	
   G4UIcmdWithADoubleAndUnit* z_slitCmd;
   G4UIcmdWithADoubleAndUnit* x_slitCmd;	     	 
   G4UIcmdWithADoubleAndUnit* xShiftPocketCmd;	     	         
 
   G4UIcmdWithoutParameter*   updateCmd;    
 
   G4UIcmdWithABool*                      setDUTsetupCmd;
 };
  
 //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
 #endif
 
