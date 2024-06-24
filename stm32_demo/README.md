# 此项目为在linux系统下基于vscode+cmake用hal库开发stm32的模版框架.

## 目录架构

stm32_demo/
├── CMakeLists.txt        # 项目的CMake配置文件
├── build/                # 编译生成的文件目录
├── cmake/                # CMake模块和脚本
├── driver/               # 驱动程序文件
├── linker/               # 链接脚本
├── startup/              # 启动代码
└── user/                 # 用户代码

## 目录说明

CMakeLists.txt
项目的主要CMake配置文件，定义了项目的构建过程和依赖关系。

build/
编译生成的文件目录，通常包含生成的二进制文件和中间文件。

cmake/
包含CMake模块和脚本，用于支持项目的构建配置。

driver/
驱动程序文件，包含与硬件外设相关的代码。

linker/
链接脚本，定义了固件在STM32微控制器内存中的布局。

startup/
启动代码，通常包含复位向量表和初始化代码。

user/
用户代码目录，建议在此目录中添加应用程序逻辑和自定义代码。

## 使用前提

CMake
ARM GCC 编译器
STM32 开发工具链 (如 STM32CubeMX)

## 使用方法

在vscode下直接使用cmake进行编译，编译成功后会在build目录下生成.bin和.elf文件

确保安装好openocd后执行下面的命令

先打开第一个终端(根据自己的板子自己修改此命令的参数)

```shell
sudo openocd -f interface/stlink.cfg -f target/stm32f1x.cfg
```

打开第二个终端

```shell
sudo telnet localhost 4444

rest halt
#.elf文件
flash write_image erase /file/path/.elf
#.bin文件
flash write_image erase /file/path/.bin 0x08000000

reset run 

```

