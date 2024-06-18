import sys
import serial
import re
import serial.tools.list_ports

from PySide6.QtWidgets import QApplication, QWidget, QLabel
from HeartBeat_ui import Ui_Form_main
from PySide6.QtCore import QThread, Signal, Slot

from PySide6.QtUiTools import QUiLoader

from PySide6.QtCore import QFile

class SerialThread(QThread):
    data_received = Signal(str)

    def __init__(self, port):
        super().__init__()
        self.port = port
        self.running = True

    def run(self):
        try:
            ser = serial.Serial(self.port, 115200)
            while self.running:
                if ser.in_waiting:
                    data = ser.readline().decode('utf-8').strip()
                    self.data_received.emit(data)
        except serial.SerialException as e:
            print(f"Serial exception: {e}")

    def stop(self):
        self.running = False
        self.quit()
        self.wait()

class MainWindow(QWidget, Ui_Form_main):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.serial_thread = None
        self.init_serial()

    def init_serial(self):
        port = self.find_esp32_port()
        if port:
            self.serial_thread = SerialThread(port)
            self.serial_thread.data_received.connect(self.update_label)
            self.serial_thread.start()
        else:
            print("ESP32 not found")

    def find_esp32_port(self):
        ports = serial.tools.list_ports.comports()
        for port in ports:
            print(f"Port: {port.device}, Description: {port.description}")
            if 'CH340' in port.description:
                return port.device
        return None

    @Slot(str)
    def update_label(self, data):
        # 使用正则表达式从字符串中提取$后面的数字
        match = re.search(r'\$(\d+)', data)
        if match:
            number = match.group(1)
            self.HartBeat_label.setText(number)

    def closeEvent(self, event):
        if self.serial_thread:
            self.serial_thread.stop()
        event.accept()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())