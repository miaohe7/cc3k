#include "enemy.h"
#include "treasureTypes.h"
#include <math.h>
#include <cstdlib>
#include <stdlib.h>
#include "pc.h"
#include "helpers.h"


// Enemy
Enemy::Enemy(int hp,int atk,int def):HP{hp},Atk{atk},Def{def}{};

//accessor imp
int Enemy::getHP(){
    return(this->HP);
}

int Enemy::getATK(){
    return(this->Atk);
}

int Enemy::getDEF(){
    return(this->Def);
}

bool Enemy::isHostile(){
    return true;
}


//mutator imp

void Enemy::addHP(int Damage){
    this->HP += Damage;
}

void Enemy::setHP(int hp){
    this->HP = hp;
}

void Enemy::setATK(int atk){
    this->Atk = atk;
}

void Enemy::setDEF(int def){
    this->Def = def;
}



//methods

// virtual method that can be overriden by children

Enemy::Enemy():HP{0},Atk(0),Def{0} {}

int Enemy::attack(PC * pc){
    return pc->beStruckBy(this);
}

// Virtual method that can be overriden by children
int Enemy::beStruckBy(PC *pc){
    int damage = DamageCalc(pc->getATK(),getDEF());
    if(damage >= getHP()){
      setHP(0);
      return -1; // Tells level that monster died
    }
    addHP(- damage);
    return damage; // damage was deal but monster didnt die
}

Enemy::~Enemy(){};


// HUMANS ------------------------------
//Human drops two normal piles of gold

Human::Human():Enemy{140,20,20}{
    type = 'H';

}

//2 piles of normal gold

Human::~Human(){}


//Merchant --------------------------
bool Merchant::hostile = false;


Merchant::Merchant():Enemy{30,70,5}{
    type =  'M';
}


bool Merchant::isHostile(){
    return hostile;
}

void Merchant::becomehostile(){ // Merchant is now hostile
    hostile = true;
}

int Merchant::beStruckBy(PC * pc) {
  this->becomehostile();
  int damage = DamageCalc(pc->getATK(),getDEF());
    if(damage >= getHP()){
        setHP(0);
        return -1; // Tells floor merchant died
    }else{
        addHP(-damage); // decrease enemy hp
        return damage;  // tells floor monster didnt die
    }
}

Merchant::~Merchant(){}


// ORCS -----------------------

////Orcs does 50% more damage to goblins


Orcs::Orcs():Enemy{180,30,25}{
    type = 'O';
}


Orcs::~Orcs(){}

///Dwarf ------------------------

Dwarf::Dwarf():Enemy{100,20,30}{
    type = 'W';
}

Dwarf::~Dwarf(){}

//Elf

Elf::Elf():Enemy{140,30,10}{
    type = 'E';
}

Elf::~Elf(){}

///Dragon

Dragon::Dragon():Enemy{150,20,20}{
    type  = 'D';
}

// Dragon gets attacked by the PC
int Dragon::beStruckBy(PC *pc){
  int damage = DamageCalc(pc->getATK(),getDEF());
  if(damage >= getHP()){
        this->setHP(0); // Dragon Dies!
        gold->dragonDied(); // The Treasure can now be picked up
        return -1; // Tells level that dragon died
    }
    addHP(-damage);
  return damage; // tells level that enemy didnt die but got hit
}

// binds a DragonHoard to a Dragon

void Dragon::bindHoard(DragonHoard *hoard){
  gold = hoard;
}


Dragon::~Dragon(){}

////Halfling

Halfling::Halfling():Enemy{100,15,20}{
    type = 'L';
}

int Halfling::beStruckBy(PC *pc){
    if((rand () % 2) == 0) return 0; // Tells the Floor that the hit missed!

    int damage = DamageCalc(pc->getATK(),getDEF());

    if(damage >= getHP()){
      this->setHP(0); // Halfling Dies
      return -1; // Tells the level that the enemy died
    }

    addHP(-damage);
    return damage; // tells the level that the enemy got hit but didnt die
}

Halfling::~Halfling(){}
