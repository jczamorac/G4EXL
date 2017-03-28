//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Aug  5 13:13:25 2014 by ROOT version 5.32/00
// from TChain SiTelescope/
//////////////////////////////////////////////////////////

#ifndef simClassEXL_h
#define simClassEXL_h


#include "Riostream.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TPad.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TF1.h"
#include "TH2F.h"
#include "TF2.h"
#include "TStyle.h"
#include "TLegend.h"

#include<string>
#include <cstdio>
#include <sstream>
#include <iostream>
#include<fstream>
#include <stdlib.h>
#include <vector>


// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class simClassEXL {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         DSSD1[1][736];
   Float_t         pos_x_1[736];
   Float_t         pos_y_1[736];
   Float_t         pos_z_1[736];
   Float_t         ener_1[736];
   Float_t         truthPosx;
   Float_t         truthPosy;
   Float_t         truthPosz;
   Float_t         truthAngle_theta;
   Float_t         truthAngle_phi;
   Float_t         Ener_crystal;

   // List of branches
   TBranch        *b_DssD1;   //!
   TBranch        *b_posx1;   //!
   TBranch        *b_posy1;   //!
   TBranch        *b_posz1;   //!
   TBranch        *b_Energy1;   //!
   TBranch        *b_truthPosx;   //!
   TBranch        *b_truthPosy;   //!
   TBranch        *b_truthPosz;   //!
   TBranch        *b_truthAngle_theta;   //!
   TBranch        *b_truthAngle_phi;   //!
   TBranch        *b_Ener_crystal;   //!

   simClassEXL(TTree *tree=0);
   virtual ~simClassEXL();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef simClassEXL_cxx
simClassEXL::simClassEXL(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("SiTelescope",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("SiTelescope","");
      chain->Add("/d/d2/ag_kr/JUAN_DATA/tree_132sn_reso_quad0.root/SiTelescope");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

simClassEXL::~simClassEXL()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t simClassEXL::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t simClassEXL::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void simClassEXL::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("DSSD1", DSSD1, &b_DssD1);
   fChain->SetBranchAddress("pos_x_1", pos_x_1, &b_posx1);
   fChain->SetBranchAddress("pos_y_1", pos_y_1, &b_posy1);
   fChain->SetBranchAddress("pos_z_1", pos_z_1, &b_posz1);
   fChain->SetBranchAddress("ener_1", ener_1, &b_Energy1);
   fChain->SetBranchAddress("truthPosx", &truthPosx, &b_truthPosx);
   fChain->SetBranchAddress("truthPosy", &truthPosy, &b_truthPosy);
   fChain->SetBranchAddress("truthPosz", &truthPosz, &b_truthPosz);
   fChain->SetBranchAddress("truthAngle_theta", &truthAngle_theta, &b_truthAngle_theta);
   fChain->SetBranchAddress("truthAngle_phi", &truthAngle_phi, &b_truthAngle_phi);
   fChain->SetBranchAddress("Ener_crystal", &Ener_crystal, &b_Ener_crystal);
   Notify();
}

Bool_t simClassEXL::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void simClassEXL::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t simClassEXL::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef simClassEXL_cxx
