using System;
using System.Runtime.InteropServices;

/// \brief A basic AI interface.

///This class implements most the code an AI would need to interface with the lower-level game code.
///AIs should extend this class to get a lot of builer-plate code out of the way
///The provided AI class does just that.
public abstract class BaseAI
{
  public static ShipType[] shipTypes;
  public static Player[] players;
  public static Ship[] ships;
  IntPtr connection;
  public static int iteration;
  bool initialized;

  public BaseAI(IntPtr c)
  {
    connection = c;
  }

  ///
  ///Make this your username, which should be provided.
  public abstract String username();
  ///
  ///Make this your password, which should be provided.
  public abstract String password();
  ///
  ///This is run on turn 1 before run
  public abstract void init();
  ///
  ///This is run every turn . Return true to end the turn, return false
  ///to request a status update from the server and then immediately rerun this function with the
  ///latest game status.
  public abstract bool run();

  ///
  ///This is run on after your last turn.
  public abstract void end();


  public bool startTurn()
  {
    iteration++;
    int count = 0;
    count = Client.getShipTypeCount(connection);
    shipTypes = new ShipType[count];
    for(int i = 0; i < count; i++)
    {
      shipTypes[i] = new ShipType(Client.getShipType(connection, i));
    }
    count = Client.getPlayerCount(connection);
    players = new Player[count];
    for(int i = 0; i < count; i++)
    {
      players[i] = new Player(Client.getPlayer(connection, i));
    }
    count = Client.getShipCount(connection);
    ships = new Ship[count];
    for(int i = 0; i < count; i++)
    {
      ships[i] = new Ship(Client.getShip(connection, i));
    }

    if(!initialized)
    {
      initialized = true;
      init();
    }
    return run();
  }


  ///How many turns it has been since the beginning of the round
  public int turnNumber()
  {
    int value = Client.getTurnNumber(connection);
    return value;
  }
  ///Player Number; either 0 or 1
  public int playerID()
  {
    int value = Client.getPlayerID(connection);
    return value;
  }
  ///What number game this is for the server
  public int gameNumber()
  {
    int value = Client.getGameNumber(connection);
    return value;
  }
  ///The current round of the match
  public int roundNumber()
  {
    int value = Client.getRoundNumber(connection);
    return value;
  }
  ///How many victories a player needs to win this game.  If the last round is a tie, one more victory is needed
  public int victoriesNeeded()
  {
    int value = Client.getVictoriesNeeded(connection);
    return value;
  }
  ///The outer radius of the map.  Center of screen is (0,0), with +x right, +y up
  public int mapRadius()
  {
    int value = Client.getMapRadius(connection);
    return value;
  }
  ///Returns the distance between two points
  public int distance(int fromX, int fromY, int toX, int toY)
  {
    return Client.baseDistance(fromX, fromY, toX, toY);
  }
  ///Find a point "travel" distance from the starting point in the direction of the ending point.  Uses out parameters
  public void pointOnLine(int fromX, int fromY, int toX, int toY, int travel, out int outX, out int outY)
  {
    int ret = Client.basePointOnLine(fromX, fromY, toX, toY, travel);
    outX = ret / 1024 - 500;
    outY = ret % 1024 - 500;
  }

}
