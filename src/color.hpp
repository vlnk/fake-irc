#ifndef __irc_simulator__Color__
#define __irc_simulator__Color__

#include <ostream>
namespace Color {
  enum Code
  {
    FG_RED      = 31,
    FG_GREEN    = 32,
    FG_BLUE     = 34,
    FG_DEFAULT  = 39,
    BG_RED      = 41,
    BG_GREEN    = 42,
    BG_BLUE     = 44,
    BG_DEFAULT  = 49
  };

  class Painter {
  private:
    Code _palette;
    std::string _name;

  public:
    Painter(Code palette, std::string name):
      _palette(palette),
      _name(name) {}

    Painter(Code palette) : Painter( palette, "unknow" ) {}

    const std::string& getName() const { return _name; }

    static Painter* selectColor ( std::string colorName = "default" )
    {
      Painter * painter;

      if (colorName.compare("red") == 0)
      {
        painter = new Painter(FG_RED, colorName);
      }
      else if (colorName.compare("green") == 0)
      {
        painter = new Painter(FG_GREEN, colorName);
      }
      else if (colorName.compare("blue") == 0)
      {
        painter = new Painter(FG_BLUE, colorName);
      }
      else
      {
        painter = new Painter(FG_DEFAULT, "default");
      }

      return painter;
    }

    friend std::ostream& operator << ( std::ostream& os, const Painter& p )
    {
      return os << "\033[" << p._palette << "m";
    }
  };
}

#endif
