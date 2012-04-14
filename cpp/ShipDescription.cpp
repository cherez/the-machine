// -*-c++-*-

#include "ShipDescription.h"
#include "game.h"


ShipDescription::ShipDescription(_ShipDescription* pointer)
{
    ptr = (void*) pointer;
}

int ShipDescription::id()
{
  return ((_ShipDescription*)ptr)->id;
}

char* ShipDescription::type()
{
  return ((_ShipDescription*)ptr)->type;
}

int ShipDescription::cost()
{
  return ((_ShipDescription*)ptr)->cost;
}

int ShipDescription::radius()
{
  return ((_ShipDescription*)ptr)->radius;
}

int ShipDescription::range()
{
  return ((_ShipDescription*)ptr)->range;
}

int ShipDescription::damage()
{
  return ((_ShipDescription*)ptr)->damage;
}

int ShipDescription::selfDestructDamage()
{
  return ((_ShipDescription*)ptr)->selfDestructDamage;
}

int ShipDescription::maxMovement()
{
  return ((_ShipDescription*)ptr)->maxMovement;
}

int ShipDescription::maxAttacks()
{
  return ((_ShipDescription*)ptr)->maxAttacks;
}

int ShipDescription::maxHealth()
{
  return ((_ShipDescription*)ptr)->maxHealth;
}




std::ostream& operator<<(std::ostream& stream,ShipDescription ob)
{
  stream << "id: " << ((_ShipDescription*)ob.ptr)->id  <<'\n';
  stream << "type: " << ((_ShipDescription*)ob.ptr)->type  <<'\n';
  stream << "cost: " << ((_ShipDescription*)ob.ptr)->cost  <<'\n';
  stream << "radius: " << ((_ShipDescription*)ob.ptr)->radius  <<'\n';
  stream << "range: " << ((_ShipDescription*)ob.ptr)->range  <<'\n';
  stream << "damage: " << ((_ShipDescription*)ob.ptr)->damage  <<'\n';
  stream << "selfDestructDamage: " << ((_ShipDescription*)ob.ptr)->selfDestructDamage  <<'\n';
  stream << "maxMovement: " << ((_ShipDescription*)ob.ptr)->maxMovement  <<'\n';
  stream << "maxAttacks: " << ((_ShipDescription*)ob.ptr)->maxAttacks  <<'\n';
  stream << "maxHealth: " << ((_ShipDescription*)ob.ptr)->maxHealth  <<'\n';
  return stream;
}
