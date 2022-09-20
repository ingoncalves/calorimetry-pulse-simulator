#ifndef I_PULSE_SHAPE_H
#define I_PULSE_SHAPE_H

#include <vector>

namespace cps {
/**
 * @class IPulseShape
 * @brief An interface for pulse shapes.
 *
 * This class defines the interface for pulse shapes. A pulse shape is a
 * mathematical function of time that describes the shape of a pulse. The pulse
 * shape should be normalized to 1.0 at the peak of the pulse.
 */
class IPulseShape
  {
  public:
    virtual ~IPulseShape() {} //!< Destructor
    virtual double GetY(const double & time) const = 0; //!< Returns the amplitude of the pulse shape at the given time
    virtual double GetTMin() const = 0; //!< Returns the minimum time of the pulse shape
    virtual double GetTMax() const = 0; //!< Returns the maximum time of the pulse shape
  };
}

#endif /* I_PULSE_SHAPE_H */
