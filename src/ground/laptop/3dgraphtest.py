from pyqtgraph.Qt import QtGui#, QtCore
import numpy as np
import pyqtgraph as pg
import pyqtgraph.opengl as gl
import matplotlib.pyplot as plt


cmap = plt.get_cmap('jet')

app = QtGui.QGuiApplication([])
win = pg.GraphicsView()
layoutgb = QtGui.QGridLayout()
win.setLayout(layoutgb)

N = 11
M = 11

x = np.linspace(0, 10, N)
y = np.linspace(0, 10, M)

for i in range(5):

    glvw = gl.GLViewWidget()

    z = np.random.random((N, M))

    minZ = np.min(z)
    maxZ = np.max(z)
    colors = cmap((z - minZ)/(maxZ - minZ))
    
    surf = gl.GLSurfacePlotItem(x = x, 
                                y = y, 
                                z = z, 
                                colors = colors, 
                                drawEdges = True)

    glvw.addItem(surf)

    layoutgb.addWidget(glvw, 0, i)

p1 = pg.PlotWidget()
p1.plot([1, 2, 3, 4, 5], [1, 0, 2, 3, 1], pen ='r', name ='red')
layoutgb.addWidget(p1, 1, 0, 1, -1)

p2 = pg.PlotWidget()
p2.plot([1, 2, 3, 4, 5], [2, 1, 4, 1, 1], pen ='g', name ='green')
layoutgb.addWidget(p2, 2, 0, 1, -1)

glvw.sizeHint = lambda: pg.QtCore.QSize(100, 500)

QtGui.QApplication.instance().exec_()
