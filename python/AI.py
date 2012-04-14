#-*-python-*-
from BaseAI import BaseAI
from GameObject import *

class AI(BaseAI):
  """The class implementing gameplay logic."""
  @staticmethod
  def username():
    return "Shell AI"

  @staticmethod
  def password():
    return "password"

  ##This function is called once, before your first turn
  def init(self):
    pass

  ##This function is called once, after your last turn
  def end(self):
    pass

  ##This function is called each time it is your turn
  ##Return true to end your turn, return false to ask the server for updated information
  def run(self):
    print "Starting turn %i of round %i"%(self.turnNumber, self.roundNumber)
    #Find each player's warp gate
    for ship in self.ships:
      #if this ship is of type Warp Gate
      if ship.type == "Warp Gate":
        #if you own this ship
        if ship.owner == self.playerID:
          myGate = ship
        else:
          theirGate = ship
     
     #Warp in some ships
    for shipType in self.shipTypes:
      #If you have enough energy to warp in this type of ship
      if shipType.cost <= self.players[self.playerID].energy:
        #Warp it in directly on top of your warp gate
        shipType.warpIn(myGate.x,myGate.y)
    
    #Command your ships
    for ship in self.ships:
      #If you own this ship, it can move, and it can attack
      if ship.owner == self.playerID and ship.movementLeft > 0 and ship.attacksLeft > 0:
        #Find a point on the line connecting this ship and their warp gate is close enough for this ship to move to.
        x, y = self.pointOnLine(ship.x, ship.y, theirGate.x, theirGate.y, ship.movementLeft)
        #If I have move to get there
        if ship.x != x or ship.y != y:
          ship.move(x, y)
        #If the distance from my ship to their warp gate is less than my ships attack range plus their gate's radius
        if self.distance(ship.x, ship.y, theirGate.x, theirGate.y) <= ship.range + theirGate.radius:
          #If their warp gate is still alive
          if theirGate.health > 0:
            ship.attack(theirGate)
    return 1

  def __init__(self, conn):
    BaseAI.__init__(self, conn)
