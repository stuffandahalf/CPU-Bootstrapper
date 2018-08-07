#ifndef BUS_H
#define BUS_H

#include <Arduino.h>

#define LED_PIN 13

template <typename T>
class Bus {
private:
    byte *pins;
public:
    Bus(byte pins[sizeof(T) * 8]) {
        this->pins = pins;
    }
    
    void set_mode(byte mode) {
        for (size_t i = 0; i < (sizeof(T) * 8); i++) {
            pinMode(this->pins[i], mode);
        }
    }
    
    void write(const T data) {
        for (size_t i = 0; i < (sizeof(T) * 8); i++) {
            pinMode(this->pins[i], OUTPUT);
            digitalWrite(this->pins[i], (data >> i) & 1);
        }
    }
    
    T read() {
        T data = 0;
        
        for (size_t i = 0; i < (sizeof(T) * 8); i++) {
        //for (size_t i = (sizeof(T) * 8) - 1; i >= 0; i--) {
        //for (int i = (sizeof(T) * 8) - 1; i >= 0; i--) {
            pinMode(this->pins[i], INPUT);
            data += digitalRead(this->pins[i]) << i;
        }
        return data;
    }
};

#endif
