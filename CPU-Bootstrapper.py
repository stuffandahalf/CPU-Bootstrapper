#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Written by Gregory Norton
# July 28 2018

import sys
import serial

from options import *

if sys.version_info[0] >= 3:
    raw_input = input

def re_to_int(string):
    if string.startswith('0x'):
        return int(string, 16)
    elif string.startswith('$'):
        print int(string[1:], 16)
    else:
        return int(string)

#port_name = '/dev/ttyACM0'  # Arduino Mega 2560
port_name = '/dev/ttyUSB0'  # Arduino Uno R3

def main(args):
    port = serial.Serial(port_name)

    while True:
        try:
            command = raw_input('? ').strip()
        except EOFError:
            return 0
        
        #print command
        if acquire_re.match(command):
            print(command)
            acquire(port)
        elif release_re.match(command):
            print(command)
            release(port)
        elif peek_re.match(command):
            #print command.split()
            command = command.split()
            address = re_to_int(command[1]) & 0xFFFF
            peek(port, address)
            print(command)
        elif poke_re.match(command):
            print(command.split())
            command = command.split()
            address = re_to_int(command[1]) & 0xFFFF
            byte = re_to_int(command[2]) & 0xFF
            poke(port, address, byte)
        elif load_re.match(command):
            print(command.split())
        elif command == 'help':
            print_help()
        elif exit_re.match(command):
            break
        else:
            print('Invalid command')
            
    return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
