using System;
using System.Runtime.InteropServices;


///
public class Player
{
  public IntPtr ptr;
  protected int ID;
  protected int iteration;

  public Player()
  {
  }

  public Player(IntPtr p)
  {
    ptr = p;
    ID = Client.playerGetId(ptr);
    iteration = BaseAI.iteration;
  }

  public bool validify()
  {
    if(iteration == BaseAI.iteration) return true;
    for(int i = 0; i < BaseAI.players.Length; i++)
    {
      if(BaseAI.players[i].ID == ID)
      {
        ptr = BaseAI.players[i].ptr;
        iteration = BaseAI.iteration;
        return true;
      }
    }
    throw new ExistentialError();
  }

    //commands

  ///Allows a player to display messages on the screen
  public int talk(string message)
  {
    validify();
    return Client.playerTalk(ptr, message);
  }

    //getters

  ///Unique Identifier
  public int getId()
  {
    validify();
    int value = Client.playerGetId(ptr);
    return value;
  }
  ///Player's Name
  public string getPlayerName()
  {
    validify();
    IntPtr value = Client.playerGetPlayerName(ptr);
    return Marshal.PtrToStringAuto(value);
  }
  ///Time remaining, updated at start of turn
  public float getTime()
  {
    validify();
    float value = Client.playerGetTime(ptr);
    return value;
  }
  ///How many rounds you have won this game
  public int getVictories()
  {
    validify();
    int value = Client.playerGetVictories(ptr);
    return value;
  }
  ///How much energy the player has left to warp in ships
  public int getEnergy()
  {
    validify();
    int value = Client.playerGetEnergy(ptr);
    return value;
  }

}
