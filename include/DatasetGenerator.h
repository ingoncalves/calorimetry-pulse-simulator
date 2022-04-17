#ifndef DATASET_GENERATOR_H
#define DATASET_GENERATOR_H

#include "PulseGenerator.h"
#include <vector>
#include <random>

namespace cps {

class DatasetGenerator;

struct Dataset {
  std::vector<double> samples;
  std::vector<double> amplitudes;
  std::vector<double> phases;
};

class EventSchemeBlock {
public:
  friend DatasetGenerator;
  enum BlockType { ALLOWED_EVENTS, NOT_ALLOWED_EVENTS };
  inline EventSchemeBlock(): m_size(0), m_type(NOT_ALLOWED_EVENTS) {};
  inline EventSchemeBlock(int size, BlockType type): m_size(size), m_type(type) {};
private:
  int m_size;
  BlockType m_type;
};

class DatasetGenerator
  {
  public:
    DatasetGenerator();
    virtual ~DatasetGenerator() = default;

    // getters
    double                GetNoiseMean() const { return m_noiseMean; }
    double                GetNoiseStdDev() const { return m_noiseStdDev; }
    double                GetSamplingRate() const { return m_samplingRate; }
    double                GetOccupancy() const { return m_occupancy; }
    const PulseGenerator* GetPulseGenerator() const { return m_pulseGenerator; }
    // setters
    DatasetGenerator& SetPulseGenerator(const PulseGenerator * pulseGenerator);
    DatasetGenerator& SetNoiseParams(double noiseMean, double noiseStdDev);
    DatasetGenerator& SetSamplingRate(double samplingRate);
    DatasetGenerator& SetOccupancy(double occupancy);
    DatasetGenerator& SetEventsScheme(std::vector<EventSchemeBlock> eventsScheme);
    const Dataset*    GenerateContinuousDataset(unsigned int nEvents) const;
    // const Dataset*    GenerateSlicedDataset(unsigned int nEvents, unsigned int sliceSize) const;

    inline static EventSchemeBlock AllowedEventsBlock(int size) {
      return EventSchemeBlock(size, EventSchemeBlock::ALLOWED_EVENTS);
    }
    inline static EventSchemeBlock NotAllowedEventsBlock(int size) {
      return EventSchemeBlock(size, EventSchemeBlock::NOT_ALLOWED_EVENTS);
    }

  private:
    /*! Pulse shape */
    const PulseGenerator* m_pulseGenerator;
    /*! Sampling rate */
    double m_samplingRate;
    /*! Occupancy probability, between 0 and 1 */
    double m_occupancy;
    /*! Normal distribution mean of the noise */
    double m_noiseMean;
    /*! Normal distribution standard deviation of the noise */
    double m_noiseStdDev;
    /*! Default random engine */
    std::vector<EventSchemeBlock> m_eventsScheme;
    /*! Default random engine */
    mutable std::default_random_engine m_randomEngine;

    const std::vector<AnalogPulse*> GenerateEvents(unsigned int nEvents) const;
    const Dataset* SampleEvents(std::vector<AnalogPulse*> pulses) const;
    double         GenerateNoise() const;
  };
}

#endif /* DATASET_GENERATOR_H */
