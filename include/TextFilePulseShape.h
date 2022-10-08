/**
 * @file include/TextFilePulseShape.h
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
#ifndef TEXT_FILE_PULSE_SHAPE_H
#define TEXT_FILE_PULSE_SHAPE_H


#include "IPulseShape.h"
#include <string>
#include <vector>

namespace cps {
/**
 * @class TextFilePulseShape
 * @brief A pulse shape that is read from a text file.
 *
 * The text file should contain two columns of numbers. The first column is the
 * time, and the second column is the amplitude. The amplitude should be
 * normalized to 1.0 at the peak of the pulse.
 */
class TextFilePulseShape: public IPulseShape
  {
  public:
    TextFilePulseShape(const char * shaperFile); //!< Constructor
    ~TextFilePulseShape(); //!< Destructor

    float               GetResolution() const; //!< Returns the resolution of the pulse shape
    unsigned int        GetSize() const; //!< Returns the number of points in the pulse shape
    std::vector<double> GetTimeSeries() const { return m_tSeries; } //!< Returns the time series of the pulse shape
    std::vector<double> GetYSeries() const { return m_ySeries; } //!< Returns the ampltitude series of the pulse shape
    virtual double      GetY(const double & time) const; //!< Returns the amplitude of the pulse shape at the given time
    virtual double      GetTMin() const; //!< Returns the minimum time of the pulse shape
    virtual double      GetTMax() const; //!< Returns the maximum time of the pulse shape

  protected:
    void ReadShaper(); //!< Reads the pulse shape from the text file

    float m_resolution; //!< The resolution of the pulse shape
    const char * m_shaperFile; //!< The path to the text file containing the pulse shape
    std::vector<double> m_tSeries; //!< The time series
    std::vector<double> m_ySeries; //!< The amplitude series

  private:
    unsigned int TimeToIndex(const double & time) const; //!< Converts a time to an index in the pulse shape
  };
}

#endif /* TEXT_FILE_PULSE_SHAPE_H */
