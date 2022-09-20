import sys
import os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../../build/python'))

import unittest
import pycps as lib

PULSE_SHAPE_FILE_PATH = "tests/fixtures/unipolar-pulse-shape.dat"

class AnalogPulse(unittest.TestCase):

    def test_construction(self):
        pulse_shape = lib.TextFilePulseShape(PULSE_SHAPE_FILE_PATH)
        amplitude = 1022.9
        pedestal = 15.3
        phase = 0.5
        deformation_level = 0.2
        noise_mean = 0.01
        noise_std_dev = 0.1
        analog_pulse = lib.AnalogPulse(
                pulse_shape,
                amplitude,
                pedestal,
                phase,
                deformation_level,
                noise_mean,
                noise_std_dev
                )

        self.assertEqual(analog_pulse.get_amplitude(), amplitude)
        self.assertEqual(analog_pulse.get_pedestal(), pedestal)
        self.assertEqual(analog_pulse.get_phase(), phase)
        self.assertEqual(analog_pulse.get_deformation_level(), deformation_level)
        self.assertEqual(analog_pulse.get_noise_mean(), noise_mean)
        self.assertEqual(analog_pulse.get_noise_std_dev(), noise_std_dev)

    def test_get_sample(self):
        pulse_shape = lib.TextFilePulseShape(PULSE_SHAPE_FILE_PATH)
        amplitude = 100
        pedestal = 50
        analog_pulse = lib.AnalogPulse(pulse_shape, amplitude, pedestal)
        self.assertEqual(
            analog_pulse.get_sample(0),
            pedestal + amplitude * pulse_shape.get_y(0)
        )

if __name__ == '__main__':
    unittest.main()
