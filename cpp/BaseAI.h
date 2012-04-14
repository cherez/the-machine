//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef BASEAI_H
#define BASEAI_H

#include <vector>
#include <ctime>
#include "game.h"

#include "ShipDescription.h"
#include "ShipType.h"
#include "Player.h"
#include "Ship.h"

/// \brief A basic AI interface.

///This class implements most the code an AI would need to interface with the lower-level game code.
///AIs should extend this class to get a lot of boiler-plate code out of the way
///The provided AI class does just that.
class BaseAI
{
protected:
  Connection* c;
  std::vector<ShipType> shipTypes;
  std::vector<Player> players;
  std::vector<Ship> ships;
public:
  ///How many turns it has been since the beginning of the round
  int turnNumber();
  ///Player Number; either 0 or 1
  int playerID();
  ///What number game this is for the server
  int gameNumber();
  ///The current round of the match
  int roundNumber();
  ///How many victories a player needs to win this game.  If the last round is a tie, one more victory is needed
  int victoriesNeeded();
  ///The outer radius of the map.  Center of screen is (0,0), with +x right, +y up
  int mapRadius();

  ///Returns the distance between two points
  int distance(int fromX, int fromY, int toX, int toY);
  ///Find a point "travel" distance from the starting point in the direction of the ending point.  Uses return by reference
  void pointOnLine(int fromX, int fromY, int toX, int toY, int travel, int & outX, int & outY);

  BaseAI(Connection* c);
  virtual ~BaseAI();
  ///
  ///Make this your username, which should be provided.
  virtual const char* username() = 0;
  ///
  ///Make this your password, which should be provided.
  virtual const char* password() = 0;
  ///
  ///This function is run once, before your first turn.
  virtual void init() = 0;
  ///
  ///This function is called each time it is your turn
  ///Return true to end your turn, return false to ask the server for updated information
  virtual bool run() = 0;
  ///
  ///This function is called after the last turn.
  virtual void end() = 0;


  bool startTurn();
};

#endif
