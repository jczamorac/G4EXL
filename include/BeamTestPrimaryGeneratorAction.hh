//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
// $Id:$
// GEANT4 tag $Name:$
// 
// T. Aso        Original author
// 
#ifndef BEAMTESTPRIMARYGENERATORACTION_HH
#define BEAMTESTPRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "TwoBodyKin.hh"
//#include "ThreeBodyKin.hh"

using std::vector;

class G4ParticleGun;
class G4Event;
//class SeccionEff;
class BeamTestPrimaryGeneratorMessenger;

class BeamTestPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {


public:

  // Constructor
  BeamTestPrimaryGeneratorAction();    

  // Destructor
  virtual ~BeamTestPrimaryGeneratorAction();
  
  // Methods

  //static void Set_theta(G4double* THETA) {theta_cross = THETA;}
  //inline G4double* Get_theta() {return theta_cross;}

  void GeneratePrimaries(G4Event*);
  
  static G4ParticleGun* Gun() {return particleGun;}

   void SetZ_target(G4double val) { Z_target = val;}


   TwoBodyKin* cinem;
   
  
private:

  // Data member
  static G4ParticleGun* particleGun;
  BeamTestPrimaryGeneratorMessenger* gunMessenger; //messenger of this class
  G4double Z_target;
  
  

};

#endif


