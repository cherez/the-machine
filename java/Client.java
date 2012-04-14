import com.sun.jna.Library;
import com.sun.jna.Pointer;
import com.sun.jna.Native;

public interface Client extends Library {
  Client INSTANCE = (Client)Native.loadLibrary("client", Client.class);
  Pointer createConnection();
  boolean serverConnect(Pointer connection, String host, String port);

  boolean serverLogin(Pointer connection, String username, String password);
  int createGame(Pointer connection);
  int joinGame(Pointer connection, int id, String playerType);

  void endTurn(Pointer connection);
  void getStatus(Pointer connection);

  int networkLoop(Pointer connection);


    //commands
  int baseDistance(int fromX, int fromY, int toX, int toY);
  int basePointOnLine(int fromX, int fromY, int toX, int toY, int travel);
  int shipTypeWarpIn(Pointer object, int x, int y);
  int playerTalk(Pointer object, String message);
  int shipMove(Pointer object, int x, int y);
  int shipSelfDestruct(Pointer object);
  int shipAttack(Pointer object, Pointer target);

    //accessors
  int getTurnNumber(Pointer connection);
  int getPlayerID(Pointer connection);
  int getGameNumber(Pointer connection);
  int getRoundNumber(Pointer connection);
  int getVictoriesNeeded(Pointer connection);
  int getMapRadius(Pointer connection);

  Pointer getShipType(Pointer connection, int num);
  int getShipTypeCount(Pointer connection);
  Pointer getPlayer(Pointer connection, int num);
  int getPlayerCount(Pointer connection);
  Pointer getShip(Pointer connection, int num);
  int getShipCount(Pointer connection);


    //getters
  int shipDescriptionGetId(Pointer ptr);
  String shipDescriptionGetType(Pointer ptr);
  int shipDescriptionGetCost(Pointer ptr);
  int shipDescriptionGetRadius(Pointer ptr);
  int shipDescriptionGetRange(Pointer ptr);
  int shipDescriptionGetDamage(Pointer ptr);
  int shipDescriptionGetSelfDestructDamage(Pointer ptr);
  int shipDescriptionGetMaxMovement(Pointer ptr);
  int shipDescriptionGetMaxAttacks(Pointer ptr);
  int shipDescriptionGetMaxHealth(Pointer ptr);

  int shipTypeGetId(Pointer ptr);
  String shipTypeGetType(Pointer ptr);
  int shipTypeGetCost(Pointer ptr);
  int shipTypeGetRadius(Pointer ptr);
  int shipTypeGetRange(Pointer ptr);
  int shipTypeGetDamage(Pointer ptr);
  int shipTypeGetSelfDestructDamage(Pointer ptr);
  int shipTypeGetMaxMovement(Pointer ptr);
  int shipTypeGetMaxAttacks(Pointer ptr);
  int shipTypeGetMaxHealth(Pointer ptr);

  int playerGetId(Pointer ptr);
  String playerGetPlayerName(Pointer ptr);
  float playerGetTime(Pointer ptr);
  int playerGetVictories(Pointer ptr);
  int playerGetEnergy(Pointer ptr);

  int shipGetId(Pointer ptr);
  String shipGetType(Pointer ptr);
  int shipGetCost(Pointer ptr);
  int shipGetRadius(Pointer ptr);
  int shipGetRange(Pointer ptr);
  int shipGetDamage(Pointer ptr);
  int shipGetSelfDestructDamage(Pointer ptr);
  int shipGetMaxMovement(Pointer ptr);
  int shipGetMaxAttacks(Pointer ptr);
  int shipGetMaxHealth(Pointer ptr);
  int shipGetOwner(Pointer ptr);
  int shipGetX(Pointer ptr);
  int shipGetY(Pointer ptr);
  int shipGetAttacksLeft(Pointer ptr);
  int shipGetMovementLeft(Pointer ptr);
  int shipGetHealth(Pointer ptr);


    //properties

}
