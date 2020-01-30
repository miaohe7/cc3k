#include "helpers.h"
#include <math.h>

// Converts an integer to a string
std::string makeString(int num){
    std::string numAsString;
    std::stringstream convertToString;
    convertToString << num;
    convertToString >> numAsString;
    return numAsString;
}

// Converts a character to a string ( overloading )
std::string makeString(char character){
    std::string characterAsString;
    std::stringstream convertToString;
    convertToString << character;
    convertToString >> characterAsString;
    return characterAsString;
}

// Attack of the attacker and the Def of the Defenser
int DamageCalc(int Atk, int Def){
    return (ceil((100.0/(100 + Def)))* Atk);
}

// Translate Character letter to the race type
std::string charToRace(char characterType){
  switch (characterType) {
    case ('s'):
      return "Shade";
    case ('d'):
      return "Drow";
    case ('v'):
      return "Vampire";
    case ('t'):
      return "Troll";
    default:
      return "Goblin";
  }
}

// Translate shortform direction to long
std::string translateDirection(std::string shortForm){
  if (shortForm == "no"){
    return "North";
  } else if (shortForm == "so"){
    return "South";
  } else if (shortForm == "ea"){
    return "East";
  } else if (shortForm == "we"){
    return "West";
  } else if (shortForm == "ne"){
    return "North-East";
  } else if (shortForm == "nw"){
    return "North-West";
  } else if (shortForm == "se"){
    return "South-East";
  } else {
    return "South-West";
  }
}

// Translate the potion "number" to the actual type
std::string translatePotion(char number){
  switch (number) {
    case ('0'):
      return "RH";
    case ('1'):
      return "BA";
    case ('2'):
      return "BD";
    case ('3'):
      return "PH";
    case ('4'):
      return "WA";
    default:
      return "WD";
  }
}

// Translate the treasure "number" to it's whole name
std::string translateTreasure(char number){
  switch (number) {
    case (6):
      return "normal gold pile";
    case (7):
      return "small hoard";
    case (8):
      return "merchant hoard";
      default:
      return "dragon hoard";
  }
}

// Randomly generate a number from 1 - 5
int randomChamber(){
	return rand() % 5;
}
