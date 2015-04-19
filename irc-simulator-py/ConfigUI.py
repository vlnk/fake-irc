# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'Config.ui'
#
# Created: Fri Apr 17 20:23:25 2015
#      by: PyQt5 UI code generator 5.4
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(404, 368)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.centralwidget)
        self.verticalLayout.setObjectName("verticalLayout")
        self.gridLayout = QtWidgets.QGridLayout()
        self.gridLayout.setObjectName("gridLayout")
        self.Color = QtWidgets.QLabel(self.centralwidget)
        self.Color.setText("")
        self.Color.setObjectName("Color")
        self.gridLayout.addWidget(self.Color, 2, 2, 1, 1)
        self.SpeedTitle = QtWidgets.QLabel(self.centralwidget)
        self.SpeedTitle.setAlignment(QtCore.Qt.AlignCenter)
        self.SpeedTitle.setObjectName("SpeedTitle")
        self.gridLayout.addWidget(self.SpeedTitle, 7, 2, 1, 1)
        self.ColorsTitle = QtWidgets.QLabel(self.centralwidget)
        self.ColorsTitle.setAlignment(QtCore.Qt.AlignCenter)
        self.ColorsTitle.setObjectName("ColorsTitle")
        self.gridLayout.addWidget(self.ColorsTitle, 5, 2, 1, 1)
        self.CharactersListView = QtWidgets.QListView(self.centralwidget)
        self.CharactersListView.setEditTriggers(QtWidgets.QAbstractItemView.NoEditTriggers)
        self.CharactersListView.setSelectionRectVisible(True)
        self.CharactersListView.setObjectName("CharactersListView")
        self.gridLayout.addWidget(self.CharactersListView, 0, 0, 11, 2)
        self.NumOfDialog = QtWidgets.QLabel(self.centralwidget)
        self.NumOfDialog.setText("")
        self.NumOfDialog.setAlignment(QtCore.Qt.AlignLeading|QtCore.Qt.AlignLeft|QtCore.Qt.AlignVCenter)
        self.NumOfDialog.setObjectName("NumOfDialog")
        self.gridLayout.addWidget(self.NumOfDialog, 1, 2, 1, 1)
        spacerItem = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.gridLayout.addItem(spacerItem, 4, 2, 1, 1)
        spacerItem1 = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.gridLayout.addItem(spacerItem1, 9, 2, 1, 1)
        self.Name = QtWidgets.QLabel(self.centralwidget)
        self.Name.setText("")
        self.Name.setAlignment(QtCore.Qt.AlignLeading|QtCore.Qt.AlignLeft|QtCore.Qt.AlignVCenter)
        self.Name.setObjectName("Name")
        self.gridLayout.addWidget(self.Name, 0, 2, 1, 1)
        self.ColorsCombo = QtWidgets.QComboBox(self.centralwidget)
        self.ColorsCombo.setObjectName("ColorsCombo")
        self.gridLayout.addWidget(self.ColorsCombo, 6, 2, 1, 1)
        self.PushButton = QtWidgets.QPushButton(self.centralwidget)
        self.PushButton.setObjectName("PushButton")
        self.gridLayout.addWidget(self.PushButton, 13, 2, 1, 1)
        self.Speed = QtWidgets.QLabel(self.centralwidget)
        self.Speed.setText("")
        self.Speed.setObjectName("Speed")
        self.gridLayout.addWidget(self.Speed, 3, 2, 1, 1)
        self.SpeedSpin = QtWidgets.QDoubleSpinBox(self.centralwidget)
        self.SpeedSpin.setMaximum(1.0)
        self.SpeedSpin.setSingleStep(1.01)
        self.SpeedSpin.setProperty("value", 0.5)
        self.SpeedSpin.setObjectName("SpeedSpin")
        self.gridLayout.addWidget(self.SpeedSpin, 8, 2, 1, 1)
        self.verticalLayout.addLayout(self.gridLayout)
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.actionFile = QtWidgets.QAction(MainWindow)
        self.actionFile.setObjectName("actionFile")

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.SpeedTitle.setText(_translate("MainWindow", "Select speed"))
        self.ColorsTitle.setText(_translate("MainWindow", "Select color"))
        self.PushButton.setText(_translate("MainWindow", "Launch"))
        self.actionFile.setText(_translate("MainWindow", "File"))

