# -*- python -*-

from library import library

class BaseAI:
  """@brief A basic AI interface.

  This class implements most the code an AI would need to interface with the lower-level game code.
  AIs should extend this class to get a lot of builer-plate code out of the way
  The provided AI class does just that.
  """
  #\cond
  initialized = False
  iteration = 0
  runGenerator = None
  connection = None
  #\endcond
  shipTypes = []
  players = []
  ships = []
  #\cond
  def startTurn(self):
    from GameObject import ShipType
    from GameObject import Player
    from GameObject import Ship

    BaseAI.shipTypes = [ShipType(library.getShipType(self.connection, i)) for i in xrange(library.getShipTypeCount(self.connection))]
    BaseAI.players = [Player(library.getPlayer(self.connection, i)) for i in xrange(library.getPlayerCount(self.connection))]
    BaseAI.ships = [Ship(library.getShip(self.connection, i)) for i in xrange(library.getShipCount(self.connection))]

    if not self.initialized:
      self.initialized = True
      self.init()
    BaseAI.iteration += 1;
    if self.runGenerator:
      try:
        return self.runGenerator.next()
      except StopIteration:
        self.runGenerator = None
    r = self.run()
    if hasattr(r, '__iter__'):
      self.runGenerator = r
      return r.next()
    return r
  #\endcond
  #\cond
  def getTurnNumber(self):
    return library.getTurnNumber(self.connection)
  #\endcond
  turnNumber = property(getTurnNumber)
  #\cond
  def getPlayerID(self):
    return library.getPlayerID(self.connection)
  #\endcond
  playerID = property(getPlayerID)
  #\cond
  def getGameNumber(self):
    return library.getGameNumber(self.connection)
  #\endcond
  gameNumber = property(getGameNumber)
  #\cond
  def getRoundNumber(self):
    return library.getRoundNumber(self.connection)
  #\endcond
  roundNumber = property(getRoundNumber)
  #\cond
  def getVictoriesNeeded(self):
    return library.getVictoriesNeeded(self.connection)
  #\endcond
  victoriesNeeded = property(getVictoriesNeeded)
  #\cond
  def getMapRadius(self):
    return library.getMapRadius(self.connection)
  #\endcond
  mapRadius = property(getMapRadius)
  ##Returns the distance between two points
  def distance(self, fromX, fromY, toX, toY):
    return library.baseDistance(fromX, fromY, toX, toY)
  ##Find a point "travel" distance from the starting point in the direction of the ending point.  Returns the tuple (x, y)
  def pointOnLine(self, fromX, fromY, toX, toY, travel):
    ret = library.basePointOnLine(fromX, fromY, toX, toY, travel)
    return (ret / 1024 - 500, ret % 1024 - 500)
  def __init__(self, connection):
    self.connection = connection
