#include <HM62256.h>

#define ADDRESS_PIN_0 53
#define DATA_PIN_0 52

#define READ_PIN 24
#define WRITE_PIN 22

#define LED_PIN 13

#define BUSREQ_PIN 26
#define RESET_PIN 28

#define ACQUIRE 0
#define RELEASE 1
#define RESET 2
#define PEEK 3
#define POKE 4
#define INVALID 255

void blink();
hm62256_address_t get_address();
void acquire();
void release();
void reset();
hm62256_data_t peek(hm62256_address_t address);
bool poke(hm62256_address_t address, hm62256_data_t data);

Bus<hm62256_address_t> *address_bus;
Bus<hm62256_data_t> *data_bus;
HM62256 *mem;

void setup() {
    size_t i;

    byte address_bus_pins[sizeof(hm62256_address_t) * 8];
    for (i = 0; i < sizeof(hm62256_address_t) * 8; i++) {
        address_bus_pins[i] = ADDRESS_PIN_0 - 2 * i;
    }

    byte data_bus_pins[sizeof(hm62256_data_t) * 8];
    for (i = 0; i < sizeof(hm62256_data_t) * 8; i++) {
        data_bus_pins[i] = DATA_PIN_0 - 2 * i;
    }

    address_bus = new Bus<hm62256_address_t>(address_bus_pins);
    data_bus = new Bus<hm62256_data_t>(data_bus_pins);

    mem = new HM62256(address_bus, data_bus, READ_PIN, WRITE_PIN);

    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    uint8_t mode = Serial.read();

    hm62256_address_t address;
    hm62256_data_t data;

    switch (mode) {
    case 'a':
    case ACQUIRE:
        acquire();
        Serial.write(1);
        break;
    case 'r':
    case RELEASE:
        release();
        Serial.write(1);
        break;
    case PEEK:
        address = get_address();
        data = peek(address);
        Serial.write(data);
        break;
    case POKE:
        address = get_address();
        data = get_byte();
        Serial.write(poke(address, data));
        break;
    case 'q':
        data = peek(0xFFEF);
        if (data == 'a') blink();
        Serial.println(data);
        break;
    case 'w':
        Serial.println(poke(0xFFEF, 'a'));
        break;
    case INVALID:
        break;
    }
}

void blink() {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(500);
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

hm62256_data_t get_byte() {
    while (Serial.available() < 1);
    return Serial.read();
}

hm62256_address_t get_address() {
    uint8_t hbyte, lbyte;

    while (Serial.available() < 2);
    blink();
    hbyte = Serial.read();
    lbyte = Serial.read();

    return (hbyte << 8) + lbyte;
}

void reset() {
    digitalWrite(RESET_PIN, LOW);
    delay(1000);
    digitalWrite(RESET_PIN, HIGH);
}

void acquire() {
    digitalWrite(BUSREQ_PIN, LOW);
//    pinMode(RW_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
}

void release() {
    digitalWrite(BUSREQ_PIN, HIGH);
//    pinMode(RW_PIN, INPUT_PULLUP);
    digitalWrite(LED_PIN, LOW);
}

hm62256_data_t peek(hm62256_address_t address) {
    if (digitalRead(BUSREQ_PIN)) {
        return 0xFF;
    }
    else {
        return mem->read(address);
    }
}

bool poke(hm62256_address_t address, hm62256_data_t data) {
    if (!digitalRead(BUSREQ_PIN)) {
        mem->write(address, data);
        return data == mem->read(address);
    }
    return false;
}
