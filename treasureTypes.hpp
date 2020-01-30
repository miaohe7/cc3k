//
//  treasureTypes.h
//  cc3kcode
//
//  Created by Brandon Weng on 2016-11-26.
//  Copyright © 2016 Brandon Weng. All rights reserved.
//

#ifndef treasureTypes_hpp
#define treasureTypes_hpp
#include "treasure.h"
#include "subscriptions.h"
#include "observer.h"

// Small gold pile, value of 1
class SmallHoard:public Treasure{
public:
    SmallHoard();
    void pickedUpBy(Stats &) override;
    ~SmallHoard();
};

// Normal gold pile, value of 2
class NormalHoard:public Treasure{
public:
    NormalHoard();
    void pickedUpBy(Stats &) override;
    ~NormalHoard();
};

// Merchant gold pile, drop on death of a merchant value of 4
class MerchantHoard:public Treasure{
public:
    MerchantHoard();
    void pickedUpBy(Stats &) override;
    ~MerchantHoard();
};


// Dragon's gold pile, can only be picked up if the dragon dies
//  value of 6
class DragonHoard:public Treasure{
    bool canBePickedUp = false;
public:
    DragonHoard();
    void dragonDied(); // Hoard can now be picked up
    bool canPickup()override;
    void pickedUpBy(Stats &) override;
    ~DragonHoard();
};
#endif /* treasureTypes_hpp */
