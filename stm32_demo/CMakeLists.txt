cmake_minimum_required(VERSION 3.13)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/gcc_arm_none_eabi.cmake)

# 项目信息
project(stm32_project C CXX ASM)
set(CMAKE_C_STANDARD 11)

# 设置处理器和编译器选项
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-m3 -mthumb -Wall -O2 -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcpu=cortex-m3 -mthumb -Wall -O2 -ffunction-sections -fdata-sections")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_SOURCE_DIR}/linker/STM32F103VBIx_FLASH.ld -Wl,--gc-sections")

# 包含头文件目录
include_directories(
    ${CMAKE_SOURCE_DIR}/user/include
    ${CMAKE_SOURCE_DIR}/driver/cmsis/include
    ${CMAKE_SOURCE_DIR}/driver/hal/include
)

# 源文件列表
set(DRIVER_SRC
    ${CMAKE_SOURCE_DIR}/driver/cmsis/src/system_stm32f1xx.c
    ${CMAKE_SOURCE_DIR}/driver/hal/src/stm32f1xx_hal.c
    ${CMAKE_SOURCE_DIR}/driver/hal/src/stm32f1xx_hal_rcc.c
    ${CMAKE_SOURCE_DIR}/driver/hal/src/stm32f1xx_hal_gpio.c
    ${CMAKE_SOURCE_DIR}/driver/hal/src/stm32f1xx_hal_tim.c
    ${CMAKE_SOURCE_DIR}/driver/hal/src/stm32f1xx_hal_cortex.c
    # 添加其他 HAL 源文件
)
file(GLOB USER_SRC user/src/*.cpp user/src/*.c)

set(SRC 
    ${DRIVER_SRC}
    ${USER_SRC})

# 添加汇编启动文件
set(STARTUP ${CMAKE_SOURCE_DIR}/startup/startup_stm32f103xb.s)

# 添加可执行目标
add_executable(${PROJECT_NAME}.elf ${SRC} ${STARTUP})

# 输出 HEX 和 BIN 文件
add_custom_target(${PROJECT_NAME}.hex ALL
    DEPENDS ${PROJECT_NAME}.elf
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
)

add_custom_target(${PROJECT_NAME}.bin ALL
    DEPENDS ${PROJECT_NAME}.elf
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
)

# 打印最终可执行文件的大小
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf
)
