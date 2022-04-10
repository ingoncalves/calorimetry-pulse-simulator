#ifndef I_PULSE_SHAPE_H
#define I_PULSE_SHAPE_H

#include <vector>

class IPulseShape
{
  public:
    virtual float GetResolution() const = 0;
    virtual unsigned int GetOrigin() const = 0;
    virtual unsigned int GetSize() const = 0;
    virtual std::vector<std::pair<float,float>> GetTimeSeries() const = 0;
};

#endif /* I_PULSE_SHAPE_H */
