//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#pragma warning(disable : 4996)

#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <math.h>

#include "game.h"
#include "network.h"
#include "structures.h"

#include "sexp/sfcompat.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#ifdef _WIN32
//Doh, namespace collision.
namespace Windows
{
    #include <Windows.h>
};
#else
#include <unistd.h>
#endif

#ifdef ENABLE_THREADS
#define LOCK(X) pthread_mutex_lock(X)
#define UNLOCK(X) pthread_mutex_unlock(X)
#else
#define LOCK(X)
#define UNLOCK(X)
#endif

using std::cout;
using std::cerr;
using std::endl;
using std::stringstream;
using std::string;
using std::ofstream;

DLLEXPORT Connection* createConnection()
{
  Connection* c = new Connection;
  c->socket = -1;
  #ifdef ENABLE_THREADS
  pthread_mutex_init(&c->mutex, NULL);
  #endif

  c->turnNumber = 0;
  c->playerID = 0;
  c->gameNumber = 0;
  c->roundNumber = 0;
  c->victoriesNeeded = 0;
  c->mapRadius = 0;
  c->ShipTypes = NULL;
  c->ShipTypeCount = 0;
  c->Players = NULL;
  c->PlayerCount = 0;
  c->Ships = NULL;
  c->ShipCount = 0;
  return c;
}

DLLEXPORT void destroyConnection(Connection* c)
{
  #ifdef ENABLE_THREADS
  pthread_mutex_destroy(&c->mutex);
  #endif
  if(c->ShipTypes)
  {
    for(int i = 0; i < c->ShipTypeCount; i++)
    {
      delete[] c->ShipTypes[i].type;
    }
    delete[] c->ShipTypes;
  }
  if(c->Players)
  {
    for(int i = 0; i < c->PlayerCount; i++)
    {
      delete[] c->Players[i].playerName;
    }
    delete[] c->Players;
  }
  if(c->Ships)
  {
    for(int i = 0; i < c->ShipCount; i++)
    {
      delete[] c->Ships[i].type;
    }
    delete[] c->Ships;
  }
  delete c;
}

DLLEXPORT int serverConnect(Connection* c, const char* host, const char* port)
{
  c->socket = open_server_connection(host, port);
  return c->socket + 1; //false if socket == -1
}

DLLEXPORT int serverLogin(Connection* c, const char* username, const char* password)
{
  string expr = "(login \"";
  expr += username;
  expr += "\" \"";
  expr += password;
  expr +="\")";

  send_string(c->socket, expr.c_str());

  sexp_t* expression, *message;

  char* reply = rec_string(c->socket);
  expression = extract_sexpr(reply);
  delete[] reply;

  message = expression->list;
  if(message->val == NULL || strcmp(message->val, "login-accepted") != 0)
  {
    cerr << "Unable to login to server" << endl;
    destroy_sexp(expression);
    return 0;
  }
  destroy_sexp(expression);
  return 1;
}

DLLEXPORT int createGame(Connection* c)
{
  sexp_t* expression, *number;

  send_string(c->socket, "(create-game)");

  char* reply = rec_string(c->socket);
  expression = extract_sexpr(reply);
  delete[] reply;

  number = expression->list->next;
  c->gameNumber = atoi(number->val);
  destroy_sexp(expression);

  std::cout << "Creating game " << c->gameNumber << endl;

  c->playerID = 0;

  return c->gameNumber;
}

DLLEXPORT int joinGame(Connection* c, int gameNum, const char* playerType)
{
  sexp_t* expression;
  stringstream expr;

  c->gameNumber = gameNum;

  expr << "(join-game " << c->gameNumber << " "<< playerType << ")";
  send_string(c->socket, expr.str().c_str());

  char* reply = rec_string(c->socket);
  expression = extract_sexpr(reply);
  delete[] reply;

  if(strcmp(expression->list->val, "join-accepted") == 0)
  {
    destroy_sexp(expression);
    c->playerID = 1;
    send_string(c->socket, "(game-start)");
    return 1;
  }
  else if(strcmp(expression->list->val, "create-game") == 0)
  {
    std::cout << "Game did not exist, creating game " << c->gameNumber << endl;
    destroy_sexp(expression);
    c->playerID = 0;
    return 1;
  }
  else
  {
    cerr << "Cannot join game "<< c->gameNumber << ": " << expression->list->next->val << endl;
    destroy_sexp(expression);
    return 0;
  }
}

DLLEXPORT void endTurn(Connection* c)
{
  LOCK( &c->mutex );
  send_string(c->socket, "(end-turn)");
  UNLOCK( &c->mutex );
}

DLLEXPORT void getStatus(Connection* c)
{
  LOCK( &c->mutex );
  send_string(c->socket, "(game-status)");
  UNLOCK( &c->mutex );
}


#include <cmath>
DLLEXPORT int baseDistance(int fromX, int fromY, int toX, int toY)
{
  int dx = (fromX - toX);
  int dy = (fromY - toY);
  return int(ceil(sqrt((float)(dx * dx + dy * dy))));
}

DLLEXPORT int basePointOnLine(int fromX, int fromY, int toX, int toY, int travel)
{
  int x, y, dx, dy;
  int toGoal = baseDistance(fromX, fromY, toX, toY);
  if(toGoal <= travel)
  {
    x = toX;
    y = toY;
  }
  else if(travel <= 0)
  {
    x = fromX;
    y = fromY;
  }
  else
  {
    dx = toX - fromX;
    dy = toY - fromY;
    x = fromX + dx * travel / toGoal;
    y = fromY + dy * travel / toGoal;
    dx = toX - x;
    dy = toY - y;
    float ratio = 1;
    if(dx != 0)
    {
      ratio = static_cast<float>(dy) / dx;
    }
    // Do ray tracing to correct for rounding error
    while(baseDistance(fromX, fromY, x, y) < travel)
    {
      if(dx != 0 && static_cast<float>(dy) / dx < ratio)
      {
        if(toX > x) {x++; dx--;}
        else {x--; dx++;}
      }
      else
      {
        if(toY > y) {y++; dy--;}
        else {y--; dy++;}
      }
    }
  }
  // Pack the X and Y into a single integer for interlanguage movement
  return ((x+500)<<10) + (y+500);
}

DLLEXPORT int shipTypeWarpIn(_ShipType* object, int x, int y)
{
  stringstream expr;
  expr << "(game-warp-in " << object->id
       << " " << x
       << " " << y
       << ")";
  LOCK( &object->_c->mutex);
  send_string(object->_c->socket, expr.str().c_str());
  UNLOCK( &object->_c->mutex);
  
  //Game state update
  Connection * c = object->_c;
  if(baseDistance(0, 0, x, y) + object->radius > c->mapRadius)
  {
    return 0;
  }
  else if (c->Players[c->playerID].energy < object->cost)
  {
    return 0;
  }
  else
  {
    // Find the player's warp gate
    int gateIndex = -1;
    for(int i=0; i < c->ShipCount && gateIndex == -1; i++)
    {
      if(c->Ships[i].owner == c->playerID && strcmp("Warp Gate", c->Ships[i].type) == 0)
      {
        gateIndex = i;
      }
    }
    if(baseDistance(c->Ships[gateIndex].x, c->Ships[gateIndex].y, x, y) + object->radius > c->Ships[gateIndex].radius)
    {
      return 0;
    }
    else
    {
      c->Players[c->playerID].energy -= object->cost;
      return 1;
    }
  }
}


DLLEXPORT int playerTalk(_Player* object, char* message)
{
  stringstream expr;
  expr << "(game-talk " << object->id
      << " \"" << escape_string(message) << "\""
       << ")";
  LOCK( &object->_c->mutex);
  send_string(object->_c->socket, expr.str().c_str());
  UNLOCK( &object->_c->mutex);

  //Game State Update
  Connection * c = object->_c;
  if(object->id == c->playerID)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}


DLLEXPORT int shipMove(_Ship* object, int x, int y)
{
  stringstream expr;
  expr << "(game-move " << object->id
       << " " << x
       << " " << y
       << ")";
  LOCK( &object->_c->mutex);
  send_string(object->_c->socket, expr.str().c_str());
  UNLOCK( &object->_c->mutex);
  
  //Game State Update
  Connection * c = object->_c;
  int moved = baseDistance(object->x, object->y, x, y);
  if(object->owner != c->playerID)
  {
    return 0;
  }
  else if(baseDistance(0, 0, x, y) + object->radius > c->mapRadius)
  {
    return 0;
  }
  else if(object->movementLeft < moved)
  {
    return 0;
  }
  else if (moved == 0)
  {
    return 0;
  }
  object->x = x;
  object->y = y;
  object->movementLeft -= moved;
  return 1;
}

DLLEXPORT int shipSelfDestruct(_Ship* object)
{
  stringstream expr;
  expr << "(game-self-destruct " << object->id
       << ")";
  LOCK( &object->_c->mutex);
  send_string(object->_c->socket, expr.str().c_str());
  UNLOCK( &object->_c->mutex);
  
  //Game state update
  Connection * c = object->_c;
  if(strcmp(object->type,"Warp Gate") == 0)
  {
    return 0;
  }
  else if(object->owner != c->playerID)
  {
    return 0;
  }
  for(int i = 0; i < c->ShipCount; i++)
  {
    if(c->Ships[i].owner != object->owner)
    {
      if(baseDistance(object->x, object->y, c->Ships[i].x, c->Ships[i].y) < c->Ships[i].radius + object->radius)
      {
        c->Ships[i].health -= object->selfDestructDamage;
      }
    }
  }
  object->health = 0;
  return 1;
}

DLLEXPORT int shipAttack(_Ship* object, _Ship* target)
{
  stringstream expr;
  expr << "(game-attack " << object->id
      << " " << target->id
       << ")";
  LOCK( &object->_c->mutex);
  send_string(object->_c->socket, expr.str().c_str());
  UNLOCK( &object->_c->mutex);

  //Game state update
  Connection * c = object->_c;

  if(object->owner != c->playerID)
    return 0;
  if(object->attacksLeft <= 0)
    return 0;
  //TODO Does not check for repeated attacks against the same target
  if(strcmp(object->type, "Mine Layer") == 0)
  {
    object->maxAttacks -= 1;
    object->attacksLeft -= 1;
    return 1;
  }
  if(strcmp(object->type, "EMP") == 0)
  {
    object->maxAttacks -= 1;
    object->attacksLeft -= 1;
    for(int i = 0; i < c->ShipCount; i++)
    {
      if(c->Ships[i].owner != object->owner)
      {
        if(baseDistance(object->x, object->y, c->Ships[i].x, c->Ships[i].y) < c->Ships[i].radius + object->range)
        {
          // EMP the ship
          c->Ships[i].movementLeft = -1;
          c->Ships[i].attacksLeft = -1;
        }
      }
    }
    return 1;
  }
  else if(target->owner == object->owner)
    return 0;
  else if (baseDistance(object->x, object->y, target->x, target->y) > object->range + target->radius)
    return 0;
  else
  {
    float modifier = 1;
    for(int i = 0; i < c->ShipCount; i++)
    {
      if(c->Ships[i].owner == object->owner && strcmp(c->Ships[i].type, "Support") == 0)
      {
        if(baseDistance(target->x, target->y, c->Ships[i].x, c->Ships[i].y) < c->Ships[i].range + target->radius)
        {
          modifier += (c->Ships[i].damage / 100.0);
        }
      }
    }
    target->health -= int(object->damage*modifier);
    object->attacksLeft -= 1;
  }
  return 1;
}


//Utility functions for parsing data
void parseShipDescription(Connection* c, _ShipDescription* object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;

  object->_c = c;

  object->id = atoi(sub->val);
  sub = sub->next;
  object->type = new char[strlen(sub->val)+1];
  strncpy(object->type, sub->val, strlen(sub->val));
  object->type[strlen(sub->val)] = 0;
  sub = sub->next;
  object->cost = atoi(sub->val);
  sub = sub->next;
  object->radius = atoi(sub->val);
  sub = sub->next;
  object->range = atoi(sub->val);
  sub = sub->next;
  object->damage = atoi(sub->val);
  sub = sub->next;
  object->selfDestructDamage = atoi(sub->val);
  sub = sub->next;
  object->maxMovement = atoi(sub->val);
  sub = sub->next;
  object->maxAttacks = atoi(sub->val);
  sub = sub->next;
  object->maxHealth = atoi(sub->val);
  sub = sub->next;

}
void parseShipType(Connection* c, _ShipType* object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;

  object->_c = c;

  object->id = atoi(sub->val);
  sub = sub->next;
  object->type = new char[strlen(sub->val)+1];
  strncpy(object->type, sub->val, strlen(sub->val));
  object->type[strlen(sub->val)] = 0;
  sub = sub->next;
  object->cost = atoi(sub->val);
  sub = sub->next;
  object->radius = atoi(sub->val);
  sub = sub->next;
  object->range = atoi(sub->val);
  sub = sub->next;
  object->damage = atoi(sub->val);
  sub = sub->next;
  object->selfDestructDamage = atoi(sub->val);
  sub = sub->next;
  object->maxMovement = atoi(sub->val);
  sub = sub->next;
  object->maxAttacks = atoi(sub->val);
  sub = sub->next;
  object->maxHealth = atoi(sub->val);
  sub = sub->next;

}
void parsePlayer(Connection* c, _Player* object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;

  object->_c = c;

  object->id = atoi(sub->val);
  sub = sub->next;
  object->playerName = new char[strlen(sub->val)+1];
  strncpy(object->playerName, sub->val, strlen(sub->val));
  object->playerName[strlen(sub->val)] = 0;
  sub = sub->next;
  object->time = atof(sub->val);
  sub = sub->next;
  object->victories = atoi(sub->val);
  sub = sub->next;
  object->energy = atoi(sub->val);
  sub = sub->next;

}
void parseShip(Connection* c, _Ship* object, sexp_t* expression)
{
  sexp_t* sub;
  sub = expression->list;

  object->_c = c;

  object->id = atoi(sub->val);
  sub = sub->next;
  object->type = new char[strlen(sub->val)+1];
  strncpy(object->type, sub->val, strlen(sub->val));
  object->type[strlen(sub->val)] = 0;
  sub = sub->next;
  object->cost = atoi(sub->val);
  sub = sub->next;
  object->radius = atoi(sub->val);
  sub = sub->next;
  object->range = atoi(sub->val);
  sub = sub->next;
  object->damage = atoi(sub->val);
  sub = sub->next;
  object->selfDestructDamage = atoi(sub->val);
  sub = sub->next;
  object->maxMovement = atoi(sub->val);
  sub = sub->next;
  object->maxAttacks = atoi(sub->val);
  sub = sub->next;
  object->maxHealth = atoi(sub->val);
  sub = sub->next;
  object->owner = atoi(sub->val);
  sub = sub->next;
  object->x = atoi(sub->val);
  sub = sub->next;
  object->y = atoi(sub->val);
  sub = sub->next;
  object->attacksLeft = atoi(sub->val);
  sub = sub->next;
  object->movementLeft = atoi(sub->val);
  sub = sub->next;
  object->health = atoi(sub->val);
  sub = sub->next;

}

DLLEXPORT int networkLoop(Connection* c)
{
  while(true)
  {
    sexp_t* base, *expression, *sub, *subsub;

    char* message = rec_string(c->socket);
    string text = message;
    base = extract_sexpr(message);
    delete[] message;
    expression = base->list;
    if(expression->val != NULL && strcmp(expression->val, "game-winner") == 0)
    {
      expression = expression->next->next->next;
      int winnerID = atoi(expression->val);
      if(winnerID == c->playerID)
      {
        cout << "You win!" << endl << expression->next->val << endl;
      }
      else
      {
        cout << "You lose. :(" << endl << expression->next->val << endl;
      }
      stringstream expr;
      expr << "(request-log " << c->gameNumber << ")";
      send_string(c->socket, expr.str().c_str());
      destroy_sexp(base);
      return 0;
    }
    else if(expression->val != NULL && strcmp(expression->val, "log") == 0)
    {
      ofstream out;
      stringstream filename;
      expression = expression->next;
      filename << expression->val;
      filename << ".gamelog";
      expression = expression->next;
      out.open(filename.str().c_str());
      if (out.good())
        out.write(expression->val, strlen(expression->val));
      else
        cerr << "Error : Could not create log." << endl;
      out.close();
      destroy_sexp(base);
      return 0;
    }
    else if(expression->val != NULL && strcmp(expression->val, "game-accepted")==0)
    {
      char gameID[30];

      expression = expression->next;
      strcpy(gameID, expression->val);
      cout << "Created game " << gameID << endl;
    }
    else if(expression->val != NULL && strstr(expression->val, "denied"))
    {
      cout << expression->val << endl;
      cout << expression->next->val << endl;
    }
    else if(expression->val != NULL && strcmp(expression->val, "status") == 0)
    {
      while(expression->next != NULL)
      {
        expression = expression->next;
        sub = expression->list;
        if(string(sub->val) == "game")
        {
          sub = sub->next;
          c->turnNumber = atoi(sub->val);
          sub = sub->next;

          c->playerID = atoi(sub->val);
          sub = sub->next;

          c->gameNumber = atoi(sub->val);
          sub = sub->next;

          c->roundNumber = atoi(sub->val);
          sub = sub->next;

          c->victoriesNeeded = atoi(sub->val);
          sub = sub->next;

          c->mapRadius = atoi(sub->val);
          sub = sub->next;

        }
        else if(string(sub->val) == "ShipType")
        {
          if(c->ShipTypes)
          {
            for(int i = 0; i < c->ShipTypeCount; i++)
            {
              delete[] c->ShipTypes[i].type;
            }
            delete[] c->ShipTypes;
          }
          c->ShipTypeCount =  sexp_list_length(expression)-1; //-1 for the header
          c->ShipTypes = new _ShipType[c->ShipTypeCount];
          for(int i = 0; i < c->ShipTypeCount; i++)
          {
            sub = sub->next;
            parseShipType(c, c->ShipTypes+i, sub);
          }
        }
        else if(string(sub->val) == "Player")
        {
          if(c->Players)
          {
            for(int i = 0; i < c->PlayerCount; i++)
            {
              delete[] c->Players[i].playerName;
            }
            delete[] c->Players;
          }
          c->PlayerCount =  sexp_list_length(expression)-1; //-1 for the header
          c->Players = new _Player[c->PlayerCount];
          for(int i = 0; i < c->PlayerCount; i++)
          {
            sub = sub->next;
            parsePlayer(c, c->Players+i, sub);
          }
        }
        else if(string(sub->val) == "Ship")
        {
          if(c->Ships)
          {
            for(int i = 0; i < c->ShipCount; i++)
            {
              delete[] c->Ships[i].type;
            }
            delete[] c->Ships;
          }
          c->ShipCount =  sexp_list_length(expression)-1; //-1 for the header
          c->Ships = new _Ship[c->ShipCount];
          for(int i = 0; i < c->ShipCount; i++)
          {
            sub = sub->next;
            parseShip(c, c->Ships+i, sub);
          }
        }
      }
      destroy_sexp(base);
      return 1;
    }
    else
    {
#ifdef SHOW_WARNINGS
      cerr << "Unrecognized message: " << text << endl;
#endif
    }
    destroy_sexp(base);
  }
}

DLLEXPORT _ShipType* getShipType(Connection* c, int num)
{
  return c->ShipTypes + num;
}
DLLEXPORT int getShipTypeCount(Connection* c)
{
  return c->ShipTypeCount;
}

DLLEXPORT _Player* getPlayer(Connection* c, int num)
{
  return c->Players + num;
}
DLLEXPORT int getPlayerCount(Connection* c)
{
  return c->PlayerCount;
}

DLLEXPORT _Ship* getShip(Connection* c, int num)
{
  return c->Ships + num;
}
DLLEXPORT int getShipCount(Connection* c)
{
  return c->ShipCount;
}


DLLEXPORT int getTurnNumber(Connection* c)
{
  return c->turnNumber;
}
DLLEXPORT int getPlayerID(Connection* c)
{
  return c->playerID;
}
DLLEXPORT int getGameNumber(Connection* c)
{
  return c->gameNumber;
}
DLLEXPORT int getRoundNumber(Connection* c)
{
  return c->roundNumber;
}
DLLEXPORT int getVictoriesNeeded(Connection* c)
{
  return c->victoriesNeeded;
}
DLLEXPORT int getMapRadius(Connection* c)
{
  return c->mapRadius;
}
