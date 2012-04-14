using System;
using System.Runtime.InteropServices;

public class Client {
  [DllImport("client")]
  public static extern IntPtr createConnection();
  [DllImport("client")]
  public static extern int serverConnect(IntPtr connection, string host, string port);

  [DllImport("client")]
  public static extern int serverLogin(IntPtr connection, string username, string password);
  [DllImport("client")]
  public static extern int createGame(IntPtr connection);
  [DllImport("client")]
  public static extern int joinGame(IntPtr connection, int id, string playerType);

  [DllImport("client")]
  public static extern void endTurn(IntPtr connection);
  [DllImport("client")]
  public static extern void getStatus(IntPtr connection);

  [DllImport("client")]
  public static extern int networkLoop(IntPtr connection);


    //commands
  [DllImport("client")]
  public static extern int baseDistance(int fromX, int fromY, int toX, int toY);
  [DllImport("client")]
  public static extern int basePointOnLine(int fromX, int fromY, int toX, int toY, int travel);
  [DllImport("client")]
  public static extern int shipTypeWarpIn(IntPtr self, int x, int y);
  [DllImport("client")]
  public static extern int playerTalk(IntPtr self, string message);
  [DllImport("client")]
  public static extern int shipMove(IntPtr self, int x, int y);
  [DllImport("client")]
  public static extern int shipSelfDestruct(IntPtr self);
  [DllImport("client")]
  public static extern int shipAttack(IntPtr self, IntPtr target);

    //accessors
  [DllImport("client")]
  public static extern int getTurnNumber(IntPtr connection);
  [DllImport("client")]
  public static extern int getPlayerID(IntPtr connection);
  [DllImport("client")]
  public static extern int getGameNumber(IntPtr connection);
  [DllImport("client")]
  public static extern int getRoundNumber(IntPtr connection);
  [DllImport("client")]
  public static extern int getVictoriesNeeded(IntPtr connection);
  [DllImport("client")]
  public static extern int getMapRadius(IntPtr connection);

  [DllImport("client")]
  public static extern IntPtr getShipType(IntPtr connection, int num);
  [DllImport("client")]
  public static extern int getShipTypeCount(IntPtr connection);
  [DllImport("client")]
  public static extern IntPtr getPlayer(IntPtr connection, int num);
  [DllImport("client")]
  public static extern int getPlayerCount(IntPtr connection);
  [DllImport("client")]
  public static extern IntPtr getShip(IntPtr connection, int num);
  [DllImport("client")]
  public static extern int getShipCount(IntPtr connection);


    //getters
  [DllImport("client")]
  public static extern int shipDescriptionGetId(IntPtr ptr);
  [DllImport("client")]
  public static extern IntPtr shipDescriptionGetType(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipDescriptionGetCost(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipDescriptionGetRadius(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipDescriptionGetRange(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipDescriptionGetDamage(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipDescriptionGetSelfDestructDamage(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipDescriptionGetMaxMovement(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipDescriptionGetMaxAttacks(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipDescriptionGetMaxHealth(IntPtr ptr);

  [DllImport("client")]
  public static extern int shipTypeGetId(IntPtr ptr);
  [DllImport("client")]
  public static extern IntPtr shipTypeGetType(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipTypeGetCost(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipTypeGetRadius(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipTypeGetRange(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipTypeGetDamage(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipTypeGetSelfDestructDamage(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipTypeGetMaxMovement(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipTypeGetMaxAttacks(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipTypeGetMaxHealth(IntPtr ptr);

  [DllImport("client")]
  public static extern int playerGetId(IntPtr ptr);
  [DllImport("client")]
  public static extern IntPtr playerGetPlayerName(IntPtr ptr);
  [DllImport("client")]
  public static extern float playerGetTime(IntPtr ptr);
  [DllImport("client")]
  public static extern int playerGetVictories(IntPtr ptr);
  [DllImport("client")]
  public static extern int playerGetEnergy(IntPtr ptr);

  [DllImport("client")]
  public static extern int shipGetId(IntPtr ptr);
  [DllImport("client")]
  public static extern IntPtr shipGetType(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipGetCost(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipGetRadius(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipGetRange(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipGetDamage(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipGetSelfDestructDamage(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipGetMaxMovement(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipGetMaxAttacks(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipGetMaxHealth(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipGetOwner(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipGetX(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipGetY(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipGetAttacksLeft(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipGetMovementLeft(IntPtr ptr);
  [DllImport("client")]
  public static extern int shipGetHealth(IntPtr ptr);


    //properties

}
