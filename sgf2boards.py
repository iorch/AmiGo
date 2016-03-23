#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import re
import copy


class Group():
  def __init__(self, move = None, color = None, board = None):
    self.COLOR = color
    self.board = copy.deepcopy(board)
    self.stones = set([move])
    self.liberties = set()
    self.coords = 'abcdefghijklmnopqrs'
    self.add_stone(move, color, self.board)
    self.compute_liberties()

  def add_stone(self, move = None, color = None, board = None):
    if not board: board = self.board
    x = self.get_coord( position=move, which='x' )
    y = self.get_coord( position=move, which='y' )
    top = None
    bottom = None
    right = None
    left = None
    if x < 18:
      top = self.coords[x+1] + self.coords[y]
    if x >  0:
      bottom = self.coords[x-1] + self.coords[y]
    if y < 18:
      right = self.coords[x] + self.coords[y+1]
    if y >  0:
      left = self.coords[x] + self.coords[y-1]
    if ( top in self.stones or bottom in self.stones or right in self.stones or left in self.stones ):
      if color == self.COLOR:
        self.stones.add(move)
    board[ x ][ y ] = color
    self.board = board
    self.compute_liberties()
    return self.stones

  def get_coord( self, position='zz', which='' ):
    if which == 'x':
      _coord = re.search(position[ 0 ], self.coords).start()
    elif which == 'y':
      _coord = re.search(position[ 1 ], self.coords).start()
    else:
      _coord = None
    return _coord

  def compute_liberties(self):
    for s in self.stones:
      x = self.get_coord( position=s, which='x' )
      y = self.get_coord( position=s, which='y' )
      if x < 18:
        top = self.coords[x+1] + self.coords[y]
        self.liberties.add(top)
      if x >  0:
        bottom = self.coords[x-1] + self.coords[y]
        self.liberties.add(bottom)
      if y < 18:
        right = self.coords[x] + self.coords[y+1]
        self.liberties.add(right)
      if y >  0:
        left = self.coords[x] + self.coords[y-1]
        self.liberties.add(left)
    _to_remove = set()
    for l in self.liberties:
      x = self.get_coord( position=l, which='x' )
      y = self.get_coord( position=l, which='y' )
      if self.board[x][y] != '.':
        _to_remove.add(l)
    for r in _to_remove:
      self.liberties.remove(r)
    return self.liberties

  def merge(self, group):
    self.stones = self.stones | group.stones
    self.compute_liberties()
    return(self)


class Kifu():
  def __init__( self, file='' ):
    with open(file, 'r') as f:
      _read_data = f.read()
      _kifu = _read_data.split(';')
      self.empty = [ [ '.' for i in range(19) ] for j in range(19) ]
      self.board = copy.deepcopy(self.empty)
      self.coords = 'abcdefghijklmnopqrs'
      self.stones = [ ]
      self.alive_groups = set()
      self.dead_groups = set()
      self.moves = _kifu[ 2: ]
      self.moves_played = 0
      self.next2move = 'B'
      self.pass1 = False
      self.pass2 = False
      self.total_moves = len(self.moves)
      self.set_fileds_and_handicap(_kifu[ 1 ])
      print(self.moves)

  def set_fileds_and_handicap(self, _info):
    fields = {
      'black': 'PB',
      'black_rank': 'BR',
      'white': 'PW',
      'white_rank': 'WR',
      'handicap': 'HA',
      'stone0': 'AB',
      'stones': '',
      'rules': 'RU',
      'komi': 'KM',
      'result': 'RE',
      'size': 'SZ',
    }
    for _line in _info.split('\n'):
      for key in fields:
        _match = '^' + fields[ key ] + '\[(?P<' + key + '>.*)\]$'
        _parse = re.search(_match, _line)
        if key[ 0:5 ] == 'stone':
          if _parse:
            self.stones.append(_parse.group(key))
          key = 'stones'
        else:
          if _parse: setattr(self, key, _parse.group(key))
        if _parse: print(key, getattr(self, key))

  def get_coord( self, position='zz', which='' ):
    if which == 'x':
      _coord = re.search(position[ 0 ], self.coords).start()
    elif which == 'y':
      _coord = re.search(position[ 1 ], self.coords).start()
    else:
      _coord = None
    return _coord

  def starting_board( self ):
    print('test')
    self.next2move = 'B'
    for s in self.stones:
      print(s)
      x = self.get_coord(s, 'x')
      y = self.get_coord(s, 'y')
      g = Group(s, 'B', self.board)
      self.alive_groups.add(g)
      self.board[ x ][ y ] = 'B'
      self.next2move = 'W'
    return self.board

  def print_board( self, board=None ):
    _tmp = [ ]
    if not board: board = self.board
    for row in board:
      _tmp.append(''.join(row))
    visual_board = '\n'.join(_tmp)
    return visual_board

  def get_position_at( self, move=0 ):
    if (move == -1 or move == 'last'):
      move = len(self.moves) - 1
    if (move > len(self.moves)):
      print('Not enough moves, showing last instead')
      move = len(self.moves) - 1
    _colors = [ 'B', 'W' ]
    for m in self.moves[ 0:move ]:
      m = m.rstrip('\r\n')
      _match = self.next2move + '\[(?P<stone>.*)\]'
      _parse = re.search(_match, m)
      _stone = _parse.group('stone')
      if _stone == '':
        self.pass2 = self.pass1 & True
        self.pass1 = True
      else:
        self.pass1 = False
        x = self.get_coord(_stone, 'x')
        y = self.get_coord(_stone, 'y')
      if not self.pass1:
        self.board[ x ][ y ] = self.next2move
      self.next2move = _colors[ (_colors.index(self.next2move) + 1) % len(_colors) ]
    self.moves_played = move
    return self.board

  def get_alive_groups(self,move=None):
    if move==None: move = self.moves_played
    if (move == -1 or move == 'last'):
      move = len(self.moves) - 1
    if (move > len(self.moves)):
      print('Not enough moves, showing last instead')
      move = len(self.moves) - 1
    for m in self.moves[ 0:move ]:
      _match = '(?P<color>.*)\[(?P<stone>.*)\]'
      _parse = re.search(_match, m)
      _stone = _parse.group('stone')
      _color = _parse.group('color')
      added = False
      for g in self.alive_groups:
        _gsize_prev = len(g.stones)
        g.add_stone(_stone, _color)
        _gsize_after = len(g.stones)
        if _gsize_after > _gsize_prev: added = True
      if not added:
        g = Group(_stone, _color, self.board)
        self.alive_groups.add(g)
    for g in self.alive_groups:
      if len(g.liberties)==0:
        self.dead_groups.add(g)
    self.alive_groups.discard(self.dead_groups)
    self.merge_groups()
    return self.alive_groups

  def merge_groups(self):
    _to_remove = []
    c1 = 1
    for g1 in self.alive_groups:
      c2 = 0
      for g2 in self.alive_groups:
        c2 += 1
        if c2 <= c1: continue
        if len(g2.stones & g1.stones) > 0:
          g1.merge(g2)
          self.alive_groups.add(g)
          _to_remove.append(g2)
      c1 += 1
    for _r in _to_remove:
      self.alive_groups.remove(_r)







  #def remove(self, board=None):
  #  if not board: board = self.board

if __name__ == '__main__':
  k = Kifu('sgfs/kgs-19-2015-05-new/2015-05-27-4.sgf')
  b = k.starting_board()
  for g in k.alive_groups:
    print(g.COLOR, g.stones)
  m1 = k.get_position_at(40)
  a1 = k.get_alive_groups(40)
  print(k.print_board(m1))
  for g in a1:
    print(g.COLOR,g.stones)
  print(k.dead_groups)
