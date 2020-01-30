#ifndef ENEMY_H
#define ENEMY_H

class PC;
#include "Object.h"
class DragonHoard;

class Enemy: public Object{
private:
    int HP;
    int Atk;
    int Def;
public:

    Enemy(int,int,int);
    //accessor
    int getHP(); //return enemy HP;
    int getATK(); //return enemy Atk;
    int getDEF(); //return enemy Def;
    virtual bool isHostile(); // Returns enemy hostility
    
    
    //mutator
    void addHP(int Damage);  // increment current hp
    void setHP(int hp);     // set current hp
    void setATK(int atk);
    void setDEF(int def);
   
    
    //methods
    Enemy();//initializer
    virtual int attack (PC *); // Enemy Attacks the PC, can be modded
    virtual int beStruckBy(PC *); // Virtual

    //notifier
    virtual ~Enemy();
};

class Human : public Enemy{
public:
    Human();//initializer
    ~Human();//dtor
};

class Merchant : public Enemy{
    static bool hostile;
public:
    Merchant();//initializer
    bool isHostile() override; //return whether if it is hostile
    static void becomehostile();
    int beStruckBy(PC * pc) override;

    ~Merchant() override;//dtor
};

class Orcs : public Enemy{
public:
    Orcs();//Initializer
    ~Orcs() override;//dtor
};

class Dwarf : public Enemy{
public:
    Dwarf();//Initializer
    ~Dwarf() override;//dtor
};

class Elf : public Enemy{
public:
    Elf();//Initializer
    ~Elf();//dtor
};


class Dragon : public Enemy {
    DragonHoard *gold;
public:
    Dragon();//Initializer
    int beStruckBy(PC * pc) override;
    void bindHoard(DragonHoard *);
    ~Dragon();//dtor
};

class Halfling : public Enemy{
public:
    Halfling();//Initializer
    int beStruckBy(PC * pc) override;
    ~Halfling();//dtor
};

#endif /* enemy_hpp */
