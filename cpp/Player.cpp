// -*-c++-*-

#include "Player.h"
#include "game.h"


Player::Player(_Player* pointer)
{
    ptr = (void*) pointer;
}

int Player::id()
{
  return ((_Player*)ptr)->id;
}

char* Player::playerName()
{
  return ((_Player*)ptr)->playerName;
}

float Player::time()
{
  return ((_Player*)ptr)->time;
}

int Player::victories()
{
  return ((_Player*)ptr)->victories;
}

int Player::energy()
{
  return ((_Player*)ptr)->energy;
}


int Player::talk(char* message)
{
  return playerTalk( (_Player*)ptr, message);
}



std::ostream& operator<<(std::ostream& stream,Player ob)
{
  stream << "id: " << ((_Player*)ob.ptr)->id  <<'\n';
  stream << "playerName: " << ((_Player*)ob.ptr)->playerName  <<'\n';
  stream << "time: " << ((_Player*)ob.ptr)->time  <<'\n';
  stream << "victories: " << ((_Player*)ob.ptr)->victories  <<'\n';
  stream << "energy: " << ((_Player*)ob.ptr)->energy  <<'\n';
  return stream;
}
