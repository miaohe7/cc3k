#include "treasureTypes.h"
#include "stats.h"

// Treasures -----------------------------
bool Treasure::canPickup(){
    return true;
}
// Base Class Public Methods
bool Treasure::isThisBinded(){
    return isBinded;
}

void Treasure::bindThis(){
    isBinded = true;
}

// SmallHoard
SmallHoard::SmallHoard(){    // Initailizes a small pile of gold
    description = "A small pile of gold, value = 1";
    value = 1;
    type = '7';
}

void SmallHoard::pickedUpBy(Stats &s){  // Increase the goldValue of s by 1
    s.addGold(value);
}

SmallHoard::~SmallHoard(){}

// Normal Hoard
NormalHoard::NormalHoard(){   // Initalizes a normal pile of gold
    description = "A normal pile of gold, value = 2";
    value = 2;
    type = '6';
}

void NormalHoard::pickedUpBy(Stats &s){ // Increase the goldValue of s by 2
    s.addGold(value);
}

NormalHoard::~NormalHoard(){}

// merchant Hoard
MerchantHoard::MerchantHoard(){ // Initalizes a merchant's dropped gold
    description = "Gold carried by a merchant, value = 4";
    value = 4;
    type = '8';
}

void MerchantHoard::pickedUpBy(Stats &s){ // Increase the goldValue of s by 4
    s.addGold(value);
}

MerchantHoard::~MerchantHoard(){}

// dragon Hoard
DragonHoard::DragonHoard(){    // Initalize a pile of gold guarded by a dragon
    description = "Gold protected by a dragon, value = 6";
    value = 6;
    type = '9';
}

void DragonHoard::dragonDied(){
    canBePickedUp = true;
}

void DragonHoard::pickedUpBy(Stats &s){ // Increase the goldValue of s by 6
    s.addGold(value);
}

bool DragonHoard::canPickup(){  // Tells the level whether the treasure can be picked up
  return canBePickedUp;
}

DragonHoard::~DragonHoard(){}
