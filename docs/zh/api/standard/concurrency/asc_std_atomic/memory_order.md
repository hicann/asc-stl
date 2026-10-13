# asc::std::memory_order

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

`asc::std::memory_order`列出原子操作可用的内存顺序。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 声明

```cpp
namespace asc::std {
enum memory_order;
} // namespace asc::std
```

## 约束说明

- 提供全部标准枚举值。
- Device侧consume内存序加强为acquire。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic<int> cell{0};
    cell.store(7, asc::std::memory_order_release);
    return cell.load(asc::std::memory_order_acquire) == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_atomic.md)
