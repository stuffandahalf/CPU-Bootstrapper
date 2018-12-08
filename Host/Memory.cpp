#include "Memory.h"

Memory::memory_init(Bus<uint16_t> *address_bus, Bus<uint8_t> *data_bus, byte rw_pin, bool alloced) {
    this->address_bus = address_bus;
    this->data_bus = data_bus;
    this->rw_pin = rw_pin;
    this->alloced = alloced;
    
    this->high_impedence();
}

Memory::Memory(Bus<uint16_t> *address_bus, Bus<uint8_t> *data_bus, byte rw_pin) {
    this->memory_init(address_bus, data_bus, rw_pin, false);
}

Memory::Memory(byte address_pins[sizeof(uint16_t) * 8], byte data_pins[sizeof(uint8_t) * 8], byte rw_pin) {
    Bus<uint16_t> *address_bus = new Bus<uint16_t>(address_pins);
    Bus<uint8_t> *data_bus = new Bus<uint8_t>(data_pins);
    
    this->memory_init(address_bus, data_bus, rw_pin, true);
}

Memory::~Memory() {
    if (this->alloced) {
        delete this->address_bus;
        delete this->data_bus;
    }
}

uint8_t Memory::read(uint16_t address) {
    /*pinMode(this->rw_pin, OUTPUT);
    digitalWrite(this->rw_pin, HIGH);
    address_bus->set(address);
    uint8_t data = data_bus->get();
    
    this->high_impedence();
    return data;*/
    uint8_t data;
    this->read(address, 1, &data);
    return data;
}

void Memory::read(uint16_t address, size_t byte_count, uint8_t *data_out) {
    pinMode(this->rw_pin, OUTPUT);
    digitalWrite(this->rw_pin, HIGH);
    delay(10);
    for (size_t i = 0; i < byte_count; i++) {
        address_bus->set(address + i);
        delay(15);
        data_out[i] = data_bus->get();
        Serial.print(data_out[i], HEX);
        Serial.print(' ');
    }
    Serial.println();
    
    this->high_impedence();
}

void Memory::write(uint16_t address, uint8_t data) {
    this->write(address, 1, &data);
}

void Memory::write(uint16_t address, size_t byte_count, uint8_t *data) {
    pinMode(this->rw_pin, OUTPUT);
    digitalWrite(this->rw_pin, HIGH);
    //delay(10);
    for (size_t i = 0; i < byte_count; i++) {
        address_bus->set(address + i);
        digitalWrite(this->rw_pin, LOW);    // Set to read so i dont overwrite valid locations during address transition
        //delay(15);
        data_bus->set(data[i]);
        digitalWrite(this->rw_pin, HIGH);
        Serial.print(data[i], HEX);
        Serial.print(' ');
    }
    Serial.println();
    this->high_impedence();
}

void Memory::high_impedence() {
    pinMode(this->rw_pin, INPUT_PULLUP);
    this->address_bus->set_mode(INPUT_PULLUP);
    this->data_bus->set_mode(INPUT_PULLUP);
}
