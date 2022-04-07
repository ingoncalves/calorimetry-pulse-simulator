import sys
import os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../../build/python'))

import unittest
import pyCaloPulseSimulator as lib

PULSE_SHAPE_FILE_PATH = "tests/fixtures/unipolar-pulse-shape.dat"

class TextFilePulseShape(unittest.TestCase):

    def test_get_resolution(self):
        pulse_shape = lib.TextFilePulseShape(PULSE_SHAPE_FILE_PATH)
        self.assertEqual(pulse_shape.get_resolution(), 0.5)

    def test_get_origin(self):
        pulse_shape = lib.TextFilePulseShape(PULSE_SHAPE_FILE_PATH)
        self.assertEqual(pulse_shape.get_origin(), 151)

    def test_get_time_series(self):
        pulse_shape = lib.TextFilePulseShape(PULSE_SHAPE_FILE_PATH)
        time_series = pulse_shape.get_time_series()
        self.assertEqual(len(time_series), 401)
        self.assertEqual(time_series[0], (-75.5, 0.))
        self.assertEqual(time_series[-1][0], 124.5)
        self.assertAlmostEqual(time_series[-1][1], 0.0018547, 7)

if __name__ == '__main__':
    unittest.main()
