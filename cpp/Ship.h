// -*-c++-*-

#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include "structures.h"

#include "ShipDescription.h"
class Ship;

///A space ship!
class Ship : public ShipDescription {
  public:
  Ship(_Ship* ptr = NULL);

  // Accessors
  ///Unique Identifier
  int id();
  ///The ship type
  char* type();
  ///The amount of energy required to warp in this type of ship
  int cost();
  ///The radius of the ship
  int radius();
  ///The range of attacks for this ship, given as the maximum distance from the center of this ship to the edge of the target
  int range();
  ///The strength of attacks for this ship
  int damage();
  ///The amount of damage done when this ship self destructs
  int selfDestructDamage();
  ///The largest possible movement for this ship
  int maxMovement();
  ///The max number of attacks for this ship
  int maxAttacks();
  ///The max health possible for the ship
  int maxHealth();
  ///The owner of the ship
  int owner();
  ///X position of the ship
  int x();
  ///Y position of the ship
  int y();
  ///How many more attacks this ship can make this turn
  int attacksLeft();
  ///How much more this ship can move this turn
  int movementLeft();
  ///The current health of the ship
  int health();

  // Actions
  ///Command a ship to move to a specified position
  int move(int x, int y);
  ///Blow yourself up, damage enemy ships that overlap this ship
  int selfDestruct();
  ///Commands your ship to attack a target.
  int attack(Ship& target);

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Ship ob);
};

#endif

