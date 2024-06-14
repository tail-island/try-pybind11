import matplotlib.pyplot as plot


def read_image():
    def f():
        while True:
            try:
                yield tuple(map(float, input().split()))
            except EOFError:
                break

    return tuple(f())


plot.axis('off')
plot.imshow(read_image())
plot.show()
