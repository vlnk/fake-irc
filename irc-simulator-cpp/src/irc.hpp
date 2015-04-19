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
#include <time.h>
#include <chrono>
#include <sstream>
#include <random>
#include <thread>

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

  std::string _start_msg;
  std::string _end_msg;

  std::vector<Character> _characters;
  std::vector<Dialog> _dialogs;
  struct tm _starting_date;

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

    os << "year: " << irc._starting_date.tm_year << "\n";
    os << "month: " << irc._starting_date.tm_mon << "\n";
    os << "day: " << irc._starting_date.tm_wday << "\n";
    os << "hour: " << irc._starting_date.tm_hour << "\n";
    os << "min: " << irc._starting_date.tm_min << "\n";
    os << "sec: " << irc._starting_date.tm_sec << "\n";

    return os;
  }

private:
  void setCharacters(const YAML::Node&);
  void setDate(const YAML::Node&);

  const std::string getFormatedDate() const;

  void parseDialog(const std::string&);
  IRC::Dialog parseCharacter(const std::string&);

};

#endif
