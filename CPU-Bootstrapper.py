#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Written by Gregory Norton
# July 28 2018

import serial

from options import *

#port_name = '/dev/ttyACM0'  # Arduino Mega 2560
port_name = '/dev/ttyUSB0'  # Arduino Uno R3

def main(args):
    port = serial.Serial(port_name)

    while True:
        command = raw_input('? ').strip()
        print command
        if command[0] == 'exit' or command[0] == 'quit':
            break
        elif command[0] == 'help':
            print_help()
            
    return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
