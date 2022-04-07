%module pyCaloPulseSimulator

%include <std_pair.i>
%include <std_vector.i>
%include <std_string.i>

%template() std::pair<float,float>;
%template(FloatPairVector) std::vector<std::pair<float,float>>;

%{
  #include "algorithms/Accumulator.h"
  #include "TextFilePulseShape.h"
%}

%rename("%(undercase)s", %$isfunction) "";

%include "algorithms/Accumulator.h"
%include "TextFilePulseShape.h"
