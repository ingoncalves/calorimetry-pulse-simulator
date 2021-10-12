#!/usr/bin/env python3

import pyCaloPulseSimulator

print("Calo Pulse Simulator - Example Python")

c = pyCaloPulseSimulator.Accumulator()
print(c.get_next_value())
print(c.get_next_value())
print(c.get_next_value())
