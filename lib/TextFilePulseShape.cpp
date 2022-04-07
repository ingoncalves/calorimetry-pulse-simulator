#include "TextFilePulseShape.h"
#include <stdexcept>
#include <fstream>

TextFilePulseShape::TextFilePulseShape(const char* shaperFile) :
  m_shaperFile(shaperFile),
  m_origin(0),
  m_resolution(0)
{
  ReadShaper();
}

float TextFilePulseShape::GetResolution() const {
  return m_resolution;
}

unsigned int TextFilePulseShape::GetOrigin() const {
  return m_origin;
}

std::vector<std::pair<float,float>> TextFilePulseShape::GetTimeSeries() const {
  return m_pulseShape;
}

void TextFilePulseShape::ReadShaper() {
  m_pulseShape.clear();

  /*! open file */
  std::ifstream file;
  file.open(m_shaperFile);

  if (file) {
    unsigned int i = 0;
    float time, sample;
    while (file >> time >> sample) // loop on the input operation, not eof
    {
      m_pulseShape.push_back(std::make_pair(time, sample));
      if (time == 0.0) m_origin = i;
      i++;
    }
  } else {
    throw std::invalid_argument("Invalid shaper path: " + std::string(m_shaperFile));
  }

  /*! close file */
  file.close();

  /*! calculate shaper resolution */
  m_resolution = m_pulseShape.size() > 2 ?
    m_pulseShape[1].first - m_pulseShape[0].first :
    m_pulseShape[0].first;
}
