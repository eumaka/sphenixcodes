// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef EVENTPLANE_EPFINDERRECO_H
#define EVENTPLANE_EPFINDERRECO_H

#include <fun4all/SubsysReco.h>

#include <string>
#include <vector>
#include <array>
#include <map>
#include <cmath>
#include <TH3.h>

//Forward declarations
class PHCompositeNode;
class EpFinder;
class EpInfo;

class EpFinderReco : public SubsysReco
{
 public:

  EpFinderReco(const std::string &name = "EpFinderReco");

  ~EpFinderReco() override;

  int Init(PHCompositeNode *) override;

  int process_event(PHCompositeNode *) override;

  int End(PHCompositeNode *) override;

  int ResetEvent(PHCompositeNode * /*topNode*/) override;

  void Detector(const std::string &d){ detector = d;}

  void set_truncation_filename(const std::string &fname) { truncationFile = fname; }
  
  void set_truncation_histname(const std::string &hname) { truncationHist = hname; }
  
  enum kCentrality {kBimp, kEPD, kMBD};
 
  void set_centralitytype(EpFinderReco::kCentrality CentType) { m_CentType = CentType; }
 
 private: 

  void GetEventPlanes(PHCompositeNode *);

  int GetNodes(PHCompositeNode *); 

  int CreateNodes(PHCompositeNode *);

  EpFinderReco::kCentrality m_CentType = EpFinderReco::kCentrality::kBimp; 

  std::string detector;

  std::string truncationFile;

  std::string truncationHist;

  EpFinder *_EpFinder[2] = {};

  EpInfo *_EpInfo;

  TH3* mTruncationInput;
  
  int cent_index = -1;
  
  std::string TowerNode = "TOWERINFO_CALIB_";

  std::string TowerGeomNode = "TOWERGEOM_";
  
  std::vector<std::pair<int,int>> Nepd_phi_list[16];
  std::vector<std::pair<int,int>> Sepd_phi_list[16];
  std::vector<std::pair<int,int>> Nepd_phi_list0[1];
  std::vector<std::pair<int,int>> Sepd_phi_list0[1];

};

#endif  //* EVENTPLANE_EPFINDERRECO_H *//
