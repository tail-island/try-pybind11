import numpy as np


H = 1024
W = 1024

IMAG_MIN = -2.0
IMAG_MAX =  2.0  # noqa: E222

REAL_MIN = -2.0
REAL_MAX =  2.0  # noqa: E222


def get_divergence_count(c):
    z = 0 + 0j

    for i in range(100):
        if abs(z) >= 2:
            return i

        z = z ** 2 + c

    return 0


def get_mandelbrot_set():
    def f():
        for imag in np.linspace(IMAG_MIN, IMAG_MAX, H):
            for real in np.linspace(REAL_MIN, REAL_MAX, W):
                yield get_divergence_count(complex(real, imag))

    return tuple(f())
