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

void acquire();
void release();
void reset();
uint8_t peek(uint16_t address);
void poke(uint16_t address, uint8_t data);

Bus<uint16_t> *address_bus;
Bus<uint8_t> *data_bus;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUSREQ_PIN, OUTPUT);
    pinMode(RESET_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    Serial.begin(9600);
}

void loop() {
    byte mode = Serial.read();
    uint16_t address;
    switch (mode) {
    case ACQUIRE:
        break;
    case RELEASE:
        break;
    case '3':
    case PEEK:
        address = 0;
        //address += Serial.read() << 8 + Serial.read();
        //Serial.write(peek(address));
        /*if (address == (('3' << 8) + '3')) {
            digitalWrite(LED_PIN, HIGH);
        }
        Serial.write(address);*/
        peek(address);
        break;
    case POKE:
        break;
    case INVALID:
        break;
    }
}

void acquire() {
    digitalWrite(BUSREQ_PIN, LOW);
}

void release() {
    digitalWrite(BUSREQ_PIN, HIGH);
}

uint8_t peek(uint16_t address) {
    Serial.write("3\n");
}
