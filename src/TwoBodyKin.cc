
/*Relativistic calculator of 2 body kinematics*/
/*Program made by J.C. Zamora, 2012*/


#include "TwoBodyKin.hh"
#include "Randomize.hh"

#define amu 931.494

 TwoBodyKin::TwoBodyKin() {
         m1 = 0;
	 m2 = 0;
	 m3 = 0;
	 m4 = 0;
	 Ex3 = 0;
	 Ex4 = 0;
	 K1 = 0;
	 K3 = 0;
	 K4 = 0;
	 theta_lab3 = 0;
	 theta_lab4 = 0;
}	 
 


void TwoBodyKin::SetTwoBodyMass(double v1, double v2, double v3, double v4, double v5){

	m1 = v1*amu;
	m2 = v2*amu;
	m3 = v3*amu;
	m4 = v4*amu;	
	K1 = v5;

	
}

void TwoBodyKin::SetTwoBodyKin(double thcm, double ex){

	

	K1_inv = round(m1/amu)*K1;
	m3 = m3 + Ex3 ;  
 	m4 = m4 + ex ;  
	Et1 = K1_inv + m1;
	Et2 = m2;

	s = sq(m1) + sq(m2) +2*m2*Et1;
	a =4.*m2*s;
	b =(TwoBodyKin::sq(m3)-TwoBodyKin::sq(m4)+s)*(TwoBodyKin::sq(m1)-TwoBodyKin::sq(m2)-s);
	c = TwoBodyKin::omega(s,TwoBodyKin::sq(m1),TwoBodyKin::sq(m2))*TwoBodyKin::omega(s,TwoBodyKin::sq(m3),TwoBodyKin::sq(m4));


	Et3 = (c*cos((180.-thcm)*TMath::Pi()/180)-b)/a; //estamos viendo el recoil en cm (pi-theta)
	Et4 = (Et1 + m2 - Et3);
	
	K3 = Et3 - m3;
	K4 = Et4 - m4;

	t =  TwoBodyKin::sq(m2) + TwoBodyKin::sq(m4) - 2*m2*Et4;
	u =  TwoBodyKin::sq(m2) + TwoBodyKin::sq(m3) - 2*m2*Et3;

	theta_lab3 = acos(((s-TwoBodyKin::sq(m1)-TwoBodyKin::sq(m2))*(TwoBodyKin::sq(m2)+TwoBodyKin::sq(m3)-u)+2.*TwoBodyKin::sq(m2)*(TwoBodyKin::sq(m2)+sq(m4)-s-u))/(TwoBodyKin::omega(s,TwoBodyKin::sq(m1),TwoBodyKin::sq(m2))*TwoBodyKin::omega(u,TwoBodyKin::sq(m2),TwoBodyKin::sq(m3))))*180./TMath::Pi();


	theta_lab4 = acos(((s-TwoBodyKin::sq(m1)-TwoBodyKin::sq(m2))*(TwoBodyKin::sq(m2)+TwoBodyKin::sq(m4)-t)+2*TwoBodyKin::sq(m2)*(u-TwoBodyKin::sq(m1)-TwoBodyKin::sq(m4)))/(TwoBodyKin::omega(s,TwoBodyKin::sq(m1),TwoBodyKin::sq(m2))*TwoBodyKin::omega(t,TwoBodyKin::sq(m2),TwoBodyKin::sq(m4))))*180./TMath::Pi();




}


