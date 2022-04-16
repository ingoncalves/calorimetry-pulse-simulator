#include "TextFilePulseShape.h"
#include <stdexcept>
#include <fstream>

TextFilePulseShape::TextFilePulseShape(const char* shaperFile) :
  m_shaperFile(shaperFile),
  m_resolution(0)
{
  ReadShaper();
}

float TextFilePulseShape::GetResolution() const {
  return m_resolution;
}

unsigned int TextFilePulseShape::GetSize() const {
  return m_ySeries.size();
}

void TextFilePulseShape::ReadShaper() {
  m_tSeries.clear();
  m_ySeries.clear();

  /*! open file */
  std::ifstream file;
  file.open(m_shaperFile);

  if (file) {
    double time, sample;
    while (file >> time >> sample) // loop on the input operation, not eof
    {
      m_tSeries.push_back(time);
      m_ySeries.push_back(sample);
    }
  } else {
    throw std::invalid_argument("Invalid shaper path: " + std::string(m_shaperFile));
  }

  /*! close file */
  file.close();

  /*! calculate shaper resolution */
  m_resolution = m_tSeries.size() > 2 ?
    m_tSeries[1] - m_tSeries[0] :
    0;
}
