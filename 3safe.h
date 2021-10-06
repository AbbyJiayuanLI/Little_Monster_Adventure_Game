#ifndef SAFE2_H
#define SAFE2_H

#include "3brick.h"
class Safe2 : public Brick2
{
public:

  Safe2(int, int);
  ~Safe2();
  int getCapacity(){ return this->capacity; }
  void setCapacity( int cap){ this->capacity = cap; }

private:
  int capacity = 0;
};

#endif // SAFE2_H
