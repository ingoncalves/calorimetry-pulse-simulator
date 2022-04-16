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

    def test_get_size(self):
        pulse_shape = lib.TextFilePulseShape(PULSE_SHAPE_FILE_PATH)
        self.assertEqual(pulse_shape.get_size(), 401)

    def test_get_time_series(self):
        pulse_shape = lib.TextFilePulseShape(PULSE_SHAPE_FILE_PATH)
        time_series = pulse_shape.get_time_series()
        self.assertEqual(len(time_series), 401)
        self.assertEqual(time_series[0], -75.5)
        self.assertEqual(time_series[-1], 124.5)

    def test_get_y_series(self):
        pulse_shape = lib.TextFilePulseShape(PULSE_SHAPE_FILE_PATH)
        y_series = pulse_shape.get_yseries()
        self.assertEqual(len(y_series), 401)
        self.assertEqual(y_series[0],  0.)
        self.assertAlmostEqual(y_series[-1], 0.0018547, 7)

    def test_get_y(self):
        pulse_shape = lib.TextFilePulseShape(PULSE_SHAPE_FILE_PATH)
        self.assertEqual(pulse_shape.get_y(-75.5), 0.)
        self.assertEqual(pulse_shape.get_y(0), 1.)
        self.assertAlmostEqual(pulse_shape.get_y(124.5), 0.0018547, 7)
        self.assertEqual(pulse_shape.get_y(-200), 0.)
        self.assertAlmostEqual(pulse_shape.get_y(200), 0.0018547, 7)

if __name__ == '__main__':
    unittest.main()
