#ifndef TEXT_FILE_PULSE_SHAPE_H
#define TEXT_FILE_PULSE_SHAPE_H


#include "IPulseShape.h"
#include <string>
#include <vector>

class TextFilePulseShape: public IPulseShape
{
  public:
    TextFilePulseShape(const char * shaperFile);
    virtual ~TextFilePulseShape() = default;

    virtual float GetResolution() const;
    virtual unsigned int GetOrigin() const;
    virtual std::vector<std::pair<float,float>> GetTimeSeries() const;

  protected:
    void ReadShaper();

    /*! Index where t = 0 */
    unsigned int m_origin;
    /*! The shaper time resolution in ns */
    float m_resolution;
    /*! The shaper configuration path */
    const char * m_shaperFile;
    /*! The shaper values */
    std::vector<std::pair<float,float>> m_pulseShape;
};

#endif /* TEXT_FILE_PULSE_SHAPE_H */
