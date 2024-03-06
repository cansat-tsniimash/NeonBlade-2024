import sys
from PyQt5 import uic
from PyQt5.QtWidgets import QApplication, QMainWindow


class App(QMainWindow):
    def __init__(self):
        super(App, self).__init__()
        uic.loadUi('GroundMain.ui', self)


if __name__ == "__main__":
    App = QApplication(sys.argv)
    ex = App()
    ex.show()
    sys.exit(App.exec_())
