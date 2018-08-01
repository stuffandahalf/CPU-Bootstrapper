#include "Bus.h"

template <typename T>
void Bus<T>::set_mode(byte mode) {
    for (size_t i = 0; i < this->pin_count; i++) {
        pinMode(this->pins[i], mode);
    }
}
