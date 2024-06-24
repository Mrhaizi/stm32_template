#ifndef _NUMBERLED_H
#define _NUMBERLED_H

#include "stm32f1xx_hal.h"

class NumberLed {
public:
    NumberLed(GPIO_TypeDef* GPIOx);
    void add();

    void down();

    void backZero();

    void displayDight();
private:
    int now_number_;
    GPIO_TypeDef* GPIOx_;
    const uint8_t segmentcodes_[10] = {
    0b0111111, // 0
    0b0000110, // 1
    0b1011011, // 2
    0b1001111, // 3
    0b1100110, // 4
    0b1101101, // 5
    0b1111101, // 6
    0b0000111, // 7
    0b1111111, // 8
    0b1101111  // 9
  };


};

#endif // _NUMBERLED_H