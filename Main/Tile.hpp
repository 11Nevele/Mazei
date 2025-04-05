#include "ColorSensor.hpp"

#ifndef TILE_HPP
#define TILE_HPP
class Tile{
  public:
  bool wall[4];
  bool incline = false;
  ColorSensor::Color color = ColorSensor::unknown;
  bool has_color = false;
  bool has_letter = false;
};

#endif