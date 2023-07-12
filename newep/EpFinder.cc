
#include "EpFinder.h"
#include "EpInfo.h"

#include <cdbobjects/CDBHistos.h>

#include <algorithm>  // for fill
#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>


EpFinder::EpFinder(int Numdet, unsigned int maxorder)
: NumberofDetectors(Numdet)
 , m_MaxOrder(maxorder)
{
    TotalWeight4Side.resize(m_MaxOrder);
    QrawOneSide.resize(m_MaxOrder);
    PsiRaw.resize(m_MaxOrder);

    for (auto &vec : QrawOneSide)
    {
        vec.resize(2);
    }
    
    for (auto &vec : PsiRaw)
    {
        vec.resize(NumberofDetectors);
    }
   
}

//==================================================================================================================
void EpFinder::Results(const std::vector<EpHit> &EpdHits, EpInfo *epinfo, unsigned int det)
{
  

  //--------------------------------
  // begin loop over hits
  //--------------------------------

  for (unsigned int hit = 0; hit < EpdHits.size(); hit++)
  {
    float nMip = EpdHits.at(hit).nMip;
    double TileWeight = nMip;
    double phi = EpdHits.at(hit).phi;
       
    //--------------------------------
    // now calculate Q-vectors
    //--------------------------------
    
    for (unsigned int order = 1; order < m_MaxOrder + 1; order++)
    { 
      double etaWeight = 1.0;

      //total weight for normalization
      TotalWeight4Side[order - 1][0] += fabs(etaWeight) * TileWeight;
     
      double Cosine = cos(phi * (double) order);
      double Sine = sin(phi * (double) order);
      
      //raw Q vectors
      QrawOneSide[order - 1][0] += etaWeight * TileWeight * Cosine;
      QrawOneSide[order - 1][1] += etaWeight * TileWeight * Sine;
       
    }
  }  // loop over hits


  // first, normalize the Q's with total weight...
  for (unsigned int order = 1; order < m_MaxOrder + 1; order++)
  {
    if (TotalWeight4Side[order - 1][0] > 0.0001)
    {
      QrawOneSide[order - 1][0] /= TotalWeight4Side[order - 1][0];
      QrawOneSide[order - 1][1] /= TotalWeight4Side[order - 1][0];
    }
  }

  //---------------------------------
  // Calculate unshifted EP angles
  //---------------------------------
   for (unsigned int order = 1; order < m_MaxOrder + 1; order++)
   {
     PsiRaw[order - 1].at(det) = GetPsiInRange(QrawOneSide[order - 1][0], QrawOneSide[order - 1][1], order); 
   }    


    //n index = # of event planes orders
    //det index = detector index
    //k index = key for event plane orders and detector type
    k = det * m_MaxOrder;
    unsigned int nMax = k + m_MaxOrder;
    for(; k < nMax; k ++)
    {
        epinfo->set_psi(k , PsiRaw[n].at(det));
        epinfo->set_q(k , QrawOneSide);
        n++;
    }
    
    
     return;
}


double EpFinder::GetPsiInRange(double Qx, double Qy, unsigned int order) const
{
  double temp;
  if ((Qx == 0.0) || (Qy == 0.0))
    temp = NAN;
  else
  {
    temp = atan2(Qy, Qx) / ((double) order);
    double AngleWrapAround = (2.0 * M_PI) / (double) order;
    if (temp < 0.0)
      temp += AngleWrapAround;
    else if (temp > AngleWrapAround)
      temp -= AngleWrapAround;
  }
  return temp;
}



void EpFinder::ResetEvent()
{
  for (auto &vec : TotalWeight4Side)
  {
    vec.fill(0);
  }
    
  for (auto &vec : QrawOneSide)
  {
    std::fill(vec.begin(), vec.end(), 0);
  }
    
  for (auto &vec : PsiRaw)
  {
    std::fill(vec.begin(), vec.end(), 0);
  }
   
}
