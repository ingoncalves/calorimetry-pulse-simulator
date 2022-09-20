/**
 * @file include/IDigitizer.h
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
#ifndef I_DIGITIZER_H
#define I_DIGITIZER_H

#include "AnalogPulse.h"
#include <vector>

namespace cps {
/**
 * @class IDigitizer
 * @brief An interface for digitizers.
 *
 * This class defines the interface for digitizers. A digitizer converts analog
 * pulses to digital pulses.
 */
class IDigitizer
  {
  public:
    virtual ~IDigitizer() {} //!< Destructor
    virtual std::vector<double> Digitize(const AnalogPulse * pulse) const = 0; //!< Digitizes the given pulse
  };
}

#endif /* I_DIGITIZER_H */
