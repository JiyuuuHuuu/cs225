#include "Piece.h"
// implementation of class piece
Piece::Piece()
{
  type = "Unknown Piece Type";
}

std::string Piece::getType()
{
  return type;
}
