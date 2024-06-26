/**
 * @file include/DatasetGenerator.h
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
#ifndef DATASET_GENERATOR_H
#define DATASET_GENERATOR_H

#include "PulseGenerator.h"
#include <vector>
#include <random>

namespace cps {
/**
 * @class DatasetGenerator
 * @brief A class that generates a dataset of pulses.
 *
 * This class generates a dataset of pulses. The pulses are generated using the
 * PulseGenerator class. It generates both continuous and sliced datasets.
 * This generator has also the ability to simulate signal pileup.
 */
class DatasetGenerator;

/**
 * @struct ContinuousDataset
 * @brief A struct that contains a continuous dataset.
 *
 * This struct contains a continuous dataset. The dataset is composed of the
 * following vectors:
 *   - time: the time coordinate of the signal at a given index;
 *   - samples: the sample coordinate of the signal at a given index plus the noise;
 *   - amplitudes: the truth amplitude value at a given index;
 *   - phases: the truth phase value at a given index;
 *   - noise: the background noise;
 */
struct ContinuousDataset {
  std::vector<double> time; //!< The time series of the dataset
  std::vector<double> samples; //!< The samples of the dataset
  std::vector<double> amplitudes; //!< The amplitudes of the pulses in the dataset
  std::vector<double> phases; //!< The phases of the pulses in the dataset
  std::vector<double> noise; //!< The background noise in the dataset
};

/**
 * @struct SlicedDataset
 * @brief A struct that contains a sliced dataset.
 *
 * This struct contains a sliced dataset. The dataset is composed of the following
 * matrices: time, samples, ampltitudes, phases, and noise.
 * Each matrix has a number of rows equal to the number of pulses in the
 * dataset, and a number of columns equal to the slice size. Please, refer to the
 * ContinuousDataset struct for more information about the dataset.
 * */
struct SlicedDataset {
  std::vector<std::vector<double>> time;
  std::vector<std::vector<double>> samples;
  std::vector<std::vector<double>> amplitudes;
  std::vector<std::vector<double>> phases;
  std::vector<std::vector<double>> noise;
};

/**
 * @class EventSchemeBlock
 * @brief A class that contains a block of events.
 *
 * This class contains scheme of the events block, which is the way the events
 * are distributed in the dataset. A scheme is a cyclic vector of blocks, where
 * each block contains the number of events that will be generated following the
 * block rule. A block can allow or disallow the generation of an event. The
 * scheme is used to generate the dataset.
 */
class EventSchemeBlock {
public:
  friend DatasetGenerator;
  enum BlockType {
    ALLOWED_EVENTS, //!< The block allows the generation of events
    NOT_ALLOWED_EVENTS //!< The block disallows the generation of events
  };
  inline EventSchemeBlock(): m_size(0), m_type(NOT_ALLOWED_EVENTS) {}; //!< Constructor
  inline EventSchemeBlock(int size, BlockType type): m_size(size), m_type(type) {}; //!< Constructor
private:
  int m_size; //!< The size of the block
  BlockType m_type; //!< The type of the block
};

class DatasetGenerator
  {
  public:
    DatasetGenerator(); //!< Constructor
    virtual ~DatasetGenerator() = default; //!< Destructor

    // getters
    double                   GetNoiseMean() const { return m_noiseMean; } //!< Returns the mean of the noise
    double                   GetNoiseStdDev() const { return m_noiseStdDev; } //!< Returns the standard deviation of the noise
    double                   GetSamplingRate() const { return m_samplingRate; } //!< Returns the sampling rate
    double                   GetOccupancy() const { return m_occupancy; } //!< Returns the occupancy
    const PulseGenerator*    GetPulseGenerator() const { return m_pulseGenerator; } //!< Returns the pulse generator
    // setters
    void                     SetPulseGenerator(const PulseGenerator * pulseGenerator); //!< Sets the pulse generator
    void                     SetNoiseParams(double noiseMean, double noiseStdDev); //!< Sets the noise parameters
    void                     SetSamplingRate(double samplingRate); //!< Sets the sampling rate
    void                     SetOccupancy(double occupancy); //!< Sets the occupancy
    void                     SetEventsScheme(std::vector<EventSchemeBlock> eventsScheme); //!< Sets the events scheme
    // methods
    const ContinuousDataset* GenerateContinuousDataset(unsigned int nEvents) const; //!< Generates a continuous dataset
    const SlicedDataset*     GenerateSlicedDataset(unsigned int nSlices, unsigned int sliceSize) const; //!< Generates a sliced dataset

    inline static EventSchemeBlock AllowedEventsBlock(int size) { //!< Returns an allowed events block
      return EventSchemeBlock(size, EventSchemeBlock::ALLOWED_EVENTS);
    }
    inline static EventSchemeBlock NotAllowedEventsBlock(int size) { //!< Returns a not allowed events block
      return EventSchemeBlock(size, EventSchemeBlock::NOT_ALLOWED_EVENTS);
    }

  private:
    const PulseGenerator* m_pulseGenerator; //!< The pulse generator
    double m_samplingRate; //!< The sampling rate
    double m_occupancy; //!< The occupancy between 0 and 1, the probability of generating an event at a given time
    double m_noiseMean; //!< The mean of the gaussian noise
    double m_noiseStdDev; //!< The standard deviation of the gaussian noise
    std::vector<EventSchemeBlock> m_eventsScheme; //!< The events scheme

    const std::vector<AnalogPulse*> GenerateEvents(unsigned int nEvents) const; //!< Generates a vector of events
    const ContinuousDataset* SampleEvents(std::vector<AnalogPulse*> pulses) const; //!< Samples a vector of events
    double GenerateNoise() const; //!< Generates a noise sample
  };
} // namespace cps

#endif /* DATASET_GENERATOR_H */
