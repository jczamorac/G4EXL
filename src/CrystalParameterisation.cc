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
#include "CrystalParameterisation.hh"
#include "G4Sphere.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"

CrystalParameterisation::CrystalParameterisation(const G4double minRadius, 
							     const G4double maxRadius,
							     const G4double Thetaini,
								const G4double deltaPhi)
  :G4VPVParameterisation()
  ,fMinRadius(minRadius)
  ,fMaxRadius(maxRadius)
  ,fThetaini(Thetaini)
  ,fDeltaPhi(deltaPhi)
{}

CrystalParameterisation::~CrystalParameterisation() {}

void CrystalParameterisation::ComputeDimensions(G4Sphere& sphere, 
						      const G4int copyNo, 
						      const G4VPhysicalVolume*) const
{
  G4double startPhi = copyNo*fDeltaPhi;
  sphere.SetInsideRadius(fMinRadius);
  sphere.SetOuterRadius(fMaxRadius);
  sphere.SetStartPhiAngle(startPhi);
  sphere.SetDeltaPhiAngle(fDeltaPhi);
  sphere.SetStartThetaAngle(fThetaini);
  sphere.SetDeltaThetaAngle(8.79*deg);
}





