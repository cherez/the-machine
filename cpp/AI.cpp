#include "AI.h"
#include "util.h"
#include <string.h>

AI::AI(Connection* conn) : BaseAI(conn) {}

const char* AI::username()
{
  return "Shell AI";
}

const char* AI::password()
{
  return "password";
}

//This function is run once, before your first turn.
void AI::init(){}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  std::cout<< "Starting turn " << turnNumber() << " of round " << roundNumber() << std::endl;
  // Find each player's warp gate
  int myGateIndex, theirGateIndex;
  for(size_t i=0; i<ships.size();i++)
  {
    // If this ship is of type Warp Gate
    if(strcmp(ships[i].type(), "Warp Gate") == 0)
    {
      // If you own this ship
      if(ships[i].owner() == playerID())
      {
        myGateIndex = i;
      }
      else
      {
        theirGateIndex = i;
      }
    }
  }

  // Warp in some ships
  for(size_t i=0; i<shipTypes.size(); i++)
  {
    // If you have enough energy to warp in this type of ship
    if(shipTypes[i].cost() <= players[playerID()].energy())
    {
      // Warp it in directly on top of your warp gate
      shipTypes[i].warpIn(ships[myGateIndex].x(), ships[myGateIndex].y());
    }
  }

  // Command your ships
  for(size_t i=0; i<ships.size();i++)
  {
    // if you own this ship, it can move and it can attack
    if(ships[i].owner() == playerID() && ships[i].movementLeft() > 0 && ships[i].attacksLeft() > 0)
    {
      int x, y;
      // Find a point on the line connecting this ship and their warp gate that is close enough for this ship to move to.
      // x and y are out parameters
      pointOnLine(ships[i].x(), ships[i].y(), ships[theirGateIndex].x(), ships[theirGateIndex].y(), ships[i].movementLeft(), x, y);
      // If I have to move to get there
      if(ships[i].x() != x || ships[i].y() != y)
      {
        ships[i].move(x, y);
      }
      // If the distance from my ship to their warp gate is less than my ships attack range plus their gate's radius
      if(distance(ships[i].x(), ships[i].y(), ships[theirGateIndex].x(), ships[theirGateIndex].y()) <= ships[i].range() + ships[theirGateIndex].radius())
      {
        // If their warp gate is still alive
        if(ships[theirGateIndex].health() > 0)
        {
          ships[i].attack(ships[theirGateIndex]);
        }
      }
    }
  }
  return true;
}

//This function is run once, after your last turn.
void AI::end(){}
