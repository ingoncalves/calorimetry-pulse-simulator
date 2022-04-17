#ifndef I_PULSE_SHAPE_H
#define I_PULSE_SHAPE_H

#include <vector>

namespace cps {
class IPulseShape
  {
  public:
    virtual double GetY(const double & time) const = 0;
  };
}

#endif /* I_PULSE_SHAPE_H */
