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
    virtual unsigned int GetSize() const;

  protected:
    void ReadShaper();

    /*! The shaper time resolution in ns */
    float m_resolution;
    /*! The shaper configuration path */
    const char * m_shaperFile;
};

#endif /* TEXT_FILE_PULSE_SHAPE_H */
