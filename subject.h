#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

// DO NOT MODIFY THIS FILE!

template <typename StateType> class Observer;

template <typename StateType> class Subject {
  std::vector<Observer<StateType>*> observers;
  StateType state;
 protected:
  void setState(StateType newS);
 public:
  void attach(Observer<StateType> *o);  
  void notifyObservers();
  StateType getState() const;
  virtual ~Subject() = default;
};

template <typename StateType>
void Subject<StateType>::attach(Observer<StateType> *o) {
    observers.emplace_back(o);
}

template <typename StateType>
void Subject<StateType>::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

template <typename StateType>
void Subject<StateType>::setState(StateType newS) { state = newS; }

template <typename StateType>
StateType Subject<StateType>::getState() const { return state; }

#endif
