#include "irc.hpp"

IRC::IRC(std::string config_yaml, std::string dialog_txt) {
  try {
    YAML::Node config = YAML::LoadFile(config_yaml);
    setCharacters(config["characters"]);
    parseDialog(dialog_txt);
  }
  catch(std::invalid_argument& ia) {
    std::cerr << "exception caught: " << ia.what() << "\n";
  }
  catch(std::exception& e) {
    std::cerr << "exception caught: " << e.what() << '\n';
  }
}

IRC::IRC():IRC("config.yaml", "dialog.txt") {}

void IRC::setCharacters(const YAML::Node& node) {
  bool isNullPriorityFound = false;

  for(std::size_t i = 0; i < node.size(); ++i) {
    Character ch;

    ch.name = node[i]["name"].as<std::string>();
    ch.numOfDialog = node[i]["num"].as<int>();

    ch.color = Color::Painter::selectColor(node[i]["color"].as<std::string>());

    double speed = node[i]["speed"].as<double>();
    if (speed > 0 && speed < 1)
      ch.speed = speed;
    else
      throw std::invalid_argument("bad speed range (0 < speed < 1)");

    int priority = node[i]["status"].as<int>();

    if (priority == 0 && isNullPriorityFound)
      throw std::invalid_argument("null priority must be unique !");
    else {
      ch.priority = priority;
      if (priority == 0) isNullPriorityFound = true;
    }

    _characters.push_back(ch);
  }
}

void IRC::parseDialog(const std::string& dialog_txt) {
  std::ifstream file;
  file.exceptions(std::ifstream::failbit);

  std::string ch_name;
  Dialog dialog;

  int dialog_counter = 0;

  std::string line;

  try {
    file.open(dialog_txt);

    while (getline(file, line)) {
      if (line[0] == '[') {
        if (dialog_counter > 0) {
          _dialogs.push_back(Dialog(dialog.ch, dialog.txt));

          dialog.txt.clear();
          ch_name.clear();
        }

        dialog = parseCharacter(line);

        dialog_counter++;
      }
      else {
        dialog.txt.append(line);
      }
    }

    _dialogs.push_back(Dialog(dialog.ch, dialog.txt));

  }
  catch (std::ifstream::failure e) {
      std::cerr << "<dialog.txt> path is invalid!" << std::endl;
      throw std::ifstream::failure("parser failure");
  }
  catch(std::invalid_argument& ia) {
    std::cerr << "exception caught: " << ia.what() << "\n";
  }
}

IRC::Dialog IRC::parseCharacter(const std::string& line) {
  std::size_t pos_1 = line.find('[');
  std::size_t pos_2 = line.find(']');

  Dialog dialog;

  std::string ch_name = line.substr(pos_1 + 1, pos_2 - 1);

  bool isFind = false;

  for(Character ch : _characters) {
    if (ch.name.compare(ch_name) == 0) {
      dialog.ch = ch;
      isFind = true;
      break;
    }
  }

  if (!isFind) {
    throw std::invalid_argument("invalid match between config and dialog");
  }

  return dialog;
}

void IRC::run() {
  
}
