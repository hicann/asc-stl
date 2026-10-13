# asc::std::atomic_compare_exchange_strong_explicit

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

`asc::std::atomic_compare_exchange_strong_explicit` 比较当前值与 expected；相等时写入 desired，否则更新 expected；内存序与地址空间须符合本页限制。

该接口的可用位置为 Host、AI Core SIMT 编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 函数原型

```cpp
template<class T> bool asc::std::atomic_compare_exchange_strong_explicit(atomic<T>* object, T* expected, T desired, memory_order success, memory_order failure) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 原子对象存储的值类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `object` | 输入 | 提供“比较当前值与 expected”所需的数据地址；可访问范围和生命周期须满足约束。 |
| `expected` | 输入/输出 | 提供预期值或目标值的地址；比较失败时函数把观察到的当前原子值写入 `*expected`；strong 形式不允许伪失败，weak 形式允许伪失败（值相等也可能返回 `false`）。 |
| `desired` | 输入 | 比较相等时写入原子对象的目标值。 |
| `success` | 输入 | 比较交换成功分支使用的内存序，约束交换写入的可见性顺序。 |
| `failure` | 输入 | 比较交换失败分支（仅读取）使用的内存序；不得为 release 或 acq_rel，且不得强于 success。 |
## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回 `true`，否则返回 `false`。 |

## 约束说明

- 标准整数/字符owning atomic别名及列出自由函数
- bool/8/16位用32位内部存储
- 32/64位按有符号位模式分派
- Host 和 AI Core SIMT 编程 GM

## 调用示例

以下 Host 片段使用具体整数原子对象；设备端对象须位于可访问的全局内存。

```cpp
#include <asc/std/atomic>

decltype(auto) example()
{
    asc::std::atomic<int> value{1};
    int expected = 1;
    return asc::std::atomic_compare_exchange_strong_explicit(&value, &expected, 2, asc::std::memory_order_acq_rel, asc::std::memory_order_acquire);
}
```
