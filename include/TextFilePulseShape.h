#ifndef TEXT_FILE_PULSE_SHAPE_H
#define TEXT_FILE_PULSE_SHAPE_H


#include "IPulseShape.h"
#include <string>
#include <vector>

namespace cps {
class TextFilePulseShape: public IPulseShape
  {
  public:
    TextFilePulseShape(const char * shaperFile);
    ~TextFilePulseShape();

    float               GetResolution() const;
    unsigned int        GetSize() const;
    std::vector<double> GetTimeSeries() const { return m_tSeries; }
    std::vector<double> GetYSeries() const { return m_ySeries; }
    virtual double      GetY(const double & time) const;
    virtual double      GetTMin() const;
    virtual double      GetTMax() const;

  protected:
    void ReadShaper();

    /*! The shaper time resolution in ns */
    float m_resolution;
    /*! The shaper configuration path */
    const char * m_shaperFile;
    /*! The time series */
    std::vector<double> m_tSeries;
    /*! The shaper values of each time coordinate */
    std::vector<double> m_ySeries;

  private:
    unsigned int TimeToIndex(const double & time) const;
  };
}

#endif /* TEXT_FILE_PULSE_SHAPE_H */
