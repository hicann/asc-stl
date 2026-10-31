# 显式分配器vector

[English](README_en.md) | [示例总览](../../README.md)

## 概述

用调用者提供的256字节arena构造vector，演示reserve、插入、删除、清空和移动赋值。

## 支持环境

支持C++17/20的Host编译器及配套系统库，CMake 3.20或更新版本；无需CANN或NPU。

## 文件职责

- [main.cpp](main.cpp)：示例与结果检查。
- [CMakeLists.txt](CMakeLists.txt)：独立构建与CTest登记。

## 编译运行

在仓库根目录执行：

```bash
cmake -S examples/standard/explicit_allocator_vector -B build/explicit_allocator_vector17 -DASC_STL_EXAMPLE_STANDARD=17 -DCMAKE_BUILD_TYPE=Release
cmake --build build/explicit_allocator_vector17 -j2
ctest --test-dir build/explicit_allocator_vector17 --output-on-failure
```

C++20改用语言选项20及独立构建目录。

## 预期结果与约束

程序检查容量、元素值、迭代器、分配器身份及移动后的状态；退出码为0且无输出表示通过。arena必须比容器活得更久；本例的顺序分配器不回收单次分配，不能作为通用分配器。
