#!/usr/bin/env python

#import gi
#gi.require_version('Gtk', '3.0')
#from gi.repository import Gtk

from pyfirmata import ArduinoMega, util
from interface import Interface

board = ArduinoMega('/dev/ttyACM0')
addr_pins = [23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53]
io_pins = [22, 24, 26, 28, 30, 32, 34, 36]

def main(args):
    inter = Interface(board, addr_pins, io_pins)
    inter.set_address(0xCF00)
    #inter.read(0xFFFF)
    return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
