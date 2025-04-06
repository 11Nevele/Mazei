#ifndef VECTOR_HPP
#define VECTOR_HPP
class Vector
{
  public:
  int x = 0;
  int y = 0;
  Vector(int, int);
};

Vector::Vector(int new_x, int new_y)
{
  x = new_x;
  y = new_y;
}

#endif