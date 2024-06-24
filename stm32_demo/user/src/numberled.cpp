#include "numberled.h"

NumberLed::NumberLed(GPIO_TypeDef* GPIOx) : GPIOx_(GPIOx) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    now_number_ = 0;
    /* GPIO Ports Clock Enable */
    
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // HAL_GPIO_WritePin(GPIOx_, GPIO_PIN_7, GPIO_PIN_SET);
    // HAL_GPIO_WritePin(GPIOx_, GPIO_PIN_8, GPIO_PIN_SET);
    // HAL_GPIO_WritePin(GPIOx_, GPIO_PIN_9, GPIO_PIN_SET);
    // HAL_GPIO_WritePin(GPIOx_, GPIO_PIN_13, GPIO_PIN_SET);
    // HAL_GPIO_WritePin(GPIOx_, GPIO_PIN_14, GPIO_PIN_SET);
    // HAL_GPIO_WritePin(GPIOx_, GPIO_PIN_15, GPIO_PIN_SET);
    // HAL_GPIO_WritePin(GPIOx_, GPIO_PIN_6, GPIO_PIN_SET);

    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_13
                            |GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOx_, &GPIO_InitStruct);
}

void NumberLed::add() {
    if (!(0 <= now_number_  && now_number_ < 9)) return;
    now_number_++;

}

void NumberLed::down() {
    if (!(0 < now_number_  && now_number_ < 10)) return;
    now_number_--;
}

void NumberLed::backZero() {
    now_number_ = 0;
}

void NumberLed::displayDight() {
    if (!(0 <= now_number_  && now_number_ < 10)) return;
    uint8_t code = segmentcodes_[now_number_];
    // HAL_GPIO_WritePin(GPIOx_, GPIO_PIN_6, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOx_, GPIO_PIN_7, (code & 0b0000001) ? GPIO_PIN_RESET : GPIO_PIN_SET); // a
    HAL_GPIO_WritePin(GPIOx_, GPIO_PIN_6, (code & 0b0000010) ? GPIO_PIN_RESET : GPIO_PIN_SET); // b
    HAL_GPIO_WritePin(GPIOx_, GPIO_PIN_13, (code & 0b0000100) ? GPIO_PIN_RESET : GPIO_PIN_SET); // c
    HAL_GPIO_WritePin(GPIOx_, GPIO_PIN_14, (code & 0b0001000) ? GPIO_PIN_RESET : GPIO_PIN_SET); // d
    HAL_GPIO_WritePin(GPIOx_, GPIO_PIN_15, (code & 0b0010000) ? GPIO_PIN_RESET : GPIO_PIN_SET); // e
    HAL_GPIO_WritePin(GPIOx_, GPIO_PIN_8, (code & 0b0100000) ? GPIO_PIN_RESET : GPIO_PIN_SET); // f
    HAL_GPIO_WritePin(GPIOx_, GPIO_PIN_9, (code & 0b1000000) ? GPIO_PIN_RESET : GPIO_PIN_SET); // g
    
}