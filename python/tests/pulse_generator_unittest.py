import sys
import os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../../build/python'))

import unittest
import pyCaloPulseSimulator as lib

class PulseGenerator(unittest.TestCase):

    def setUp(self):
        pulse_shape_file_path = "tests/fixtures/unipolar-pulse-shape.dat"
        self.pulse_shape = lib.TextFilePulseShape(pulse_shape_file_path)

    def test_construction(self):
        pedestal = 15.3
        deformation_level = 0.2
        noise_mean = 0.01
        noise_std_dev = 0.1

        pulse_generator = lib.PulseGenerator(self.pulse_shape)\
                             .set_pedestal(pedestal)\
                             .set_deformation_level(deformation_level)\
                             .set_noise_params(noise_mean, noise_std_dev)\
                             .set_amplitude_distribution(lib.PulseGenerator.UNIFORM_INT_DISTRIBUTION, [80, 90])\
                             .set_phase_distribution(lib.PulseGenerator.NORMAL_DISTRIBUTION, [0, 4])

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
