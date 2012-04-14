// -*-c++-*-

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "structures.h"


class Player {
  public:
  void* ptr;
  Player(_Player* ptr = NULL);

  // Accessors
  ///Unique Identifier
  int id();
  ///Player's Name
  char* playerName();
  ///Time remaining, updated at start of turn
  float time();
  ///How many rounds you have won this game
  int victories();
  ///How much energy the player has left to warp in ships
  int energy();

  // Actions
  ///Allows a player to display messages on the screen
  int talk(char* message);

  // Properties


  friend std::ostream& operator<<(std::ostream& stream, Player ob);
};

#endif

