#include "SingletonMessage.h"

SingletonMessage *SingletonMessage::Instance() {
  static SingletonMessage instance;
  return &instance;
}