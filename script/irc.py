#!/usr/local/bin/python3.4

import sys, re, time, random
from threading import Thread

from termcolor import colored

from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

from ConfigUI import Ui_MainWindow

def run(dialog, characters):
    for c,d in dialog:

        print(colored(c, characters[c]['color']) + " says:")
        time.sleep(1)

        for info in d:
            print(info, end="", flush=True)

            time.sleep(random.uniform(0, characters[c]['speed']))

        print('\n')

class Config(QMainWindow, Ui_MainWindow):
    def __init__(self, parent = None):
        super(Config, self).__init__(parent)

        fileInfo = QFileDialog. getOpenFileNames(self, 'Dialog Title', '~', '*.txt')

        self.charactersModel = {}
        self.dialog = []
        #self.dialog =

        if fileInfo:
            self.parse(fileInfo[0][0])

        self.selectedCharacter = "None"
        self.setupUi(self)

        # Set ListView
        self.model = QStandardItemModel(self.CharactersListView)

        for c in self.charactersModel.keys():
            self.model.appendRow(QStandardItem(c))

        self.CharactersListView.setModel(self.model)
        self.CharactersListView.clicked.connect(self.on_characters_selected)

        # Set Color
        self.colors = ['grey', 'red', 'green', 'yellow', 'blue', 'magenta', 'cyan', 'white']

        for color in self.colors:
            self.ColorsCombo.addItem(color)

        self.ColorsCombo.currentIndexChanged.connect(self.on_color_selected)

        # Set Speed
        self.SpeedSpin.valueChanged.connect(self.on_speed_changed)

        # Set Button
        self.PushButton.clicked.connect(self.on_button_pressed)


    def on_characters_selected(self, index):
        name = str(self.CharactersListView.model().itemData(index)[0])
        self.Name.setText(name)

        for c in self.charactersModel.keys():
            if c == name:
                self.NumOfDialog.setText("Dialogues: " + str(self.charactersModel[c]['num']))
                self.Color.setText("Color: " + str(self.charactersModel[c]['color']))
                self.Speed.setText("Speed: " + str(self.charactersModel[c]['speed']))

        self.selectedCharacter = name

    def on_color_selected(self, index):
        if (self.selectedCharacter) == "None":
            return

        self.charactersModel[self.selectedCharacter]['color'] = self.colors[index]
        self.Color.setText("Color: " + str(self.charactersModel[self.selectedCharacter]['color']))

    def on_speed_changed(self, value):
        if (self.selectedCharacter) == "None":
            return

        self.charactersModel[self.selectedCharacter]['speed'] = value
        self.Speed.setText("Speed: " + "{0:.2f}".format(self.charactersModel[self.selectedCharacter]['speed']))

    def on_button_pressed(self):
        p = Thread(target=run, args = (self.dialog, self.charactersModel))
        p.start()
        #p.join()

    def main(self):
        self.show()

    def parse(self, path):
        with open(path, "r", encoding="utf-8") as f:
            data = f.read()

            pattern = re.compile(r'^\[(.+)\]\s*(\w.*)', re.MULTILINE)

            self.dialog = re.findall(pattern, data)

            #print(dialog)
            for c,d in self.dialog:
                if c in self.charactersModel.keys():
                    self.charactersModel[c]['num'] += 1
                else:
                    self.charactersModel[c] = {'num': 1, 'color': 'red', 'speed': 0.5}

def display(dialog):
    for c,d in dialog:
        #print(colored(c, 'red') + " says:")
        time.sleep(1)

        for char in d:
            print(char, end="", flush=True)

            time.sleep(random.uniform(0, 0.6))

        print('\n');
        app.quit()


def main():
    #display(dialog)
    app = QApplication(sys.argv)
    config = Config()
    config.main()
    app.exec_()

if __name__ == "__main__":
    main()
