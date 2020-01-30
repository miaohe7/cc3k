
#ifndef subject_hpp
#define subject_hpp
#include <vector>
#include "subscriptions.h"
#include "Object.h"
class Observer;

class Subject {
    std::vector<Observer*> observers;    // Vector of Observer pointers
public:
    void attach(Observer *o);
    void notifyObservers(SubscriptionType t);
    virtual Coordinates getCoord() = 0;
    virtual Object* getObject() = 0;
    virtual bool isInChamber() = 0;
    virtual ~Subject() = 0;
};
#endif /* subject_hpp */
