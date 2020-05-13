//weapons.cpp
//
//
//Created by Juan Martinez on 2/17/17
//
//

#include <iostream>
#include <cstdlib>
#include <bitset>
#include <ctime>

using namespace std;

enum class Weapon: uint8_t
{
    None = 0b00000000,
    Melee = 0b00000001,
    Fire = 0b00000010,
    Ice = 0b00000100,
    Poison = 0b00001000
    
};

// Prototype function
bool checkWeapon(uint8_t currentWeapon, Weapon weapon);
void displayWeapon(uint8_t currentWeapon);
uint8_t addWeapon(uint8_t currentWeapon, Weapon weapon);
uint8_t removeWeapon(uint8_t currentWeapon, Weapon weapon);
uint8_t toggleWeapon(uint8_t currentWeapon, Weapon weapon);

int main()
{
  srand (time(NULL));

  // Max value myweapon can get.
  const uint8_t maxWeapons = 16;
  
  uint8_t myweapon;
  
  // Randomly initialize value of myweapon.
  myweapon = rand() % maxWeapons;
  cout << "Starting with myweapon = " << unsigned(myweapon) << endl;
  
  // Print out binary representation of wyweapon.
  cout << "Binary representation: " << bitset<8>(myweapon) << endl;
  
  displayWeapon(myweapon);

  // Toggle Poison
  cout << "***Toggling Poison***" << endl;
  myweapon = toggleWeapon(myweapon, Weapon::Poison);
  displayWeapon(myweapon);
  
  // Toggle Fire
  cout << "***Toggling Fire***" << endl;
  myweapon = toggleWeapon(myweapon, Weapon::Fire);
  displayWeapon(myweapon);

  // Check Ice
  if (checkWeapon(myweapon, Weapon::Ice))
  {
    cout << "***Found Ice.. removing it***" << endl;
    myweapon = removeWeapon(myweapon, Weapon::Ice);
    displayWeapon(myweapon);
  }
  else
    {
      cout << "***Ice not found.. can't remove it***" << endl;
    }

  // Check Melee
  if (checkWeapon(myweapon, Weapon::Melee))
  {
    cout << "***Melee already exists.. can't add it***" << endl;
  }
  else
    {
      cout << "***Melee not found.. adding it***" << endl;
      myweapon = addWeapon(myweapon, Weapon::Melee);
      displayWeapon(myweapon);
    }

  // Print final value
  cout << "Ending with myweapon = " << int(myweapon) << endl;
  cout << "Bianry representation: " << bitset<8>(myweapon) << endl;
 
  return 0;
}

// Implementation

bool checkWeapon(uint8_t currentWeapon, Weapon weapon)
{
  return currentWeapon & uint8_t(weapon);
}


void displayWeapon(uint8_t currentWeapon)
{
  cout << "Your Weapons: ";
  
  Weapon a = Weapon::None;
  if (currentWeapon == 0)
  {
   cout << "None ";
  }
  
  Weapon b = Weapon::Melee;
  if (checkWeapon(currentWeapon, b))
    {
      cout << "Melee ";
    }
  
  Weapon c = Weapon::Fire;
  if (checkWeapon(currentWeapon, c))
    {
      cout << "Fire ";
    }
  
  Weapon d = Weapon::Ice;
  if (checkWeapon(currentWeapon, d))
    {
      cout << "Ice ";
    }

  Weapon e = Weapon::Poison;
  if (checkWeapon(currentWeapon, e))
    {
      cout << "Poison ";
    }
  cout << endl;
  
}

uint8_t addWeapon(uint8_t currentWeapon, Weapon weapon)
{
  return currentWeapon | uint8_t(weapon);
}

uint8_t removeWeapon(uint8_t currentWeapon, Weapon weapon)
{
  return currentWeapon &~ uint8_t(weapon);
}

uint8_t toggleWeapon(uint8_t currentWeapon, Weapon weapon)
{
  return currentWeapon ^ uint8_t(weapon); 
}

  
  
