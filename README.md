# STM32 + ESP8266 物联网远程监控系统

> 一个面向农业大棚场景的嵌入式物联网远程监控项目，基于 STM32F103 实现环境数据采集、OLED 本地显示、执行器控制，并通过 ESP8266 接入机智云 APP 进行远程监测与控制。

本项目原型为农业大棚环境监测系统，适合作为嵌入式开发、物联网开发、单片机软硬件联调方向的求职展示项目。项目包含 STM32 固件源码、Keil 工程、传感器与执行器驱动、机智云通信协议、PCB/原理图、BOM、Proteus 仿真和项目文档资料。

建议 GitHub 仓库名：

```text
stm32-esp8266-iot-greenhouse-monitor
```

## 项目功能

- 环境数据采集：温湿度、CO2 浓度、土壤湿度、光照强度。
- 本地数据显示：通过 OLED 显示系统首页、环境数据、设备状态和功能菜单。
- 自动/手动控制：支持风扇、水泵、加热器、补光 LED、蜂鸣器等执行器控制。
- 远程监测控制：通过 ESP8266 接入机智云，实现 APP 端数据查看和设备控制。
- 阈值判断与状态提示：根据环境数据判断干旱、光照不足、CO2 状态等，并进行页面提示。
- 硬件资料配套：包含原理图、PCB、BOM、硬件接口说明和仿真工程。

## 技术栈

- 主控芯片：STM32F103
- 开发语言：C
- 开发环境：Keil uVision
- 通信模块：ESP8266
- 物联网平台：机智云 Gizwits
- 显示模块：OLED
- 传感器：DHT11、CO2 传感器、土壤湿度传感器、光敏电阻
- 执行器：风扇、水泵、加热器、补光 LED、蜂鸣器
- 仿真工具：Proteus
- 硬件设计：原理图、PCB、BOM

## 系统架构

```text
传感器层
  DHT11 / CO2 / 土壤湿度 / 光照强度
        |
        v
主控层
  STM32F103
  - ADC 采集
  - 串口通信
  - OLED 显示
  - 按键交互
  - 阈值判断
        |
        +--------------------+
        |                    |
        v                    v
执行器层                 云端/APP 层
风扇 / 水泵 / 加热器      ESP8266 + 机智云
补光 LED / 蜂鸣器         远程查看与控制
```

## 核心模块说明

| 模块 | 文件 | 说明 |
| --- | --- | --- |
| 主程序 | `代码/user/src/main.c` | 初始化外设并循环执行大棚监测主逻辑 |
| 页面显示 | `代码/user/src/show.c` | OLED 菜单、图标、环境数据和设备状态显示 |
| 温湿度采集 | `代码/user/src/dht11.c` | DHT11 温湿度数据读取 |
| CO2 采集 | `代码/user/src/co2.c` | CO2 浓度数据处理 |
| ADC 采集 | `代码/user/src/adc.c` | 土壤湿度、光照强度等模拟量采集 |
| 风扇控制 | `代码/user/src/fan.c` | 风扇开关控制 |
| 水泵控制 | `代码/user/src/water.c` | 灌溉水泵控制 |
| 加热控制 | `代码/user/src/hot.c` | 加热器控制 |
| 蜂鸣器 | `代码/user/src/buzzer.c` | 报警提示控制 |
| OLED 驱动 | `代码/user/src/oled.c` | OLED 底层显示驱动 |
| 按键输入 | `代码/user/src/key.c` | 本地按键扫描 |
| 机智云通信 | `代码/Gizwits/` | 数据点上报、APP 控制事件处理 |
| 工具模块 | `代码/Utils/` | 环形缓冲区、数据点处理等工具代码 |

## 硬件接口

| 外设 | 接口 |
| --- | --- |
| ESP8266 WiFi | PB11-RX，PB10-TX |
| OLED | PB12-SCK，PB13-SDA |
| DHT11 | PB14-DATA |
| CO2 传感器 | PA3 |
| 风扇 | PB15 |
| 光敏电阻 | PA5 |
| 补光 LED | PB0 |
| 水泵 | PA11 |
| 土壤湿度传感器 | PA4 |
| 蜂鸣器 | PB1 |
| 加热器 | PA7 |
| AT24C04 存储器 | PB7-SDA，PB6-SCL |
| 按键 | KEY1-PA0，KEY2-PB5，KEY3-PB8，KEY4-PB9 |

## 代码运行逻辑

系统上电后，`main.c` 依次初始化中断优先级、串口、LED、按键、OLED、DHT11、ADC、蜂鸣器、水泵、风扇、加热器、AT24C04、ESP8266 和机智云协议栈。

主循环中调用 `Smart_Greenhouse()` 执行大棚监测逻辑，并在功能页面中通过 `Wifi_date()` 调用机智云协议处理函数，实现数据上报与 APP 控制指令接收。

机智云数据点主要包括：

- `Temp`：温度
- `Humi`：湿度
- `CO2`：二氧化碳浓度
- `Light`：光照强度
- `Soil`：土壤湿度
- `Water`：水泵开关
- `Fan`：风扇开关
- `LED`：补光 LED 档位
- `Voice`：蜂鸣器开关
- `All`：一键控制

## 编译与烧录

1. 使用 Keil uVision 打开工程文件：

   ```text
   代码/project/smart-greenhouse.uvprojx
   ```

2. 在 `代码/Gizwits/gizwits_protocol.h` 中填入自己的机智云产品参数：

   ```c
   #define PRODUCT_KEY "YOUR_GIZWITS_PRODUCT_KEY"
   #define PRODUCT_SECRET "YOUR_GIZWITS_PRODUCT_SECRET"
   ```

   公开仓库中不包含真实 Product Key 和 Product Secret。

3. 确认目标芯片为 STM32F103 系列。

4. 编译工程，生成固件。

5. 通过 ST-Link 或其他下载器将程序烧录到 STM32 开发板。

6. ESP8266 固件可参考目录：

   ```text
   ESP8266固件烧录/
   ```

7. APP 安装包和说明位于：

   ```text
   机智云APP/
   ```

## 仿真与硬件资料

| 类型 | 路径 |
| --- | --- |
| Proteus 仿真工程 | `仿真/stm32f103.pdsprj` |
| 仿真/烧录 hex | `仿真/smart-greenhouse.hex` |
| 原理图 PDF | `PCB/原理图.pdf` |
| 核心电路板 PDF | `PCB/核心电路板.pdf` |
| PCB 文件 | `PCB/PCB(改版20231122）.PcbDoc` |
| BOM | `bom.xlsx` |
| 硬件接口说明 | `毕设硬件对接口.txt` |

## 项目目录

当前资料包目录如下：

```text
农业大棚环境监测系统全资料/
├─ 代码/                 STM32 固件源码、Keil 工程、CMSIS、外设库
├─ PCB/                  原理图、PCB、BOM 导出文件、历史版本
├─ 仿真/                 Proteus 仿真工程和 hex 文件
├─ ESP8266固件烧录/       ESP8266 固件和烧录工具
├─ 机智云APP/             Android/iOS APP 安装包和说明
├─ 文档图片/              项目图片、页面图、硬件图等
├─ 讲解视频/              项目讲解视频
├─ bom.xlsx              元件清单
└─ 相关论文/PPT/文档       毕设论文、答辩 PPT、参考资料
```

如果用于 GitHub 求职展示，建议整理为：

```text
smart-greenhouse-monitor/
├─ README.md
├─ LICENSE
├─ .gitignore
├─ firmware/             STM32 固件源码和 Keil 工程
├─ hardware/             原理图、PCB、BOM、接口说明
├─ simulation/           Proteus 仿真工程
├─ docs/                 项目说明、架构图、运行截图
└─ app/                  机智云 APP 使用说明
```

## GitHub 上传建议

建议上传：

- `代码/user/`
- `代码/Gizwits/`
- `代码/Utils/`
- `代码/CMSIS/`
- `代码/lib/`
- `代码/project/smart-greenhouse.uvprojx`
- `PCB/原理图.pdf`
- `PCB/核心电路板.pdf`
- `PCB/PCB(改版20231122）.PcbDoc`
- `仿真/stm32f103.pdsprj`
- `仿真/smart-greenhouse.hex`
- `bom.xlsx`
- `毕设硬件对接口.txt`
- 精选后的 `文档图片/`

不建议上传：

- `代码/project/Objects/`
- `代码/project/Listings/`
- `*.o`、`*.d`、`*.crf`、`*.axf`、`*.map`、`*.lst`
- `*.uvguix.*`
- `讲解视频/` 中的大视频文件
- `答辩PPT.pptx` 等大体积答辩文件
- 参考论文、论文格式模板、无关项目 PPT
- 第三方烧录工具 exe
- APP 安装包 `*.apk`、`*.ipa`

## 个人贡献

- 完成 STM32 主控程序设计与外设初始化。
- 编写温湿度、CO2、土壤湿度、光照强度等数据采集模块。
- 实现 OLED 菜单页面、图标显示和状态展示。
- 实现风扇、水泵、加热器、补光 LED、蜂鸣器等执行器控制。
- 对接 ESP8266 与机智云平台，实现数据点上报和 APP 远程控制。
- 整理硬件接口、原理图、PCB、BOM 和仿真资料，完成软硬件联调。

## 项目亮点

- 软硬件资料完整：源码、工程、仿真、原理图、PCB、BOM 均有配套。
- 模块化代码结构：传感器、显示、通信、执行器控制分模块实现，便于维护和扩展。
- 具备物联网闭环：本地采集、本地显示、本地控制、云端上报、APP 控制流程完整。
- 贴近真实农业场景：围绕温湿度、土壤湿度、光照和 CO2 等关键环境参数进行监测与控制。

## 后续优化方向

- 增加更多传感器，如光照数字传感器、土壤温度、PH 值等。
- 增加历史数据存储和曲线展示。
- 优化自动控制策略，支持多级阈值和定时控制。
- 增加异常报警策略，如传感器离线、通信断开、执行器故障等。
- 将 APP 端数据展示和控制逻辑进一步产品化。

## 说明

本仓库为毕业设计和求职展示项目，重点展示嵌入式系统开发、传感器采集、执行器控制、物联网通信和硬件联调能力。
