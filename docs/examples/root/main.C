R__ADD_INCLUDE_PATH(/usr/local/include)
R__LOAD_LIBRARY(/usr/local/lib/libcps.dylib)

#include <iostream>
#include <cps/Accumulator.h>

// ROOT macro
int main() {
  std::cout << "Calo Pulse Simulator - Example ROOT Macro" << std::endl;

  cps::Accumulator c;
  std::cout << c.getNextValue() << std::endl;
  std::cout << c.getNextValue() << std::endl;
  std::cout << c.getNextValue() << std::endl;

  return 0;
}
