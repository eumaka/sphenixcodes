// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef EVENTPLANERECO_H
#define EVENTPLANERECO_H

//===========================================================
/// \author Ejiro Umaka
//===========================================================

#include <fun4all/SubsysReco.h>

#include <string>  // for string
#include <vector>  // for vector

class PHCompositeNode;

class EventPlaneReco : public SubsysReco
{
 public:
  EventPlaneReco(const std::string &name = "EventPlaneReco");
  ~EventPlaneReco() override = default;

  int InitRun(PHCompositeNode *topNode) override;
  int process_event(PHCompositeNode *topNode) override;
  void ResetMe();


 private:
  int CreateNodes(PHCompositeNode *topNode);   
  unsigned int m_MaxOrder = 0;
    
  //std::vector<double> south_norm;
  std::vector<std::vector<double>> south_q;
 
  
  //std::vector<double> north_norm;
  std::vector<std::vector<double>> north_q;
  
  std::vector<std::pair<double,double>> south_Qvec;  
  std::vector<std::pair<double,double>> north_Qvec;  
};

#endif  // EVENTPLANERECO_H
