#include "led.h"

LED::LED(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) : GPIOx_(GPIOx), GPIO_Pin_(GPIO_Pin) {
    if (GPIOx_ == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if (GPIOx_ == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } else if (GPIOx_ == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    } 
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin_;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOx_, &GPIO_InitStruct);
}

void LED::on() {
    HAL_GPIO_WritePin(GPIOx_, GPIO_Pin_, GPIO_PIN_SET);
}

void LED::off() {
    HAL_GPIO_WritePin(GPIOx_, GPIO_Pin_, GPIO_PIN_RESET);
}

void LED::toggle() {
    HAL_GPIO_TogglePin(GPIOx_, GPIO_Pin_);
}
