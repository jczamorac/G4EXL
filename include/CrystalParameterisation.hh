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
#ifndef CrystalParameterisation_HH
#define CrystalParameterisation_HH

#include "G4VPVParameterisation.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include <vector>

class G4Box;
class G4Cons;
class G4Hype;
class G4LogicalVolume;
class G4Orb;
class G4Para;
class G4Polycone;
class G4Polyhedra; 
class G4Sphere;
class G4Trap;
class G4Trd;
class G4Tubs;
class G4Torus;

class CrystalParameterisation : public G4VPVParameterisation {

public:
  
  // Constructor
  CrystalParameterisation(const G4double minRadius, const G4double maxRadius, 
				const G4double Thetaini, const G4double deltaPhi);
  
  // Destructor
  virtual ~CrystalParameterisation();
  
  // Method
  virtual void ComputeDimensions(G4Sphere& sphere, 
				 const G4int copyNo, 
				 const G4VPhysicalVolume*) const;  

  
private:

  // Override to get rid of warning messages
  void ComputeTransformation(const G4int, G4VPhysicalVolume*)const  {};
  void ComputeDimensions (G4Tubs&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Trd&,const G4int,const G4VPhysicalVolume*)  const {}
  void ComputeDimensions (G4Trap&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Cons&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Orb&,const G4int,const G4VPhysicalVolume*)  const {}
  void ComputeDimensions (G4Torus&,const G4int,const G4VPhysicalVolume*)const {}
  void ComputeDimensions (G4Para&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Hype&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Box&,const G4int,const G4VPhysicalVolume*)  const {}
  void ComputeDimensions (G4Polycone&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Polyhedra&,const G4int,const G4VPhysicalVolume*) const {}

private:
  
  // Data members
  G4double fMinRadius;  // Inner radius of scoring sphere.
  G4double fMaxRadius;  // Outer radius of scoring sphere.
  G4double fThetaini; 
  G4double fDeltaPhi; // Delta theta angle

};

#endif
