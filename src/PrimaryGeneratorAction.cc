 // $Id: PrimaryGeneratorAction.cc 94 2010-01-26 13:18:30Z adotti $
 /**
  * @file
  * @brief implements mandatory user class PrimaryGeneratorAction
  */
 
 #include "PrimaryGeneratorAction.hh"
 #include "PrimaryGeneratorAction.hh"
 
 #include "G4Event.hh"
 #include "G4ParticleGun.hh"
 #include "G4GeneralParticleSource.hh"
 #include "G4ParticleTable.hh"
 #include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh" 
 
 PrimaryGeneratorAction::PrimaryGeneratorAction()
   : outfile(0)
 {
   gun = InitializeGPS();
   
 }
 
 void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
 { 
   gun->GeneratePrimaryVertex(anEvent);
 }
 
 PrimaryGeneratorAction::~PrimaryGeneratorAction()
 {
   delete gun;
 }
 
 G4VPrimaryGenerator* PrimaryGeneratorAction::InitializeGPS()
 {
   G4GeneralParticleSource * gps = new G4GeneralParticleSource();
   
   // setup details easier via UI commands see gps.mac
 
   // particle type
   G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
   G4ParticleDefinition* pion = particleTable->FindParticle("proton");  
   gps->GetCurrentSource()->SetParticleDefinition(pion);
 
   // set energy distribution
   G4SPSEneDistribution *eneDist = gps->GetCurrentSource()->GetEneDist() ;
   eneDist->SetEnergyDisType("Mono"); // or gauss
   eneDist->SetMonoEnergy(200.0*MeV);
 
   // set position distribution
   G4SPSPosDistribution *posDist = gps->GetCurrentSource()->GetPosDist();
   posDist->SetPosDisType("Point");  // or Point,Plane,Volume,Beam
   posDist->SetCentreCoords(G4ThreeVector(0.0*mm,0.0*mm,0.0*mm));
   //posDist->SetBeamSigmaInX(0.1*mm);
   //posDist->SetBeamSigmaInY(0.1*mm);
 
   // set angular distribution
   G4SPSAngDistribution *angDist = gps->GetCurrentSource()->GetAngDist();
   angDist->SetParticleMomentumDirection( G4ThreeVector(-1., 0., 0.) );
   //angDist->SetAngDistType("beam2d");
   //angDist->SetBeamSigmaInAngX(0.1*mrad);
   //angDist->SetBeamSigmaInAngY(0.1*mrad);
   //angDist->DefineAngRefAxes("angref1",G4ThreeVector(-1.,0.,0.));
 
   return gps;
 }
 
