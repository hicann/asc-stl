# Stream与Event生命周期

[English](README_en.md) | [示例总览](../../README.md)

## 概述

演示设备引用、Stream/Event创建、非拥有引用、事件记录与等待、计时、句柄释放与
接管、移动以及显式关闭。程序在逻辑设备0初始化Runtime，检查结果后重置设备并结束。

## 支持环境

Host C++17/20编译器及配套系统库、CMake 3.20或更新版本、提供`acl/acl.h`和
`libascendcl`的CANN。运行需要支持的Ascend 950PR/950DT设备、配套驱动及Runtime。
本例从Host管理设备资源，不编译自定义Kernel；纯Host标准层示例不需要这些依赖。

## 文件职责

- [main.cpp](main.cpp)：资源生命周期与结果检查。
- [CMakeLists.txt](CMakeLists.txt)：查找ACL并构建可执行程序。

## 编译运行

source实际安装的CANN `set_env.sh`后，在仓库根目录执行：

```bash
cmake -S examples/runtime/stream_event -B build/stream_event17 -DASC_STL_EXAMPLE_STANDARD=17
cmake --build build/stream_event17 -j2
timeout --signal=TERM --kill-after=10s 60s build/stream_event17/asc_stl_stream_event
```

C++20改用语言选项20及独立构建目录。示例不会由CTest自动启动。

## 预期结果与约束

退出码为0且无输出表示全部检查以及设备重置和Runtime结束成功；失败返回非零。
引用不拥有句柄，拥有者在引用使用期间必须保持有效；release后由接管对象负责关闭。
计时只检查结果非负，不作为性能结论。超时或设备错误后先核对设备状态再运行其它程序。
