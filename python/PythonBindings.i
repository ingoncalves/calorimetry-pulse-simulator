%module pyCaloPulseSimulator

%{
  #include "algorithms/Accumulator.h"
%}

%rename ("get_next_value") Accumulator::getNextValue();
%include "algorithms/Accumulator.h"
