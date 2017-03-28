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
#include "BeamTestPrimaryGeneratorAction.hh"
#include "BeamTestPrimaryGeneratorMessenger.hh"


#include "G4Event.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"


#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include <stdlib.h> 

#include "TMath.h"
 


G4ParticleGun* BeamTestPrimaryGeneratorAction::particleGun(0);

//SeccionEff* BeamTestPrimaryGeneratorAction::apuntador(0);

BeamTestPrimaryGeneratorAction::BeamTestPrimaryGeneratorAction()
{
  G4int n_particle = 1;
  particleGun  = new G4ParticleGun(n_particle);

  gunMessenger = new BeamTestPrimaryGeneratorMessenger(this);
  
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="proton");
  
  particleGun->SetParticleDefinition(particle);

 particleGun->SetParticleMomentumDirection(G4ThreeVector(-1.,0.,0.));
 //G4cout<<"angulo aleatotio  "<<angle<<G4endl;
  particleGun->SetParticleEnergy(63.0*MeV);	
   
  
  
  particleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.*cm));


  cinem = new TwoBodyKin();
  

}


BeamTestPrimaryGeneratorAction::~BeamTestPrimaryGeneratorAction()
{
  delete particleGun;
  delete gunMessenger;
}



void BeamTestPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

	
//----------------------------------generador con densidad constante, cilindo vs gaussiana


 G4double x, y, z;
 G4double sigma_beam, radio_target;
 G4double x0, y0, z0;
 //G4double radio, sinomega;

  //seed();
 	
	x=0.*mm;
	y=0.*mm;
	z=0.*mm;
	sigma_beam = 1.5*mm/2.35;  //alta intensidad 3mm-sigma
	radio_target = 2.00*mm;  //ojo, para el actual en el esr es 3.45 mm
	y0 = 0.*mm;
	z0 = Z_target;
	x0 = 0.58*mm; //0.58 desfase del jet
	

	do{
		//radio = radio_target*(2.*G4UniformRand() -1.);
		//sinomega = 2.*G4UniformRand() - 1.0;
		x = G4RandGauss::shoot(x0,sigma_beam);
		y = G4RandGauss::shoot(y0,sigma_beam);
		z = radio_target*(2.*G4UniformRand() -1.) + z0;
			

	if( fabs(x) < 3*(fabs(x0)+sigma_beam) && fabs(y) < 3*(fabs(y0)+sigma_beam) && fabs(z) < (fabs(z0)+radio_target)){break;}
	}
	while(1==1);
	
	//x =0.;
	//y =0.;
	//z =0.;
	particleGun->SetParticlePosition(G4ThreeVector(x,y,z));



//--------------------------------------------------------------------------------------------

			
	
	//all masses in units of aum=931.494
	//m1(beam), m2(target), m3(recoil), m4(ejectile), Kbeam(in MeV/u)
  	cinem->SetTwoBodyMass(55.942128580, 1.00782503223, 1.00782503223, 55.942128580, 400.);
			//Thcm(deg), Ex4[MeV]
	cinem->SetTwoBodyKin(40.*G4UniformRand(), 20.*G4UniformRand());

	//std::cout<<cinem->GetK3()<<"  "<<cinem->GetThLab3()<<std::endl;	

	G4double kinE = cinem->GetK3()*MeV;
	G4double theta_lab = cinem->GetThLab3() * TMath::Pi()/180;;
	G4double phi = (2.*TMath::Pi())*(G4UniformRand());
	particleGun->SetParticleEnergy(kinE);
	particleGun->SetParticleMomentumDirection(G4ThreeVector(sin(theta_lab)*cos(phi),sin(theta_lab)*sin(phi),cos(theta_lab)));
	particleGun->GeneratePrimaryVertex(anEvent); 




//--------------------------------------------------------------------------------------------

			

}

