//
//  potionTypes.cpp
//  cc3kcode
//
//  Created by Brandon Weng on 2016-11-26.
//  Copyright © 2016 Brandon Weng. All rights reserved.
//

#include "potionTypes.h"
#include "stats.h"
#include "math.h"
Potion::~Potion(){};

// defining the static variables for each type of potion
bool RH::isIdentified = false;
bool BA::isIdentified = false;
bool BD::isIdentified = false;
bool PH::isIdentified = false;
bool WA::isIdentified = false;
bool WD::isIdentified = false;


// RH ---------------------
RH::RH(){                       // Initalize the potion with the proper description
    description = "Restore health (RH): restore up to 10 HP (cannot exceed maximum prescribed by race)";
    value = 10;
    type = '0' ;
}

// Increase hp of s based on value and the bonusEffect
void RH::usePotion(Stats &s,float bonusEffect){
    s.addHP(ceil(this->value*bonusEffect));
    this->isIdentified = true; // player ided this potion
}

// returns if the potion has been identified
bool RH::isID(){
    return this->isIdentified;
}

std::string RH::getDescription() const{
    // returns the description of the potion if it has been indentified, Unknown Potion if it hasnt
    if (isIdentified){
        return description;
    } else {
        return "Unknown Potion";
    }
}

// BA ----------------------
BA::BA(){                       // Initalize the potion with the proper description
    description = "Boost Atk (BA): increase ATK by 5 (Under Normal Circumtances)";
    value = 5;
    type = '1';
}

void BA::usePotion(Stats &s,float bonusEffect){  // increase atk of s basd on value
    s.addATK(ceil(this->value*bonusEffect));
    this->isIdentified = true; // player ided this potion
}

bool BA::isID(){               // returns if the potion has been identified
    return this->isIdentified;
}

std::string BA::getDescription() const{
    // returns the description of the potion if it has been indentified, Unknown Potion if it hasnt
    if (isIdentified){
        return description;
    } else {
        return "Unknown Potion";
    }
}


// BD --------------------
BD::BD(){                   // Initalize the potion with the proper description
    description = "Boost Def (BD): increase Def by 5 (Under Normal Circumtances)";
    value = 5;
    type = '2';
}

void BD::usePotion(Stats &s,float bonusEffect){ // increase def of s based on value
    s.addDEF(ceil(this->value*bonusEffect));
    this->isIdentified = true; // player ided this potion
}

bool BD::isID(){               // returns if the potion has been identified
    return this->isIdentified;
}

std::string BD::getDescription() const{
    // returns the description of the potion if it has been indentified, Unknown Potion if it hasnt
    if (isIdentified){
        return description;
    } else {
        return "Unknown Potion";
    }
}

//PH ------------------
PH::PH(){               // Initalize the potion with the proper description
    description = "Poison health (PH): lose up to 10 HP (cannot fall below 0 HP)";
    value = -10;
    type = '3';
}

void PH::usePotion(Stats &s,float bonusEffect) { // decrease hp of s based on value
    s.addHP(ceil(this->value*bonusEffect));
    this->isIdentified = true; // player ided this potion
}

bool PH::isID(){            // returns if the potion has been identified
    return this->isIdentified;
}

std::string PH::getDescription() const{
    // returns the description of the potion if it has been indentified, Unknown Potion if it hasnt
    if (isIdentified){
        return description;
    } else {
        return "Unknown Potion";
    }
}


// WA ------------------
WA::WA(){               // Initalize the potion with the proper description
    description = "Wound Atk (WA): decrease Atk by 5 (Under Normal Circumtances)";
    value = -5;
    type = '4';
}

void WA::usePotion(Stats &s,float bonusEffect){  // decrease atk of s based on value
    s.addATK(ceil(this->value * bonusEffect));
    this->isIdentified = true; // player ided this potion
}

bool WA::isID(){            // returns if the potion has been identified
    return this->isIdentified;
}

std::string WA::getDescription() const{
    // returns the description of the potion if it has been indentified, Unknown Potion if it hasnt
    if (isIdentified){
        return description;
    } else {
        return "Unknown Potion";
    }
}

// WD -----------------
WD::WD(){           // Initalize the potion with the proper description
    description = "Wound Def (WD): decrease Def by 5 (Under Normal Circumtances)";
    value = -5;
    type = '5';
}

void WD::usePotion(Stats &s,float bonusEffect){ // decrease def of s based on value
    s.addDEF(ceil(this->value * bonusEffect));
    this->isIdentified = true; // player ided this potion
}

bool WD::isID(){            // returns if the potion has been identified
    return this->isIdentified;
}

std::string WD::getDescription() const{
    // returns the description of the potion if it has been indentified, Unknown Potion if it hasnt
    if (isIdentified){
        return description;
    } else {
        return "Unknown Potion";
    }
}
