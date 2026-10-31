# Warp集体操作

[English](README_en.md) | [示例总览](../../README.md)

## 概述

启动一个32线程SIMT线程组，演示lane掩码、投票、匹配、shuffle及归约，Host检查32个失败计数均为0。

## 支持环境

- Host + AI Core SIMT; C++17/20; CMake 3.20+.
- Ascend 950PR/950DT，提供ASC CMake模块与毕昇编译器的CANN。
- 配置前source实际安装的CANN set_env.sh；执行还需配套Runtime、驱动和可用逻辑设备0。

## 文件职责

- [kernel.asc](kernel.asc)：Kernel及启动接口。
- [main.cpp](main.cpp)：Host资源管理与结果检查。
- [warp_example.h](warp_example.h)：共享启动声明。
- [CMakeLists.txt](CMakeLists.txt)：独立构建。

## 编译运行

激活CANN后，在仓库根目录执行：

```bash
cmake -S examples/extension/warp_collectives -B build/warp_collectives17 \
  -DASC_STL_EXAMPLE_STANDARD=17 -DCMAKE_ASC_ARCHITECTURES=dav-3510 -DCMAKE_BUILD_TYPE=Release
cmake --build build/warp_collectives17 -j2
timeout --signal=TERM --kill-after=10s 60s build/warp_collectives17/asc_stl_warp_example
```

C++20改用语言选项20及独立构建目录。

## 预期结果与约束

成功须同时满足退出码0和`PASS: warp collectives`。Host等待Stream完成后才读回结果并释放存储，异步访问期间存储必须持续有效。本例用于展示用法，不提供性能结论。超时或设备错误后，应先检查设备状态再运行其它示例。

任务执行时限为10秒，Stream同步上限为10000毫秒，均检查返回值；输出先填入sentinel。成功还要求cleanup_passed=1。同步失败时不提前释放buffer，尝试reset/finalize并保持失败。
