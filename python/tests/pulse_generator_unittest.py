# @file python/tests/pulse_generator_unittest.py
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

class PulseGenerator(unittest.TestCase):

    def setUp(self):
        pulse_shape_file_path = "tests/fixtures/unipolar-pulse-shape.dat"
        self.pulse_shape = lib.TextFilePulseShape(pulse_shape_file_path)

    def test_construction(self):
        pedestal = 15.3
        deformation_level = 0.2
        noise_mean = 0.01
        noise_std_dev = 0.1

        pulse_generator = lib.PulseGenerator(self.pulse_shape)
        pulse_generator.set_pedestal(pedestal)
        pulse_generator.set_deformation_level(deformation_level)
        pulse_generator.set_noise_params(noise_mean, noise_std_dev)
        pulse_generator.set_amplitude_distribution(lib.PulseGenerator.UNIFORM_INT_DISTRIBUTION, [80, 90])
        pulse_generator.set_phase_distribution(lib.PulseGenerator.NORMAL_DISTRIBUTION, [0, 4])

        self.assertEqual(pulse_generator.get_pedestal(), pedestal)
        self.assertEqual(pulse_generator.get_deformation_level(), deformation_level)
        self.assertEqual(pulse_generator.get_noise_mean(), noise_mean)
        self.assertEqual(pulse_generator.get_noise_std_dev(), noise_std_dev)
        self.assertEqual(pulse_generator.get_amplitude_distribution(), lib.PulseGenerator.UNIFORM_INT_DISTRIBUTION)
        self.assertEqual(pulse_generator.get_phase_distribution(), lib.PulseGenerator.NORMAL_DISTRIBUTION)

    def test_generate_pulse(self):
        pulse_generator = lib.PulseGenerator(self.pulse_shape)
        pulse_generator.set_amplitude_distribution(lib.PulseGenerator.UNIFORM_INT_DISTRIBUTION, [10, 20])
        pulse_generator.set_phase_distribution(lib.PulseGenerator.UNIFORM_INT_DISTRIBUTION, [-4, 4])

        # deterministic values
        deterministic_amplitude = 500
        deterministic_phase = 1.0
        analog_pulse = pulse_generator.generate_pulse(deterministic_amplitude, deterministic_phase)
        self.assertEqual(analog_pulse.get_sample(-1), deterministic_amplitude)

        # random values
        analog_pulse = pulse_generator.generate_pulse()
        self.assertGreaterEqual(analog_pulse.get_amplitude(), 10)
        self.assertLessEqual(analog_pulse.get_amplitude(), 20)
        self.assertGreaterEqual(analog_pulse.get_phase(), -4)
        self.assertLessEqual(analog_pulse.get_phase(), 4)



if __name__ == '__main__':
    unittest.main()
