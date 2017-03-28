 // $Id: RootSaver.cc 94 2010-01-26 13:18:30Z adotti $
 /**
  * @file   RootSaver.cc
  *
  * @date   17 Dec 2009
  * @author adotti
  * 
  * @brief  Implements class RootSaver.
  */
 
 #include "RootSaver.hh"
 #include "SiDigi.hh"
 #include "SiHit.hh"
 #include "CrystalHit.hh"
 #include "G4SystemOfUnits.hh"
 #include "TTree.h"
 #include "TFile.h"
 #include "TMath.h"

 #include <sstream>
 #include <iostream>
 #include <cassert>
 
#include <string.h>

 RootSaver::RootSaver() :
         rootTree(0),
         runCounter(0),
         nStrips(0),
	 ndetectors(0),
         Signal1(0),
	 Pos_x_1(0),
	 Pos_y_1(0),
	 Pos_z_1(0),
	 E_dssd1(0),
	 E_crystal(0),
         TruthPosx(0),
	 TruthPosy(0),
	 TruthPosz(0),
	 TruthAngle_theta(0),
	 TruthAngle_phi(0)
	 
 {
 }
 
 RootSaver::~RootSaver()
 {
         //Close current file if needed
         if ( rootTree )
         {
                 CloseTree();
         }
 }
 
 void RootSaver::CreateTree( const std::string& fileName , const std::string& treeName )
 {
         if ( rootTree )
         {
                 std::cerr<<"TTree already created, first call CloseTree"<<std::endl;
                 return;
         }
         std::ostringstream fn;
         fn << fileName << "_run" << runCounter++ << ".root";
	 //fn <<"/d/d2/ag_kr/JUAN_DATA/"<< fileName << "_132sn_reso_quad" << runCounter++ << ".root";
         //Create a new file and open it for writing, if the file already exists the file
         //is overwritten
         TFile* rootFile = TFile::Open( fn.str().data() , "recreate" );
         if ( rootFile == 0 || rootFile->IsZombie() )
         {
                 G4cerr<<"Error opening the file: "<<fn.str() <<" TTree will not be saved."<<G4endl;
                 return;
         }
         rootTree = new TTree( treeName.data() , treeName.data() );
         //TODO: Get detector strip numbers automatically
         nStrips = 1;
	 ndetectors = 736;
         Signal1 = new Float_t[nStrips][736];
	 //Signal2 = new Float_t[nStrips][12];
	 Pos_x_1 = new Float_t[ndetectors];
	 Pos_y_1 = new Float_t[ndetectors];
	 Pos_z_1 = new Float_t[ndetectors];
	 /*Pos_x_2 = new Float_t[ndetectors];
	 Pos_y_2 = new Float_t[ndetectors];
	 Pos_z_2 = new Float_t[ndetectors];*/
         E_dssd1 = new Float_t[ndetectors];
	 //E_dssd2 = new Float_t[ndetectors];

	
 	std::fill(&Signal1[0][0], &Signal1[0][0] + nStrips * (ndetectors) , -1000.);
	//std::fill(&Signal2[0][0], &Signal2[0][0] + nStrips * ndetectors , -1000.);

	std::fill(Pos_x_1, Pos_x_1+ndetectors, -1000.);
	std::fill(Pos_y_1, Pos_y_1+ndetectors, -1000.);
	std::fill(Pos_z_1, Pos_z_1+ndetectors, -1000.);
	/*std::fill(Pos_x_2, Pos_x_2+ndetectors, -1000.);
	std::fill(Pos_y_2, Pos_y_2+ndetectors, -1000.);
	std::fill(Pos_z_2, Pos_z_2+ndetectors, -1000.);*/

	std::fill(E_dssd1, E_dssd1+(ndetectors), 0);
	//std::fill(E_dssd2, E_dssd2+ndetectors, 0);
	
	
         //Digits variables
         rootTree->Branch( "DSSD1", Signal1 , "DssD1[1][736]/F");
	 //rootTree->Branch( "DSSD2", Signal2 , "DssD2[1][12]/F");
         
         //Hits variables
         rootTree->Branch( "pos_x_1" , Pos_x_1, "posx1[736]/F" );
	 rootTree->Branch( "pos_y_1" , Pos_y_1, "posy1[736]/F" );
	 rootTree->Branch( "pos_z_1" , Pos_z_1, "posz1[736]/F" );

	 /*rootTree->Branch( "pos_x_2" , Pos_x_2, "posx2[12]/F" );
	 rootTree->Branch( "pos_y_2" , Pos_y_2, "posy2[12]/F" );
	 rootTree->Branch( "pos_z_2" , Pos_z_2, "posz2[12]/F" );
	*/
	 
         rootTree->Branch( "ener_1" , E_dssd1, "Energy1[736]/F" );
	 //rootTree->Branch( "ener_2" , E_dssd2, "Energy2[12]/F" );
         
         rootTree->Branch( "truthPosx" , &TruthPosx );
	 rootTree->Branch( "truthPosy" , &TruthPosy );
	 rootTree->Branch( "truthPosz" , &TruthPosz );
         rootTree->Branch( "truthAngle_theta" , &TruthAngle_theta );
	 rootTree->Branch( "truthAngle_phi" , &TruthAngle_phi );
         rootTree->Branch( "Ener_crystal" , &E_crystal );
	 
 }
 
 void RootSaver::CloseTree()
 {
         //Check if ROOT TTree exists,
         //in case get the associated file and close it.
         //Note that if a TFile goes above 2GB a new file
         //will be automatically opened. We have thus to get,
         //from the TTree the current opened file
         if ( rootTree )
         {
                 G4cout<<"Writing ROOT TTree: "<<rootTree->GetName()<<G4endl;
                 //rootTree->Print();
                 rootTree->Write();
                 TFile* currentFile = rootTree->GetCurrentFile();
                 if ( currentFile == 0 || currentFile->IsZombie() )
                 {
                         G4cerr<<"Error closing TFile "<<G4endl;
                         return;
                 }
                 currentFile->Close();
                 //The root is automatically deleted.
                 rootTree = 0;
                 delete[] Signal1;
		 //delete[] Signal2;
		 delete[] Pos_x_1;
		 delete[] Pos_y_1;
		 delete[] Pos_z_1;
		 /*delete[] Pos_x_2;
		 delete[] Pos_y_2;
		 delete[] Pos_z_2;*/
		 delete[] E_dssd1;
		 //delete[] E_dssd2;
		 
                 
         }
 }
 
 void RootSaver::AddEvent( const SiHitCollection* const hits, const SiDigiCollection* const digits ,
                                                   const G4ThreeVector& primPos, const G4ThreeVector& primMom, const CrystalHitsCollection* const crystalhits)
 {
         //If root TTree is not created ends
         if ( rootTree == 0 )
         {
                 return;
         }
        

	 //Store Digits information
         if ( digits )
         {


		 	std::fill(&Signal1[0][0], &Signal1[0][0] + nStrips * ndetectors , -1000.);
			//std::fill(&Signal2[0][0], &Signal2[0][0] + nStrips * ndetectors , -1000.);
                 G4int nDigits = digits->entries();
                 for ( G4int d = 0 ; d<nDigits ; ++d )
                 {
                         const SiDigi* digi = static_cast<const SiDigi*>( digits->GetDigi( d ) );
                         G4int stripNum = digi->GetStripNumber();
			 G4int planeNum = digi->GetPlaneNumber();
                         //Safety check
                         if ( stripNum >= nStrips )
                         {
                                 G4cerr<<"Digi Error: Strip number "<<stripNum<<" expected max value:"<<nStrips<<G4endl;
                                 continue;//Go to next digit
                         }
                         if ( planeNum < ndetectors ){
				Signal1[ stripNum ][planeNum ] = static_cast<Float_t>(digi->GetCharge());
				//G4cout<<d<<" "<<planeNum<<"  "<<Signal1[ stripNum ][planeNum ]<<" Digi"<<G4endl;
			 }
			 /*else if(planeNum == 736){
				Signal1[ stripNum ][planeNum ] = static_cast<Float_t>(digi->GetCharge());

			 }*/
                         else
                         {
                                 G4cerr<<"Digi Error: Plane number "<<planeNum<<" expected max value: 736"<<G4endl;
                         }
                 }
         }
         else
         {
                 G4cerr<<"Error: No digi collection passed to RootSaver"<<G4endl;
         }
 
         //Store Hits infromation
         if ( hits )
         {
		//hits->PrintAllHits();
		std::fill(E_dssd1, E_dssd1+(ndetectors), 0);
		//std::fill(E_dssd2, E_dssd2+ndetectors, 0);

		std::fill(Pos_x_1, Pos_x_1+ndetectors, -1000.);
		std::fill(Pos_y_1, Pos_y_1+ndetectors, -1000.);
		std::fill(Pos_z_1, Pos_z_1+ndetectors, -1000.);
		/*std::fill(Pos_x_2, Pos_x_2+ndetectors, -1000.);
		std::fill(Pos_y_2, Pos_y_2+ndetectors, -1000.);
		std::fill(Pos_z_2, Pos_z_2+ndetectors, -1000.);*/

                 G4int nHits = hits->entries();
                 
		 Float_t edep_hit[ndetectors];
                 std::fill(edep_hit, edep_hit+(ndetectors), 0);
                 //Loop on all hits, consider only the hits with isPrimary flag
                 //Position is weighted average of hit x()
                 for ( G4int h = 0 ; (h<nHits) ; ++h )
                 {
                         const SiHit* hit = static_cast<const SiHit*>( hits->GetHit( h ) );
                         //Uncomment this line if you want to record only
                         //primary energy depositions
                         //if ( hit->GetIsPrimary() == false ) continue;
                         G4int planeNum = hit->GetPlaneNumber();
                         G4ThreeVector pos = hit->GetPosition();
			 G4ThreeVector momentum = hit->GetIncidenceMomentumDirection();
                         G4double x = pos.x();
			 G4double y = pos.y();
			 G4double z = pos.z();
	
			 
			 
                         //We save xyz in mm (detector coordinates)
                         x /= mm;
			 y /= mm;
			 z /= mm;
			 
                         //We save energy in MeV
                         Float_t edep = static_cast<Float_t>(hit->GetEdep());
                         edep /= MeV;


			  
                         if( planeNum < ndetectors )
                         {
                                 //if ( hit->GetIsPrimary() == true ){ 
							Pos_x_1[planeNum] = x;
							Pos_y_1[planeNum] = y;
							Pos_z_1[planeNum] = z;
							//E_dssd1[planeNum] = edep;
							//G4cout<<h<<" "<<planeNum<<"  "<<E_dssd1[planeNum]<<" Hit"<<G4endl;
				//			}
				 edep_hit[planeNum] += edep;
                                 E_dssd1[planeNum] = edep_hit[planeNum];
				 //G4cout<<h<<" "<<planeNum<<"  "<<E_dssd1[planeNum]<<" Hit"<<G4endl;
                         }
                         /*else if(planeNum == 736)
                         {
                                 
                                 E_dssd1[planeNum] = edep;
				 //G4cout<<planeNum<<"  "<<planeNum - n	detectors<<"  "<<x<<" "<<y<<G4endl;
                         }*/
	                    
                         else
                         {
                                 G4cerr<<"Hit Error: Plane number "<<planeNum<<" expected max value: 736"<<G4endl;
                                 continue;
                         }
 
                 }
         }
         else
         {
                 G4cerr<<"Error: No hits collection passed to RootSaver"<<G4endl;
         }

	 if(crystalhits){
		E_crystal = 0;
		G4int nHitsCry = crystalhits->entries();

		 for ( G4int hc = 0 ; (hc<nHitsCry) ; ++hc )
                 {
                         const CrystalHit* hitCry = static_cast<const CrystalHit*>( crystalhits->GetHit( hc ) );
			 Float_t edepcrys = static_cast<Float_t>(hitCry->GetDepositedEnergy());
			  edepcrys	/= MeV;
			  E_crystal = edepcrys;
			
			//G4cout<<"Hola mundo!! "<<nHitsCry<<" "<<hc<<"  "<<edepcrys<<G4endl;
			
		}
		
		
	}

	
         TruthPosx = static_cast<Float_t>( primPos.x() );
	 TruthPosy = static_cast<Float_t>( primPos.y() );
	 TruthPosz = static_cast<Float_t>( primPos.z() );
         //Measure angle of the beam in xz plane measured from z+ direction
         // 0<Angle<=pi (positive when close to x positiove direction)
  
	 Float_t norma_mom = std::sqrt(primMom.x()*primMom.x() + primMom.y()*primMom.y() +primMom.z()*primMom.z());
	 TruthAngle_theta = ( norma_mom != 0 ) ?
                         std::acos( primMom.z()/norma_mom )
                         : 0.; //beam perpendicular to z
         TruthAngle_theta /= deg;

	  //Measure angle of the beam in xy. Phi
         // -pi/2<Phi<=pi/2 
	
	 Float_t sign_y = ( primMom.y()>= 0 ) ? +1 : -1;
	 TruthAngle_phi = ( primMom.x() != 0 ) ?
                           atan( primMom.y()/primMom.x()) 
                         : sign_y*TMath::PiOver2(); //beam perpendicular to x
         TruthAngle_phi /= deg;
	//G4cout<<"x mom "<<primMom.x()<<" y mom "<<primMom.y()<<G4endl;
	 //G4cout<<TruthAngle_theta<<G4endl;
	//if(TruthAngle_phi>7 && E_dssd2 > 0)G4cout<<"atan "<<std::abs(atan( primMom.y()/primMom.x() ))<<" en degree "<<TruthAngle_phi<<G4endl;
	//if(TruthAngle_phi>9 && E_dssd2 > 2)G4cout<<"x mom "<<primMom.x()<<" y mom "<<primMom.y()<<" z mom "<< primMom.z()<<" pos x  "<<TruthPosx<<" pos y  "<<TruthPosy<<" pos z "<<TruthPosz<<" posy "<< Pos_y_dssd2<<G4endl;

         rootTree->Fill();
 }
