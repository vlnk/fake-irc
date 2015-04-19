#include "IRC.hpp"
#include <iostream>

void help(std::string prog_name) {
  std::cout << "USAGE: " << prog_name << " <OPTION>" << std::endl;
  std::cout << "DISPOSABLE OPTIONS:" << std::endl;
  std::cout << "\t start" << "\t Start the configured irc conversation" << std::endl;
  std::cout << "\t check" << "\t Check if input files are well configured" << std::endl;
  std::cout << std::endl;
  std::cout << "for other helps see documentation" << std::endl;
}

int main(int argc, char * argv[]) {
  if (argc != 2) {
    help(argv[0]);
  }
  else {
    std::string opt(argv[1]);

    if (opt.compare("check") == 0) {
      IRC * irc = new IRC();

      std::cout << "Welcome to this wonderful irc-simulator !" << std::endl;
      std::cout << *irc << std::endl;
      std::cout << "All configuration files are parsed successfully." << std::endl;

      delete irc;
    }
    else if (opt.compare("start") == 0) {
      IRC * irc = new IRC();
      delete irc;
    }
    else {
      help(argv[0]);
    }
  }
  return 0;
}
