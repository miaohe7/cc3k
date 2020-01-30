#include "pc.h"
#include <math.h>
#include <stdlib.h>
#include "helpers.h"
//remove this after!
#include <iostream>

using namespace std;

//PC
PC::PC(int hp,int atk,int def,bool maxhp):data{new Stats{hp,atk,def,maxhp}}{
    type ='@';
};

//accessor Impl
int PC::getinitialATK(){
    return initialAtk;
}

int PC::getinitialDEF(){
    return initialDef;
}

int PC::getHP(){
    return(data->getHP());
}

int PC::getATK(){
    return(data->getATK());
}

int PC::getDEF(){
    return(data->getDEF());
}

int PC::getGold(){
    return(data->getGoldValue());
}


//mutator

void PC::setATK(int atk){
    data->setATK(atk);
}

void PC::setDEF(int def){
    data->setDEF(def);
}

//Methods

void PC::takePotion(Potion * potion){
    potion->usePotion(*data,1);
}

void PC::takeGold(Treasure * gold){
     gold->pickedUpBy(*data);
}

void PC::takeGold(int gold){
    data->addGold(gold);
}
int PC::attack(Enemy * enemy){
    return enemy->beStruckBy(this);
}

int PC::beStruckBy(Enemy * enemy){
  int damage = (DamageCalc(enemy->getATK(),data->getDEF()));
    if((enemy->getType() =='E')){  // If enemy is elf, attacks twice
        for(int i = 0; i < 2; i++){
            if((rand() % 2) == 1){ // 50% chance to dodge
							data->addHP(- damage);
                if (data->getHP() == 0) return -1; // Tells level pc died
                  return damage; // Tells level that PC did not die
            }
        }
    }else{
        if((rand() % 2) == 1){ // 50% chance to dodge
            data->addHP(- damage);
            if (data->getHP() == 0) return -1;
                return damage; // tells Level that PC didnt die
        }
    }
    return 0; // Tells level that the Enemy missed
}

PC::~PC(){
    delete data;
};

//Shade initialization

Shade::Shade():PC{125,25,25,false}{
    initialAtk = 25;
    initialDef = 25;
}

Shade::~Shade(){};

//Drow initialization

Drow::Drow(): PC{150,25,15,false}{
    initialAtk = 25;
    initialDef = 15;
}

void Drow::takePotion(Potion * potion){
    potion->usePotion(*data,1.5);//effect manigied by 1.5
}

Drow::~Drow(){};

//Vampire
// allargic to dwarf
// otherwise gain 5HP each attack

Vampire::Vampire():PC{50,25,25,true}{
    initialAtk = 25;
    initialDef = 25;
}//initialization

int Vampire::attack(Enemy * enemy){
    if(enemy->getType() == 'W'){//check if enemy is dwarf
        data->addHP(-5); //vampire is allergic to dwarf
    }else{
        data->addHP(5); //vampire get extra 5 HP for every successful attack(if enemy is not dwarf)
    }
    return enemy->beStruckBy(this);
}

Vampire::~Vampire(){};

//Troll:: regain 5 HP every turn

Troll::Troll():PC{120,25,15,false}{
    initialAtk = 25;
    initialDef = 15;
}//initialization

int Troll::attack(Enemy * enemy){
    data->addHP(5);
    return enemy->beStruckBy(this);
}

int Troll::beStruckBy(Enemy * enemy) {
    int damage = DamageCalc(enemy->getATK(), data->getDEF());
    data->addHP(5);
    if((rand() % 2) == 1){
				data->addHP(- damage);
        if (data->getHP() == 0) return -1; // tells level PC died
        return damage;    // Tells level PC got hit and amount of damage delt
    }
    return 0; // Tells level that Enemy missed
}

Troll::~Troll(){};

//Goblin:: steal 5 gold from every died enemy

Goblin::Goblin():PC{110,15,20,false}{
    initialAtk = 15;
    initialDef = 20;
}

int Goblin::attack(Enemy * enemy){
    int status = enemy->beStruckBy(this);
    if (status < 0) data->addGold(5); // If enemy is dead, steal gold
    return status;
}

int Goblin::beStruckBy(Enemy * enemy){
    int damage = DamageCalc(enemy->getATK(), data->getDEF());
    if((rand() % 2) == 1){  // 50% chance to dodge
			
        if(enemy->getType() == 'O'){
            data->addHP(ceil(- 1.5 * damage));
						if(data->getHP() == 0) return -1; // Tell level that pc died
            return ceil(1.5 * damage);
        } else {
            data->addHP(- damage);
						if(data->getHP() == 0) return -1; // Tell level that pc died
            return damage; // tell level damage delt to pc
        }
    }
    return 0; // tell level that enemy missed
}

Goblin::~Goblin(){};
