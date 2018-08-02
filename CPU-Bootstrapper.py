#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Written by Gregory Norton
# July 28 2018

import argparse
import os
import serial
import sys

from options import process

if sys.version_info[0] >= 3:
    raw_input = input

port_name = '/dev/ttyACM0'  # Arduino Mega 2560 and leonardo
#port_name = '/dev/ttyUSB0'  # Arduino Uno R3

def main(args):
    parser = argparse.ArgumentParser(description='Load bytes into computer memory')
    parser.add_argument('script', nargs='?', help='The script file to execute')
    parser.add_argument('-port', '-p', nargs=1, default='/dev/ttyACM0', help='The serial port to send commands to')
    parser.print_help()
    
    args = parser.parse_args()
    fd = None
    if args.script != None and not os.path.isfile(args.script):
        print('Script does not exist')
        port.close()
        return 1
    
    #if args.port != None:
        #port_name = args.port
    
    port = serial.Serial(args.port)
    #port = None

    lineno = 0

    #port.write(232)
    #print(ord(port.read(size=1)))

    if args.script == None:
        while True:
            try:
                command = raw_input('? ').strip()
            except EOFError:
                break
            if process(command, port) == -1:
                break;
    else:
        with open(args.script) as f:
            for command in f:
                if process(command.strip(), port) == -1:
                    break;
    port.close()
    return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
