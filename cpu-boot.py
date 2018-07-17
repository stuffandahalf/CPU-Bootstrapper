#!/usr/bin/env python

#import gi
#gi.require_version('Gtk', '3.0')
#from gi.repository import Gtk

from pyfirmata import Arduino, util

board = Arduino('/dev/ttyUSB0')

addr_pins = [23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53]
io_pins = [22, 24, 26, 28, 30, 32, 34, 36]

def write(address):
    pass

def main(args):
    
    return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
