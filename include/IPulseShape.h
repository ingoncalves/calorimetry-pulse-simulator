/**
 * @file include/IPulseShape.h
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
