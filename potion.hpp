//
//  potion.h
//  cc3kcode
//
//  Created by Brandon Weng on 2016-11-26.
//  Copyright © 2016 Brandon Weng. All rights reserved.
//

#ifndef potion_hpp
#define potion_hpp
#include <string>
#include "Object.h"

class Stats;

class Potion:public Object{
protected:
    std::string description;    //description of the potion thats identified
    int value;                  // The value of the potion
public:
    virtual void usePotion(Stats &s,float) = 0;  // Mutate s based on value
    virtual std::string getDescription() const = 0; // get description or just Unknown
    ~Potion();
};
#endif /* potion_hpp */
