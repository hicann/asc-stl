# 位标志处理

[English](README_en.md) | [示例总览](../../README.md)

## 概述

初始掩码5表示第0、2位置位，加入第5位后得到37，再清除第2位得到33。检查置位数、有效位宽、单比特标志和零掩码。

主要公共接口：cstdint、bit、popcount、bit_width、has_single_bit。

## 支持环境

- Host：支持C++17/20的编译器及配套系统库，CMake 3.20或更新版本，无需CANN。
- Device：Ascend 950PR/950DT、提供ASC CMake模块和毕昇编译器的CANN、配套驱动和Runtime，以及可用逻辑设备0。使用SIMT，由一个活动线程完成计算。

## 文件职责

- [example.h](example.h)：Host和Device共用的计算逻辑。
- [example_types.h](example_types.h)：普通输入/输出类型。
- [check.h](check.h)：Host输入、独立预期值及输出检查。
- [共用Host入口](../../common/standard_host_main.cpp)：构造输入、调用计算并检查结果。
- [共享Kernel](../../common/standard_kernel.asc)与[Host启动程序](../../common/standard_device_main.cpp)：上传、启动、有界等待、回读和清理。
- [CMakeLists.txt](CMakeLists.txt)：独立构建。

## Host编译运行

在仓库根目录执行：

```bash
cmake -S examples/standard/bit_flags -B build/bit_flags17 -DASC_STL_EXAMPLE_STANDARD=17 -DCMAKE_BUILD_TYPE=Release
cmake --build build/bit_flags17 -j2
build/bit_flags17/asc_stl_bit_flags
ctest --test-dir build/bit_flags17 --output-on-failure
```

## Device编译运行

source实际安装的CANN set_env.sh后，在仓库根目录执行：

```bash
cmake -S examples/standard/bit_flags -B build/bit_flags-device17 \
  -DASC_STL_EXAMPLE_DEVICE=ON -DASC_STL_EXAMPLE_STANDARD=17 \
  -DCMAKE_ASC_ARCHITECTURES=dav-3510 -DCMAKE_BUILD_TYPE=Release
cmake --build build/bit_flags-device17 --target asc_stl_bit_flags_device -j2
timeout --signal=TERM --kill-after=10s 60s build/bit_flags-device17/asc_stl_bit_flags_device
```

C++20改用语言选项20及独立构建目录。CTest只执行Host程序，NPU运行须显式调用。

## 预期结果

Host和Device应得到相同的计算结果：

```text
enabled=37 final=33 active=2 width=6 single=1 zero_count=0
```

Host成功退出码为0。Device成功还须同时满足退出码0、cleanup_passed=1和ASC_STL_STANDARD_DEVICE_PASS；device_cplusplus在C++17为201703，C++20为202002。Host上传真实GM输入，Kernel计算并回写，Host以独立常量检查结果。

## 约束说明

使用无符号整数表示掩码，bit接口遵循各自的无符号类型约束。bit_width表示最高置位位置加1，不是置位数量。

Device任务执行时限为10秒，Stream等待上限为10000毫秒，均检查返回值；外层timeout限制进程。同步失败时保留可能仍在使用的buffer，尝试reset/finalize并保持失败。设备错误或超时后停止后续投放，先检查设备状态。这些标量案例演示语义，不提供并行加速结论。

## 关联API

- [popcount](../../../docs/zh/api/standard/utilities/asc_std_bit/popcount.md)
- [bit_width](../../../docs/zh/api/standard/utilities/asc_std_bit/bit_width.md)
- [has_single_bit](../../../docs/zh/api/standard/utilities/asc_std_bit/has_single_bit.md)
