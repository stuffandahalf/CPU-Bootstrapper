class Interface:
    def __init__(self, arduino, address_pins, io_pins):
        self.arduino = arduino
        self.address_pins = address_pins
        self.io_pins = io_pins

    def read(self, address):
        print hex(address)

    def set_address(self, address):
        for i in range(0, len(self.address_pins)):
            #self.arduino.digital[self.address_pins[i]].write(address >> i)
            #print self.address_pins[i]
            print (address >> i) & 1
