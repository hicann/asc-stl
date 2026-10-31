# 完整设备入门：Add + ReLU

[English](README_en.md) | [快速入门](../../docs/zh/quick_start.md)

## 概述

本工程在64个float元素上执行`z = max(x + y, 0)`，展示ASC-STL公共算法在Ascend C
Kernel中的调用及完整Host生命周期。Kernel只用一个block做标量演示，不承诺性能收益。

## 支持环境

C++17/20、CMake 3.20或更新版本，以及提供AscendC CMake模块和毕昇编译器的CANN。
Kernel使用Ascend 950PR/950DT的AI Core SIMD模式；执行还需配套Runtime、驱动和可用逻辑设备0。

## 文件职责

| 文件 | 职责 |
| --- | --- |
| [add_relu_kernel.cpp](add_relu_kernel.cpp) | 用ASC-STL pipeline搬运GM/UB数据，通过`asc::std::max`计算 |
| [main.cpp](main.cpp) | 初始化、分配、上传、启动、同步、回读、独立golden检查和释放 |
| [CMakeLists.txt](CMakeLists.txt) | 使用CANN官方AscendC构建模块和生成的启动Header |

## 构建与执行

在仓库根目录执行，环境脚本路径和SoC按安装环境调整：

```bash
source /usr/local/Ascend/ascend-toolkit/set_env.sh
cmake -S examples/quick_start -B build/quick-start-17 \
  -DASC_STL_EXAMPLE_STANDARD=17 -DSOC_VERSION=Ascend950PR_9599 \
  -DCMAKE_BUILD_TYPE=Release
cmake --build build/quick-start-17 -j2
timeout --signal=TERM --kill-after=10s 60s build/quick-start-17/asc_stl_quick_start
```

C++20使用`-DASC_STL_EXAMPLE_STANDARD=20`及独立构建目录。
程序通过`$ORIGIN/lib`定位同一构建目录下生成的Kernel动态库，无须额外设置该库的搜索路径。
移动构建产物时须一起保留可执行程序与其相邻的`lib`目录。
默认从源码位置解析ASC-STL `include`目录，也可用`-DASC_STL_INCLUDE_DIR=/path/to/include`
选择已安装的头文件。程序使用ACL逻辑设备0；运行需真实950设备、驱动和匹配的CANN Runtime。
仅安装Toolkit的机器可编译，无法据此完成真机验证。

## 预期结果与约束

成功必须同时满足退出码0、`elements=64 mismatches=0`、`cleanup_passed=1`及
`ASC_STL_QUICK_START_PASS`。每项ACL调用会记录操作名和返回码。输入包含正、负和零和；
输出先填入不可能成功的sentinel，Host golden用普通条件表达式计算，避免把同一实现当作判定依据。

任务时限10秒，Stream同步时限10000毫秒；外层`timeout`限制整个进程。
同步失败后不释放可能仍被Kernel使用的buffer，不销毁该Stream，只尝试并记录reset/finalize，
最终保持失败。设备错误、清理失败或进程超时后应检查设备状态，不继续投放下一组Kernel。

## 验证结果检查器

维护者可在健康设备上显式执行受控结果错配：

```bash
timeout --signal=TERM --kill-after=10s 60s \
  build/quick-start-17/asc_stl_quick_start --inject-mismatch
```

该选项仅改变Host端一个预期值，不向设备提交故障Kernel。正确表现是
`elements=64 mismatches=1`、`cleanup_passed=1`、
`ASC_STL_QUICK_START_EXPECTED_MISMATCH`和退出码42；不能将任意非零退出当作预期成功。
正常运行不传此选项。
