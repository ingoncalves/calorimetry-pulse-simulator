# CPS - Calorimetry Pulse Simulator

Set of functions in C++ and Python for generating typical analog and digital
calorimetry signals with the ability to simulate phenomena such as electronic
noise, signal pileup, phase shift, baseline, among others.

Useful links:
 - [API Reference](https://ingoncalves.github.io/calorimetry-pulse-simulator/)
 - [Examples](./docs/examples)

## Getting started

Please, follow the instructions for Unix based SO. Requires
[SWIG](http://www.swig.org), and [CMake](https://cmake.org) version 3.8.

1. Create a build directory and make it the current directory

```shell
mkdir build
cd build
```

2. Configure

```shell
cmake ..
```

3. Build

```shell
make
```

4. Install

```shell
make install
```

You are now ready to use the CPS lib in C++ and Python applications.


## Examples

Find **C++**, and **Python**, and CERN **ROOT** examples at `docs/examples/` folder.


## Development

Below is some useful information for developers.


### Tests

To run the automated tests, go the `build` folder and run

```shell
ctest
```


### Build Documentation

Requires [Doxygen](https://www.doxygen.nl/).
Might need to run `cmake ..` again if you installed Doxygen after running it.

```shell
cmake ..
make docs
```

### Author

**Guilherme Gonçalves**

* [github/ingoncalves](https://github.com/ingoncalves)
* [ggoncalves@iprj.uerj.br](mailto:ggoncalves@iprj.uerj.br)

### License

Copyright © 2022, [Guilherme Gonçalves](https://github.com/ingoncalves).
Released under the [GNU GPL License](LICENSE).
