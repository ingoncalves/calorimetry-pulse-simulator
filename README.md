# Calo Pulse Simulator

## Instructions for Unix based SO

Requires [SWIG](http://www.swig.org), [CMake](https://cmake.org) version 3.8, and [Doxygen](https://www.doxygen.nl/).

1. Create a build directory and make it the current dir

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

5. Test

```shell
ctest
```

6. Examples

Find C++, CERN Root, and Python examples at `docs/examples/`.
