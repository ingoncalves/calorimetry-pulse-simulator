import unittest
import pyCaloPulseSimulator

class AccumulatorTest(unittest.TestCase):

  def test_first_number(self):
    a = pyCaloPulseSimulator.Accumulator()
    self.assertEqual(a.get_next_value(), 0)

  def test_second_number(self):
    a = pyCaloPulseSimulator.Accumulator()
    a.get_next_value()
    self.assertEqual(a.get_next_value(), 1)

if __name__ == '__main__':
  unittest.main()
