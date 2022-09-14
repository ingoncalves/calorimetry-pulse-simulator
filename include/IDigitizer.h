#ifndef I_DIGITIZER_H
#define I_DIGITIZER_H

#include "AnalogPulse.h"
#include <vector>

namespace cps {
class IDigitizer
  {
  public:
    virtual ~IDigitizer() {}
    virtual std::vector<double> Digitize(const AnalogPulse * pulse) const = 0;
  };
}

#endif /* I_DIGITIZER_H */
