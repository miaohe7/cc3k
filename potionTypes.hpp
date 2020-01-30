//
//  potionTypes.h
//  cc3kcode
//
//  Created by Brandon Weng on 2016-11-26.
//  Copyright © 2016 Brandon Weng. All rights reserved.
//

#ifndef potionTypes_hpp
#define potionTypes_hpp
#include "potion.h"


// Restore Health Potion. increase hp
class RH:public Potion {
    static bool isIdentified;
public:
    RH();
    void usePotion(Stats &s,float) override;
    bool isID();
    std::string getDescription() const override;
};


// Boost Attack Potion, increase atk
class BA: public Potion {
    static bool isIdentified;
public:
    BA();
    void usePotion(Stats &s,float) override;
    bool isID();
    std::string getDescription() const override;
};


// Boost Defense potion. increase def
class BD: public Potion {
    static bool isIdentified;
public:
    BD();
    void usePotion(Stats &s,float) override;
    bool isID();
    std::string getDescription() const override;
};


// Poison Health Potion,decrease hp;hp cannot fall under 0
class PH: public Potion {
    static bool isIdentified;
public:
    PH();
    void usePotion(Stats &s,float) override;
    bool isID();
    std::string getDescription() const override;
};


// Wound Attack potion, decrease atk
class WA: public Potion {
    static bool isIdentified;
public:
    WA();
    void usePotion(Stats &s,float) override;
    bool isID();
    std::string getDescription() const override;
};


// Wound defense potion, decrease def
class WD: public Potion {
    static bool isIdentified;
public:
    WD();
    void usePotion(Stats &s,float) override;
    bool isID();
    std::string getDescription() const override;
};


#endif /* potionTypes_hpp */
