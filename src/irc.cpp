#include "IRC.hpp"

IRC::IRC(std::string config_yaml, std::string dialog_txt) {
  try {
    YAML::Node config = YAML::LoadFile(config_yaml);

    _start_msg = config["start"].as<std::string>();
    _end_msg = config["end"].as<std::string>();
    _irc_model = config["model"].as<std::string>();

    _end_wait = config["end_wait"].as<int>();

    std::cout << _irc_model << std::endl;

    setCharacters(config["characters"]);
    createDialog(dialog_txt);
    //setDate(config["date"]);
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

void IRC::createDialog(const std::string& dialog_txt) {
  std::ifstream file;
  file.exceptions(std::ifstream::failbit);

  std::string ch_name;
  Dialog dialog;

  int dialog_counter = 0;

  std::string line;

  try {
    file.open(dialog_txt);

    while (getline(file, line)) {
      if (line[0] == '#') {
        if (dialog_counter > 0) {
          _dialogs.push_back(Dialog(dialog));

          dialog.txt.clear();
          ch_name.clear();
        }

        parseCharacter(line, dialog);
        parseDate(line, dialog);
        parseWait(line, dialog);

        dialog_counter++;
      }
      else {
        dialog.txt.append(line);
      }
    }

    _dialogs.push_back(Dialog(dialog));

  }
  catch (std::ifstream::failure e) {
      std::cerr << "<dialog.txt> path is invalid!" << std::endl;
      throw std::ifstream::failure("parser failure");
  }
  catch(std::invalid_argument& ia) {
    std::cerr << "Exception caught: " << ia.what() << '\n';
    std::cerr << "Exception thrown on dialog number " << dialog_counter << std::endl;
  }
}

void IRC::parseCharacter(const std::string& line, IRC::Dialog& dialog) {
  size_t begin = line.find("[") + 1;
  size_t end = line.find("]");

  std::string ch_name = line.substr(begin, end - begin);
  //std::cout << ch_name << std::endl;

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
}

void IRC::parseDate(const std::string& line, IRC::Dialog& d) {
  std::size_t begin = line.find('(') + 1;
  std::size_t end = line.find(')');

  std::string ch_date = line.substr(begin, end - begin);

  std::istringstream ss(ch_date);

  std::cout << ch_date << std::endl;
  ss >> std::get_time(&(d.date), "%d/%m/%Y %S:%M:%H");

  //std::cout << std::put_time(&(d.date), "%c") << std::endl;

  if (ss.fail()) {
    throw std::invalid_argument("invalid match for date");
  }
}

const int IRC::parseWait(const std::string& line, const std::size_t pos) const {
  std::size_t begin = line.find('{') + 1;
  std::size_t end = line.find('}');

  std::string ch_wait = line.substr(begin, end - begin);

  if (ch_wait.empty() || line.compare(ch_wait) == 0) {
    return 0;
  }
  else {
    return std::stoi(ch_wait);
  }
}

void IRC::parseWait(const std::string& l, IRC::Dialog& d, const std::size_t p) {
  d.wait = parseWait(l, p);
  //std::cout << d.wait << std::endl;
}

void IRC::run() {
  typedef std::chrono::duration<int,std::milli> milli_t;
  std::default_random_engine gen;

  std::cout << _start_msg << std::endl;

  //A FORMATER
  for(Dialog dialog : _dialogs) {

    if (dialog.wait > 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(dialog.wait));
    }

    std::cout << getFormatedMessage(dialog);
    std::this_thread::sleep_for (std::chrono::seconds(1));

    std::size_t i = 0;
    while(i < dialog.txt.length()) {

      if (dialog.txt[i] == '{') {
        int wait = parseWait(dialog.txt, i);
        std::this_thread::sleep_for(std::chrono::milliseconds(wait));
        while(dialog.txt[i] != '}') ++i;
      }
      else {
        std::uniform_real_distribution<double> dist(0,dialog.ch.speed);
        std::chrono::milliseconds ms(static_cast<int>(dist(gen)*1000));

        //std::chrono::milliseconds ms(dist(gen));

        std::this_thread::sleep_for (ms);

        std::cout << dialog.txt[i];
        std::cout.flush();
      }

      ++i;
    }

    std::cout << std::endl;
    std::cout.flush();
  }

  std::cout << _end_msg << std::endl;

  std::this_thread::sleep_for(std::chrono::milliseconds(_end_wait));
}

void IRC::setStartingDate(const YAML::Node& node) {
  time_t local_time = time(NULL);
  struct tm * local_tm = localtime(&local_time);
  struct tm starting_date;

  if (node["year"].as<std::string>().compare("local") == 0) {
    starting_date.tm_year = local_tm->tm_year;
  }
  else {
    starting_date.tm_year = node["year"].as<int>();
  }

  if (node["month"].as<std::string>().compare("local") == 0) {
    starting_date.tm_mon = local_tm->tm_mon;
  }
  else {
    starting_date.tm_mon = node["month"].as<int>();
  }

  if (node["day"].as<std::string>().compare("local") == 0) {
    starting_date.tm_wday = local_tm->tm_wday;
  }
  else {
    starting_date.tm_wday = node["day"].as<int>();
  }

  if (node["hour"].as<std::string>().compare("local") == 0) {
    starting_date.tm_hour = local_tm->tm_hour;
  }
  else {
    starting_date.tm_hour = node["hour"].as<int>();
  }

  if (node["min"].as<std::string>().compare("local") == 0) {
    starting_date.tm_min = local_tm->tm_min;
  }
  else {
    starting_date.tm_min = node["min"].as<int>();
  }

  if (node["sec"].as<std::string>().compare("local") == 0) {
    starting_date.tm_sec = local_tm->tm_sec;
  }
  else {
    starting_date.tm_sec = node["sec"].as<int>();
  }

}

const std::string IRC::getFormatedDate(struct tm date) const {
  std::stringstream ss;

  ss << '[';
  ss << date.tm_hour << ":";
  ss << date.tm_min << ":";
  ss << date.tm_sec;
  ss << ']';

  return ss.str();
}

const std::string IRC::getFormatedMessage(const IRC::Dialog& dialog) const {
  std::ostringstream msg;
  Color::Painter def(Color::FG_DEFAULT);

  std::size_t i = 0;
  while (i < _irc_model.length()) {
    if (_irc_model[i] == '%') {
      ++i;

      if (_irc_model[i] == 'P') {
        msg << *(dialog.ch.color) << dialog.ch.name << def;
      }
      else {
        std::string fmt("%");
        fmt += _irc_model[i];

        msg << std::put_time(&(dialog.date), fmt.c_str());

        if (msg.fail()) {
          throw std::invalid_argument("invalid MODEL PARAMETER !");
        }
      }
    }
    else {
      msg << _irc_model[i];
    }

    ++i;
  }

  msg << '\n';

  return msg.str();
}
