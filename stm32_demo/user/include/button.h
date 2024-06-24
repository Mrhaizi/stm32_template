#ifndef _BUTTON_H
#define _BUTTON_H

#include "stm32f1xx_hal.h"


class Button {
public:
    Button(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

    bool isPressed();
private:
    GPIO_TypeDef* GPIOx_;
    uint16_t GPIO_Pin_;

};

#endif // _BUTTON_H