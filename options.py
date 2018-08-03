import re

start_re = r'^[ \t]*'
number_re = r'((0x|$)[0-9a-f]+|[0-9]+)'
whitespace_re = r'[ \t]+'
end_re = r'[ \t]*$'

def re_builder(*args):
    re_str = start_re + whitespace_re.join(args) + end_re
    #print re_str
    return re.compile(re_str, re.IGNORECASE)

acquire_re = re_builder('(acquire|a)')
release_re = re_builder('(release|r)')
reset_re = re_builder('reset')
peek_re = re_builder('(peek|p)', number_re)
poke_re = re_builder('(poke|w)', number_re, number_re)
load_re = re_builder('(load|l)', '.+')
comment_re = re_builder('#.*')
exit_re = re_builder('(exit|quit|q)')

def re_to_int(string):
    if string.startswith('0x'): return int(string, 16)
    elif string.startswith('$'): return int(string[1:], 16)
    else: return int(string)

def ACQUIRE(): return chr(0)
def RELEASE(): return char(1)
def RESET(): return chr(2)
def PEEK(): return chr(3)
def POKE(): return chr(4)
def INVALID(): return chr(5)

def process(command, port):
    if acquire_re.match(command):
        print('acquire')
        acquire(port)
    elif release_re.match(command):
        print('release')
        release(port)
    elif reset_re.match(command):
        print('reset')
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
        return -1
    elif comment_re.match(command) or command == '':
        print('ignore')
        #continue
    else:
        print('Invalid command')

def acquire(port):
    #port.
    pass
    
def release(port):
    pass
    
def reset(port):
    pass
    
def load(port, fd):
    pass
    
def poke(port, address, byte):
    pass

def peek(port, address):
    print(address)
    port.write(PEEK())
    port.write(chr((address >> 8) & 0xFF))
    port.write(chr(address & 0xFF))
    #naddress = ord(port.read(size=1)) << 8
    #naddress += ord(port.read(size=1))
    print(ord(port.read(size=1)))

def print_help():
    print('Available Options:')
    print('  a  acquire                 Halts the cpu until release signal is sent.')
    print('  r  release                 Releases the bus.')
    print('     reset                   Resets the CPU on release')
    print('  w  poke [ADDRESS] [BYTE]   Writes the given byte to the given address.')
    print('  p  peek [ADDRESS]          Prints the byte located at the given address.')
    print('  l  load [FNAME]            Loads a file into memory.')
    print('  h  help                    Prints this message.')
    print('  q  exit/quit               Exits the application.')
