//
// Created by Kaden Cassidy on 6/20/24.
//

#ifndef ARDUINOBATTLEBOTCODE_RINGBUFFER_H
#define ARDUINOBATTLEBOTCODE_RINGBUFFER_H

#include "Arduino.h"
#include <cstddef>

template <typename T, int L>
class ringBuffer {
public:
    ringBuffer(T initialValue) {
        for (int i = 0; i < L; ++i) {
            array[i] = initialValue;
        }
    }

    // Method to add an element to the buffer
    T getValue(T value) {
        T currentValue = array[head];
        array[head] = value;
        head = (head + 1) % L;
        return currentValue;
    }

    void fill(T value){
        for (int i = 0; i < L; ++i) {
            array[i] = value;
        }
    }

private:
    T array[L];
    size_t head = 0;
    size_t size = 0;
};

#endif //ARDUINOBATTLEBOTCODE_RINGBUFFER_H
