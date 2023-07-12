// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef EVENTPLANE_EPFINDER_H
#define EVENTPLANE_EPFINDER_H

#include <string>
#include <array>  // for array
#include <vector>

class EpInfo;

typedef struct
{
  float nMip;
  double phi;
  int ix;
  int iy;
  int side;
  std::vector<std::pair<int,int>> *sameRing;

} EpHit;

class EpFinder
{
 public:

  EpFinder(int nDetectors = 2, unsigned int order = 3);

 ~EpFinder(){};

  void Results(const std::vector<EpHit> &EpdHits, EpInfo *epinfo, unsigned int det);

  void ResetEvent();  // clear current event for safety
 
 private:

  double GetPsiInRange(const double Qx, const double Qy, const unsigned int order) const;
  unsigned int NumberofDetectors = 0;
  unsigned int k = 0;
  unsigned int n = 0;
  unsigned int m_MaxOrder = 0;
  std::vector<std::array<double, 2>> TotalWeight4Side;
  std::vector<std::vector<double>> QrawOneSide;
  std::vector<std::vector<double>> PsiRaw; 
  
};

#endif // EVENTPLANE_EPFINDER_H
