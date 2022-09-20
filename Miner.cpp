#include "Miner.h"
#include "MinerOwnedStates.h"
#include <string>

using namespace std;

Miner::Miner(int id):
      BaseGameEntity(id), 
      enum_location(shack), 
      carried_gold_amount(0),
      money_in_bank(0), 
      fatigue(0),
      // m_iThirst(0), 
      pCurrentState(GoHomeAndSleepTilRested::Instance())  // Use GoHomeAndSleepTilRested state to begin
      {}

//--------------------------- ChangeState -------------------------------------
//-----------------------------------------------------------------------------
void Miner::ChangeState(State *pNewState) {
  // make sure both states are both valid before attempting to
  // call their methods
  assert(pCurrentState && pNewState);

  // call the exit method of the existing state
  pCurrentState->Exit(this);

  // change state to the new state
  pCurrentState = pNewState;

  // call the entry method of the new state
  pCurrentState->Enter(this);
}

//-----------------------------------------------------------------------------
void Miner::Update()
{
  // m_iThirst += 1;

  if (pCurrentState) {
    pCurrentState->Execute(this);
  }
}

//-----------------------------------------------------------------------------
void Miner::AddToGoldCarried(const int val) {
  carried_gold_amount += val;

  if (carried_gold_amount < 0)
    carried_gold_amount = 0;
}

//-----------------------------------------------------------------------------
void Miner::AddToWealth(const int val) {
  money_in_bank += val;

  if (money_in_bank < 0)
    money_in_bank = 0;
}

//-----------------------------------------------------------------------------
bool Miner::Fatigued() const {
  if (fatigue > tiredness_threshold) {
    return true;
  }

  return false;
}

//-----------------------------------------------------------------------------
// bool Miner::Thirsty() const {
//   if (m_iThirst >= ThirstLevel) {
//     return true;
//   }

//   return false;
// }
