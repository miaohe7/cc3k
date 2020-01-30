//
//  stats.cpp
//  cc3kcode
//
//  Created by Brandon Weng on 2016-11-24.
//  Copyright © 2016 Brandon Weng. All rights reserved.
//

#include "stats.h"
#include <algorithm>


// Initialize the base stats
Stats::Stats(int hp,int atk,int def,bool hasMax):hp{hp},atk{atk},def{def}{
    this->maxHP = hp;      // max hp to prevent classes going over
    this->goldValue = 0;
    this->hasMaxHP = hasMax;
}

// Defining the accessor methods

int Stats::getHP(){  // return current hp
    return hp;
}

int Stats::getATK(){  // return current atk
    return atk;
}

int Stats::getDEF(){  // return current def
    return def;
}

int Stats::getMaxHP(){  // return maxHP
    return maxHP;
}

int Stats::getGoldValue(){ // return goldvalue
    return goldValue;
}

// Defining the mutator methods

void Stats::setDEF(int d){ //set the def
    def = d;
}

void Stats::setATK(int a){ //set the atk
    atk = a;
}

void Stats::addHP(int num){  // add num to hp
    if (hasMaxHP) {          // if there's a limit on max hp
        hp = std::max(0,std::min((hp + num),maxHP));
    } else {                 // no limit
        hp = std::max(hp + num,0);
    }
}

void Stats::addATK(int num){ // add num to atk
    atk = std::max((atk + num),0);  // atk cannot fall below 0

}

void Stats::addDEF(int num){  // add num to def
    def = std::max((def + num),0);   // def cannot fall below 0
}

void Stats::addGold(int num){  // add num to gold
    goldValue +=num;                // increase gold
}
