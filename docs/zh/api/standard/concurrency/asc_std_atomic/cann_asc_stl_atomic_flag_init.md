# CANN_ASC_STL_ATOMIC_FLAG_INIT

## 产品支持情况

<!-- npu="950" id1 -->
- Ascend 950PR&950DT系列产品：支持
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3系列产品：不支持
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2系列产品：不支持
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2推理产品：不支持
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas推理系列产品AI Core：不支持
<!-- end id5 -->
<!-- npu="310p" id6 -->
- Atlas推理系列产品Vector Core：不支持
<!-- end id6 -->
<!-- npu="910" id7 -->
- Atlas训练系列产品：不支持
<!-- end id7 -->

## 功能说明

头文件路径为：`<asc/std/atomic>`。

`CANN_ASC_STL_ATOMIC_FLAG_INIT`提供`atomic_flag`的静态初始化形式。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 声明

```cpp
#define CANN_ASC_STL_ATOMIC_FLAG_INIT {}
```

## 约束说明

- 本宏展开为标志对象的初始化列表，使[atomic_flag](atomic_flag.md)初始值为`false`。
- 初始化仅可用于Host或AI Core SIMT编程中，须在其他线程并发访问前完成；SIMT共享对象须位于GM。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic_flag value = CANN_ASC_STL_ATOMIC_FLAG_INIT;
    return !value.test_and_set();
}
```

## 关联API

- [本头文件的接口列表](asc_std_atomic.md)
