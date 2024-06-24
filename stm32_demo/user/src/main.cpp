#include "main.h"

int main(void)
{
    // 初始化HAL库
    HAL_Init();

    // 配置系统时钟
    SystemClock_Config();
    
    LED green_led(GPIOA, GPIO_PIN_0); // green LED
    LED red_led(GPIOB, GPIO_PIN_10); // red LED
    Button green_button(GPIOA, GPIO_PIN_1); // green button
    Button red_button(GPIOB, GPIO_PIN_11); // red button
    LED own_led(GPIOC, GPIO_PIN_13); // ownz
    NumberLed led_number(GPIOB);
    while (1)
    {   
        led_number.displayDight();    
        if (green_button.isPressed()) {
            if (red_button.isPressed()) {
                led_number.add();                
            }
            led_number.add();
            green_led.on();
        } else {
            green_led.off();
        }
        if (red_button.isPressed()) {
            if (green_button.isPressed()) {
                led_number.backZero();
            }
            red_led.on();
            led_number.down();
        } else {
            red_led.off();
        }
        HAL_Delay(200);
    }
}
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // 1. 配置HSE振荡器作为PLL的时钟源
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9; // 8 MHz * 9 = 72 MHz

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        // 初始化错误处理
        Error_Handler();
    }

    // 2. 初始化RCC时钟配置
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; // AHB时钟不分频
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  // APB1时钟2分频
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  // APB2时钟不分频

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        // 初始化错误处理
        Error_Handler();
    }

    // 3. 配置SysTick定时器中断
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    // 配置SysTick中断优先级
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void Error_Handler(void) {
    while (1)
    {
        // 死循环
    }
}


    
