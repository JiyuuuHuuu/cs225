#pragma once
#include <string>

class Piece
{
  private:
    std::string type;

  public:
    Piece();
    std::string getType();
};
