#include "Color.hpp"
#include "Direction.hpp"

#ifndef TILE_HPP
#define TILE_HPP
class Tile{
  public:
  
  bool incline = false;
  bool has_color = false;
  bool has_letter = false;
  bool visited = false;
};

#endif