#ifndef I_PULSE_SHAPE_H
#define I_PULSE_SHAPE_H

#include <vector>

class IPulseShape
{
  public:
    IPulseShape() = default;
    virtual ~IPulseShape() = default;
    double GetY(const double & time) const;
    std::vector<double> GetTimeSeries() const { return m_tSeries; }
    std::vector<double> GetYSeries() const { return m_ySeries; }
    virtual float GetResolution() const = 0;
    virtual unsigned int GetSize() const = 0;
  protected:
    std::vector<double> m_ySeries;
    std::vector<double> m_tSeries;
  private:
    unsigned int TimeToIndex(const double & time) const;
};

#endif /* I_PULSE_SHAPE_H */
