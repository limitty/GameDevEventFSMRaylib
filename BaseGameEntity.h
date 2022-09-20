#ifndef ENTITY_H
#define ENTITY_H
#include <string>

using namespace std;
//------------------------------------------------------------------------
//
//  Name:   BaseGameEntity.h
//
//  Desc:   Base class for a game object
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

class BaseGameEntity {

private:
  // every entity must have a unique identifying number
  int entity_id;

  // this is the next valid ID. Each time a BaseGameEntity is instantiated
  // this value is updated
  static int next_valid_id;

  // this must be called within the constructor to make sure the ID is set
  // correctly. It verifies that the value passed to the method is greater
  // or equal to the next valid ID, before setting the ID and incrementing
  // the next valid ID
  void SetID(int val);

public:
  // constructor
  BaseGameEntity(int id) { SetID(id); }

  // destructor
  virtual ~BaseGameEntity() {}

  // all entities must implement an update function
  virtual void Update() = 0;

  int GetID() const { return entity_id; }
};

#endif
