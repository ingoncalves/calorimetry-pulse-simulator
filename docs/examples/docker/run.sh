#!/bin/sh

set -e

cd ../../../
docker build -t cps:latest .
docker run -v ./docs/examples/docker/continuous_dataset.py:/examples/continuous_dataset.py --rm -it cps:latest /bin/sh -c "python3 /examples/continuous_dataset.py"

