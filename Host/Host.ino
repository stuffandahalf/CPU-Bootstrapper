#include "Bus.h"

#define LED_PIN 13
#define BUSREQ_PIN 22
#define RW_PIN 10
#define RESET_PIN 7

#define ACQUIRE 0
#define RELEASE 1
#define RESET 2
#define PEEK 3
#define POKE 4
#define INVALID 255

#define READ HIGH
#define WRITE LOW

uint16_t get_address();
void acquire();
void release();
void reset();
uint8_t peek(uint16_t address);
bool poke(uint16_t address, uint8_t data);

Bus<uint16_t> *address_bus;
Bus<uint8_t> *data_bus;

void setup() {
    uint8_t address_pins[16];
    uint8_t data_pins[8];
    
    for (uint8_t i = 0; i < 16; i++) {
        address_pins[i] = 23 + (i * 2);
    }
    for (uint8_t i = 0; i < 8; i++) {
        data_pins[i] = 38 + (i * 2);
    }
    
    address_bus = new Bus<uint16_t>(address_pins);
    data_bus = new Bus<uint8_t>(data_pins);
    
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUSREQ_PIN, OUTPUT);
    pinMode(RW_PIN, INPUT_PULLUP);
    pinMode(RESET_PIN, OUTPUT);
    
    //digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUSREQ_PIN, HIGH);
    digitalWrite(RESET_PIN, HIGH);
    
    reset();
    
    /*acquire();
    address_bus->write(0);
    uint8_t data = data_bus->read();
    Serial.write(data);
    */
    Serial.begin(9600);
    Serial.write(1);
}

void loop() {
    uint8_t mode = Serial.read();
    
    uint16_t address;
    uint8_t data;
    
    switch (mode) {
    case ACQUIRE:
        acquire();
        Serial.write(1);
        break;
    case RELEASE:
        release();
        Serial.write(1);
        break;
    case PEEK:
        address = get_address();
        Serial.write(peek(address));
        break;
    case POKE:
        address = get_address();
        data = get_byte();
        Serial.write(poke(address, data));
        break;
    case INVALID:
        break;
    }
}

uint8_t get_byte() {
    while (!Serial.available());
    return Serial.read();
}

uint16_t get_address() {
    uint8_t hbyte, lbyte;
    
    hbyte = get_byte();
    lbyte = get_byte();
    
    return (hbyte << 8) + lbyte;
}

void reset() {
    digitalWrite(RESET_PIN, LOW);
    delay(1000);
    digitalWrite(RESET_PIN, HIGH);
}

void acquire() {
    digitalWrite(BUSREQ_PIN, LOW);
    pinMode(RW_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
}

void release() {
    digitalWrite(BUSREQ_PIN, HIGH);
    pinMode(RW_PIN, INPUT_PULLUP);
    digitalWrite(LED_PIN, LOW);
}

uint8_t peek(uint16_t address) {
    //Serial.write(digitalRead(BUSREQ_PIN));
    if (digitalRead(BUSREQ_PIN)) {
        return 0xFF;
    }
    else {
        digitalWrite(RW_PIN, READ);
        address_bus->write(address);
        //return 5;
        return data_bus->read();
    }
}

bool poke(uint16_t address, uint8_t data) {
    if (!digitalRead(BUSREQ_PIN)) {
        digitalWrite(RW_PIN, WRITE);
        address_bus->write(address);
        data_bus->write(data);
        return data == data_bus->read();
    }
    return false;
}
