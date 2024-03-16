#!/usr/bin/python3
from PyQt5 import QtWidgets, QtCore
from sys import argv, exit, stdout
from PyQt5 import uic
from PyQt5.QtWidgets import QApplication, QWidget
from source.main_window import MainWindow
import random

import math
import time
import pyqtgraph as pg
import numpy as np



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
            time.sleep(0.05)

    def finish(self):
        self.mutex.lock()
        self.close_flag = 1
        self.mutex.unlock()

def add_data_to_plot(curve, x, y):
    curve.setData(np.append(curve.getData()[0], x), np.append(curve.getData()[1], y))
            
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



        #График высоты
        self.graph_w = pg.GraphicsLayoutWidget()
        self.ui.verticalLayout_14.addWidget(self.graph_w)
        self.test_plot = self.graph_w.addPlot(1, 1, 1, 1)

        self.curve  = self.test_plot.plot(np.array([[0, 0]]))
        self.new_curve = True
        
        print(self.curve.getData())

        self.curve.setData(np.append(self.curve.getData()[0], 3), np.append(self.curve.getData()[1], 5))
        self.curve.setPen(color='r')

        self.legend = self.test_plot.addLegend()
        self.legend.addItem(self.curve, 'test')

        axis_x = pg.AxisItem(orientation='bottom')
        axis_x.setLabel("ОСЬ_X")
        axis_y = pg.AxisItem(orientation='left')
        axis_y.setLabel("ОСЬ_Y")
        self.test_plot.setAxisItems({'bottom': axis_x, 'left': axis_y})



        #График ускорения
        self.graph1 = pg.GraphicsLayoutWidget()
        self.ui.verticalLayout_16.addWidget(self.graph1)
        self.plot1 = self.graph1.addPlot(1, 1, 1, 1)

        self.X_curve = self.plot1.plot(np.array([[0, 0]]))
        self.Y_curve = self.plot1.plot(np.array([[0, 0]]))
        self.Z_curve = self.plot1.plot(np.array([[0, 0]]))
        self.new_curve = True

        print(self.X_curve.getData())
        print(self.Y_curve.getData())
        print(self.Z_curve.getData())

        self.X_curve.setData(np.append(self.X_curve.getData()[0], 3), np.append(self.X_curve.getData()[1], 5))
        self.X_curve.setPen(color='r')
        self.Y_curve.setData(np.append(self.Y_curve.getData()[0], 3), np.append(self.Y_curve.getData()[1], 5))
        self.Y_curve.setPen(color='g')
        self.Z_curve.setData(np.append(self.Y_curve.getData()[0], 3), np.append(self.Y_curve.getData()[1], 5))
        self.Z_curve.setPen(color='b')

        self.legend = self.plot1.addLegend()
        self.legend.addItem(self.X_curve, 'X')
        self.legend.addItem(self.Y_curve, 'Y')
        self.legend.addItem(self.Z_curve, 'Z')

        axis_x = pg.AxisItem(orientation='bottom')
        axis_x.setLabel("ОСЬ_X")
        axis_y = pg.AxisItem(orientation='left')
        axis_y.setLabel("ОСЬ_Y")
        self.plot1.setAxisItems({'bottom': axis_x, 'left': axis_y})
        


        #График GPS
        self.graph3 = pg.GraphicsLayoutWidget()
        self.ui.verticalLayout_10.addWidget(self.graph3)
        self.plot3 = self.graph3.addPlot(1, 1, 1, 1)

        self.curve3  = self.plot3.plot(np.array([[0, 0]]))
        self.new_curve = True

        print(self.curve3.getData())

        self.curve3.setData(np.append(self.curve3.getData()[0], 3), np.append(self.curve3.getData()[1], 5))
        self.curve3.setPen(color='r')

        self.legend = self.plot3.addLegend()
        self.legend.addItem(self.curve3, 'test')

        axis_x = pg.AxisItem(orientation='bottom')
        axis_x.setLabel("ОСЬ_X")
        axis_y = pg.AxisItem(orientation='left')
        axis_y.setLabel("ОСЬ_Y")
        self.plot3.setAxisItems({'bottom': axis_x, 'left': axis_y})
        


        #График угловой скорости
        self.graph4 = pg.GraphicsLayoutWidget()
        self.ui.verticalLayout_15.addWidget(self.graph4)
        self.plot4 = self.graph4.addPlot(1, 1, 1, 1)
        
        self.curve4  = self.plot4.plot(np.array([[0, 0]]))
        self.new_curve = True

        print(self.curve4.getData())

        self.curve4.setData(np.append(self.curve4.getData()[0], 3), np.append(self.curve4.getData()[1], 5))
        self.curve4.setPen(color='r')

        self.legend = self.plot4.addLegend()
        self.legend.addItem(self.curve4, 'test')

        axis_x = pg.AxisItem(orientation='bottom')
        axis_x.setLabel("ОСЬ_X")
        axis_y = pg.AxisItem(orientation='left')
        axis_y.setLabel("ОСЬ_Y")
        self.plot4.setAxisItems({'bottom': axis_x, 'left': axis_y})
        


        #График давления
        self.graph5 = pg.GraphicsLayoutWidget()
        self.ui.verticalLayout_13.addWidget(self.graph5)
        self.plot5 = self.graph5.addPlot(1, 1, 1, 1)

        self.curve5  = self.plot5.plot(np.array([[0, 0]]))
        self.new_curve = True

        print(self.curve5.getData())

        self.curve5.setData(np.append(self.curve5.getData()[0], 3), np.append(self.curve5.getData()[1], 5))
        self.curve5.setPen(color='r')

        self.legend = self.plot5.addLegend()
        self.legend.addItem(self.curve5, 'test')

        axis_x = pg.AxisItem(orientation='bottom')
        axis_x.setLabel("ОСЬ_X")
        axis_y = pg.AxisItem(orientation='left')
        axis_y.setLabel("ОСЬ_Y")
        self.plot5.setAxisItems({'bottom': axis_x, 'left': axis_y})
        


        #График магнитометра
        self.graph6 = pg.GraphicsLayoutWidget()
        self.ui.verticalLayout_18.addWidget(self.graph6)
        self.plot6 = self.graph6.addPlot(1, 1, 1, 1)
        
        self.curve6  = self.plot6.plot(np.array([[0, 0]]))
        self.new_curve = True

        print(self.curve6.getData())

        self.curve6.setData(np.append(self.curve6.getData()[0], 3), np.append(self.curve6.getData()[1], 5))
        self.curve6.setPen(color='r')

        self.legend = self.plot6.addLegend()
        self.legend.addItem(self.curve6, 'test')

        axis_x = pg.AxisItem(orientation='bottom')
        axis_x.setLabel("ОСЬ_X")
        axis_y = pg.AxisItem(orientation='left')
        axis_y.setLabel("ОСЬ_Y")
        self.plot6.setAxisItems({'bottom': axis_x, 'left': axis_y})
        


        #График температуры
        self.graph8 = pg.GraphicsLayoutWidget()
        self.ui.verticalLayout_19.addWidget(self.graph8)
        self.plot8 = self.graph8.addPlot(1, 1, 1, 1)
        
        self.curve8  = self.plot8.plot(np.array([[0, 0]]))
        self.new_curve = True

        print(self.curve8.getData())

        self.curve8.setData(np.append(self.curve8.getData()[0], 3), np.append(self.curve8.getData()[1], 5))
        self.curve8.setPen(color='r')

        self.legend = self.plot8.addLegend()
        self.legend.addItem(self.curve8, 'test')

        axis_x = pg.AxisItem(orientation='bottom')
        axis_x.setLabel("ОСЬ_X")
        axis_y = pg.AxisItem(orientation='left')
        axis_y.setLabel("ОСЬ_Y")
        self.plot8.setAxisItems({'bottom': axis_x, 'left': axis_y})
        

    #Обновление графиков    
    def new_data_reaction(self, data):
        print(data)
        self.ui.label_61.setText("{:.2f}".format(data[0]))
        if (not self.new_curve):
            add_data_to_plot(self.curve, time.time(), random.uniform(3, 5))
            add_data_to_plot(self.X_curve, time.time(), random.uniform(7, 10))
            self.ui.label_6.setText("{:.2f}".format(data[0]))
            add_data_to_plot(self.Y_curve, time.time(), random.uniform(7, 10))
            add_data_to_plot(self.Z_curve, time.time(), random.uniform(7, 10))
            add_data_to_plot(self.curve3, data[1], data[0])
            self.ui.label_12.setText("{:.2f}".format(data[0]))
            add_data_to_plot(self.curve4, data[1], data[0])
            self.ui.label_21.setText("{:.2f}".format(data[0]))
            add_data_to_plot(self.curve5, data[1], data[0])
            self.ui.label_30.setText("{:.2f}".format(data[0]))
            add_data_to_plot(self.curve6, data[1], data[0])
            self.ui.label_57.setText("{:.2f}".format(data[0]))
            add_data_to_plot(self.curve8, data[1], data[0])
            self.ui.label_61.setText("{:.2f}".format(data[0]))
        else:
            self.curve.setData(np.array([[time.time(), random.uniform(3, 5)]]))
            self.X_curve.setData(np.array([[time.time(), random.uniform(7, 10)]]))
            self.Y_curve.setData(np.array([[time.time(), random.uniform(7, 10)]]))
            self.Z_curve.setData(np.array([[time.time(), random.uniform(7, 10)]]))
            self.curve3.setData(np.array([[data[1], data[0]]]))
            self.curve4.setData(np.array([[data[1], data[0]]]))
            self.curve5.setData(np.array([[data[1], data[0]]]))
            self.curve6.setData(np.array([[data[1], data[0]]]))
            self.curve8.setData(np.array([[data[1], data[0]]]))
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
