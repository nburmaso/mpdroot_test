//------------------------------------------------------------------------------------------------------------------------
#include <iostream>

#include "MpdFfdHit.h"

using namespace std;
ClassImp(MpdFfdHit);
//------------------------------------------------------------------------------------------------------------------------
MpdFfdHit::MpdFfdHit() {}
//------------------------------------------------------------------------------------------------------------------------
MpdFfdHit::MpdFfdHit(Int_t suid, TVector3 pos, TVector3 dpos, Int_t index, Double_t time, size_t npe, Int_t flag)
   : FairHit(suid, pos, dpos, index), fTime(time), fFlag(flag), fNpe(npe)
{
}
//------------------------------------------------------------------------------------------------------------------------
MpdFfdHit::~MpdFfdHit() {}
//------------------------------------------------------------------------------------------------------------------------
void MpdFfdHit::Print(const Option_t *opt) const
{
   cout << "\n-I- MpdFfdHit: "
        << " suid=" << fDetectorID << ", Position=(" << fX << "," << fY << "," << fZ << ") cm"
        << "  time=" << fTime << ", nPe=" << fNpe << ", flag=" << fFlag;
}
//------------------------------------------------------------------------------------------------------------------------