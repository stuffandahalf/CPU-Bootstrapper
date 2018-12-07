/*#include "Bus.h"

template <typename T>
void Bus<T>::set_mode(byte mode) {
    for (size_t i = 0; i < (sizeof(T) * 8); i++) {
        pinMode(this->pins[i], mode);
    }
}

template <typename T>
void Bus<T>::write(const T data) {
    for (size_t i = 0; i < (sizeof(T) * 8); i++) {
        digitalWrite(this->pins[i], (data >> i) & 1);
    }
}

template <typename T>
T Bus<T>::read() {
    T value = 0;
    for (size_t i = (sizeof(T) * 8) - 1; i >= 0; i--) {
        value += digitalRead(this->pins[i]) << i;
    }
    return value;
}
*/
