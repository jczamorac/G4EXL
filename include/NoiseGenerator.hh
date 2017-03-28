 // $Id: NoiseGenerator.hh 28 2010-01-12 10:24:06Z adotti $
 
 /**
  * @file   NoiseGenerator.hh
  *
  * @date   10 Dec 2009
  * @author adotti
  *
  * @brief  Brief simulates electronic noise.
  */
 
 #ifndef NOISEGENERATOR_HH_
 #define NOISEGENERATOR_HH_
 
 
 #include "G4Types.hh"
 #include "Randomize.hh"
 
 /*! \brief simulates electronic noise
  * This class simulates gaussian noise around 0
  */
 class NoiseGenerator
 {
 public:
   //! \brief Default constructor
   NoiseGenerator(const G4double& value);
   //! \brief Deafault destructor
   virtual ~NoiseGenerator() {};
   /*! \brief Generate noise
    * By default generate gaussian noise
    * if sigma<0 do not smear
    */
   virtual G4double operator() ();
   /*! \name copy and assignement operators
    * These methods are needed since
    * randomGauss should not be copied
    */
   //@{
   //! \brief assignement operator
   inline NoiseGenerator& operator= (const NoiseGenerator& rhs)
   {
         sigma = rhs.sigma;
         return *this;
   }
   //! \brief copy constructor
   NoiseGenerator(const NoiseGenerator& rhs);
   //@}
 private:
   //! Noise standard deviation
   G4double sigma;
   //! Gaussian Random number
   G4RandGauss randomGauss;
 };
 
 #endif /* NOISEGENERATOR_HH_ */