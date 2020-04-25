// -------------------------------------------------------------------------
// -----                    MpdDecayer header file                     -----
// -----                      Created 22/04/2020                       -----
// -----                  R. Akhat,  A. Zinchenko                      -----
// -----                  External decayer for MPD                     -----
// -------------------------------------------------------------------------

#ifndef MPDDECAYER_H
#define MPDDECAYER_H
 
#include "TVirtualMCDecayer.h"
#include "TString.h"
#include "TArrayF.h"
 
class MpdDecayer : public TVirtualMCDecayer
{
 
 public:
  // enum of decay mode types
  
  enum SourceFlag {kPythia, kCustom}; // particle container source
  
  // protected:
 private:
  TString    fDecayTableFile; // File to read decay table from
  //EDecayType fDecay;          // Forced decay mode
  Int_t fDecay;          // Forced decay mode
  TArrayF    fBraPart;        //! Branching ratios
  Float_t fBratio[6];
  Int_t fMode[6];
  Int_t fkcLamb; // Pythia Lmabda compressed code
  Float_t fBranch; // branching of lambda to p + \pi-
  TClonesArray *fParticles;
  SourceFlag fSourceFlag;
  
  static MpdDecayer *fgInstance;
  
  // Extra functions
  MpdDecayer(); //AZ
  Int_t CountProducts (Int_t channel, Int_t particle);
  void Gdecay (Int_t idpart, TLorentzVector* p);
  void Gdeca2 (Double_t xm0, Double_t xm1, Double_t xm2, Double_t pcm[2][4]);
  void Anisotropy (Double_t* pvert, Double_t *rndm, Double_t polar, Double_t phi, Double_t costh);
  
 public:
  //AZ MpdDecayer();
  virtual ~MpdDecayer() { }
  virtual void    Init();
  virtual void    Decay(Int_t idpart, TLorentzVector* p);
  virtual Int_t   ImportParticles(TClonesArray *particles);
  virtual void    SetForceDecay(Int_t type);
  virtual void    ForceDecay();
  
  virtual Float_t GetPartialBranchingRatio(Int_t ipart);
  virtual Float_t GetLifetime(Int_t kf);
  virtual void    ReadDecayTable();
  // Extension member functions
  virtual void    SetDecayTableFile(const char* name);
  virtual void    WriteDecayTable();
  //virtual void    SetForceDecay(EDecayType type) { fDecay = type; }
  
  static  MpdDecayer *Instance();
  
  ClassDef(MpdDecayer,0); // Particle Decayer Base Class
};

inline void MpdDecayer::SetDecayTableFile(const char *name)
{
  fDecayTableFile = name;
}

#endif
