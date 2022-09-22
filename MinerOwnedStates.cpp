#include "State.h"
#include "Miner.h"
#include "MinerOwnedStates.h"
// #include "misc/ConsoleUtils.h"
#include "EnumEntityName.h"
#include "EnumLocationType.h"

#include "SingletonMessage.h"
#include <iostream>
#include <string>

using namespace std;
using std::cout;

#define SMI SingletonMessage::Instance()

// define this to output to a file
// #ifdef TEXTOUTPUT
// #include <fstream>
// extern std::ofstream os;
// #define cout os
// #endif

//----------------- methods for GoHomeAndSleepTilRested -----------------------

GoHomeAndSleepTilRested *GoHomeAndSleepTilRested::Instance() {
  static GoHomeAndSleepTilRested instance;

  return &instance;
}

void GoHomeAndSleepTilRested::Enter(Miner *pMiner) {
  if (pMiner->Location() != shack) {
    // SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << "\n"
         << GetNameOfEntity(pMiner->GetID()) << ": "
         << "( Walking home )";

    pMiner->ChangeLocation(shack);
  }
}

void GoHomeAndSleepTilRested::Execute(Miner *pMiner) {

  // if miner is not fatigued start to dig for nuggets again.
  if (!pMiner->Fatigued()) {
    // SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    // send a string to the setter of SingletonMessage
    SMI->AddVal(GetNameOfEntity(pMiner->GetID()) + ": " +
                "What a fantastic nap! Time to find more gold");
    // cout << "\n" << str;

    // switch to next state
    pMiner->ChangeState(EnterMineAndDigForNugget::Instance());
  }

  else {
    // sleep
    pMiner->DecreaseFatigue();

    // SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    // send a string to the setter of SingletonMessage
    SMI->AddVal(GetNameOfEntity(pMiner->GetID()) + ": " + "ZZZZ... ");
    // cout << "\n" << str;
  }
}

void GoHomeAndSleepTilRested::Exit(Miner *pMiner) {
  // SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
  // cout << "\n"
  //      << GetNameOfEntity(pMiner->GetID()) << ": "
  //      << "Leaving the house";
  SMI->AddVal(GetNameOfEntity(pMiner->GetID()) + ": " + "( Leaving the house )");
}

//----------------- methods for EnterMineAndDigForNugget ---------------------

EnterMineAndDigForNugget *EnterMineAndDigForNugget::Instance() {
  static EnterMineAndDigForNugget instance;

  return &instance;
}

void EnterMineAndDigForNugget::Enter(Miner *pMiner) {
  // if the miner is not already located at the goldmine, he must
  // change location to the gold mine
  if (pMiner->Location() != goldmine) {
    // SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    // cout << "\n"
    //      << GetNameOfEntity(pMiner->GetID()) << ": "
    //      << "Walking to the goldmine";
    SMI->AddVal(GetNameOfEntity(pMiner->GetID()) + ": " +
                "( Walking to the goldmine )");
    pMiner->ChangeLocation(goldmine);
  }
}

void EnterMineAndDigForNugget::Execute(Miner *pMiner) {
  // the miner digs for gold until he is carrying in excess of max_nuggets.
  // If he gets thirsty during his digging he packs up work for a while and
  // changes state to go to the saloon for a whiskey.
  pMiner->AddToGoldCarried(1);

  pMiner->IncreaseFatigue();

  // SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
  SMI->AddVal(GetNameOfEntity(pMiner->GetID()) + ": " + "( Picking up a nugget )");
  // cout << "\n" << GetNameOfEntity(pMiner->GetID()) << ": " << "Pickin' up a
  // nugget";
  // cout << "\n" << str;

  // if enough gold mined, go and put it in the bank
  if (pMiner->PocketsFull()) {
    pMiner->ChangeState(VisitBankAndDepositGold::Instance());
  }

  // if (pMiner->Thirsty()) {
  //   pMiner->ChangeState(QuenchThirst::Instance());
  // }
}

void EnterMineAndDigForNugget::Exit(Miner *pMiner) {
  // SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
  // cout << "\n"
  //      << GetNameOfEntity(pMiner->GetID()) << ": "
  //      << "Leaving the goldmine with full of sweet gold!";
  SMI->AddVal(GetNameOfEntity(pMiner->GetID()) + ": " +
              "Leaving the goldmine with full of sweet gold!");
}

//------------------- methods for VisitBankAndDepositGold ---------------------

VisitBankAndDepositGold *VisitBankAndDepositGold::Instance() {
  static VisitBankAndDepositGold instance;

  return &instance;
}

void VisitBankAndDepositGold::Enter(Miner *pMiner) {
  // on entry the miner makes sure he is located at the bank
  if (pMiner->Location() != bank) {
    // SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    // cout << "\n"
    //      << GetNameOfEntity(pMiner->GetID()) << ": "
    //      << "Going to the bank";
    SMI->AddVal(GetNameOfEntity(pMiner->GetID()) + ": " + "( Going to the bank )");
    pMiner->ChangeLocation(bank);
  }
}

void VisitBankAndDepositGold::Execute(Miner *pMiner) {

  // deposit the gold
  pMiner->AddToWealth(pMiner->GoldCarried());

  pMiner->SetGoldCarried(0);

  // SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
  SMI->AddVal(
      GetNameOfEntity(pMiner->GetID()) + ": " +
      "( Depositing gold. Total savings now: " + to_string(pMiner->Wealth()) + " )");
  // cout << "\n" << GetNameOfEntity(pMiner->GetID()) << ": "
  //      << "Depositing gold. Total savings now: "<< pMiner->Wealth();
  // cout << "\n" << str;

  // wealthy enough to have a well earned rest?
  if (pMiner->Wealth() >= comfort_level) {
    // SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    // cout << "\n"
    //      << GetNameOfEntity(pMiner->GetID()) << ": "
    //      << "WooHoo! Rich enough for now. Back home to my lady!";
    SMI->AddVal(GetNameOfEntity(pMiner->GetID()) + ": " +
                "WooHoo! Rich enough for now. Back home to my lady!");
    pMiner->ChangeState(GoHomeAndSleepTilRested::Instance());
  }

  // otherwise get more gold
  else {
    pMiner->ChangeState(EnterMineAndDigForNugget::Instance());
  }
}

void VisitBankAndDepositGold::Exit(Miner *pMiner) {
  // SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
  // cout << "\n"
  //      << GetNameOfEntity(pMiner->GetID()) << ": "
  //      << "Leaving the bank";
  SMI->AddVal(GetNameOfEntity(pMiner->GetID()) + ": " + "( Leaving the bank )");
}

//------------------------------------------------methods for QuenchThirst

// QuenchThirst *QuenchThirst::Instance() {
//   static QuenchThirst instance;

//   return &instance;
// }

// void QuenchThirst::Enter(Miner *pMiner) {
//   if (pMiner->Location() != saloon) {
//     pMiner->ChangeLocation(saloon);

//     // SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
//     cout << "\n"
//          << GetNameOfEntity(pMiner->GetID()) << ": "
//          << "Boy, ah sure is thusty! Walking to the saloon";
//   }
// }

// void QuenchThirst::Execute(Miner* pMiner){
// // string QuenchThirst::Execute(Miner *pMiner) {
//   string str;
//   if (pMiner->Thirsty()) {
//     pMiner->BuyAndDrinkAWhiskey();

//     //  SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
//     str = GetNameOfEntity(pMiner->GetID()) + ": " +
//           "That's mighty fine sippin liquer";
//     SMI->AddVal(str);
//     cout << "\n" << str;

//     pMiner->ChangeState(EnterMineAndDigForNugget::Instance());
//   }

//   else {
//     // SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
//     str = "\nERROR!\nERROR!\nERROR!";
//     SMI->AddVal(str);
//     // cout << "\nERROR!\nERROR!\nERROR!";
//     cout << str;
//   }
//   // return str;
// }

// void QuenchThirst::Exit(Miner *pMiner) {
//   // SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
//   cout << "\n"
//        << GetNameOfEntity(pMiner->GetID()) << ": "
//        << "Leaving the saloon, feelin' good";
// }
