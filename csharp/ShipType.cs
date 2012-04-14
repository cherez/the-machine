using System;
using System.Runtime.InteropServices;


///An available ship type
public class ShipType: ShipDescription
{

  public ShipType()
  {
  }

  public ShipType(IntPtr p)
  {
    ptr = p;
    ID = Client.shipTypeGetId(ptr);
    iteration = BaseAI.iteration;
  }

  public override bool validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.shipTypes.Length; i++)
    {
      if(BaseAI.shipTypes[i].ID == ID)
      {
        ptr = BaseAI.shipTypes[i].ptr;
        iteration = BaseAI.iteration;
        return true;
      }
    }
    throw new ExistentialError();
  }

    //commands

  ///Sends in a new ship of this type. Ships must be warped in within the radius of the player's warp gate.
  public int warpIn(int x, int y)
  {
    validify();
    return Client.shipTypeWarpIn(ptr, x, y);
  }

    //getters

  ///Unique Identifier
  public new int getId()
  {
    validify();
    int value = Client.shipTypeGetId(ptr);
    return value;
  }
  ///The ship type
  public new string getType()
  {
    validify();
    IntPtr value = Client.shipTypeGetType(ptr);
    return Marshal.PtrToStringAuto(value);
  }
  ///The amount of energy required to warp in this type of ship
  public new int getCost()
  {
    validify();
    int value = Client.shipTypeGetCost(ptr);
    return value;
  }
  ///The radius of the ship
  public new int getRadius()
  {
    validify();
    int value = Client.shipTypeGetRadius(ptr);
    return value;
  }
  ///The range of attacks for this ship, given as the maximum distance from the center of this ship to the edge of the target
  public new int getRange()
  {
    validify();
    int value = Client.shipTypeGetRange(ptr);
    return value;
  }
  ///The strength of attacks for this ship
  public new int getDamage()
  {
    validify();
    int value = Client.shipTypeGetDamage(ptr);
    return value;
  }
  ///The amount of damage done when this ship self destructs
  public new int getSelfDestructDamage()
  {
    validify();
    int value = Client.shipTypeGetSelfDestructDamage(ptr);
    return value;
  }
  ///The largest possible movement for this ship
  public new int getMaxMovement()
  {
    validify();
    int value = Client.shipTypeGetMaxMovement(ptr);
    return value;
  }
  ///The max number of attacks for this ship
  public new int getMaxAttacks()
  {
    validify();
    int value = Client.shipTypeGetMaxAttacks(ptr);
    return value;
  }
  ///The max health possible for the ship
  public new int getMaxHealth()
  {
    validify();
    int value = Client.shipTypeGetMaxHealth(ptr);
    return value;
  }

}
