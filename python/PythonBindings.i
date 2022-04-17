%module pyCaloPulseSimulator

%include <std_vector.i>
%include <std_string.i>

%template(DoubleVector) std::vector<double>;

%{
  #include "algorithms/Accumulator.h"
  #include "IPulseShape.h"
  #include "TextFilePulseShape.h"
  #include "AnalogPulse.h"
  #include "PulseGenerator.h"
  #include "Digitizer.h"
%}

%rename("%(undercase)s", %$isfunction) "";

%include "algorithms/Accumulator.h"
%include "IPulseShape.h"
%include "TextFilePulseShape.h"
%include "AnalogPulse.h"
%include "PulseGenerator.h"
%include "Digitizer.h"
