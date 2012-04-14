#!/bin/env python

import subprocess
import argparse
import random

host = 'server.megaminerai.com'
game = -1

def run(*args):
  command = ['./run']
  command.extend(args)
  kwargs = {} #stub for future features
  return subprocess.Popen(command, **kwargs)

def run_host(host):
  run(host).wait()

def run_guest(host, game):
  run(host, game).wait()

def run_practice(host, game):
  print `host`, `game`
  procs = [run(host, game) for i in range(2)]
  for i in procs:
    i.wait()

if __name__ == '__main__':
  parser = argparse.ArgumentParser(description='Start the client')
  parser.add_argument('--host', default=host)
  parser.add_argument('game', default=game, nargs='?')
  parser.add_argument('--practice', action='store_true', help='Run two clients to play against each other.')

  args = parser.parse_args()

  print args

  if args.practice:
    if args.game == -1:
      args.game = str(random.randrange(2**30))
    run_practice(args.host, args.game)
  else:
    if args.game == game:
      run_host(args.host)
    else:
      run_guest(args.host, args.game)

