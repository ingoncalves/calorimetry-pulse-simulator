%module pycps

%{
# define SWIG_PYTHON_EXTRA_NATIVE_CONTAINERS
%}

%include <std_vector.i>
%include <std_string.i>

%template(DoubleVector) std::vector<double>;
%template(DoubleMatrix) std::vector<std::vector<double>>;

%{
  #include "Random.h"
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

%include "Random.h"
%include "IPulseShape.h"
%include "TextFilePulseShape.h"
%include "AnalogPulse.h"
%include "PulseGenerator.h"
%include "IDigitizer.h"
%include "Digitizer.h"
%include "DatasetGenerator.h"
