using System;
using System.Runtime.InteropServices;


///Base class for all variables needed to define a ship
public abstract class ShipDescription
{
  public IntPtr ptr;
  protected int ID;
  protected int iteration;

  public ShipDescription()
  {
  }

  public ShipDescription(IntPtr p)
  {
    ptr = p;
    ID = Client.shipDescriptionGetId(ptr);
    iteration = BaseAI.iteration;
  }

  public abstract bool validify();

    //commands


    //getters

  ///Unique Identifier
  public int getId()
  {
    validify();
    int value = Client.shipDescriptionGetId(ptr);
    return value;
  }
  ///The ship type
  public string getType()
  {
    validify();
    IntPtr value = Client.shipDescriptionGetType(ptr);
    return Marshal.PtrToStringAuto(value);
  }
  ///The amount of energy required to warp in this type of ship
  public int getCost()
  {
    validify();
    int value = Client.shipDescriptionGetCost(ptr);
    return value;
  }
  ///The radius of the ship
  public int getRadius()
  {
    validify();
    int value = Client.shipDescriptionGetRadius(ptr);
    return value;
  }
  ///The range of attacks for this ship, given as the maximum distance from the center of this ship to the edge of the target
  public int getRange()
  {
    validify();
    int value = Client.shipDescriptionGetRange(ptr);
    return value;
  }
  ///The strength of attacks for this ship
  public int getDamage()
  {
    validify();
    int value = Client.shipDescriptionGetDamage(ptr);
    return value;
  }
  ///The amount of damage done when this ship self destructs
  public int getSelfDestructDamage()
  {
    validify();
    int value = Client.shipDescriptionGetSelfDestructDamage(ptr);
    return value;
  }
  ///The largest possible movement for this ship
  public int getMaxMovement()
  {
    validify();
    int value = Client.shipDescriptionGetMaxMovement(ptr);
    return value;
  }
  ///The max number of attacks for this ship
  public int getMaxAttacks()
  {
    validify();
    int value = Client.shipDescriptionGetMaxAttacks(ptr);
    return value;
  }
  ///The max health possible for the ship
  public int getMaxHealth()
  {
    validify();
    int value = Client.shipDescriptionGetMaxHealth(ptr);
    return value;
  }

}
