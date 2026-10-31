# 分配器特征与内外层访问

[English](README_en.md) | [示例总览](../../README.md)

## 概述

使用`allocator_traits`分别查询分配器特征，再通过`scoped_allocator_adaptor`访问保存的内外层分配器。

## 支持环境

支持C++17/20的Host编译器及配套系统库，CMake 3.20或更新版本；无需CANN或NPU。

## 文件职责

- [main.cpp](main.cpp)：示例与结果检查。
- [CMakeLists.txt](CMakeLists.txt)：独立构建与CTest登记。

## 编译运行

在仓库根目录执行：

```bash
cmake -S examples/standard/allocator_traits -B build/allocator_traits17 -DASC_STL_EXAMPLE_STANDARD=17 -DCMAKE_BUILD_TYPE=Release
cmake --build build/allocator_traits17 -j2
ctest --test-dir build/allocator_traits17 --output-on-failure
```

C++20改用语言选项20及独立构建目录。

## 预期结果与约束

本例通过static_assert检查每个分配器的特征和公开类型，再检查内外层分配器各自保存的状态。编译成功且程序退出码为0表示检查通过，程序不打印输出。它不演示分配/释放存储。

当前适配器不提供outer_traits成员，也不合并内外层传播特征；参见[公开支持范围](../../../docs/zh/api/standard/memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor.md)。本例分别查询各分配器，不将外层继承成员当作合并结果。
