#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Written by Gregory Norton
# July 28 2018

import serial
import re

from options import *

#port_name = '/dev/ttyACM0'  # Arduino Mega 2560
port_name = '/dev/ttyUSB0'  # Arduino Uno R3

number_re = r'((0x|$)[0-9a-f]+|[0-9]+)'
whitespace_re = r'[ \t]+'

peek_re = re.compile('^peek' + whitespace_re + number_re + '$', re.IGNORECASE)
poke_re = re.compile('^poke' + whitespace_re + number_re + whitespace_re + number + '$')
load_re = re.compile('^load' + whitespace_re + '.+$', re.IGNORECASE)
exit_re = re.compile('^(exit|quit|q)$', re.IGNORECASE)

def main(args):
    port = serial.Serial(port_name)

    while True:
        try:
            command = raw_input('? ').strip()
        except EOFError:
            return 0
            
        address = 0
        data = 0    
        
        #print command
        if peek_re.match(command):
            #print command.split()
            command = command.split()
            address = int(peek[1])
            peek(port, address)
        elif poke_re.match(command):
            print command.split()
        elif load_re.match(command):
            print command.split()
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
