# asc::std::atomic::operator T

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

`asc::std::atomic::operator T` 是到所存值类型的转换运算符，按默认内存序原子加载并返回所存的值，语义等价于调用 `load`。

该接口的可用位置为 Host、AI Core SIMT 编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 函数原型

```cpp
asc::std::atomic::operator T() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回原子加载到的值。 |

## 约束说明

- 原子操作可在Host和AI Core SIMT编程中调用；SIMT线程共享的原子对象须位于GM，并在并发访问前完成初始化。
- 转换结果类型为原子对象的`value_type`即`T`；转换以`memory_order_seq_cst`读取并返回当前值。

## 调用示例

以下 Host 片段演示原子操作；设备端对象须放在本页规定的有效内存空间。

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic<int> value{7};
    const int observed = value;
    return observed == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_atomic.md)
