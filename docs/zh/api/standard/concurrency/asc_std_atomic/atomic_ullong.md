# asc::std::atomic_ullong

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

`asc::std::atomic_ullong`把指定基础整数或布尔类型绑定到当前交付的原子类型别名。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 声明

```cpp
namespace asc::std {
using atomic_ullong = atomic<unsigned long long>;
} // namespace asc::std
```

## 约束说明

- 标准整数/字符owning atomic别名及列出自由函数。
- bool/8/16位用32位内部存储。
- 32/64位按有符号位模式分派。
- Host和AI Core SIMT编程GM。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic_ullong cell{};
    cell.store(1, asc::std::memory_order_relaxed);
    return cell.load(asc::std::memory_order_relaxed) == 1;
}
```

## 关联API

- [本头文件的接口列表](asc_std_atomic.md)
