#ifndef observer_hpp
#define observer_hpp

#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "subscriptions.h"




class Subject;

class Observer {
public:
    virtual void notify(Subject &whoNotified) = 0;  // Notified
    virtual SubscriptionType subType() const = 0;   // return type of subscription
    virtual ~Observer() = default;
};
#endif

#endif /* observer_hpp */
