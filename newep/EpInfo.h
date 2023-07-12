#ifndef EVENTPLANE_EPINFO_H
#define EVENTPLANE_EPINFO_H

#include <phool/PHObject.h>
#include <cmath>

class EpInfo : public PHObject
{
 public:
  EpInfo() {}
  ~EpInfo() override {}

  void Reset() override { return; }
  
  enum detName {epd_S, epd_N, mbd_S, mbd_N};
    
  virtual unsigned int maxsize() const { return 0; }
    
  virtual  int get_det_key(const detName /*detname*/) { return 0; }

  virtual  unsigned int get_ep_key(const int /*det*/, const int /*maxorder*/, const int /*thisorder*/) {return 0;}

  virtual void set_psi(unsigned int /*key*/, double /*f*/) {return;}
    
  virtual double get_psi(const int /*thisorder*/, const detName /*detname*/) {return NAN;}

  virtual void set_q(unsigned int /*key*/, std::vector<std::vector<double>> /*q*/) {return;}

  virtual std::pair<double, double> get_q(const int /*thisorder*/, const detName /*detname*/) { return std::make_pair(NAN, NAN); }

 private:

 ClassDefOverride(EpInfo, 1);
};

#endif  // EVENTPLANE_EPINFO_H
