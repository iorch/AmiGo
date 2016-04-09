#!/usr/bin/env python3

import amigo
import sys

def usage():
    print("Usage: ./show_game.py sgf_file. \n       use 'q' to exit.\n\n")
    return

def draw_match( sgf_file ):
    kifu = amigo.kifu(sgf_file)
    move = 0
    while True:
        print(chr(27) + "[2J")
        print(chr(27) + "[H")
        kifu.position_at(move).draw()
        key = input()
        if (key == 'q'):
            break
        move = move + 1


if (__name__ == "__main__"):
    print('test')
    if (len(sys.argv) != 2):
        usage()
    else:
        draw_match(sys.argv[1])
