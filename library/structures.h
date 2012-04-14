//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that
#ifndef STRUCTURES_H
#define STRUCTURES_H

struct Connection;
struct _ShipDescription;
struct _ShipType;
struct _Player;
struct _Ship;


struct _ShipDescription
{
  Connection* _c;
  int id;
  char* type;
  int cost;
  int radius;
  int range;
  int damage;
  int selfDestructDamage;
  int maxMovement;
  int maxAttacks;
  int maxHealth;
};
struct _ShipType
{
  Connection* _c;
  int id;
  char* type;
  int cost;
  int radius;
  int range;
  int damage;
  int selfDestructDamage;
  int maxMovement;
  int maxAttacks;
  int maxHealth;
};
struct _Player
{
  Connection* _c;
  int id;
  char* playerName;
  float time;
  int victories;
  int energy;
};
struct _Ship
{
  Connection* _c;
  int id;
  char* type;
  int cost;
  int radius;
  int range;
  int damage;
  int selfDestructDamage;
  int maxMovement;
  int maxAttacks;
  int maxHealth;
  int owner;
  int x;
  int y;
  int attacksLeft;
  int movementLeft;
  int health;
};

#endif
