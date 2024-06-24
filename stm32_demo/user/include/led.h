#ifndef _LED_H
#define _LED_H

#include "stm32f1xx_hal.h"

class LED {
public:
    LED(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
    void on();
    void off();
    void toggle();

private:
    GPIO_TypeDef* GPIOx_;
    uint16_t GPIO_Pin_;
};

#endif // _LED_H
