from PyQt5 import QtWidgets

class CentralWidget(QtWidgets.QWidget):
    def __init__(self):
        super(CentralWidget, self).__init__()
        self.text1 = QtWidgets.QLabel("ускорение")
        self.text1x = QtWidgets.QLabel("x")
        self.text1y = QtWidgets.QLabel("y")
        
        self.btn1 = QtWidgets.QPushButton()
        self.vlayout = QtWidgets.QVBoxLayout()
        self.setLayout(self.vlayout)
        self.vlayout.addWidget(self.text1)
        

        self.hlayout = QtWidgets.QHBoxLayout()
        self.btn2 = QtWidgets.QPushButton()
        self.hlayout.addWidget(self.btn1)
        self.hlayout.addWidget(self.btn2)
        self.vlayout.addLayout(self.hlayout)


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        #self.setWindowTitle("GCS")
        #self.resize(1200,800)
        #self.move_center()
        #self.c_widget = CentralWidget()
        #self.setCentralWidget(self.c_widget)

    def move_center(self):
        frame = self.frameGeometry()
        frame.moveCenter(QtWidgets.QDesktopWidget().availableGeometry().center())
        self.move(frame.topLeft())
        
