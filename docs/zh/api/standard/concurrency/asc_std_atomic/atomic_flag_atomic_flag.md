# asc::std::atomic_flag::atomic_flag

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

`asc::std::atomic_flag::atomic_flag` 按本页所列构造形态初始化 `atomic_flag` 对象。

该接口的可用位置为 Host、AI Core SIMT 编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 函数原型

```cpp
constexpr atomic_flag() noexcept;
```

## 参数说明

无参数。

## 约束说明

- atomic_flag的test/test_and_set/clear成员与非volatile自由函数
- Host 和 AI Core SIMT 编程 GM

## 调用示例

以下 Host 片段演示原子操作；设备端对象须放在本页规定的有效内存空间。

```cpp
#include <asc/std/atomic>

void example()
{
    asc::std::atomic_flag flag{};
    (void)flag;
}
```
