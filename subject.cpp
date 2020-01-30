
#include "subject.h"
#include "observer.h"
#include "subscriptions.h"


// attach additional observers
void Subject::attach(Observer *o) {
    observers.push_back(o);
}

// notify all observers of type t
void Subject::notifyObservers(SubscriptionType t) {
    for (auto iterate:observers){
        if (iterate->subType() == t){
            iterate->notify(*this);
        }
    }
}

Subject::~Subject(){}
