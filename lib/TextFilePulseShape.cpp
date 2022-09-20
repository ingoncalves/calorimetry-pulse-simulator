/**
 * @file lib/TextFilePulseShape.cpp
 * @author Guilherme Inacio Goncalves <ggoncalves@iprj.uer.br>
 * @copyright Copyright 2022, Guilherme Inacio Goncalves. All rights reserved.
 *
 * This file is part of CPS (Calorimetry Pulse Simulator).
 *
 * CPS is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or any later version.
 *
 * CPS is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * CPS. If not, see <https://www.gnu.org/licenses/>.
 */
#include "TextFilePulseShape.h"
#include <stdexcept>
#include <fstream>

using namespace cps;

TextFilePulseShape::TextFilePulseShape(const char* shaperFile) :
  m_shaperFile(shaperFile),
  m_resolution(0)
{
  ReadShaper();
}

TextFilePulseShape::~TextFilePulseShape() {
  m_tSeries.clear();
  m_ySeries.clear();
}

float TextFilePulseShape::GetResolution() const {
  return m_resolution;
}

unsigned int TextFilePulseShape::GetSize() const {
  return m_ySeries.size();
}

unsigned int TextFilePulseShape::TimeToIndex(const double & time) const {
  auto timeAnchor = std::lower_bound(m_tSeries.begin(), m_tSeries.end(), time);
  unsigned int timeIndex = timeAnchor != m_tSeries.end()
    ? std::distance(m_tSeries.begin(), timeAnchor)
    : m_tSeries.size() - 1;
  return timeIndex;
}

double TextFilePulseShape::GetTMin() const {
  return m_tSeries[0];
}

double TextFilePulseShape::GetTMax() const {
  return m_tSeries[m_tSeries.size() - 1];
}

double TextFilePulseShape::GetY(const double & time) const {
  if (m_tSeries.size() == 0 || m_ySeries.size() == 0) return 0;
  unsigned int timeIndex = TimeToIndex(time);
  return m_ySeries[timeIndex];
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
