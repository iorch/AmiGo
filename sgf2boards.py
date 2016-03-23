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
    ctop = None
    cbottom = None
    cright = None
    cleft = None
    if x < 18:
      ctop = self.board[x+1][y]
    if x >  0:
      cbottom = self.board[x-1][y]
    if y < 18:
      cright = self.board[x][y+1]
    if y >  0:
      cleft = self.board[x][y-1]
    if ( ctop == self.COLOR or cbottom == self.COLOR or cright == self.COLOR or cleft == self.COLOR ):
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



class Kifu():
  def __init__( self, file='' ):
    with open(file, 'r') as f:
      _read_data = f.read()
      _kifu = _read_data.split(';')
      _info = _kifu[ 1 ]
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
      self.empty = [ [ '.' for i in range(19) ] for j in range(19) ]
      self.board = copy.deepcopy(self.empty)
      self.coords = 'abcdefghijklmnopqrs'
      self.stones = [ ]
      for _line in _info.split('\n'):
        for key in fields:
          _match = '^' + fields[ key ] + '\[(?P<' + key + '>.*)\]$'
          _parse = re.search(_match, _line)
          if key[ 0:5 ] == 'stone':
            if _parse: self.stones.append(_parse.group(key))
            key = 'stones'
          else:
            if _parse: setattr(self, key, _parse.group(key))
          if _parse: print(key, getattr(self, key))
      self.moves = _kifu[ 2: ]
      self.moves_played = 0
      self.next2move = 'B'
      self.pass1 = False
      self.pass2 = False
      self.total_moves = len(self.moves)
      print(self.moves)

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

  #def remove(self, board=None):
  #  if not board: board = self.board



if __name__ == '__main__':
  k = Kifu('sgfs/kgs-19-2015-05-new/2015-05-27-4.sgf')
  g = Group('dd', 'B', copy.deepcopy(k.empty))
  g.add_stone('cd','B')
  g.add_stone('cc','W')

  b = k.starting_board()
  m1 = k.get_position_at(20000)
  print(k.print_board(m1))

  print(g.stones)
  print(g.liberties)
  print(g.board)