import sys
import os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../../build/python'))

import unittest
import pyCaloPulseSimulator as lib

class AccumulatorTest(unittest.TestCase):

    def test_first_number(self):
        acc = lib.Accumulator()
        self.assertEqual(acc.get_next_value(), 0)

    def test_second_number(self):
        acc = lib.Accumulator()
        acc.get_next_value()
        self.assertEqual(acc.get_next_value(), 1)

if __name__ == '__main__':
    unittest.main()
