// Copyright 2021 VadMack

#include <ocean.h>
#include <iostream>
#include <vector>
#include <zconf.h>
#include "predator.h"
#include "prey.h"
#include "stone.h"

Ocean::Ocean(int sizeM, int sizeN, int numOfStones, int numOfPreys, int numOfPredators) {
  this->sizeM = sizeM;
  this->sizeN = sizeN;
  cells = new Cell *[sizeM];
  for (int i = 0; i < sizeM; ++i) {
    cells[i] = new Cell[sizeN];
    for (int j = 0; j < sizeN; ++j) {
      cells[i][j].init({i, j}, this);
    }
  }
  addObjects(ObjType::STONE, numOfStones);
  addObjects(ObjType::PREY, numOfPreys);
  addObjects(ObjType::PREDATOR, numOfPredators);
}

void Ocean::addObjects(ObjType type, int number) {
  for (int i = 0; i < number;) {
    int x = rand() % sizeM;
    int y = rand() % sizeN;

    if (cells[x][y].getObject())
      continue;
    Object *obj = nullptr;
    if (type == ObjType::STONE) {
      obj = new Stone(&cells[x][y]);
    } else if (type == ObjType::PREY) {
      obj = new Prey(&cells[x][y]);
    } else if (type == ObjType::PREDATOR) {
      obj = new Predator(&cells[x][y]);
    }

    cells[x][y].setObject(obj);
    stuff.push_back(obj);
    i++;
  }
}

void Ocean::print() const {
  for (int i = 0; i < sizeM; ++i) {
    for (int j = 0; j < sizeN; ++j) {
      if (cells[i][j].getObject()) {
        std::cout << cells[i][j].getObject()->GetColor();
      } else {
        std::cout << BLUE;
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

Cell *Ocean::findCellAround(Pair coord) {
  std::vector<Cell *> emptyCells;

  size_t startX = 0;
  size_t finishX = 0;
  if (coord.x - 1 < 0) {
    startX = 0;
  } else {
    startX = coord.x - 1;
  }
  if (coord.x + 1 > sizeN - 1) {
    finishX = sizeN - 1;
  } else {
    finishX = coord.x + 1;
  }

  size_t startY = 0;
  size_t finishY = 0;

  if (coord.y - 1 < 0) {
    startY = 0;
  } else {
    startY = coord.y - 1;
  }
  if (coord.y + 1 > sizeM - 1) {
    finishY = sizeM - 1;
  } else {
    finishY = coord.y + 1;
  }

  for (int i = startX; i <= finishX; ++i) {
    for (int j = startY; j <= finishY; ++j) {
      if (!cells[i][j].getObject()) {
        emptyCells.push_back(&cells[i][j]);
      }
    }
  }

  if (!emptyCells.empty()) {
    return emptyCells[rand() % emptyCells.size()];
  } else {
    return nullptr;
  }
}

void Ocean::run() {
  print();
  for (int i = 0; i < 1000; ++i) {
    /*for (auto &obj : stuff) {
      if (!obj->live()) {
        stuff.erase(obj);
      }
    }*/

    int end = stuff.size();
    int index = 0;

    for (auto obj = stuff.begin(); obj != stuff.end(); obj++) {
      if (!(*obj)->live()) {
        stuff.erase(obj++);
        (*obj)->GetCell()->killMe();
      }
    }

    system("clear");
    print();
    usleep(100000);
  }
}

void Ocean::addObject(Object *object) {
  stuff.push_back(object);
}

void Ocean::removeObject(Object *object) {
  //stuff.erase(object);
}


