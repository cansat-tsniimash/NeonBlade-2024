#!/usr/bin/python3
from PyQt5 import QtWidgets, QtCore
from sys import argv, exit, stdout
from PyQt5 import uic
from PyQt5.QtWidgets import QApplication, QWidget
from source.main_window import MainWindow

import math
import time
import pyqtgraph as pg
import numpy as np


x = np.arange(1000)
y = np.random.normal(size=(3, 1000))


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
            self.new_data.emit([h, time.time()])
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
        
        self.graph_w = pg.GraphicsLayoutWidget()
        self.ui.verticalLayout_14.addWidget(self.graph_w)
        self.test_plot = self.graph_w.addPlot(1, 1, 1, 1)
        

        self.curve  = self.test_plot.plot(np.array([[0, 0]]))
        #self.curve2 = self.test_plot.plot(np.array([[0, 0]]))
        self.new_curve = True

        print(self.curve.getData())

        self.curve.setData(np.append(self.curve.getData()[0], 3), np.append(self.curve.getData()[1], 5))
        #self.curve2.setData(np.append(self.curve2.getData()[0], 5), np.append(self.curve2.getData()[1], 7))
        self.curve.setPen(color='r')
        #self.curve2.setPen(color="#16c4b9")

        self.legend = self.test_plot.addLegend()
        self.legend.addItem(self.curve, 'test')
        #self.legend.addItem(self.curve2, 'test2') 


        axis_x = pg.AxisItem(orientation='bottom')
        axis_x.setLabel("ОСЬ_X")
        axis_y = pg.AxisItem(orientation='left')
        axis_y.setLabel("ОСЬ_Y")
        self.test_plot.setAxisItems({'bottom': axis_x, 'left': axis_y})
        

        #self.graphicsView = pg.plot()
        #self.graphicsView.plot(x, y, pen=(3))

    def new_data_reaction(self, data):
        print(data)
        self.ui.label_61.setText("{:.2f}".format(data[0]))
        if (not self.new_curve):
            add_data_to_plot(self.curve, data[1], data[0])
        else:
            self.curve.setData(np.array([[data[1], data[0]]]))
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
