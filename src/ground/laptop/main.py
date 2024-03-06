#!/usr/bin/python3
from PyQt5 import QtWidgets, QtCore
from sys import argv, exit, stdout
from PyQt5 import uic
from PyQt5.QtWidgets import QApplication, QWidget
from source.main_window import MainWindow

import math
import time
import pyqtgraph

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
            print('1')
            self.mutex.lock()
            print(self.close_flag)
            if self.close_flag == 1:
                self.mutex.unlock()
                break
            self.mutex.unlock()
            h = math.sin(time.time())
            self.new_data.emit([h])
            print('2')

    def finish(self):
        self.mutex.lock()
        self.close_flag = 1
        self.mutex.unlock()


            
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

    def new_data_reaction(self, data):
        print(data)
        self.ui.label_61.setText("{:.2f}".format(data[0]))

    def closeEvent(self, evnt):
        self.data_object.finish()
        start_time = time.time()
        while self.data_thread.isRunning():
            if (time.time() == start_time) > 20:
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
