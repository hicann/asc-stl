# asc::std::atomic_compare_exchange_strong

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

`asc::std::atomic_compare_exchange_strong`比较当前值与expected；相等时写入desired，否则更新expected；内存序与地址空间须符合本页限制。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 函数原型

```cpp
namespace asc::std {
template<class T> bool atomic_compare_exchange_strong(atomic<T>* object, T* expected, T desired) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 原子对象存储的值类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `object` | 输入/输出 | 指向存活且满足类型对齐的原子对象；本操作按指定内存序修改其原子状态。 |
| `expected` | 输入/输出 | 提供预期值或目标值的地址；比较失败时函数把观察到的当前原子值写入`*expected`；strong形式不允许伪失败，weak形式允许伪失败（值相等也可能返回`false`）。 |
| `desired` | 输入 | 比较相等时写入原子对象的目标值。 |
## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 原子操作可在Host和AI Core SIMT编程中调用；SIMT线程共享的原子对象须位于GM，并在并发访问前完成初始化。
- `object`须指向有效的[atomic](atomic.md)对象，其值类型须与模板参数`T`一致。
- 比较失败时将观察到的当前值写回`expected`；调用方须提供可写且在调用期间有效的预期值对象。

## 调用示例

以下Host片段使用具体整数原子对象；设备端对象须位于可访问的全局内存。

```cpp
#include <asc/std/atomic>

decltype(auto) example()
{
    asc::std::atomic<int> value{1};
    int expected = 1;
    return asc::std::atomic_compare_exchange_strong(&value, &expected, 2);
}
```

## 关联API

- [本头文件的接口列表](asc_std_atomic.md)
