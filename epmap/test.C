#include <eventplaneinfo/Eventplaneinfo.h>
#include <eventplaneinfo/EventplaneinfoMap.h>


int test::process_event(PHCompositeNode *topNode)
{

  EventplaneinfoMap *epmap = findNode::getClass<EventplaneinfoMap>(topNode, "EventplaneinfoMap");
    if (!epmap)
    {
       std::cout << PHWHERE << "::ERROR - cannot find EventplaneinfoMap" << std::endl;
         exit(-1);
    }

  auto epds = epmap->get(EventplaneinfoMap::sEPDS);
  float sep = epds->get_psi(2); 

  std::pair<double, double> m;
   m = epds->get_flowvector(2);


  auto epdn = epmap->get(EventplaneinfoMap::sEPDN);
  float nep = epdn->get_psi(2);

  return 0;
    
}
