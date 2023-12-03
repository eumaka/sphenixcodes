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
class TProfile;
class TFile;

class EventPlaneReco : public SubsysReco
{
 public:
  EventPlaneReco(const std::string &name = "EventPlaneReco");
  ~EventPlaneReco() override = default;
  int Init(PHCompositeNode *topNode) override;
  int InitRun(PHCompositeNode *topNode) override;
  int process_event(PHCompositeNode *topNode) override;
  int End (PHCompositeNode * /*topNode*/) override;

  void ResetMe();
  void set_sepd_epreco(bool sepdEpReco)
  {
    _sepdEpReco = sepdEpReco;
  }
  void set_mbd_epreco(bool mbdEpReco)
  {
    _mbdEpReco = mbdEpReco;
  }
  void set_sEPD_Mip_cut(const float &e)
  {
    _epd_e = e;
  }
  void set_Ep_orders(const unsigned int &n)
  {
    m_MaxOrder = n;
  }
 
 private:
    
  int CreateNodes(PHCompositeNode *topNode);
  const char *OutFileName = "Correction_histograms.root";
    
  unsigned int m_MaxOrder = 3;

  std::vector<std::vector<double>> south_q;
  std::vector<std::vector<double>> north_q;
  std::vector<std::vector<double>> south_q_subtract;
  std::vector<std::vector<double>> north_q_subtract;

  std::vector<std::pair<double, double>> south_Qvec;
  std::vector<std::pair<double, double>> north_Qvec;
    
  std::vector<double> mean_cos_south;
  std::vector<double> mean_sin_south;
  std::vector<double> mean_cos_north;
  std::vector<double> mean_sin_north;

  bool _mbdEpReco = false;
  bool _sepdEpReco = false;
    
  float _epd_e  = 6.0;
  float mbd_e_north;
  float mbd_e_south;
    
  TFile *outputfile;
    
  TProfile * tprof_mean_cos_north_mbd[6] = {};
  TProfile * tprof_mean_sin_north_mbd[6] = {};
  TProfile * tprof_mean_cos_south_mbd[6] = {};
  TProfile * tprof_mean_sin_south_mbd[6] = {};
    
  TProfile * tprof_mean_cos_north_mbd_input[6] = {};
  TProfile * tprof_mean_sin_north_mbd_input[6] = {};
  TProfile * tprof_mean_cos_south_mbd_input[6] = {};
  TProfile * tprof_mean_sin_south_mbd_input[6] = {};
    
};

#endif  // EVENTPLANERECO_H
