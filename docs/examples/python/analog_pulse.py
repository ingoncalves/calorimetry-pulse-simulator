#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np
from pyCaloPulseSimulator import AnalogPulse, TextFilePulseShape, Digitizer


def main():
    """
    main function
    """

    shape_path = "../../../tests/fixtures/unipolar-pulse-shape.dat"
    pulse_shape = TextFilePulseShape(shape_path)
    digitizer = Digitizer(7, 25, -75)

    amplitude = 100.0
    pedestal = 0.0

    default_pulse = AnalogPulse(pulse_shape, amplitude)
    plot_pulse(default_pulse, digitizer, "default pulse")

    phase = -25
    phased_pulse = AnalogPulse(pulse_shape, amplitude, pedestal, phase)
    plot_pulse(phased_pulse, digitizer, "phased pulse")

    phase = 25
    noise_mean = 0
    noise_sigma = 1.5
    noisy_and_phased_pulse = AnalogPulse(
        pulse_shape,
        amplitude,
        pedestal,
        phase,
        noise_mean,
        noise_sigma
    )
    plot_pulse(noisy_and_phased_pulse, digitizer, "noisy and phased pulse")

    plt.grid(zorder=0, linestyle='--')
    plt.legend()
    plt.xlabel("time", horizontalalignment='right', x=1.0, zorder=3)
    plt.ylabel("ADC", horizontalalignment='right', y=1.0)
    plt.show()


def plot_pulse(pulse, digitizer, label):
    """
    draw a pulse
    """
    time_series = list()
    sample_series = list()
    for time in np.arange(-75.5, 124.5, 0.5):
        time_series.append(time)
        sample_series.append(pulse.get_sample(time))
    plot = plt.plot(time_series, sample_series, "-", label=label)
    digital_samples_time = [-75.0, -50.0, -25.0, 0.0, 25.0, 50.0, 75.0]
    digitial_samples = digitizer.digitize(pulse)
    plt.plot(digital_samples_time, digitial_samples, ".",
             color=plot[0].get_color(),
             markersize=10,
             markeredgewidth=1.5,
             markeredgecolor="black")


if __name__ == '__main__':
    main()
