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
peek_re = re_builder('(peek|p)', number_re)
poke_re = re_builder('(poke|w)', number_re, number_re)
load_re = re_builder('(load|l)', '.+')
comment_re = re_builder('#.*')
exit_re = re_builder('(exit|quit|q)')

def acquire(port):
    pass
    
def release(port):
    pass
    
def poke(port, address, byte):
    pass

def peek(port, address):
    pass

def print_help():
    print('Available Options:')
    print('  a  acquire                 Halts the cpu until release signal is sent.')
    print('  r  release                 Releases the bus.')
    print('  w  poke [ADDRESS] [BYTE]   Writes the given byte to the given address.')
    print('  p  peek [ADDRESS]          Prints the byte located at the given address.')
    print('  l  load [FNAME]            Loads a file into memory.')
    print('  h  help                    Prints this message.')
    print('  q  exit/quit               Exits the application.')
