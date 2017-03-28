 
#ifndef TWOBODYKIN_HH_
#define TWOBODYKIN_HH_
 
#include "G4VUserPrimaryGeneratorAction.hh"
#include<iostream>
#include<fstream>
#include<cmath>
#include<tgmath.h>
#include<string>
#include "TMath.h"


 class TwoBodyKin 
 {
 public:
         //! Default constructor
         TwoBodyKin();
         //! Default destructor
         virtual ~TwoBodyKin() {};
	
	 double omega(double x, double y, double z){
		return sqrt(x*x + y*y + z*z -2*x*y -2*y*z -2*x*z);
		}

	double sq(double val ){
		return val*val;
	}
         
	void SetTwoBodyMass(double v1, double v2, double v3, double v4, double v5);
	void SetTwoBodyKin(double thcm, double ex);
	
	void SetEx3(double value){Ex3 = value;}	

	double GetK3(){return K3;}
	double GetK4(){return K4;}
	double GetThLab3(){return theta_lab3;}
	double GetThLab4(){return theta_lab4;}


	 double m1;
	 double m2;
	 double m3;
	 double m4;
	 double Ex3;
	 double Ex4;
	 double K1;
	 double K1_inv;

	 double theta_lab3;
	 double theta_lab4; 
	 double Et1;
	 double Et2;
	 double Et3;
	 double Et4;
	 double K3 ;
	 double K4 ; 

	//---Mandelstam variables
	double s ;
	double t ;
	double u ;

	double a;
	double b;
	double c;



 private:
      
 };
 
 #endif 

