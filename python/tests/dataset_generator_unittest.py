import sys
import os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../../build/python'))

import unittest
import pyCaloPulseSimulator as lib

PULSE_SHAPE_FILE_PATH = "tests/fixtures/unipolar-pulse-shape.dat"

class DatasetGenerator(unittest.TestCase):

    def test_construction(self):
        pulse_shape = lib.TextFilePulseShape(PULSE_SHAPE_FILE_PATH)

        pedestal = 15.3
        deformation_level = 0.2
        pulse_generator = lib.PulseGenerator(pulse_shape)\
            .set_pedestal(pedestal)\
            .set_deformation_level(deformation_level)\
            .set_noise_params(0, 0)\
            .set_amplitude_distribution(lib.PulseGenerator.UNIFORM_INT_DISTRIBUTION, [80, 90])\
            .set_phase_distribution(lib.PulseGenerator.NORMAL_DISTRIBUTION, [0, 4])

        noise_mean = 0.01
        noise_std_dev = 0.1
        occupancy = 0.5
        sampling_rate = 25.0
        dataset_generator = lib.DatasetGenerator()\
            .set_occupancy(occupancy)\
            .set_sampling_rate(sampling_rate)\
            .set_noise_params(noise_mean, noise_std_dev)\
            .set_pulse_generator(pulse_generator)

        self.assertEqual(dataset_generator.get_occupancy(), occupancy)
        self.assertEqual(dataset_generator.get_sampling_rate(), sampling_rate)
        self.assertEqual(dataset_generator.get_noise_mean(), noise_mean)
        self.assertEqual(dataset_generator.get_noise_std_dev(), noise_std_dev)

    def test_continuous_dataste(self):
        pulse_shape = lib.TextFilePulseShape(PULSE_SHAPE_FILE_PATH)
        pulse_generator = lib.PulseGenerator(pulse_shape)
        pulse_generator.set_amplitude_distribution(lib.PulseGenerator.UNIFORM_INT_DISTRIBUTION, [10, 20])
        pulse_generator.set_phase_distribution(lib.PulseGenerator.UNIFORM_INT_DISTRIBUTION, [-4, 4])
        dataset_generator = lib.DatasetGenerator()
        dataset_generator.set_pulse_generator(pulse_generator)
        dataset_generator.set_occupancy(1)
        dataset_generator.set_sampling_rate(25.0)
        dataset_generator.set_events_scheme([lib.DatasetGenerator.allowed_events_block(5), lib.DatasetGenerator.not_allowed_events_block(10) ])

        n_events = 1000
        dataset = dataset_generator.generate_continuous_dataset(n_events)
        self.assertEqual(dataset.samples.size(), n_events)
        self.assertEqual(dataset.amplitudes.size(), n_events)
        self.assertEqual(dataset.phases.size(), n_events)



if __name__ == '__main__':
    unittest.main()
