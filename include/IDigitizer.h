#ifndef I_DIGITIZER_H
#define I_DIGITIZER_H

#include "AnalogPulse.h"
#include <vector>

namespace cps {
/**
 * @class IDigitizer
 * @brief An interface for digitizers.
 *
 * This class defines the interface for digitizers. A digitizer converts analog
 * pulses to digital pulses.
 */
class IDigitizer
  {
  public:
    virtual ~IDigitizer() {} //!< Destructor
    virtual std::vector<double> Digitize(const AnalogPulse * pulse) const = 0; //!< Digitizes the given pulse
  };
}

#endif /* I_DIGITIZER_H */
