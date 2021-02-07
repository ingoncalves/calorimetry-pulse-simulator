#include <iostream>
#include <CaloPulseSimulator/Accumulator.h>

int main()
{
  std::cout << "CPP Lib Tutorial Example - C++" << std::endl;

  Accumulator c;
  std::cout << c.getNextValue() << std::endl;
  std::cout << c.getNextValue() << std::endl;
  std::cout << c.getNextValue() << std::endl;

  return 0;
}
