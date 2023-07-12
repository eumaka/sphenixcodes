#include "EpInfov1.h"

#include <algorithm>  // for fill
#include <cmath>      // for fabs, M_PI
#include <vector>  
#include <iostream>
#include <memory>       // for allocator_traits<>::value_type
#include <type_traits>  // for __decay_and_strip<>::__type

void EpInfov1::Reset()
{
 
    for (auto &vec : QrawOneSide)
      {
        std::fill(vec.begin(), vec.end(), NAN);
      }
    
    for (auto &vec : PsiRaw)
     {
       std::fill(vec.begin(), vec.end(), NAN);
     }
}

unsigned int EpInfov1::get_ep_key(int det,  int maxorder,  int thisorder)
{
    int shiftorder = thisorder - 1;
    
    return det * maxorder + shiftorder;
}

int EpInfov1::get_det_key(const detName detname)
{
    switch(detname) {
     case epd_S:
            thisdetep = 0;
        break;
     case epd_N:
            thisdetep = 1;
        break;
     case mbd_S:
            thisdetep = 2;
        break;
    case mbd_N:
            thisdetep = 3;
        break;
    }
    
    return thisdetep;
}


double EpInfov1::get_psi(int thisorder, detName detname) 
{
  
    unsigned int key; 
    unsigned int n_Orders = maxsize()/2;
    int detep = get_det_key(detname);
    
    if((thisorder > 0) && ((unsigned int) thisorder <= n_Orders))
    {
        key = get_ep_key(detep, n_Orders, thisorder);
    }
    else
    {
        std::cout<<"you requested for the " << thisorder << "th psi order" << std::endl;
        std::cout<<"valid ep orders are 1 to "<< n_Orders << std::endl;
        std::cout<<"you asking for ep order beyond what was reconstructed"<< std::endl;
        std::cout<<"run the ep reconstruction up to this order before asking for it"<< std::endl;
        exit(1);
    }
    
    return _psi[key];

}

std::pair<double, double>  EpInfov1::get_q(int thisorder, detName detname)
{
  
    unsigned int key;
    unsigned int n_Orders = maxsize()/2;
    int detep = get_det_key(detname);
    
    if((thisorder > 0) && ((unsigned int) thisorder <= n_Orders))
    {
        key = get_ep_key(detep, n_Orders, thisorder);
    }
    else
    {
        std::cout<<"you requested for the " << thisorder << "th Q order" << std::endl;
        std::cout<<"valid ep orders are 1 to "<< n_Orders << std::endl;
        std::cout<<"you asking for Qth order beyond what was reconstructed"<< std::endl;
        std::cout<<"run the ep reconstruction up to this order before asking for it"<< std::endl;
        exit(1);
    }
    
    std::vector<std::vector<double>> Q = _q[key];
    return std::make_pair(Q.at(thisorder - 1).at(0), Q.at(thisorder - 1).at(1));

}

