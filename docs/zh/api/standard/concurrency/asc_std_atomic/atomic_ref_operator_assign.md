# asc::std::atomic_ref::operator=

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

`asc::std::atomic_ref::operator=` 原子存储值到被引用对象并返回所存的值，语义等价于按默认内存序调用 `store`。

该接口的可用位置为 Host、AI Core SIMT 编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 函数原型

```cpp
T asc::std::atomic_ref::operator=(T value) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 写入被引用对象的值。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回所存储的值。 |

## 约束说明

- atomic_ref 自身的拷贝与移动赋值被删除，仅接受对被引用对象的值赋值
- 原子对象的类型、地址空间、作用域和内存序必须匹配
- Device 作用域的 64 位对象位于 GM，UB 原子操作仅使用 memory_order_relaxed

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/atomic>

bool example()
{
    alignas(int) int storage = 5;
    int before = 0;
    {
        asc::std::atomic_ref<int> value(storage);
        before = (value = 3);
    }
    return before == 3 && storage == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_atomic.md)
