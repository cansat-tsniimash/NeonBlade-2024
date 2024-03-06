import sys
from PyQt5 import QtWidgets
import Ground_Main


class ExampleApp(QtWidgets.QMainWindow, Ground_Main.Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        
def main():
    app = QtWidgets.QApplication(sys.argv)
    window = ExampleApp()
    window.show()
    app.exec_()


if __name__ == '__LaptopMain__':
    main()

