//#include "Bus.h"
#include "Memory.h"

#define DIAGNOSTIC 8

#define BUS_AVAILABLE 22
#define BUS_STATUS 24
#define HALT 26
#define RESET 28
#define DMA_BREQ 30
#define RW 32

#define ADDRESS_BUS_0 23
#define DATA_BUS_0 38

void blink() {
    digitalWrite(LED_PIN, LOW);
    delay(500);
    digitalWrite(LED_PIN, HIGH);
}

/*Bus<uint16_t> *address_bus;
Bus<uint8_t> *data_bus;*/
Memory *memory;

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

    /*address_bus = new Bus<uint16_t>(address_pins);
    data_bus = new Bus<uint8_t>(data_pins);*/
    memory = new Memory(address_pins, data_pins, RW);

    reset_cpu();
    halt_and_acquire_bus();

    /*pinMode(RW, OUTPUT);
    digitalWrite(RW, LOW);
    //address_bus->set_mode(OUTPUT);
    address_bus->set(0x1234 | 0x8000);
    //address_bus->set(0x1234);
    data_bus->set(0xCD);
    digitalWrite(RW, HIGH);
    Serial.println(data_bus->get(), HEX);*/
    
    
    /*#define TEST_ADDRESS 0xFFEE
    #define TEST_DATA 0xCD
    memory->write(TEST_ADDRESS, TEST_DATA);
    uint8_t data = memory->read(TEST_ADDRESS);
    Serial.println(data, HEX);*/
    
    int8_t data[] = {
        0x86, 5,            // LDA #$5
        0x8B, 5,            // ADDA #$5
        0xB7, 0x80, 0x0A,   // STA result (0x800A)
        0x7E, 0x80, 0x07,   // jmp rpt (0x8007)
        0x00                // result
    };
    
    uint8_t reset_vector[] = { 0x80, 0x00 };
    
    memory->write(0x8000, sizeof(data), data);
    memory->read(0x8000, sizeof(data), data);
    memory->write(0xFFFE, sizeof(reset_vector), reset_vector);
    memory->read(0xFFFE, sizeof(reset_vector), reset_vector);
    
    //uint8_t test[11];
    
    /*for (int i = 0; i < 11; i++) {
        test[i] = i;
        memory->write(0x8000 + i, test[i]);
        delay(1000);
        memory->read(0x8000 + i);
        delay(1000);
    }*/
    
    
    //memory->write(0x8000, sizeof(test), test);
    //memory->read(0x8000, sizeof(test), test);
    /*for (int i = 0; i < 11; i++) {
        memory->read(0x8000 + i);
    }*/
    
    /*uint8_t data = 0x10101010;
    memory->write(0x8001, data);
    Serial.println(memory->read(0x8001), BIN);
    memory->write(0x8001, ~data);
    Serial.println(memory->read(0x8001), BIN);*/
    
    /*for (size_t i = 0; i < 256; i++) {
        memory->write(0x8000, i);
        uint8_t test = memory->read(0x8000);
        if (test != i) {
            Serial.print(i);
            Serial.print(" != ");
            Serial.println(test);
        }
    }
    Serial.println("Complete");*/
    
    
    release_bus_reset();
    delay(500);
    halt_and_acquire_bus();
    
    Serial.println(memory->read(0x800A));
}

void loop() {
    //Serial.println(digitalRead(DIAGNOSTIC));
}

void reset_cpu() {
    digitalWrite(RESET, LOW);
    delay(200);
    digitalWrite(RESET, HIGH);
}

void halt_and_acquire_bus() {
    digitalWrite(HALT, LOW);
    digitalWrite(DMA_BREQ, LOW);
    while (!(digitalRead(BUS_STATUS) & digitalRead(BUS_AVAILABLE)));
    Serial.println("Acquired");
}


void release_bus_reset() {
    //memory->high_impedence();
    digitalWrite(DMA_BREQ, HIGH);
    reset_cpu();
    digitalWrite(HALT, HIGH);
}
