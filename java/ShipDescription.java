import com.sun.jna.Pointer;

///Base class for all variables needed to define a ship
abstract class ShipDescription
{
  Pointer ptr;
  int ID;
  int iteration;
  public ShipDescription(Pointer p)
  {
    ptr = p;
    ID = Client.INSTANCE.shipDescriptionGetId(ptr);
    iteration = BaseAI.iteration;
  }
  abstract boolean validify();

    //commands


    //getters

  ///Unique Identifier
  public int getId()
  {
    validify();
    return Client.INSTANCE.shipDescriptionGetId(ptr);
  }
  ///The ship type
  public String getType()
  {
    validify();
    return Client.INSTANCE.shipDescriptionGetType(ptr);
  }
  ///The amount of energy required to warp in this type of ship
  public int getCost()
  {
    validify();
    return Client.INSTANCE.shipDescriptionGetCost(ptr);
  }
  ///The radius of the ship
  public int getRadius()
  {
    validify();
    return Client.INSTANCE.shipDescriptionGetRadius(ptr);
  }
  ///The range of attacks for this ship, given as the maximum distance from the center of this ship to the edge of the target
  public int getRange()
  {
    validify();
    return Client.INSTANCE.shipDescriptionGetRange(ptr);
  }
  ///The strength of attacks for this ship
  public int getDamage()
  {
    validify();
    return Client.INSTANCE.shipDescriptionGetDamage(ptr);
  }
  ///The amount of damage done when this ship self destructs
  public int getSelfDestructDamage()
  {
    validify();
    return Client.INSTANCE.shipDescriptionGetSelfDestructDamage(ptr);
  }
  ///The largest possible movement for this ship
  public int getMaxMovement()
  {
    validify();
    return Client.INSTANCE.shipDescriptionGetMaxMovement(ptr);
  }
  ///The max number of attacks for this ship
  public int getMaxAttacks()
  {
    validify();
    return Client.INSTANCE.shipDescriptionGetMaxAttacks(ptr);
  }
  ///The max health possible for the ship
  public int getMaxHealth()
  {
    validify();
    return Client.INSTANCE.shipDescriptionGetMaxHealth(ptr);
  }

}
