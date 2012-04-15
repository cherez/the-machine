#-*-python-*-
from BaseAI import BaseAI
from GameObject import *
from collections import defaultdict
from math import *

shipPriorities = defaultdict(lambda: 100)
shipPriorities['EMP'] = 1
shipPriorities['Support'] = 2
shipPriorities['Warp Gate'] = 1000
shipPriorities['Mine'] = 9001

class AI(BaseAI):
  """The class implementing gameplay logic."""
  @staticmethod
  def username():
    return "the-machine"

  @staticmethod
  def password():
    return "YXBTUZ"

  ##This function is called once, before your first turn
  def init(self):
    print 'Priority.'
    self.targetList = []
    self.myShips = []
    pass

  ##This function is called once, after your last turn
  def end(self):
    pass

  def moveAngle(self, x, y, angle, distance):
    dx = int(cos(angle) * distance)
    dy = int(sin(angle) * distance)
    x += dx
    y += dy
    return x, y

  def genPoints(self, x, y, distance, angles, distances):
    for i in range(1, distances+1):
      d = int(i * float(distance) / distances)
      for j in range(angles):
        angle = 2*pi * j / angles
        yield self.moveAngle(x, y, angle, d)


  def flee(self, kiter, kitee):
    points = [(i[0], i[1]) for i in self.genPoints(kiter.x, kiter.y, kiter.movementLeft, 8, 2)]
    points = [i for i in points if self.distance(0, 0, i[0], i[1]) <= 500-kiter.radius]
    points.sort(key = lambda p: self.distance(kitee.x, kitee.y, p[0], p[1]), reverse=True)
    point = points[0]

    kiter.move(point[0], point[1])

  def fleeAll(self, kiter):
    if not self.targetList:
      return
    kitee = min(self.targetList, key=lambda s: self.distance(kiter.x, kiter.y, s.x, s.y))
    self.flee(kiter, kitee)

  def spawnShips(self):
    types = sorted(self.shipTypes, key = lambda s: s.damage/s.cost, reverse=True)
    types = [i for i in types if i.type not in ["Support", "EMP", "Mine Layer"] ] #It's complicated
    cheapest = min(i.cost for i in types)
    #Warp in some ships
    while self.players[self.playerID].energy >= cheapest:
      for shipType in types:
        #If you have enough energy to warp in this type of ship
        if shipType.cost <= self.players[self.playerID].energy:
          #Warp it in directly on top of your warp gate
          shipType.warpIn(self.myGate.x,self.myGate.y)
          break

  def controlShips(self):
    self.targetList.sort(key= lambda s:shipPriorities[s.type])
    for ship in self.myShips:
      #If you own this ship, it can move, and it can attack
      if ship.owner == self.playerID and ship.movementLeft > 0 and ship.attacksLeft > 0:
        #Find a point on the line connecting this ship and their warp gate is close enough for this ship to move to.
        ship.hasHit = []
        self.shootShips(ship)
        x, y = self.pointOnLine(ship.x, ship.y, self.theirGate.x, self.theirGate.y, ship.movementLeft)
        #If I have move to get there
        if ship.x != x or ship.y != y:
          ship.move(x, y)
        #If the distance from my ship to their warp gate is less than my ships attack range plus their gate's radius
        self.shootShips(ship)
      #if a ship should explode, we make sure that it explodes
      if self.shouldExplode(ship):
        ship.selfDestruct()
    self.fleeAll(self.myGate)


  def shouldExplode(self, ship):
    if ship.type == 'Battleship':
      return False
    nobleSacrificeQuotient = 0
    for target in self.targetList:
      if target.health > 0 and self.distance(ship.x, ship.y, target.x, target.y) - ship.radius - target.radius < 0:
        if target.type == "EMP":
          nobleSacrificeQuotient += 10
        else:
          nobleSacrificeQuotient += 1

    if nobleSacrificeQuotient > 5:
      return True
    return False

  def shootShips(self, ship):
    if ship.attacksLeft <= 0:
      return
    for target in self.targetList:
      if target.health > 0 and target not in ship.hasHit and self.distance(ship.x, ship.y, target.x, target.y) < ship.range + target.radius:
        if ship.attacksLeft > 0:
          ship.attack(target)
          ship.hasHit += [target]
          if ship.attacksLeft <= 0:
            return

  ##This function is called each time it is your turn
  ##Return true to end your turn, return false to ask the server for updated information
  def run(self):
    print "Starting turn %i of round %i"%(self.turnNumber, self.roundNumber)
    #Find each player's warp gate
    self.targetList = []
    self.myShips = []
    for ship in self.ships:
      #if this ship is an enemy, add it to the hitlist
      if ship.owner != self.playerID:
        self.targetList += [ship]
      if ship.owner == self.playerID:
        if ship.type != "Warp Gate":
          self.myShips += [ship]
      #if this ship is of type Warp Gate
      if ship.type == "Warp Gate":
        #if you own this ship
        if ship.owner == self.playerID:
          self.myGate = ship
        else:
          self.theirGate = ship

    self.spawnShips()

    self.controlShips()


    #Command your ships
    return 1

  def __init__(self, conn):
    BaseAI.__init__(self, conn)
