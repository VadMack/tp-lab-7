// Copyright 2021 VadMack

#ifndef INCLUDE_STONE_H_
#define INCLUDE_STONE_H_

#include "cell.h"
class Stone : public Object {
 public:
  explicit Stone(Cell *cell) : Object(cell) {
    color = GREY;
  }
  bool live() {};
};

#endif  // INCLUDE_STONE_H_
