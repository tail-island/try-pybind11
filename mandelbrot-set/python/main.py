import sys

from mandelbrot_set import H, W, get_mandelbrot_set
from timeit import timeit


t = timeit(lambda: get_mandelbrot_set(), globals=globals(), number=10)
print(f'{t / 10} sec', file=sys.stderr)

mandelbrot_set = get_mandelbrot_set()
for i in range(H):
    for j in range(W):
        print(mandelbrot_set[i * W + j], end=' ')
    print()
