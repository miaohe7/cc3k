#ifndef helpers_hpp
#define helpers_hpp

#include <string>
#include <sstream>

std::string makeString(int);
std::string makeString(char);
int DamageCalc(int, int);
std::string charToRace(char);
std::string translateDirection(std::string);
std::string translatePotion(char);
std::string translateTreasure(char);

int randomChamber();
#endif /* sss_hpp */
