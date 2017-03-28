 // $Id: RootSaver.hh 47 2010-01-19 16:20:46Z adotti $
 /**
  * @file   RootSaver.hh
  *
  * @date   17 Dec 2009
  * @author adotti
  *
  * @brief  Save hits and digits in a ROOT TTree
  */
 
 #ifndef ROOTSAVER_HH_
 #define ROOTSAVER_HH_
 
 #include <string>
 #include <TTree.h>
 #include "SiDigi.hh"
 #include "SiHit.hh"
 #include "CrystalHit.hh"
 class TFile;
 
 /*!
  * \brief Save hits and digits to a ROOT TTree.
  *
  * This class can be used to save in a TTree hits
  * and digits.
  * The TTree structure is described below.
  */
 class RootSaver
 {
 public:
         //! Default constructor,
         RootSaver();
         //! Default destructor.
         virtual ~RootSaver();
         /*! \brief Open a TFile and create ROOT TTree.
          *
          * Each time that a /run/beamOn command is issued
          * this method should be called
          * Every time this method is called the run counter
          * is incremented and the file name is modified accordingly:
          * tree_run<n>.root
          * \sa CloseTree()
          * @param fileName : The ROOT file name prefix
          * @param treeName : The name of the TTree
          */
         virtual void CreateTree( const std::string& fileName = "tree" , const std::string& treeName = "SiTelescope" );
         /*! Close the file and save ROOT TTree
          * The ROOT file should be closed at the end of each /run/beamOn
          * \sa CloseTree
          */
         virtual void CloseTree();
         //! Add hits and digi container for this event
         virtual void AddEvent( const SiHitCollection* const hits , const SiDigiCollection* const digits ,
                                                    const G4ThreeVector& primaryPos , const G4ThreeVector& primaryMom, const CrystalHitsCollection* const crystalhits);
 private:
         TTree* rootTree; //!< Pointer to the ROOT TTree
         unsigned int runCounter; //!< Run counter to uniquely identify ROOT file
 
         //! \name TTree variables
         //@{
         //! Number of strips of each module
         Int_t nStrips;
	 Int_t ndetectors;
         //! Signal in each strip for first module
         Float_t (*Signal1)[736];
	 //Float_t (*Signal2)[736];         

         //! "Truth" position of module 1
         Float_t* Pos_x_1;
	 Float_t* Pos_y_1;
	 Float_t* Pos_z_1;
         
	 /*Float_t* Pos_x_2;
	 Float_t* Pos_y_2;
	 Float_t* Pos_z_2;*/
         //! Sum of Hits Edep in module 1
         Float_t* E_dssd1;
	 Float_t E_crystal;
         
         //! X of the primary at origin
         Float_t TruthPosx;
	 Float_t TruthPosy;
	 Float_t TruthPosz;
         //! Angle in the xz plane (measured from z-axis) of primary at origin
         Float_t TruthAngle_theta;
	 Float_t TruthAngle_phi;


	 //@}
 
 };
 
 #endif /* ROOTSAVER_HH_ */
