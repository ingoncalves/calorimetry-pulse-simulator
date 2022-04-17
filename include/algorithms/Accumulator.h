#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

namespace cps {
class Accumulator
  {
  private:
    int accumulator = -1;

  public:
    Accumulator() = default;
    virtual ~Accumulator() = default;

    int getNextValue();
  };
}

#endif /* ACCUMULATOR_H */
