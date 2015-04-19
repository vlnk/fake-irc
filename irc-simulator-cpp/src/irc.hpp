#ifndef __irc_simulator__IRC__
#define __irc_simulator__IRC__

#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

#include "yaml-cpp/yaml.h"

#include "color.hpp"

class IRC {
private:
  YAML::Node _config;

  struct Character {
    std::string name;
    int numOfDialog;
    Color::Painter * color;
    double speed;
    int priority;

    //~Character() { delete color; }
    bool operator == (const Character& ch) {
      return name.compare(ch.name) == 0;
    }
  };

  struct Dialog {
    Character ch;
    std::string txt;

    Dialog() {}
    Dialog(Character c, std::string t):
      ch(c),
      txt(t) {}
  };

  std::vector<Character> _characters;
  std::vector<Dialog> _dialogs;

public:
  IRC();
  IRC(std::string, std::string);

  ~IRC() {};

  static void isCharacterEqual(const Character&);

  void run();

  friend std::ostream& operator << (std::ostream& os, const IRC& irc) {
    Color::Painter def(Color::FG_DEFAULT);

    for(Character ch : irc._characters) {
      os << "name: " << ch.name << "\n";
      os << "dialogs: " << ch.numOfDialog << "\n";
      os << "color: " << *(ch.color) << ch.color->getName() << def << "\n";
      os << "speed: " << ch.speed << "\n";
    }

    for(Dialog d : irc._dialogs) {
      os << "[" << d.ch.name << ']' << "\n";
      os << d.txt << "\n";
    }

    return os;
  }

private:
  void setCharacters(const YAML::Node&);
  void parseDialog(const std::string&);
  IRC::Dialog parseCharacter(const std::string&);

};

#endif
