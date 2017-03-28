 // $Id: DetectorMessenger.cc 94 2010-01-26 13:18:30Z adotti $
 /**
  * @file
  * @brief Implements class DetectorMessenger.
  */
 
 #include "DetectorMessenger.hh"
 #include "DetectorConstruction.hh"
 
 #include "G4UIdirectory.hh"
 #include "G4UIcmdWithAString.hh"
 #include "G4UIcmdWithADoubleAndUnit.hh"
 #include "G4UIcmdWithoutParameter.hh"
 #include "G4UIcmdWithABool.hh"
 
 DetectorMessenger::DetectorMessenger(DetectorConstruction * det)
 :detector(det)
 { 
   detDir = new G4UIdirectory("/det/");
   detDir->SetGuidance("detector construction commands");
 
   secondSensorDir = new G4UIdirectory("/det/secondSensor/");
   secondSensorDir->SetGuidance("comands related to the second sensor plane");
 
 
   xShiftCmd = new G4UIcmdWithADoubleAndUnit("/det/secondSensor/xShift",this);
   xShiftCmd->SetGuidance("Define x-shift of second sensor plane");
   xShiftCmd->SetParameterName("xShift",true);
   xShiftCmd->SetDefaultValue(0.);
   xShiftCmd->SetUnitCategory("Length");
   xShiftCmd->SetDefaultUnit("um");
 
   yShiftCmd = new G4UIcmdWithADoubleAndUnit("/det/secondSensor/yShift",this);
   yShiftCmd->SetGuidance("Define y-shift of second sensor plane");
   yShiftCmd->SetParameterName("yShift",true);
   yShiftCmd->SetDefaultValue(0.);
   yShiftCmd->SetUnitCategory("Length");
   yShiftCmd->SetDefaultUnit("um");
 
   thetaCmd = new G4UIcmdWithADoubleAndUnit ("/det/secondSensor/theta", this);
   thetaCmd->SetGuidance("Select rotation angle of second sensor plane around y axis");
   thetaCmd->SetParameterName("thetaDUT",true);
   thetaCmd->SetUnitCategory("Angle");
   thetaCmd->SetDefaultUnit("deg");

   z_slitCmd = new G4UIcmdWithADoubleAndUnit("/det/slit/z",this);
   z_slitCmd->SetGuidance("Define z pos of slit");
   z_slitCmd->SetParameterName("z_slit",true);
   z_slitCmd->SetDefaultValue(30.);
   z_slitCmd->SetUnitCategory("Length");
   z_slitCmd->SetDefaultUnit("mm");

   x_slitCmd = new G4UIcmdWithADoubleAndUnit("/det/slit/x",this);
   x_slitCmd->SetGuidance("Define x pos of slit");
   x_slitCmd->SetParameterName("x_slit",true);
   x_slitCmd->SetDefaultValue(0.);
   x_slitCmd->SetUnitCategory("Length");
   x_slitCmd->SetDefaultUnit("mm");

   xShiftPocketCmd = new G4UIcmdWithADoubleAndUnit("/det/pocket/xShiftPocket",this);
   xShiftPocketCmd->SetGuidance("Define x-shift of firtst pocket");
   xShiftPocketCmd->SetParameterName("xShiftPocket",true);
   xShiftPocketCmd->SetDefaultValue(0.);
   xShiftPocketCmd->SetUnitCategory("Length");
   xShiftPocketCmd->SetDefaultUnit("mm");
 
   setDUTsetupCmd = new G4UIcmdWithABool("/det/secondSensor/DUTsetup",this);
   setDUTsetupCmd->SetGuidance("Select setup. true to have DUT (Device Under Test) setup: second Si plane replaced by DUT");
   setDUTsetupCmd->AvailableForStates(G4State_Idle);
 
   updateCmd = new G4UIcmdWithoutParameter("/det/update",this);
   updateCmd->SetGuidance("force to recompute geometry.");
   updateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
   updateCmd->SetGuidance("if you changed geometrical value(s).");
   updateCmd->AvailableForStates(G4State_Idle);
 
 }
 
 DetectorMessenger::~DetectorMessenger()
 {
   delete xShiftCmd;
   delete yShiftCmd;
   delete thetaCmd;
   delete x_slitCmd;
   delete z_slitCmd;
   delete xShiftPocketCmd;

   delete setDUTsetupCmd;
 
   delete secondSensorDir;
 
   delete updateCmd;
 
   delete detDir;  
 }
 
 void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
 {
   if ( command == xShiftCmd ) {
     G4ThreeVector pos= detector->SecondSensorPosition();
     pos.setX( xShiftCmd->GetNewDoubleValue(newValue) );
     detector->SetSecondSensorPosition(pos);
   }
 
   if ( command == yShiftCmd ) {
     G4ThreeVector pos= detector->SecondSensorPosition();
     pos.setY( yShiftCmd->GetNewDoubleValue(newValue) );
     detector->SetSecondSensorPosition(pos);
   }
 
   if ( command == thetaCmd )
     detector->SetDUTangle(thetaCmd->GetNewDoubleValue(newValue));

   if ( command == z_slitCmd )
     detector->SetSlit_z(z_slitCmd->GetNewDoubleValue(newValue));

   if ( command == x_slitCmd )
     detector->SetSlit_x(x_slitCmd->GetNewDoubleValue(newValue));

    if ( command == xShiftPocketCmd )
     detector->SetPocket1_x(xShiftPocketCmd->GetNewDoubleValue(newValue));
               
   if ( command == updateCmd )
     detector->UpdateGeometry();
 
   if ( command == setDUTsetupCmd )
         detector->SetDUTSetup( setDUTsetupCmd->GetNewBoolValue(newValue) );
 }
 
