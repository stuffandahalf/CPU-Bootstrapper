#ifndef MEMORY_H
#define MEMORY_H

#include <Arduino.h>
#include "Bus.h"

// Might make template for address and data type
class Memory {
private:
    Bus<uint16_t> *address_bus;
    Bus<uint8_t> *data_bus;
    byte rw_pin;
    bool alloced;
    
    memory_init(Bus<uint16_t> *address_bus, Bus<uint8_t> *data_bus, byte rw_pin, bool alloced);
    void high_impedence();
    
public:
    Memory(Bus<uint16_t> *address_bus, Bus<uint8_t> *data_bus, byte rw_pin);
    Memory(byte address_pins[sizeof(uint16_t) * 8], byte data_pins[sizeof(uint8_t) * 8], byte rw_pin);
    
    uint8_t read(uint16_t address);
    void read(uint16_t address, size_t byte_count, uint8_t *data_out);
    void write(uint16_t address, uint8_t data);
    void write(uint16_t address, size_t byte_count, uint8_t *data);
    
    ~Memory();
};

#endif
