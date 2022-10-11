/**
 * @file include/Random.h
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
#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace cps {
/**
 * @class Random
 * @brief Manage random number engine
 *
 * This class offers static functions to get the random number engine and set its seed.
 * It used a std::default_random_engine as the random number engine.
 */
class Random
  {
  public:
    static void Seed(unsigned int seed); //!< Set seed
    static std::default_random_engine& GetEngine(); //!< Get engine

  private:
    Random() = default; //!< Private constructor to avoid instanciation
    static std::default_random_engine m_randomEngine; //!< The random number generator

  // remove copy and move constructors and assign operators
  public:
    virtual ~Random() = default; //!< Destructor
    Random(const Random&) = delete; //!< Copy constructor
    Random(Random&&) = delete; //!< Move constructor
    Random& operator=(const Random&) = delete; //!< Copy assignment operator
    Random& operator=(Random&&) = delete; //!< Move assignment operator
  };
}

#endif /* RANDOM_H */
