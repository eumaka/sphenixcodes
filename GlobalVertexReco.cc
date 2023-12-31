#include "GlobalVertexReco.h"

#include "GlobalVertex.h"     // for GlobalVertex, GlobalVe...
#include "GlobalVertexMap.h"  // for GlobalVertexMap
#include "GlobalVertexMapv1.h"
#include "GlobalVertexv1.h"

#include <bbc/BbcVertex.h>
#include <bbc/BbcVertexMap.h>

#include <trackbase_historic/SvtxTrack.h>
#include <trackbase_historic/SvtxTrackMap.h>
#include <trackbase_historic/SvtxVertex.h>
#include <trackbase_historic/SvtxVertexMap.h>

#include <fun4all/Fun4AllReturnCodes.h>
#include <fun4all/SubsysReco.h>  // for SubsysReco

#include <phool/PHCompositeNode.h>
#include <phool/PHIODataNode.h>
#include <phool/PHNode.h>  // for PHNode
#include <phool/PHNodeIterator.h>
#include <phool/PHObject.h>  // for PHObject
#include <phool/getClass.h>
#include <phool/phool.h>  // for PHWHERE

#include <cfloat>
#include <cmath>
#include <cstdlib>  // for exit
#include <iostream>
#include <set>      // for _Rb_tree_const_iterator
#include <utility>  // for pair

using namespace std;

GlobalVertexReco::GlobalVertexReco(const string &name)
  : SubsysReco(name)
{
}

int GlobalVertexReco::InitRun(PHCompositeNode *topNode)
{
  if (Verbosity() > 0)
  {
    cout << "======================= GlobalVertexReco::InitRun() =======================" << endl;
    cout << "===========================================================================" << endl;
  }

  return CreateNodes(topNode);
}

int GlobalVertexReco::process_event(PHCompositeNode *topNode)
{
  if (Verbosity() > 1)
  {
    cout << "GlobalVertexReco::process_event -- entered" << endl;
  }

  //---------------------------------
  // Get Objects off of the Node Tree
  //---------------------------------
  GlobalVertexMap *globalmap = findNode::getClass<GlobalVertexMap>(topNode, "GlobalVertexMap");
  if (!globalmap)
  {
    cout << PHWHERE << "::ERROR - cannot find GlobalVertexMap" << endl;
    exit(-1);
  }

  BbcVertexMap *bbcmap = findNode::getClass<BbcVertexMap>(topNode, "BbcVertexMap");

  std::set<unsigned int> used_svtx_vtxids;
  std::set<unsigned int> used_bbc_vtxids;
 

 
  // okay now loop over all unused BBC vertexes (3rd class)...
  if (bbcmap)
  {
    if (Verbosity())
    {
      cout << "GlobalVertexReco::process_event -  bbcmap" << endl;
    }

    for (BbcVertexMap::ConstIter bbciter = bbcmap->begin();
         bbciter != bbcmap->end();
         ++bbciter)
    {
      const BbcVertex *bbc = bbciter->second;

      if (used_bbc_vtxids.find(bbc->get_id()) != used_bbc_vtxids.end())
      {
        continue;
      }
      if (isnan(bbc->get_z()))
      {
        continue;
      }

      GlobalVertex *vertex = new GlobalVertexv1(GlobalVertex::VTXTYPE::BBC);
      vertex->set_id(globalmap->size());

      // nominal beam location
      // could be replaced with a beam spot some day
      vertex->set_x(_xdefault);
      vertex->set_y(_ydefault);
      vertex->set_z(bbc->get_z());

      vertex->set_t(bbc->get_t());
      vertex->set_t_err(bbc->get_t_err());

      vertex->set_error(0, 0, pow(_xerr, 2));
      vertex->set_error(0, 1, 0.0);
      vertex->set_error(0, 2, 0.0);

      vertex->set_error(1, 0, 0.0);
      vertex->set_error(1, 1, pow(_yerr, 2));
      vertex->set_error(1, 2, 0.0);

      vertex->set_error(0, 2, 0.0);
      vertex->set_error(1, 2, 0.0);
      vertex->set_error(2, 2, pow(bbc->get_z_err(), 2));

      vertex->insert_vtxids(GlobalVertex::BBC, bbc->get_id());
      used_bbc_vtxids.insert(bbc->get_id());

      globalmap->insert(vertex);

      if (Verbosity() > 1)
      {
        vertex->identify();
      }
    }
  }


  if (Verbosity())
  {
    globalmap->identify();
  }
  return Fun4AllReturnCodes::EVENT_OK;
}

int GlobalVertexReco::CreateNodes(PHCompositeNode *topNode)
{
  PHNodeIterator iter(topNode);

  // Looking for the DST node
  PHCompositeNode *dstNode = dynamic_cast<PHCompositeNode *>(iter.findFirst("PHCompositeNode", "DST"));
  if (!dstNode)
  {
    cout << PHWHERE << "DST Node missing, doing nothing." << endl;
    return Fun4AllReturnCodes::ABORTRUN;
  }

  // store the GLOBAL stuff under a sub-node directory
  PHCompositeNode *globalNode = dynamic_cast<PHCompositeNode *>(iter.findFirst("PHCompositeNode", "GLOBAL"));
  if (!globalNode)
  {
    globalNode = new PHCompositeNode("GLOBAL");
    dstNode->addNode(globalNode);
  }

  // create the GlobalVertexMap
  GlobalVertexMap *vertexes = findNode::getClass<GlobalVertexMap>(topNode, "GlobalVertexMap");
  if (!vertexes)
  {
    vertexes = new GlobalVertexMapv1();
    PHIODataNode<PHObject> *VertexMapNode = new PHIODataNode<PHObject>(vertexes, "GlobalVertexMap", "PHObject");
    globalNode->addNode(VertexMapNode);
  }
  return Fun4AllReturnCodes::EVENT_OK;
}
