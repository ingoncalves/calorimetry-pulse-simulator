# @file python/tests/dataset_generator_unittest.py
# @author Guilherme Inacio Goncalves <ggoncalves@iprj.uer.br>
# @copyright Copyright 2022, Guilherme Inacio Goncalves. All rights reserved.
#
# This file is part of CPS (Calorimetry Pulse Simulator).
#
# CPS is free software: you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or any later version.
#
# CPS is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# CPS. If not, see <https://www.gnu.org/licenses/>.
import sys
import os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../../build/python'))

import unittest
import pycps as lib

class DatasetGenerator(unittest.TestCase):

    def setUp(self):
        pulse_shape_file_path = "tests/fixtures/unipolar-pulse-shape.dat"
        self.pulse_shape = lib.TextFilePulseShape(pulse_shape_file_path)

    def test_construction(self):
        pedestal = 15.3
        deformation_level = 0.2
        pulse_generator = lib.PulseGenerator(self.pulse_shape)
        pulse_generator.set_pedestal(pedestal)
        pulse_generator.set_deformation_level(deformation_level)
        pulse_generator.set_noise_params(0, 0)
        pulse_generator.set_amplitude_distribution(lib.PulseGenerator.UNIFORM_INT_DISTRIBUTION, [80, 90])
        pulse_generator.set_phase_distribution(lib.PulseGenerator.NORMAL_DISTRIBUTION, [0, 4])

        noise_mean = 0.01
        noise_std_dev = 0.1
        occupancy = 0.5
        sampling_rate = 25.0
        dataset_generator = lib.DatasetGenerator()
        dataset_generator.set_occupancy(occupancy)
        dataset_generator.set_sampling_rate(sampling_rate)
        dataset_generator.set_noise_params(noise_mean, noise_std_dev)
        dataset_generator.set_pulse_generator(pulse_generator)

        self.assertEqual(dataset_generator.get_occupancy(), occupancy)
        self.assertEqual(dataset_generator.get_sampling_rate(), sampling_rate)
        self.assertEqual(dataset_generator.get_noise_mean(), noise_mean)
        self.assertEqual(dataset_generator.get_noise_std_dev(), noise_std_dev)

    def test_continuous_dataset(self):
        pulse_generator = lib.PulseGenerator(self.pulse_shape)
        pulse_generator.set_amplitude_distribution(lib.PulseGenerator.UNIFORM_INT_DISTRIBUTION, [10, 20])
        pulse_generator.set_phase_distribution(lib.PulseGenerator.UNIFORM_INT_DISTRIBUTION, [-4, 4])
        dataset_generator = lib.DatasetGenerator()
        dataset_generator.set_pulse_generator(pulse_generator)
        dataset_generator.set_occupancy(1)
        dataset_generator.set_sampling_rate(25.0)
        dataset_generator.set_events_scheme([lib.DatasetGenerator.allowed_events_block(5), lib.DatasetGenerator.not_allowed_events_block(10) ])

        n_events = 1000
        dataset = dataset_generator.generate_continuous_dataset(n_events)
        self.assertEqual(dataset.time.size(), n_events)
        self.assertEqual(dataset.samples.size(), n_events)
        self.assertEqual(dataset.amplitudes.size(), n_events)
        self.assertEqual(dataset.phases.size(), n_events)


    def test_sliced_dataset(self):
        pulse_generator = lib.PulseGenerator(self.pulse_shape)
        pulse_generator.set_amplitude_distribution(lib.PulseGenerator.UNIFORM_INT_DISTRIBUTION, [10, 20])
        pulse_generator.set_phase_distribution(lib.PulseGenerator.UNIFORM_INT_DISTRIBUTION, [-4, 4])
        dataset_generator = lib.DatasetGenerator()
        dataset_generator.set_pulse_generator(pulse_generator)
        dataset_generator.set_occupancy(1)
        dataset_generator.set_sampling_rate(25.0)
        dataset_generator.set_events_scheme([lib.DatasetGenerator.allowed_events_block(5), lib.DatasetGenerator.not_allowed_events_block(10) ])

        n_slices = 100
        slice_size = 7
        dataset = dataset_generator.generate_sliced_dataset(n_slices, slice_size)
        self.assertEqual(dataset.time.size(), n_slices)
        self.assertEqual(dataset.time[0].size(), slice_size)
        self.assertEqual(dataset.samples.size(), n_slices)
        self.assertEqual(dataset.samples[0].size(), slice_size)
        self.assertEqual(dataset.amplitudes.size(), n_slices)
        self.assertEqual(dataset.amplitudes[0].size(), slice_size)
        self.assertEqual(dataset.phases.size(), n_slices)
        self.assertEqual(dataset.phases[0].size(), slice_size)


if __name__ == '__main__':
    unittest.main()
