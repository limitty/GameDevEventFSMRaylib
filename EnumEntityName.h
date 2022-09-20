#ifndef NAMES_H
#define NAMES_H

#include <string>

enum {
  Miner_Bob,
  Wife_Elsa
};

inline std::string GetNameOfEntity(int n) {
  switch (n) {
  case Miner_Bob:

    return "Miner Bob";

  case Wife_Elsa:

    return "Elsa";

  default:

    return "UNKNOWN!";
  }
}

#endif