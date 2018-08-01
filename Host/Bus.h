#ifndef BUS_H
#define BUS_H

#include <Arduino.h>

template <typename T>
class Bus {
private:
    byte *pins;
    size_t pin_count;
public:
    Bus(byte *pins, size_t pin_count) {
        this->pins = pins;
        this->pin_count = pin_count;
    }
    void set_mode(byte mode);
    T read();
    void write(const T data);
};

#endif
