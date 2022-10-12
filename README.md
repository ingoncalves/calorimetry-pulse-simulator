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


## Cite

Please, cite this project using the following reference:

> GONÇALVES, Guilherme Inácio et al. Performance of Optimal Linear Filtering Methods for Signal Estimation in High-Energy Calorimetry. Journal of Control, Automation and Electrical Systems, p. 1-11, 2022.

Or, using bibtex format:

```bib
@article{gonccalves2022performance,
  title={Performance of Optimal Linear Filtering Methods for Signal Estimation in High-Energy Calorimetry},
  author={Gon{\c{c}}alves, Guilherme In{\'a}cio and Peralva, Bernardo Sotto-Maior and de Seixas, Jos{\'e} Manoel and de Andrade Filho, Luciano Manh{\~a}es and Cerqueira, Augusto Santiago},
  journal={Journal of Control, Automation and Electrical Systems},
  pages={1--11},
  year={2022},
  publisher={Springer}
}
```

Link to the paper: https://link.springer.com/article/10.1007/s40313-022-00907-0


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
