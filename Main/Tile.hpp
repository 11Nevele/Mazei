#include "Color.hpp"
#include "Direction.hpp"

#ifndef TILE_HPP
#define TILE_HPP


class Tile{
  private:
  char memory = 0;
  public:
  
  bool GetIncline(){return memory & (1 << 0);}
  void SetIncline(bool b){memory = (memory & ~(1 << 0)) | (int(b) << 0);}

  bool GetHasColor(){return memory & (1 << 1);}
  void SetHasColor(bool b){memory = (memory & ~(1 << 1)) | (int(b) << 1);}

  bool GetHasLetter(){return memory & (1 << 2);}
  void SetHasLetter(bool b){memory = (memory & ~(1 << 2)) | (int(b) << 2);}

  bool GetVisited(){return memory & (1 << 3);}
  void SetVisited(bool b){memory = (memory & ~(1 << 3)) | (int(b) << 3);}
};
#endif