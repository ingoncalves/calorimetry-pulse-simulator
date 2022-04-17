%module pyCaloPulseSimulator

%include <std_vector.i>
%include <std_string.i>

%template(DoubleVector) std::vector<double>;

%{
  #include "algorithms/Accumulator.h"
  #include "TextFilePulseShape.h"
  #include "AnalogPulse.h"
  #include "PulseGenerator.h"
  #include "Digitizer.h"
  #include "DatasetGenerator.h"
  using namespace cps;
%}

%template(EventScheme) std::vector<cps::EventSchemeBlock>;
%template(Events) std::vector<cps::AnalogPulse*>;
%rename("%(undercase)s", %$isfunction) "";

%include "algorithms/Accumulator.h"
%include "TextFilePulseShape.h"
%include "AnalogPulse.h"
%include "PulseGenerator.h"
%include "Digitizer.h"
%include "DatasetGenerator.h"

