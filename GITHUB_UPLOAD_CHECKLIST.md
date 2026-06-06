# GitHub 上传前整理清单

本清单用于把当前毕业设计资料包整理成适合求职展示的 GitHub 仓库。

## 仓库信息

- 推荐仓库名：`stm32-esp8266-iot-greenhouse-monitor`
- 推荐项目标题：`STM32 + ESP8266 物联网远程监控系统`
- 推荐描述：`基于 STM32F103 和 ESP8266 的农业大棚环境监测与远程控制系统，支持环境采集、OLED 显示、执行器控制和机智云 APP 远程监控。`
- 推荐标签：`stm32`、`esp8266`、`iot`、`embedded-c`、`greenhouse`、`gizwits`、`keil`

## 建议上传

- `README.md`
- `.gitignore`
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
- `bom.xlsx`
- `毕设硬件对接口.txt`
- 精选后的 `文档图片/`

## 不建议上传

- Keil 编译产物：`Objects/`、`Listings/`、`*.o`、`*.d`、`*.crf`、`*.axf`、`*.map`
- 用户本地配置：`*.uvguix.*`
- 大视频和大 PPT：`讲解视频/`、`答辩PPT.pptx`
- 参考资料和格式模板：参考论文、论文格式 PDF、无关项目 PPT
- 第三方工具和安装包：`*.exe`、`*.apk`、`*.ipa`
- 可能包含个人信息的论文、答辩材料、班级姓名文件

## 上传后检查

- GitHub 首页能直接看到 README 内容。
- README 第一屏能说明项目是什么、用了什么技术、能做什么。
- 仓库体积不要过大，尽量控制在几十 MB 内。
- 仓库文件名尽量清楚，避免出现大量临时文件、编译产物和历史版本。
- 至少放 3 张项目图：硬件实物图、OLED/APP 效果图、系统架构图或 PCB 图。
