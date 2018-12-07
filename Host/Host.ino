#include "Bus.h"

#define DIAGNOSTIC 8

#define BUS_AVAILABLE 22
#define BUS_STATUS 24
#define HALT 26
#define RESET 28
#define DMA_BREQ 30
#define RW 32

#define ADDRESS_BUS_0 23
#define DATA_BUS_0 38

Bus<uint16_t> *address_bus;
Bus<uint8_t> *data_bus;

void reset_cpu();
void acquire_bus();

void setup() {
    Serial.begin(115200);
    
    pinMode(DIAGNOSTIC, INPUT);
    
    pinMode(BUS_AVAILABLE, INPUT);
    pinMode(BUS_STATUS, INPUT);
    pinMode(HALT, OUTPUT);
    pinMode(RESET, OUTPUT);
    pinMode(DMA_BREQ, OUTPUT);
    pinMode(RW, INPUT_PULLUP);
    
    byte address_pins[sizeof(uint16_t) * 8] = { 0 };
    for (unsigned int i = 0; i < sizeof(uint16_t) * 8; i++) {
        address_pins[i] = ADDRESS_BUS_0 + 2 * i;
    }
    
    byte data_pins[sizeof(uint8_t) * 8] = { 0 };
    for (unsigned int i = 0; i < sizeof(uint8_t) * 8; i++) {
        data_pins[i] = DATA_BUS_0 + 2 * i;
    }
    
    digitalWrite(HALT, HIGH);
    digitalWrite(RESET, HIGH);
    digitalWrite(DMA_BREQ, HIGH);
    
    address_bus = new Bus<uint16_t>(address_pins);
    data_bus = new Bus<uint8_t>(data_pins);
    
    reset_cpu();
    acquire_bus();
    
    pinMode(RW, OUTPUT);
    digitalWrite(RW, LOW);
    //address_bus->set_mode(OUTPUT);
    address_bus->set(0x1234 | 0x8000);
    //address_bus->set(0x1234);
    data_bus->set(0xCD);
    digitalWrite(RW, HIGH);
    Serial.println(data_bus->get(), HEX);
}

void loop() {
    //Serial.println(digitalRead(DIAGNOSTIC));
}

void reset_cpu() {
    digitalWrite(RESET, LOW);
    delay(200);
    digitalWrite(RESET, HIGH);
}

void acquire_bus() {
    digitalWrite(HALT, LOW);
    digitalWrite(DMA_BREQ, LOW);
    while (!(digitalRead(BUS_STATUS) & digitalRead(BUS_AVAILABLE)));
    Serial.println("Acquired");
}
