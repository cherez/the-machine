// -*-c++-*-

#include "Ship.h"
#include "game.h"

#include "Ship.h"

Ship::Ship(_Ship* pointer)
{
    ptr = (void*) pointer;
}

int Ship::id()
{
  return ((_Ship*)ptr)->id;
}

char* Ship::type()
{
  return ((_Ship*)ptr)->type;
}

int Ship::cost()
{
  return ((_Ship*)ptr)->cost;
}

int Ship::radius()
{
  return ((_Ship*)ptr)->radius;
}

int Ship::range()
{
  return ((_Ship*)ptr)->range;
}

int Ship::damage()
{
  return ((_Ship*)ptr)->damage;
}

int Ship::selfDestructDamage()
{
  return ((_Ship*)ptr)->selfDestructDamage;
}

int Ship::maxMovement()
{
  return ((_Ship*)ptr)->maxMovement;
}

int Ship::maxAttacks()
{
  return ((_Ship*)ptr)->maxAttacks;
}

int Ship::maxHealth()
{
  return ((_Ship*)ptr)->maxHealth;
}

int Ship::owner()
{
  return ((_Ship*)ptr)->owner;
}

int Ship::x()
{
  return ((_Ship*)ptr)->x;
}

int Ship::y()
{
  return ((_Ship*)ptr)->y;
}

int Ship::attacksLeft()
{
  return ((_Ship*)ptr)->attacksLeft;
}

int Ship::movementLeft()
{
  return ((_Ship*)ptr)->movementLeft;
}

int Ship::health()
{
  return ((_Ship*)ptr)->health;
}


int Ship::move(int x, int y)
{
  return shipMove( (_Ship*)ptr, x, y);
}

int Ship::selfDestruct()
{
  return shipSelfDestruct( (_Ship*)ptr);
}

int Ship::attack(Ship& target)
{
  return shipAttack( (_Ship*)ptr, (_Ship*) target.ptr);
}



std::ostream& operator<<(std::ostream& stream,Ship ob)
{
  stream << "id: " << ((_Ship*)ob.ptr)->id  <<'\n';
  stream << "type: " << ((_Ship*)ob.ptr)->type  <<'\n';
  stream << "cost: " << ((_Ship*)ob.ptr)->cost  <<'\n';
  stream << "radius: " << ((_Ship*)ob.ptr)->radius  <<'\n';
  stream << "range: " << ((_Ship*)ob.ptr)->range  <<'\n';
  stream << "damage: " << ((_Ship*)ob.ptr)->damage  <<'\n';
  stream << "selfDestructDamage: " << ((_Ship*)ob.ptr)->selfDestructDamage  <<'\n';
  stream << "maxMovement: " << ((_Ship*)ob.ptr)->maxMovement  <<'\n';
  stream << "maxAttacks: " << ((_Ship*)ob.ptr)->maxAttacks  <<'\n';
  stream << "maxHealth: " << ((_Ship*)ob.ptr)->maxHealth  <<'\n';
  stream << "owner: " << ((_Ship*)ob.ptr)->owner  <<'\n';
  stream << "x: " << ((_Ship*)ob.ptr)->x  <<'\n';
  stream << "y: " << ((_Ship*)ob.ptr)->y  <<'\n';
  stream << "attacksLeft: " << ((_Ship*)ob.ptr)->attacksLeft  <<'\n';
  stream << "movementLeft: " << ((_Ship*)ob.ptr)->movementLeft  <<'\n';
  stream << "health: " << ((_Ship*)ob.ptr)->health  <<'\n';
  return stream;
}
