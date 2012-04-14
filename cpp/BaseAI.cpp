//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that

#include "BaseAI.h"
#include "game.h"

int BaseAI::turnNumber()
{
  return getTurnNumber(c);
}
int BaseAI::playerID()
{
  return getPlayerID(c);
}
int BaseAI::gameNumber()
{
  return getGameNumber(c);
}
int BaseAI::roundNumber()
{
  return getRoundNumber(c);
}
int BaseAI::victoriesNeeded()
{
  return getVictoriesNeeded(c);
}
int BaseAI::mapRadius()
{
  return getMapRadius(c);
}

bool BaseAI::startTurn()
{
  static bool initialized = false;
  int count = 0;
  count = getShipTypeCount(c);
  shipTypes.clear();
  shipTypes.resize(count);
  for(int i = 0; i < count; i++)
  {
    shipTypes[i] = ShipType(getShipType(c, i));
  }

  count = getPlayerCount(c);
  players.clear();
  players.resize(count);
  for(int i = 0; i < count; i++)
  {
    players[i] = Player(getPlayer(c, i));
  }

  count = getShipCount(c);
  ships.clear();
  ships.resize(count);
  for(int i = 0; i < count; i++)
  {
    ships[i] = Ship(getShip(c, i));
  }

  if(!initialized)
  {
    initialized = true;
    init();
  }
  return run();
}

BaseAI::BaseAI(Connection* conn) : c(conn) {}
BaseAI::~BaseAI() {}

int BaseAI::distance(int fromX, int fromY, int toX, int toY)
{
  return baseDistance(fromX, fromY, toX, toY);
}

void BaseAI::pointOnLine(int fromX, int fromY, int toX, int toY, int travel, int & outX, int & outY)
{
  int ret = basePointOnLine(fromX, fromY, toX, toY, travel);
  outX = ret / 1024 - 500;
  outY = ret % 1024 - 500;
}
