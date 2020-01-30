#ifndef treasure_hpp
#define treasure_hpp
#include <string>
#include "Object.h"

class Stats;

class Treasure : public Object{
protected:
    std::string description;   // The type and value of the treasure
    int value;                 // Amount of gold it contains
    bool isBinded = false;
    
public:
    virtual std::string getDescription(){ return description;} // returns description
    virtual void pickedUpBy(Stats &) = 0;         // Mutates the goldValue in Stas
    bool isThisBinded();
    void bindThis();
    virtual bool canPickup();
};

#endif /* treasure_hpp */
