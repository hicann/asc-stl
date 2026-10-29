# asc::std::atomic_flag_test_and_set_explicit

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

`asc::std::atomic_flag_test_and_set_explicit`按指定内存序置位原子标志并返回原有状态。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 函数原型

```cpp
namespace asc::std {
bool atomic_flag_test_and_set_explicit(atomic_flag* object, memory_order order) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `object` | 输入/输出 | 指向被置位或清除的原子标志对象的指针。 |
| `order` | 输入 | 置位并读取原值所用内存序，决定本次操作的可见性顺序；可取memory_order各枚举值。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 可在Host或AI Core SIMT编程中调用；SIMT线程共享的标志对象须位于GM，并在并发访问前完成初始化。
- `object`须指向有效的非volatile[atomic_flag](atomic_flag.md)对象。
- 该操作原子地将标志置为`true`并返回旧值；不带内存序参数的形式使用`memory_order_seq_cst`。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic_flag flag{};
    const bool before = asc::std::atomic_flag_test_and_set_explicit(&flag, asc::std::memory_order_relaxed);
    const bool after = asc::std::atomic_flag_test_and_set_explicit(&flag, asc::std::memory_order_relaxed);
    return !before && after;
}
```

## 关联API

- [本头文件的接口列表](asc_std_atomic.md)
