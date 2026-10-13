# asc::std::atomic_flag::clear

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

`asc::std::atomic_flag::clear`移除全部元素并使容器变为空。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 函数原型

所属类型：[`asc::std::atomic_flag`](atomic_flag.md)。

```cpp
// asc::std::atomic_flag 类内的声明节选；模板形参和其他成员由所属类提供。
void clear(memory_order order) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `order` | 输入 | 清除标志所用内存序，决定本次写入的可见性顺序；仅可取relaxed、release或seq_cst。 |

## 返回值说明

无返回值。

## 约束说明

- atomic_flag的test/test_and_set/clear成员与非volatile自由函数。
- Host和AI Core SIMT编程GM。

## 调用示例

以下Host片段演示原子操作；设备端对象须放在本页规定的有效内存空间。

```cpp
#include <asc/std/atomic>

void example(asc::std::atomic_flag& flag)
{
    flag.clear(asc::std::memory_order_relaxed);
}
```

## 关联API

- [`asc::std::atomic_flag`](atomic_flag.md)
- [本头文件的接口列表](asc_std_atomic.md)
