#ifndef SINGLETON_MESSAGE_H
#define SINGLETON_MESSAGE_H

#include <string>
#include <vector>

using namespace std;

class SingletonMessage {
private:

  vector<string> message_vector{};

  // constructor
  SingletonMessage() {}

  // copy ctor and assignment should be private
  //   SingletonMessage(const SingletonMessage &);
  //   SingletonMessage &operator=(const SingletonMessage &);

public:
  // destructor
  ~SingletonMessage() {}
  
  // methods
  void AddVal(string val) { message_vector.push_back(val); } // add value to the last position
  string GetVal() const { return message_vector.at(0); } // get the first value
  void DelFirstVal() { message_vector.erase(message_vector.begin()); } // delete the first value. 
  bool CheckEmpty() { return message_vector.empty(); }

  static SingletonMessage *Instance();
};

#endif