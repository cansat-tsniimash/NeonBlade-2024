#!/usr/bin/python3
from PyQt5 import QtWidgets, QtCore, QtGui
import sys
from sys import argv, exit, stdout
from PyQt5 import uic
from PyQt5.QtWidgets import QApplication, QWidget
from source.main_window import MainWindow
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolbar
import random
import os
import math
import time
import pyqtgraph as pg
import pyqtgraph.opengl as gl
import numpy as np
import pyquaternion
from math import *
from stl import mesh
from itertools import chain
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure


pg.setConfigOption('background', '#646464')
pg.setConfigOption('foreground', '#ffffff')


MESH_PATH = os.path.abspath('Sat_Simple2.stl')





class DataManager(QtCore.QObject):
    new_data = QtCore.pyqtSignal(list)
    mutex = QtCore.QMutex()
    #autoclose = QtCore.pyqtSignal(str)
    #finished = QtCore.pyqtSignal

    def run(self):
        self.mutex.lock()
        self.close_flag = 0
        self.mutex.unlock()
        while True:
            self.mutex.lock()
            if self.close_flag == 1:
                self.mutex.unlock()
                break
            self.mutex.unlock()
            h = math.sin(time.time())
            self.new_data.emit([random.uniform(7, 10), time.time()])
            time.sleep(0.2)

    def finish(self):
        self.mutex.lock()
        self.close_flag = 1
        self.mutex.unlock()



class TopData():
    def makeData():
        x = np.random.rand(1000) * 20.0 - 10.0
        y = np.random.rand(len(x)) * 20.0 - 10.0

        z = np.sin(x * 0.3) * np.cos(y * 0.75)
        return x, y, z




        



def add_data_to_plot(curve, x, y):
    data = curve.getData()
    if len(curve.getData()[0]) + 1 > 100:
        curve.setData(np.append(curve.getData()[0][2:], x), np.append(curve.getData()[1][2:], y))
    else:
        curve.setData(np.append(curve.getData()[0], x), np.append(curve.getData()[1], y))



class PlaneWidget(gl.GLViewWidget):
    def __init__(self, mesh_path, *args, **kwargs):
        super(PlaneWidget, self).__init__(*args, **kwargs)
        self.setCameraPosition(distance=13)
        self.setBackgroundColor([100, 100, 100, 0])
        g = gl.GLGridItem()
        self.addItem(g)

        isc_coord = gl.GLAxisItem()
        isc_coord.setSize(100, 100, 100)
        self.addItem(isc_coord)

        self.plane_axis = gl.GLAxisItem()
        self.plane_axis.setSize(x=500, y=500, z=500)
        self.addItem(self.plane_axis)

        verts = self._get_mesh_points(mesh_path)
        faces = np.array([(i, i + 1, i + 2,) for i in range(0, len(verts), 3)])
        colors = np.array([(1.0, 1.0, 0.0, 1.0,) for i in range(0, len(verts), 3)])
        self.mesh = gl.GLMeshItem(vertexes=verts, faces=faces, faceColors=colors, smooth=False, shader='shaded')

        # self.mesh.rotate(180, 0, 0, 1)

        self.addItem(self.mesh)
        # self._update_mesh([0, 0, 1])

    def on_new_records(self, records):
        self._update_mesh(records)

    def _get_mesh_points(self, mesh_path):
        your_mesh = mesh.Mesh.from_file(mesh_path)
        points = your_mesh.points

        points = np.array(list(chain(*points)))
        i = 0
        nd_points = np.ndarray(shape=(len(points) // 3, 3,))
        for i in range(0, len(points) // 3):
            nd_points[i] = points[i * 3: (i + 1) * 3]

        return nd_points

    def _transform_object(self, target, move=True, rotate=True, scale=1 / 50):
        target.resetTransform()
        target.scale(scale, scale, scale)
        if move: target.translate(0, 0, 0.1)
        if rotate:
            target.rotate(degrees(self.rotation.angle), self.rotation.axis[0], self.rotation.axis[1],
                          self.rotation.axis[2])

    def _update_rotation(self, record):
        quat = pyquaternion.Quaternion(record)
        self.rotation = quat

        self._transform_object(self.mesh)

        self._transform_object(self.plane_axis, move=False)



            
class App(QWidget):
    def __init__(self):
        super(App, self).__init__()
        Form, Baze = uic.loadUiType('GroundMain.ui')
        self.ui = Form()
        self.ui.setupUi(self)
        self.data_thread = QtCore.QThread(self)
        self.data_object = DataManager()
        self.data_object.moveToThread(self.data_thread)
        self.data_thread.started.connect(self.data_object.run)
        self.data_thread.start()
        self.data_object.new_data.connect(self.new_data_reaction)
        self.Orient = PlaneWidget(MESH_PATH)
        self.ui.verticalLayout_8.addWidget(self.Orient)



        x, y, z = TopData.makeData()
        Top = QWidget(self)

        Top.setStyleSheet('background-color:#646464;')

    
        # Создание экземпляра объекта Figure из matplotlib
        self.figure = Figure()
    
        # Создание экземпляра объекта FigureCanvas, который будет использоваться для отображения графика
        self.canvas = FigureCanvas(self.figure)
    
        # Добавление графика на макет
        self.ui.verticalLayout_17.addWidget(self.canvas)
    
        # Создание экземпляра объекта осей для графика
        self.axes = self.figure.add_subplot(projection='3d')
    
        # Вставка здесь кода для построения графика с помощью методов matplotlib
        self.axes.set_facecolor('#646464')

        self.my_cmap = plt.get_cmap("rainbow")
        self.axes.plot_trisurf(x, y, z, cmap = self.my_cmap, linewidth=0.2, edgecolors='k')
        self.axes.set_xlim(-10, 10)
        self.axes.set_ylim(-10, 10)
        self.axes.set_axis_off()
        self.axes.xaxis.pane.fill = False # Left pane
        self.axes.yaxis.pane.fill = False # Right pane

        


        

        #График высоты
        self.Hight_graph = pg.GraphicsLayoutWidget()
        self.ui.verticalLayout_14.addWidget(self.Hight_graph)
        self.Hight_plot = self.Hight_graph.addPlot(1, 1, 1, 1)

        self.Hight_BME_curve  = self.Hight_plot.plot(np.array([[0, 0]]))
        self.Hight_GPS_curve  = self.Hight_plot.plot(np.array([[0, 0]]))
        self.new_curve = True
        
        print(self.Hight_BME_curve.getData())
        print(self.Hight_GPS_curve.getData())

        self.Hight_BME_curve.setData(np.append(self.Hight_BME_curve.getData()[0], 3), np.append(self.Hight_BME_curve.getData()[1], 5))
        self.Hight_BME_curve.setPen(color='b')
        self.Hight_GPS_curve.setData(np.append(self.Hight_GPS_curve.getData()[0], 3), np.append(self.Hight_GPS_curve.getData()[1], 5))
        self.Hight_GPS_curve.setPen(color='g')

        self.legend = self.Hight_plot.addLegend()
        self.legend.addItem(self.Hight_BME_curve, 'высота по BME')
        self.legend.addItem(self.Hight_GPS_curve, 'высота по GPS')

        axis_x = pg.AxisItem(orientation='bottom')
        axis_x.setLabel("Время")
        axis_y = pg.AxisItem(orientation='left')
        axis_y.setLabel("Высота")
        self.Hight_plot.setAxisItems({'bottom': axis_x, 'left': axis_y})



        #График ускорения
        self.graph1 = pg.GraphicsLayoutWidget()
        self.ui.verticalLayout_16.addWidget(self.graph1)
        self.plot1 = self.graph1.addPlot(1, 1, 1, 1)

        self.Boost_X_curve = self.plot1.plot(np.array([[0, 0]]))
        self.Boost_Y_curve = self.plot1.plot(np.array([[0, 0]]))
        self.Boost_Z_curve = self.plot1.plot(np.array([[0, 0]]))
        self.new_curve = True

        print(self.Boost_X_curve.getData())
        print(self.Boost_Y_curve.getData())
        print(self.Boost_Z_curve.getData())

        self.Boost_X_curve.setData(np.append(self.Boost_X_curve.getData()[0], 3), np.append(self.Boost_X_curve.getData()[1], 5))
        self.Boost_X_curve.setPen(color='r')
        self.Boost_Y_curve.setData(np.append(self.Boost_Y_curve.getData()[0], 3), np.append(self.Boost_Y_curve.getData()[1], 5))
        self.Boost_Y_curve.setPen(color='g')
        self.Boost_Z_curve.setData(np.append(self.Boost_Y_curve.getData()[0], 3), np.append(self.Boost_Y_curve.getData()[1], 5))
        self.Boost_Z_curve.setPen(color='b')

        self.legend = self.plot1.addLegend()
        self.legend.addItem(self.Boost_X_curve, 'X')
        self.legend.addItem(self.Boost_Y_curve, 'Y')
        self.legend.addItem(self.Boost_Z_curve, 'Z')

        axis_x = pg.AxisItem(orientation='bottom')
        axis_x.setLabel("Время")
        axis_y = pg.AxisItem(orientation='left')
        axis_y.setLabel("Ускорение")
        self.plot1.setAxisItems({'bottom': axis_x, 'left': axis_y})
        


        #График GPS
        self.GPS_graph = pg.GraphicsLayoutWidget()
        self.ui.verticalLayout_10.addWidget(self.GPS_graph)
        self.GPS_plot = self.GPS_graph.addPlot(1, 1, 1, 1)

        self.GPS_curve  = self.GPS_plot.plot(np.array([[0, 0]]))
        self.new_curve = True

        print(self.GPS_curve.getData())

        self.GPS_curve.setData(np.append(self.GPS_curve.getData()[0], 3), np.append(self.GPS_curve.getData()[1], 5))
        self.GPS_curve.setPen(color='#fff078')

        self.legend = self.GPS_plot.addLegend()
        self.legend.addItem(self.GPS_curve, 'координаты')
        
        axis_x = pg.AxisItem(orientation='bottom')
        axis_x.setLabel("Широта")
        axis_y = pg.AxisItem(orientation='left')
        axis_y.setLabel("Долгота")
        self.GPS_plot.setAxisItems({'bottom': axis_x, 'left': axis_y})
        


        #График угловой скорости
        self.C_speed_graph = pg.GraphicsLayoutWidget()
        self.ui.verticalLayout_15.addWidget(self.C_speed_graph)
        self.C_speed_plot = self.C_speed_graph.addPlot(1, 1, 1, 1)
        
        self.C_speed_X_curve  = self.C_speed_plot.plot(np.array([[0, 0]]))
        self.C_speed_Y_curve  = self.C_speed_plot.plot(np.array([[0, 0]]))
        self.C_speed_Z_curve  = self.C_speed_plot.plot(np.array([[0, 0]]))
        self.new_curve = True

        print(self.C_speed_X_curve.getData())
        print(self.C_speed_Y_curve.getData())
        print(self.C_speed_Z_curve.getData())

        self.C_speed_X_curve.setData(np.append(self.C_speed_X_curve.getData()[0], 3), np.append(self.C_speed_X_curve.getData()[1], 5))
        self.C_speed_X_curve.setPen(color='r')
        self.C_speed_Y_curve.setData(np.append(self.C_speed_Y_curve.getData()[0], 3), np.append(self.C_speed_Y_curve.getData()[1], 5))
        self.C_speed_Y_curve.setPen(color='g')
        self.C_speed_Z_curve.setData(np.append(self.C_speed_Z_curve.getData()[0], 3), np.append(self.C_speed_Z_curve.getData()[1], 5))
        self.C_speed_Z_curve.setPen(color='b')

        self.legend = self.C_speed_plot.addLegend()
        self.legend.addItem(self.C_speed_X_curve, 'X')
        self.legend.addItem(self.C_speed_Y_curve, 'Y')
        self.legend.addItem(self.C_speed_Z_curve, 'Z')

        axis_x = pg.AxisItem(orientation='bottom')
        axis_x.setLabel("Время")
        axis_y = pg.AxisItem(orientation='left')
        axis_y.setLabel("Скорость")
        self.C_speed_plot.setAxisItems({'bottom': axis_x, 'left': axis_y})
        


        #График давления
        self.Press_graph = pg.GraphicsLayoutWidget()
        self.ui.verticalLayout_13.addWidget(self.Press_graph)
        self.Press_plot = self.Press_graph.addPlot(1, 1, 1, 1)

        self.Press_curve  = self.Press_plot.plot(np.array([[0, 0]]))
        self.new_curve = True

        print(self.Press_curve.getData())

        self.Press_curve.setData(np.append(self.Press_curve.getData()[0], 3), np.append(self.Press_curve.getData()[1], 5))
        self.Press_curve.setPen(color='#fff078')

        self.legend = self.Press_plot.addLegend()
        self.legend.addItem(self.Press_curve, 'давление')

        axis_x = pg.AxisItem(orientation='bottom')
        axis_x.setLabel("Время")
        axis_y = pg.AxisItem(orientation='left')
        axis_y.setLabel("Давление")
        self.Press_plot.setAxisItems({'bottom': axis_x, 'left': axis_y})
        


        #График магнитометра
        self.Magnet_graph = pg.GraphicsLayoutWidget()
        self.ui.verticalLayout_18.addWidget(self.Magnet_graph)
        self.Magnet_plot = self.Magnet_graph.addPlot(1, 1, 1, 1)
        
        self.Magnet_X_curve  = self.Magnet_plot.plot(np.array([[0, 0]]))
        self.Magnet_Y_curve  = self.Magnet_plot.plot(np.array([[0, 0]]))
        self.Magnet_Z_curve  = self.Magnet_plot.plot(np.array([[0, 0]]))
        self.new_curve = True

        print(self.Magnet_X_curve.getData())
        print(self.Magnet_Y_curve.getData())
        print(self.Magnet_Z_curve.getData())

        self.Magnet_X_curve.setData(np.append(self.Magnet_X_curve.getData()[0], 3), np.append(self.Magnet_X_curve.getData()[1], 5))
        self.Magnet_X_curve.setPen(color='r')
        self.Magnet_Y_curve.setData(np.append(self.Magnet_Y_curve.getData()[0], 3), np.append(self.Magnet_Y_curve.getData()[1], 5))
        self.Magnet_Y_curve.setPen(color='g')
        self.Magnet_Z_curve.setData(np.append(self.Magnet_Z_curve.getData()[0], 3), np.append(self.Magnet_Z_curve.getData()[1], 5))
        self.Magnet_Z_curve.setPen(color='b')

        self.legend = self.Magnet_plot.addLegend()
        self.legend.addItem(self.Magnet_X_curve, 'X')
        self.legend.addItem(self.Magnet_Y_curve, 'Y')
        self.legend.addItem(self.Magnet_Z_curve, 'Z')

        axis_x = pg.AxisItem(orientation='bottom')
        axis_x.setLabel("Время")
        axis_y = pg.AxisItem(orientation='left')
        axis_y.setLabel("Гс")
        self.Magnet_plot.setAxisItems({'bottom': axis_x, 'left': axis_y})
        


        #График температуры
        self.Temp_graph = pg.GraphicsLayoutWidget()
        self.ui.verticalLayout_19.addWidget(self.Temp_graph)
        self.Temp_plot = self.Temp_graph.addPlot(1, 1, 1, 1)
        
        self.Temp_curve  = self.Temp_plot.plot(np.array([[0, 0]]))
        self.new_curve = True

        print(self.Temp_curve.getData())

        self.Temp_curve.setData(np.append(self.Temp_curve.getData()[0], 3), np.append(self.Temp_curve.getData()[1], 5))
        self.Temp_curve.setPen(color='#fff078')

        self.legend = self.Temp_plot.addLegend()
        self.legend.addItem(self.Temp_curve, 'температура')

        axis_x = pg.AxisItem(orientation='bottom')
        axis_x.setLabel("Время")
        axis_y = pg.AxisItem(orientation='left')
        axis_y.setLabel("Температура")
        self.Temp_plot.setAxisItems({'bottom': axis_x, 'left': axis_y})

        



    def makeData():
        x = np.random.rand(1000) * 20.0 - 10.0
        y = np.random.rand(len(x)) * 20.0 - 10.0

        z = np.sin(x * 0.3) * np.cos(y * 0.75)
        return x, y, z




        
    #Обновление графиков    
    def new_data_reaction(self, data):
        print(data)
        self.ui.label_61.setText("{:.2f}".format(data[0]))
        self.ui.label_54.setText("{:.2f}".format(time.time()))
        if (not self.new_curve):
            add_data_to_plot(self.Hight_BME_curve, time.time(), random.uniform(1000, 2000))
            add_data_to_plot(self.Hight_GPS_curve, time.time(), random.uniform(1000, 2000))
            add_data_to_plot(self.Boost_X_curve, time.time(), random.uniform(7, 10))
            self.ui.label_6.setText("{:.2f}".format(data[0]))
            add_data_to_plot(self.Boost_Y_curve, time.time(), random.uniform(7, 10))
            add_data_to_plot(self.Boost_Z_curve, time.time(),random.uniform(7, 10) )
            add_data_to_plot(self.GPS_curve, random.uniform(0, 1001), random.uniform(0, 1001))
            self.ui.label_12.setText("{:.2f}".format(data[0]))
            add_data_to_plot(self.C_speed_X_curve, time.time(), random.uniform(1, 2))
            self.ui.label_21.setText("{:.2f}".format(data[0]))
            add_data_to_plot(self.C_speed_Y_curve, time.time(), random.uniform(1, 2))
            add_data_to_plot(self.C_speed_Z_curve, time.time(), random.uniform(1, 2))
            add_data_to_plot(self.Press_curve, time.time(), random.uniform(10, 100))
            self.ui.label_30.setText("{:.2f}".format(data[0]))
            add_data_to_plot(self.Magnet_X_curve, time.time(), random.uniform(100, 200))
            add_data_to_plot(self.Magnet_Y_curve, time.time(), random.uniform(100, 200))
            add_data_to_plot(self.Magnet_Z_curve, time.time(), random.uniform(100, 200))
            self.ui.label_57.setText("{:.2f}".format(data[0]))
            add_data_to_plot(self.Temp_curve, time.time(), random.uniform(2, 18))
            self.ui.label_61.setText("{:.2f}".format(data[0]))
        else:
            self.Hight_BME_curve.setData(np.array([[time.time(), random.uniform(1000, 2000)]]))
            self.Hight_GPS_curve.setData(np.array([[time.time(), random.uniform(1000, 2000)]]))
            self.Boost_X_curve.setData(np.array([[time.time(), random.uniform(7, 10)]]))
            self.Boost_Y_curve.setData(np.array([[time.time(), random.uniform(7, 10)]]))
            self.Boost_Z_curve.setData(np.array([[time.time(), random.uniform(7, 10)]]))
            self.GPS_curve.setData(np.array([[random.uniform(0, 1001), random.uniform(0, 1001)]]))
            self.C_speed_X_curve.setData(np.array([[time.time(), random.uniform(1, 2)]]))
            self.C_speed_Y_curve.setData(np.array([[time.time(), random.uniform(1, 2)]]))
            self.C_speed_Z_curve.setData(np.array([[time.time(), random.uniform(1, 2)]]))
            self.Press_curve.setData(np.array([[time.time(), random.uniform(10, 100)]]))
            self.Magnet_X_curve.setData(np.array([[time.time(), random.uniform(100, 200)]]))
            self.Magnet_Y_curve.setData(np.array([[time.time(), random.uniform(100, 200)]]))
            self.Magnet_Z_curve.setData(np.array([[time.time(), random.uniform(100, 200)]]))
            self.Temp_curve.setData(np.array([[time.time(), random.uniform(2, 18)]]))
            self.new_curve = False
        
    def closeEvent(self, evnt):
        self.data_object.finish()
        start_time = time.time()
        while self.data_thread.isRunning():
            if (time.time() - start_time) > 2:
                break
            time.sleep(0.01)
        super(App, self).closeEvent(evnt)




        
if __name__ == "__main__":



    QtCore.QCoreApplication.setOrganizationName("CNIImash")
    QtCore.QCoreApplication.setApplicationName("Neon_Blade")

    application = QApplication(argv)
    window = App()
    window.show()
    exit(application.exec_())
    application.exit()
