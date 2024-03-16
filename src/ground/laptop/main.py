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
    #finished = QtCore.pyqtSignal()
    
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
            self.new_data.emit([random.random(), time.time()])
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

        #
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
        



        #
        self.graph1 = pg.GraphicsLayoutWidget()
        self.ui.verticalLayout_16.addWidget(self.graph1)
        self.plot1 = self.graph1.addPlot(1, 1, 1, 1)
        

        self.curve1  = self.plot1.plot(np.array([[0, 0]]))
        self.new_curve = True

        print(self.curve1.getData())

        self.curve1.setData(np.append(self.curve1.getData()[0], 3), np.append(self.curve1.getData()[1], 5))
        self.curve1.setPen(color='r')

        self.legend = self.plot1.addLegend()
        self.legend.addItem(self.curve1, 'X')


        axis_x = pg.AxisItem(orientation='bottom')
        axis_x.setLabel("ОСЬ_X")
        axis_y = pg.AxisItem(orientation='left')
        axis_y.setLabel("ОСЬ_Y")
        self.plot1.setAxisItems({'bottom': axis_x, 'left': axis_y})
        



        #
        self.graph2 = pg.GraphicsLayoutWidget()
        self.ui.verticalLayout_8.addWidget(self.graph2)
        self.plot2 = self.graph2.addPlot(1, 1, 1, 1)
        

        self.curve2  = self.plot2.plot(np.array([[0, 0]]))
        self.new_curve = True

        print(self.curve2.getData())

        self.curve2.setData(np.append(self.curve2.getData()[0], 3), np.append(self.curve2.getData()[1], 5))
        self.curve2.setPen(color='r')

        self.legend = self.plot2.addLegend()
        self.legend.addItem(self.curve2, 'test')


        axis_x = pg.AxisItem(orientation='bottom')
        axis_x.setLabel("ОСЬ_X")
        axis_y = pg.AxisItem(orientation='left')
        axis_y.setLabel("ОСЬ_Y")
        self.plot2.setAxisItems({'bottom': axis_x, 'left': axis_y})


        #
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
        




        #
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
        




        #
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
        




        #
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
        




        #
        self.graph7 = pg.GraphicsLayoutWidget()
        self.ui.verticalLayout_17.addWidget(self.graph7)
        self.plot7 = self.graph7.addPlot(1, 1, 1, 1)
        

        self.curve7  = self.plot7.plot(np.array([[0, 0]]))
        self.new_curve = True

        print(self.curve7.getData())

        self.curve7.setData(np.append(self.curve7.getData()[0], 3), np.append(self.curve7.getData()[1], 5))
        self.curve7.setPen(color='r')

        self.legend = self.plot7.addLegend()
        self.legend.addItem(self.curve7, 'test')


        axis_x = pg.AxisItem(orientation='bottom')
        axis_x.setLabel("ОСЬ_X")
        axis_y = pg.AxisItem(orientation='left')
        axis_y.setLabel("ОСЬ_Y")
        self.plot7.setAxisItems({'bottom': axis_x, 'left': axis_y})
        




        #
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
        



        
    def new_data_reaction(self, data):
        print(data)
        self.ui.label_61.setText("{:.2f}".format(data[0]))
        if (not self.new_curve):
            add_data_to_plot(self.curve, data[1], data[0])
            add_data_to_plot(self.curve1, data[1], data[0])
            self.ui.label_6.setText("{:.2f}".format(data[0]))
            add_data_to_plot(self.curve2, data[1], data[0])
            self.ui.label_48.setText("{:.2f}".format(data[0]))
            add_data_to_plot(self.curve3, data[1], data[0])
            self.ui.label_12.setText("{:.2f}".format(data[0]))
            add_data_to_plot(self.curve4, data[1], data[0])
            self.ui.label_21.setText("{:.2f}".format(data[0]))
            add_data_to_plot(self.curve5, data[1], data[0])
            self.ui.label_30.setText("{:.2f}".format(data[0]))
            add_data_to_plot(self.curve6, data[1], data[0])
            self.ui.label_57.setText("{:.2f}".format(data[0]))
            add_data_to_plot(self.curve7, data[1], data[0])
            self.ui.label_59.setText("{:.2f}".format(data[0]))
            add_data_to_plot(self.curve8, data[1], data[0])
            self.ui.label_61.setText("{:.2f}".format(data[0]))
        else:
            self.curve.setData(np.array([[data[1], data[0]]]))
            self.curve1.setData(np.array([[data[1], data[0]]]))
            self.curve2.setData(np.array([[data[1], data[0]]]))
            self.curve3.setData(np.array([[data[1], data[0]]]))
            self.curve4.setData(np.array([[data[1], data[0]]]))
            self.curve5.setData(np.array([[data[1], data[0]]]))
            self.curve6.setData(np.array([[data[1], data[0]]]))
            self.curve7.setData(np.array([[data[1], data[0]]]))
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
