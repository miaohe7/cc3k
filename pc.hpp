#ifndef PC_H
#define PC_H
#include "treasure.h"
#include "enemy.h"
#include <string>
#include "stats.h"
#include "potion.h"


struct coordinates{
    int x,y;
};


class PC: public Object{
protected:
    int initialAtk;
    int initialDef;
    //const int initialAtk = 25;
    //const int initialDef = 25;
    Stats *data;
public:
    PC(int,int,int,bool);
    //Accessor
    int getinitialATK();
    int getinitialDEF();
    
    int getHP();
    //return HP
    int getATK();
    //return ATK
    int getDEF();
    //return DEF

    int getGold();
    //mutator
    void setATK(int);
    void setDEF(int);
    
    //Methods
    virtual int attack(Enemy * enemy);
    virtual int beStruckBy(Enemy * enemy);
    virtual void takePotion(Potion * potion);
    virtual void takeGold(Treasure * gold);
    virtual void takeGold(int);
    virtual ~PC() = 0;//dtor part may need reconsider
};

class Shade : public PC{
public:
    Shade();//initial the Shade
    ~Shade();//dtor
};

class Drow : public PC{
public:
    Drow();//initialize the Drow
    void takePotion(Potion * potion) override;
    ~Drow();//dtor
};

class Vampire : public PC{
public:
    Vampire();//Initialize the Vampire
    int attack(Enemy * ) override;
    ~Vampire();//dtor
};

class Troll : public PC{
public:
    Troll(); //Initialize the Troll
    int attack(Enemy *) override;
    int beStruckBy(Enemy * ) override;
    ~Troll();//dtor
};

class  Goblin : public PC{
public:
    Goblin(); //Initialize the Goblin
    int attack(Enemy * ) override;
    int beStruckBy(Enemy * ) override;
    ~Goblin();//dtor
};


#endif /* pc_hpp */
