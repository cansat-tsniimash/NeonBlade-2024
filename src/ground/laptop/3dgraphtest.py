import matplotlib.pyplot as plt

import numpy as np


def makeData():
    x = np.random.rand(1000) * 20.0 - 10.0
    y = np.random.rand(len(x)) * 20.0 - 10.0

    z = np.sin(x * 0.3) * np.cos(y * 0.75)
    return x, y, z


if __name__ == '__main__':
    x, y, z = makeData()

    fig = plt.figure()
    axes = fig.add_subplot(projection='3d')
    axes.set_facecolor('#646464')


    my_cmap = plt.get_cmap("rainbow")

    axes.plot_trisurf(x, y, z, cmap = my_cmap, linewidth=0.5, edgecolors='k')

    axes.set_xlim(-10, 10)
    axes.set_ylim(-10, 10)

    plt.show()
