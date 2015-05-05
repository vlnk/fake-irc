#ifndef __irc_simulator__IRC__
#define __irc_simulator__IRC__

#include <stdio.h>
#include <iostream>
#include <iomanip>
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
#include <cstddef>

#include "yaml-cpp/yaml.h"

#include "color.hpp"

class IRC {
private:
  YAML::Node _config;

  struct Character {
    std::string name;
    Color::Painter * color;
    double speed;
    int priority;

    //~Character() { delete color; }
    bool operator == (const Character& ch)
    {
      return name.compare(ch.name) == 0;
    }
  };

  struct Dialog {
    Character ch;
    std::string txt;
    struct tm date;
    int wait;

    Dialog() {}
    Dialog(Character c, std::string t, struct tm d, int w = 0):
      ch(c),
      txt(t),
      date(d),
      wait(w) {}

    Dialog(const Dialog& other):
      ch(other.ch),
      txt(other.txt),
      date(other.date),
      wait(other.wait) {}
  };

  std::string _start_msg;
  std::string _end_msg;
  std::string _irc_model;

  int _end_wait;

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
      os << "color: " << *(ch.color) << ch.color->getName() << def << "\n";
      os << "speed: " << ch.speed << "\n";
    }

    for(Dialog d : irc._dialogs) {
      os << "[" << d.ch.name << ']' << "\n";
      os << d.txt << "\n";

      os << "year: " << d.date.tm_year << "\n";
      os << "month: " << d.date.tm_mon << "\n";
      os << "day: " << d.date.tm_wday << "\n";
      os << "hour: " << d.date.tm_hour << "\n";
      os << "min: " << d.date.tm_min << "\n";
      os << "sec: " << d.date.tm_sec << "\n";

      os << "wait: " << d.wait << "\n";
    }

    return os;
  }

private:
  void setCharacters(const YAML::Node&);
  void setStartingDate(const YAML::Node&);

  const std::string getFormatedDate(struct tm) const;
  const std::string getFormatedMessage(const IRC::Dialog&) const;

  void createDialog(const std::string&);
  void parseCharacter(const std::string&, IRC::Dialog&);
  void parseDate(const std::string&, IRC::Dialog&);

  const int parseWait(const std::string&, const std::size_t pos = 0) const;
  void parseWait(const std::string&, IRC::Dialog&, const std::size_t pos = 0);

  IRC::Dialog parseCharacter(const std::string&);
};

#endif
