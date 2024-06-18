# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'HeartBeat.ui'
##
## Created by: Qt User Interface Compiler version 6.7.1
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QLabel, QSizePolicy, QWidget)

class Ui_Form_main(object):
    def setupUi(self, Form_main):
        if not Form_main.objectName():
            Form_main.setObjectName(u"Form_main")
        Form_main.resize(198, 98)
        Form_main.setStyleSheet(u"background-color: green;")
        self.HartBeat_label = QLabel(Form_main)
        self.HartBeat_label.setObjectName(u"HartBeat_label")
        self.HartBeat_label.setGeometry(QRect(50, 20, 101, 51))
        font = QFont()
        font.setPointSize(36)
        self.HartBeat_label.setFont(font)
        self.HartBeat_label.setStyleSheet(u"color: red;")

        self.retranslateUi(Form_main)

        QMetaObject.connectSlotsByName(Form_main)
    # setupUi

    def retranslateUi(self, Form_main):
        Form_main.setWindowTitle(QCoreApplication.translate("Form_main", u"HeartBeat Demo B\u7ad9\uff1aM0Ca", None))
        self.HartBeat_label.setText(QCoreApplication.translate("Form_main", u"36", None))
    # retranslateUi

