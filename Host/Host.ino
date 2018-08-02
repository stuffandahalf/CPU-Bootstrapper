#include "Bus.h"

#define LED_PIN 13
#define BUSREQ_PIN 22
#define RESET_PIN 24

#define ACQUIRE 0
#define RELEASE 1
#define RESET 2
#define PEEK 3
#define POKE 4
#define INVALID 255

uint16_t get_address();
void acquire();
void release();
void reset();
uint8_t peek(uint16_t address);
void poke(uint16_t address, uint8_t data);

Bus<uint16_t> *address_bus;
Bus<uint8_t> *data_bus;

void setup() {
    uint8_t address_pins[16];
    uint8_t data_pins[8];
    
    for (uint8_t i = 0; i < 16; i++) {
        address_pins[i] = 22 + (i * 2);
    }
    for (uint8_t i = 0; i < 8; i++) {
        data_pins[i] = 23 + (i * 2);
    }
    
    address_bus = new Bus<uint16_t>(address_pins);
    data_bus = new Bus<uint8_t>(data_pins);
    
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUSREQ_PIN, OUTPUT);
    pinMode(RESET_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    Serial.begin(9600);
}

void loop() {
    byte mode = Serial.read();
    /*if (mode != 255)
        Serial.print(mode);*/
    uint16_t address;
    switch (mode) {
    case ACQUIRE:
        break;
    case RELEASE:
        break;
    case '3':
        Serial.write(4);
        break;
    case PEEK:
        address = get_address();
        peek(address);
        break;
    case POKE:
        break;
    case INVALID:
        break;
    }
}

uint16_t get_address() {
    uint8_t hbyte, lbyte;
    do {
        hbyte = Serial.read();
    } while (hbyte == 255);
    
    do {
        lbyte = Serial.read();
    } while (lbyte == 255);
    
    return (hbyte << 8) + lbyte;
}

void acquire() {
    digitalWrite(BUSREQ_PIN, LOW);
}

void release() {
    digitalWrite(BUSREQ_PIN, HIGH);
}

uint8_t peek(uint16_t address) {
    //Serial.write(digitalRead(LED_PIN));
    //Serial.write(5);
    //Serial.write("address\n");
    //Serial.write(address);
    if (digitalRead(BUSREQ_PIN)) {
        return 0xFF;
    }
    else {
        address_bus->write(address);
        return data_bus->read();
    }
}
