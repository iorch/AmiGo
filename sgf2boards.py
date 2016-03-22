#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import re


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
      self.board = self.empty
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
  b = k.starting_board()
  m1 = k.get_position_at(20000)
  print(k.print_board(m1))
