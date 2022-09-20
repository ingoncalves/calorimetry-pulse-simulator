#include <iostream>
#include <cps/Accumulator.h>

int main()
{
  std::cout << "Calo Pulse Simulator - Example C++" << std::endl;

  cps::Accumulator c;
  std::cout << c.getNextValue() << std::endl;
  std::cout << c.getNextValue() << std::endl;
  std::cout << c.getNextValue() << std::endl;

  return 0;
}
