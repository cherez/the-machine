import com.sun.jna.Pointer;

///An available ship type
class ShipType extends ShipDescription
{
  public ShipType(Pointer p)
  {
    super(p);
  }
  boolean validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.shipTypes.length; i++)
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
  int warpIn(int x, int y)
  {
    validify();
    return Client.INSTANCE.shipTypeWarpIn(ptr, x, y);
  }

    //getters

  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.INSTANCE.shipTypeGetId(ptr);
  }
  ///The ship type
  public String getType()
  {
    validify();
    return Client.INSTANCE.shipTypeGetType(ptr);
  }
  ///The amount of energy required to warp in this type of ship
  public int getCost()
  {
    validify();
    return Client.INSTANCE.shipTypeGetCost(ptr);
  }
  ///The radius of the ship
  public int getRadius()
  {
    validify();
    return Client.INSTANCE.shipTypeGetRadius(ptr);
  }
  ///The range of attacks for this ship, given as the maximum distance from the center of this ship to the edge of the target
  public int getRange()
  {
    validify();
    return Client.INSTANCE.shipTypeGetRange(ptr);
  }
  ///The strength of attacks for this ship
  public int getDamage()
  {
    validify();
    return Client.INSTANCE.shipTypeGetDamage(ptr);
  }
  ///The amount of damage done when this ship self destructs
  public int getSelfDestructDamage()
  {
    validify();
    return Client.INSTANCE.shipTypeGetSelfDestructDamage(ptr);
  }
  ///The largest possible movement for this ship
  public int getMaxMovement()
  {
    validify();
    return Client.INSTANCE.shipTypeGetMaxMovement(ptr);
  }
  ///The max number of attacks for this ship
  public int getMaxAttacks()
  {
    validify();
    return Client.INSTANCE.shipTypeGetMaxAttacks(ptr);
  }
  ///The max health possible for the ship
  public int getMaxHealth()
  {
    validify();
    return Client.INSTANCE.shipTypeGetMaxHealth(ptr);
  }

}
