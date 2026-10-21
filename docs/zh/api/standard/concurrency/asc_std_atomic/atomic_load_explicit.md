# asc::std::atomic_load_explicit

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

`asc::std::atomic_load_explicit`按指定或默认内存序读取当前原子值；内存序与地址空间须符合本页限制。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 函数原型

```cpp
namespace asc::std {
template<class T> T atomic_load_explicit(const atomic<T>* object, memory_order order) noexcept;
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
| `object` | 输入 | 指向被读取的原子对象的指针。 |
| `order` | 输入 | 读取所用内存序，决定本次读取的可见性顺序；仅可取relaxed、consume、acquire或seq_cst。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回按所选内存序读取的当前原子值。 |

## 约束说明

- 原子操作可在Host和AI Core SIMT编程中调用；SIMT线程共享的原子对象须位于GM，并在并发访问前完成初始化。
- `object`须指向有效的[atomic](atomic.md)对象，其值类型须与模板参数`T`一致。
- 显式内存序须为`memory_order_relaxed`、`memory_order_consume`、`memory_order_acquire`或`memory_order_seq_cst`；不允许`memory_order_release`或`memory_order_acq_rel`。

## 调用示例

以下Host片段使用具体整数原子对象；设备端对象须位于可访问的全局内存。

```cpp
#include <asc/std/atomic>

decltype(auto) example()
{
    asc::std::atomic<int> value{1};
    return asc::std::atomic_load_explicit(&value, asc::std::memory_order_acquire);
}
```

## 关联API

- [本头文件的接口列表](asc_std_atomic.md)
