#ifndef MINER_H
#define MINER_H
//------------------------------------------------------------------------
//
//  Name:   Miner.h
//
//  Desc:   A class defining a goldminer.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <cassert>
// #include <string>

#include "BaseGameEntity.h"
#include "EnumLocationType.h"

using namespace std;

class State;

// the amount of gold a miner must have before he feels comfortable
const int comfort_level = 5;
// the amount of nuggets a miner can carry
const int max_nuggets = 3;
// above this value a miner is thirsty
// const int ThirstLevel = 5;
// above this value a miner is sleepy
const int tiredness_threshold = 5;

class Miner : public BaseGameEntity {
private:
  State *pCurrentState;
      
  EnumLocationType enum_location;

  // how many nuggets the miner has in his pockets
  int carried_gold_amount;

  int money_in_bank;

  // the higher the value, the more tired the miner
  int fatigue;

  // the higher the value, the thirstier the miner
  // int m_iThirst;

public:
  // constructor
  Miner(int id);

  // this must be implemented
  void Update();

  // this method changes the current state to the new state. It first
  // calls the Exit() method of the current state, then assigns the
  // new state to pCurrentState and finally calls the Entry()
  // method of the new state.
  void ChangeState(State *new_state);

  EnumLocationType Location() const { return enum_location; }
  void ChangeLocation(const EnumLocationType loc) { enum_location = loc; }

  int GoldCarried() const { return carried_gold_amount; }
  void SetGoldCarried(const int val) { carried_gold_amount = val; }
  void AddToGoldCarried(const int val);
  bool PocketsFull() const { return carried_gold_amount >= max_nuggets; }

  bool Fatigued() const;
  void DecreaseFatigue() { fatigue -= 1; }
  void IncreaseFatigue() { fatigue += 1; }

  int Wealth() const { return money_in_bank; }
  void SetWealth(const int val) { money_in_bank = val; }
  void AddToWealth(const int val);

  // bool Thirsty() const;
  // void BuyAndDrinkAWhiskey() {
  //   m_iThirst = 0;
  //   money_in_bank -= 2;
  // }
};

#endif
