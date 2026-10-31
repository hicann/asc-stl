# 指针特征与对齐

[English](README_en.md) | [示例总览](../../README.md)

## 概述

演示addressof、pointer_traits、to_address、对齐判断与在已有buffer中寻找对齐位置。

## 支持环境

支持C++17/20的Host编译器及配套系统库，CMake 3.20或更新版本；无需CANN或NPU。

## 文件职责

- [main.cpp](main.cpp)：示例与结果检查。
- [CMakeLists.txt](CMakeLists.txt)：独立构建与CTest登记。

## 编译运行

在仓库根目录执行：

```bash
cmake -S examples/standard/pointer_alignment -B build/pointer_alignment17 -DASC_STL_EXAMPLE_STANDARD=17 -DCMAKE_BUILD_TYPE=Release
cmake --build build/pointer_alignment17 -j2
ctest --test-dir build/pointer_alignment17 --output-on-failure
```

C++20改用语言选项20及独立构建目录。

## 预期结果与约束

编译期检查指针类型，运行时检查地址相等、对齐和空间调整；退出码为0且无输出表示通过。assume_aligned要求调用者预先保证对齐，不能用来修复未对齐地址。
