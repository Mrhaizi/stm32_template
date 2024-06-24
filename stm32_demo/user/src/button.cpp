#include "button.h"

Button::Button(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) : GPIOx_(GPIOx), GPIO_Pin_(GPIO_Pin) {
    // 使能GPIO时钟
    if (GPIOx_ == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if (GPIOx_ == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } else if (GPIOx_ == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    } 

    // 配置GPIO引脚
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin_;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOx_, &GPIO_InitStruct);
}

bool Button::isPressed() {
    return HAL_GPIO_ReadPin(GPIOx_, GPIO_Pin_) == GPIO_PIN_RESET;
}
