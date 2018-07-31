#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Written by Gregory Norton
# July 28 2018

import argparse
import serial
import sys

from options import *

if sys.version_info[0] >= 3:
    raw_input = input

def re_to_int(string):
    if string.startswith('0x'): return int(string, 16)
    elif string.startswith('$'): return int(string[1:], 16)
    else: return int(string)

#port_name = '/dev/ttyACM0'  # Arduino Mega 2560
port_name = '/dev/ttyUSB0'  # Arduino Uno R3

def main(args):
    parser = argparse.ArgumentParser(description='Load bytes into computer memory')
    parser.add_argument('script', nargs='?', help='script FILE')
    parser.print_help()
    
    print args
    
    #port = serial.Serial(port_name)
    port = None

    while True:
        try:
            command = raw_input('? ').strip()
        except EOFError:
            return 0
        
        #print command
        if acquire_re.match(command):
            print('acquire')
            acquire(port)
        elif release_re.match(command):
            print('release')
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
        elif comment_re.match(command):
            print('Comment')
            continue
        elif command == '':
            print('blank')
            continue
        else:
            print('Invalid command')
            
    return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
