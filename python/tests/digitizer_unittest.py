import sys
import os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../../build/python'))

import unittest
import pyCaloPulseSimulator as lib

PULSE_SHAPE_FILE_PATH = "tests/fixtures/unipolar-pulse-shape.dat"

class Digitizer(unittest.TestCase):

    def test_construction(self):
        n_samples = 7
        sampling_rate = 25.0
        start_sampling_at_time = -75.0

        digitizer = lib.Digitizer()
        digitizer.set_nsamples(n_samples)\
                 .set_sampling_rate(sampling_rate)\
                 .set_start_sampling_at_time(start_sampling_at_time)

        self.assertEqual(digitizer.get_nsamples(), n_samples)
        self.assertEqual(digitizer.get_sampling_rate(), sampling_rate)
        self.assertEqual(digitizer.get_start_sampling_at_time(), start_sampling_at_time)

    def test_digitize(self):
        n_samples = 7
        sampling_rate = 25.0
        start_sampling_at_time = -75.0
        digitizer = lib.Digitizer(n_samples, sampling_rate, start_sampling_at_time)

        pulse_shape = lib.TextFilePulseShape(PULSE_SHAPE_FILE_PATH)
        analog_pulse = lib.AnalogPulse(pulse_shape)

        digital_samples = digitizer.digitize(analog_pulse)
        self.assertEqual(len(digital_samples), n_samples)

if __name__ == '__main__':
    unittest.main()
