#ifndef EVENTPLANE_EPINFOV1_H
#define EVENTPLANE_EPINFOV1_H

#include "EpInfo.h"

#include <utility>  // for pair
#include <vector>   // for vector
#include <map>

class EpInfov1 : public EpInfo
{

 public:

  EpInfov1() {}

  ~EpInfov1() override{/* no op */};

  void Reset() override;
    
  virtual unsigned int maxsize() const override { return _psi.size(); }
    
  virtual  unsigned int get_ep_key(const int det, const int maxorder, const int thisorder) override;

  virtual  int get_det_key(const detName detname) override;

  virtual void set_psi(unsigned int key, double f) override {_psi[key] = f;}
    
  virtual double get_psi(const int thisorder, const detName detname) override;
    
  virtual void set_q(unsigned int key, std::vector<std::vector<double>> q) override {_q[key] = q;}

  virtual std::pair<double, double> get_q(const int thisorder, const detName detname) override;


  private:
  
  int thisdetep = 0;
  std::map < int, double > _psi;
  std::map < int, std::vector<std::vector<double>> > _q;
  std::vector<std::vector<double>> QrawOneSide;
  std::vector<std::vector<double>> PsiRaw;


  ClassDefOverride(EpInfov1, 1);
};

#endif  // EVENTPLANE_EPINFOV1_H
