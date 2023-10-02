
#include "caloinfo.h"

#include <eventplaneinfo/Eventplaneinfo.h>
#include <eventplaneinfo/EventplaneinfoMap.h>


#include <fun4all/Fun4AllReturnCodes.h>
#include <fun4all/PHTFileServer.h>

#include <phool/getClass.h>
#include <phool/PHCompositeNode.h>

#include <TFile.h>
#include <TH3F.h>
#include <TH2F.h>
#include <cassert>
#include <fstream>
#include <TGraph.h>
#include <vector>

//____________________________________________________________________________..
caloinfo::caloinfo(const std::string &name):
 SubsysReco(name)
{
  _event = 0;
}

//____________________________________________________________________________..
caloinfo::~caloinfo()
{
}

//____________________________________________________________________________..
int caloinfo::Init(PHCompositeNode *topNode)
{
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int caloinfo::InitRun(PHCompositeNode *topNode)
{
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int caloinfo::process_event(PHCompositeNode *topNode)
{

    _event++;
    std::cout<<"entering calinfo \t"<<_event<<std::endl;
    float sep = NAN;
    float nep = NAN;
    

    EventplaneinfoMap *epmap = findNode::getClass<EventplaneinfoMap>(topNode, "EventplaneinfoMap");
    if (!epmap)
    {
    std::cout << PHWHERE << "::ERROR - cannot find EventplaneinfoMap" << std::endl;
      exit(-1);
    }
  
    

   for (EventplaneinfoMap::ConstIter iter = epmap->begin(); iter != epmap->end(); ++iter)
   {
       Eventplaneinfo *ep = iter->second;
       auto epds = ep->find_ep_ids(Eventplaneinfo::EPDS);
       if(epds == ep->end_ep_ids())
       { continue; }
       sep = ep->get_psi_raw(2);

   }
    
    for (EventplaneinfoMap::ConstIter iter2 = epmap->begin(); iter2 != epmap->end(); ++iter2)
    {
        Eventplaneinfo *ep2 = iter2->second;
        auto epdn = ep2->find_ep_ids(Eventplaneinfo::EPDN);
        if(epdn == ep2->end_ep_ids())
        { continue; }
        nep = ep2->get_psi_raw(2);

    }
  
  std::cout<<nep<<"\t"<<sep<<std::endl;
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int caloinfo::ResetEvent(PHCompositeNode *topNode)
{
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int caloinfo::EndRun(const int runnumber)
{
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int caloinfo::End(PHCompositeNode *topNode)
{
  
  return Fun4AllReturnCodes::EVENT_OK;

}

//____________________________________________________________________________..
int caloinfo::Reset(PHCompositeNode *topNode)
{
  return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..

unsigned int caloinfo::getCaloTowerPhiBin(const unsigned int key)
{
  unsigned int etabin = key >> 16U;
  unsigned int phibin = key - (etabin << 16U);
  return phibin;
}

//____________________________________________________________________________..
unsigned int caloinfo::getCaloTowerEtaBin(const unsigned int key)
{
  unsigned int etabin = key >> 16U;
  return etabin;
}


int caloinfo::getvecsize(std::vector <double> _x)
{
    return _x.size();
}

double caloinfo::getmax(std::vector<double> arr)
{
    int size = getvecsize(arr);
    
    double x[size]; double y[size];

    for (int i = 0; i <  size ; ++i )
    {
        x [i] = i;
        y [i] = arr[i];
    }

    auto gr1 = new TGraph(size, x, y );
    gr1->SetName("gr1");
    return TMath::MaxElement(size, gr1->GetY());
    
}
double caloinfo::getmin(std::vector<double> arr2)
{
    int size2 = getvecsize(arr2);
    
    double x2[size2]; double y2[size2];

    for (int i = 0; i <  size2 ; ++i )
    {
        x2 [i] = i;
        y2 [i] = arr2[i];
    }

    auto gr2 = new TGraph(size2, x2, y2 );
    gr2->SetName("gr2");
    return TMath::MinElement(size2, gr2->GetY());
    
}
