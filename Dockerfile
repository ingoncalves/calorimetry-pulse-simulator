FROM alpine:3

# install Cmake, G++, Swig, Python3, Python3-dev, and Doxygen
RUN apk add --no-cache g++ make cmake swig python3 python3-dev

# Copy the current directory contents into the container at /simulator or
# clone from https://github.com/ingoncalves/calorimetry-pulse-simulator
COPY . /simulator

# Create a build directory, and set it as the working directory
#RUN mkdir /simulator/build
WORKDIR /simulator/build

# Build the simulator
RUN cmake -DBUILD_TESTS=ON .. && make

# Install the simulator
RUN make install

# Run the tests
CMD ["ctest"]
