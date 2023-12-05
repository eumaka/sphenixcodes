


#include "SimEP.h"

#include <eventplaneinfo/Eventplaneinfo.h>
#include <eventplaneinfo/EventplaneinfoMap.h>

#include <fun4all/Fun4AllReturnCodes.h>
#include <fun4all/PHTFileServer.h>

#include <phool/getClass.h>
#include <phool/PHCompositeNode.h>

#include <mbd/MbdGeom.h>
#include <mbd/MbdOut.h>
#include <mbd/MbdPmtContainer.h>
#include <mbd/MbdPmtHit.h>


#include <algorithm>  // for fill
#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <TFile.h>
#include <TNtuple.h>
#include <TProfile.h>
#include <TH1D.h>
#include <fstream>

//std::ofstream out1("epdeps.txt", std::ios::app);

SimEP::SimEP(const char *outfile) : SubsysReco("Sim EP Analysis Code")
{
  OutFileName = outfile;
  _event = 0;
  return;
}

int SimEP::Init(PHCompositeNode *topNode)
{

     outputfile = new TFile(OutFileName, "RECREATE"); 
     mbd = new TNtuple("mbd","mbd", "SouthQ:NorthQ:totalQ:mbds_psi2:mbdn_psi2");
   
     mbd->SetDirectory(outputfile);
   
     return 0;
    
}

int SimEP::process_event(PHCompositeNode *topNode)
{
 
    _event++;
    
    
    MbdPmtContainer *mbdpmts = findNode::getClass<MbdPmtContainer>(topNode, "MbdPmtContainer");
    if (!mbdpmts)
    {
        std::cout << PHWHERE << "::ERROR - cannot find MbdPmtContainer" << std::endl;
        exit(-1);
    }
    
   MbdGeom *mbdgeom = findNode::getClass<MbdGeom>(topNode, "MbdGeom");
    if (!mbdgeom)
    {
      std::cout << PHWHERE << "::ERROR - cannot find MbdGeom" << std::endl;
      exit(-1);
    } 



   float totalQ = 0.0; float totalS = 0.; float totalN = 0.;

    for (int ipmt = 0; ipmt < mbdpmts->get_npmt(); ipmt++)
    {
        float mbd_q = mbdpmts->get_pmt(ipmt)->get_q();
        if (mbd_q < 0.0)
        {
            continue;
        }
     

        totalQ += mbd_q;
        int arm = mbdgeom->get_arm(ipmt);
        if(arm == 0) totalS += mbd_q;
        if(arm == 1) totalN += mbd_q;
  
    }

 
    _g.clear();
    
     _g.push_back(totalS); 
     _g.push_back(totalN);
     _g.push_back(totalQ);
    float sep = NAN;
    float nep = NAN;
  
    
    EventplaneinfoMap *epmap = findNode::getClass<EventplaneinfoMap>(topNode, "EventplaneinfoMap");
    if (!epmap)
    {
       std::cout << PHWHERE << "::ERROR - cannot find EventplaneinfoMap" << std::endl;
         exit(-1);
    }
   
    auto mbds = epmap->get(EventplaneinfoMap::MBDS);
    sep = mbds->get_psi(2);
   
    auto mbdn = epmap->get(EventplaneinfoMap::MBDN);
    nep = mbdn->get_psi(2);
  
    _g.push_back(sep);
    _g.push_back(nep);
         
     GetmbdTowerInfo(_g);
         
    _g.clear();
    
    //std::cout<<"psi2 \t" << sep << "\t"<< nep << std::endl;

    std::cout<<_event<<std::endl;



  return 0;

}

int SimEP::End(PHCompositeNode *topNode)
{

  std::cout << " SimEP::End() " << std::endl;
  outputfile->Write();
  outputfile->Close();

  return 0;
    
}




double SimEP::GetmbdTowerInfo(std::vector < float > _n)
{
 
    for (int j = 0; j < 5; j++)
    {
        etower_info[j] = _n[j];
    }
 
    
    mbd->Fill(etower_info);

    return 0;

}
