// -*-c++-*-

#include "ShipType.h"
#include "game.h"


ShipType::ShipType(_ShipType* pointer)
{
    ptr = (void*) pointer;
}

int ShipType::id()
{
  return ((_ShipType*)ptr)->id;
}

char* ShipType::type()
{
  return ((_ShipType*)ptr)->type;
}

int ShipType::cost()
{
  return ((_ShipType*)ptr)->cost;
}

int ShipType::radius()
{
  return ((_ShipType*)ptr)->radius;
}

int ShipType::range()
{
  return ((_ShipType*)ptr)->range;
}

int ShipType::damage()
{
  return ((_ShipType*)ptr)->damage;
}

int ShipType::selfDestructDamage()
{
  return ((_ShipType*)ptr)->selfDestructDamage;
}

int ShipType::maxMovement()
{
  return ((_ShipType*)ptr)->maxMovement;
}

int ShipType::maxAttacks()
{
  return ((_ShipType*)ptr)->maxAttacks;
}

int ShipType::maxHealth()
{
  return ((_ShipType*)ptr)->maxHealth;
}


int ShipType::warpIn(int x, int y)
{
  return shipTypeWarpIn( (_ShipType*)ptr, x, y);
}



std::ostream& operator<<(std::ostream& stream,ShipType ob)
{
  stream << "id: " << ((_ShipType*)ob.ptr)->id  <<'\n';
  stream << "type: " << ((_ShipType*)ob.ptr)->type  <<'\n';
  stream << "cost: " << ((_ShipType*)ob.ptr)->cost  <<'\n';
  stream << "radius: " << ((_ShipType*)ob.ptr)->radius  <<'\n';
  stream << "range: " << ((_ShipType*)ob.ptr)->range  <<'\n';
  stream << "damage: " << ((_ShipType*)ob.ptr)->damage  <<'\n';
  stream << "selfDestructDamage: " << ((_ShipType*)ob.ptr)->selfDestructDamage  <<'\n';
  stream << "maxMovement: " << ((_ShipType*)ob.ptr)->maxMovement  <<'\n';
  stream << "maxAttacks: " << ((_ShipType*)ob.ptr)->maxAttacks  <<'\n';
  stream << "maxHealth: " << ((_ShipType*)ob.ptr)->maxHealth  <<'\n';
  return stream;
}
