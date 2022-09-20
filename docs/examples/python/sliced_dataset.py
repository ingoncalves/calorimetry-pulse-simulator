#!/usr/bin/env python3

# @file docs/examples/python/sliced_dataset.py
# @author Guilherme Inacio Goncalves <ggoncalves@iprj.uer.br>
# @copyright Copyright 2022, Guilherme Inacio Goncalves. All rights reserved.
#
# This file is part of CPS (Calorimetry Pulse Simulator).
#
# CPS is free software: you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or any later version.
#
# CPS is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# CPS. If not, see <https://www.gnu.org/licenses/>.

import numpy as np
import matplotlib.pyplot as plt
from pycps import DatasetGenerator, TextFilePulseShape, PulseGenerator

def main():
    """
    main function
    """
    n_slices = 10000
    slice_size = 7
    pedestal = 50
    pileup_luminosity = 100.0
    pileup_occupancy = .1

    samples = __setup_dataset_generator(n_slices, slice_size, pileup_luminosity, pileup_occupancy, pedestal)

    fig, axs = plt.subplots(2, 4, sharex=True)
    for i in range(0, 7):
        axs[i//4, i%4].hist(samples[:, i], density=True, bins=100)
        axs[i//4, i%4].set_title(f"sample {i}")
    fig.tight_layout()
    plt.show()


def __setup_dataset_generator(n_slices, slice_size, pileup_luminosity, pileup_occupancy, pedestal):
    shape_path = "../../../tests/fixtures/unipolar-pulse-shape.dat"
    pulse_shape = TextFilePulseShape(shape_path)

    pulse_generator = PulseGenerator(pulse_shape)
    pulse_generator.set_amplitude_distribution(PulseGenerator.UNIFORM_REAL_DISTRIBUTION, [0, pileup_luminosity])
    pulse_generator.set_phase_distribution(PulseGenerator.UNIFORM_INT_DISTRIBUTION, [-5, 5])
    pulse_generator.set_deformation_level(0.01)
    pulse_generator.set_noise_params(0, 0)
    pulse_generator.set_pedestal(pedestal)

    dataset_generator = DatasetGenerator()
    dataset_generator.set_pulse_generator(pulse_generator)
    dataset_generator.set_occupancy(pileup_occupancy)
    dataset_generator.set_sampling_rate(25.0)
    dataset_generator.set_noise_params(0, 1.5)
    dataset_generator.set_events_scheme([\
        DatasetGenerator.allowed_events_block(100),\
        DatasetGenerator.not_allowed_events_block(10)\
    ])

    dataset = dataset_generator.generate_sliced_dataset(n_slices, slice_size)
    samples = np.array(dataset.samples)
    return samples


if __name__ == '__main__':
    main()
