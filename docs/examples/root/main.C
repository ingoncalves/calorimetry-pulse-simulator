R__ADD_INCLUDE_PATH(/usr/local/include)
R__LOAD_LIBRARY(/usr/local/lib/libCaloPulseSimulator.dylib)

#include <iostream>
#include <CaloPulseSimulator/Accumulator.h>

// ROOT macro
int main() {
  std::cout << "Calo Pulse Simulator - Example ROOT Macro" << std::endl;

  Accumulator c;
  std::cout << c.getNextValue() << std::endl;
  std::cout << c.getNextValue() << std::endl;
  std::cout << c.getNextValue() << std::endl;

  return 0;
}
