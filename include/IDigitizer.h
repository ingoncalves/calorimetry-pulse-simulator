#ifndef I_DIGITIZER_H
#define I_DIGITIZER_H

#include "AnalogPulse.h"
#include <vector>

class IDigitizer
{
  public:
    virtual std::vector<double> Digitize(const AnalogPulse * pulse) const = 0;
};

#endif /* I_DIGITIZER_H */
