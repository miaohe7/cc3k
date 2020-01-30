#ifndef stats_hpp
#define stats_hpp

// Each race should contain a stats class that is unique to them

class Stats {
    int hp,atk,def,maxHP,goldValue;
    bool hasMaxHP;
public:
    Stats(int,int,int,bool);  // initalize the stats
    int getHP();         // return current health
    int getATK();        // return current atk
    int getDEF();        // return current defense
    int getMaxHP();      // return maxHP
    int getGoldValue();  // return current gold
    
    void setATK(int);     //set atk
    void setDEF(int);     //set def
    void addHP(int);     // add to hp
    void addATK(int);    // add to atk
    void addDEF(int);    // add to def
    void addGold(int);  // increase gold

    ~Stats(){};   // Virutal destructor
};



#endif /* stats_hpp */
