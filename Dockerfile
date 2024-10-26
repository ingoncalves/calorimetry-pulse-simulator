FROM alpine:3

# install Cmake, G++, Swig, Python3 and Python3-dev
RUN apk add --no-cache g++ make cmake swig python3 python3-dev

## Install  python packages
#RUN apk add --no-cache py3-numpy py3-scipy py3-matplotlib

# Copy the current directory contents into the container at /cps or
# clone from https://github.com/ingoncalves/calorimetry-pulse-simulator
COPY . /cps

# Create a build directory, and set it as the working directory
WORKDIR /cps/build

# Build and install the library
RUN cmake -DBUILD_TESTS=ON -DBUILD_DOCS=OFF .. && make && make install

WORKDIR /cps
