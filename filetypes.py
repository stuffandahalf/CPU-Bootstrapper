def get_extension(fname):
    return fname.split('.')[-1:]

def identify(fname):
    with open(fname, 'rb') as f:
        magic = f.read(4)
    if magic == chr(0x7F) + 'ELF':
        print('ELF File')
        return 'ELF'
    elif get_extension(fname) == 's19':
        print('S19 File')
        return 'S19'
    else:
        print('BIN File')
        return 'BIN'

def load_elf(fname):
    pass
    
def load_srec(fname):
    
    pass

def load_bin(srec):
    pass
