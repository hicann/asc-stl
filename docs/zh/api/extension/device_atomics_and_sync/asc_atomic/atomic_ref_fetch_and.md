# asc::atomic_ref::fetch_and

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

头文件路径为：`<asc/atomic>`。

`asc::atomic_ref::fetch_and`原子执行按位与并返回修改前的值。

该接口的可用位置为AI Core SIMT编程。

## 函数原型

所属类型：[`asc::atomic_ref`](atomic_ref.md)。

```cpp
// asc::atomic_ref 类内的声明节选；模板形参和其他成员由所属类提供。
T fetch_and(T operand, asc::std::memory_order order = asc::std::memory_order_seq_cst) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `operand` | 输入 | 参与按位与的操作数：原子对象当前值与该值按位与后写回，返回修改前的旧值。 |
| `order` | 输入 | 本次原子读改写使用的内存序；可取`asc::std::memory_order`的六种标准值。单元须位于GM；relaxed不建立其他对象的发布/获取关系。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回修改前的值。 |

## 约束说明

- 原子对象的类型、地址空间、作用域和内存序必须匹配。
- 所有Device原子单元必须位于GM；UB、栈或每核私有存储不属于当前支持域。

## 调用示例

以下SIMT核函数由单个线程初始化并访问一个GM原子单元；无其他并发访问，预期output[0]为1。Host须在核函数完成后读取结果。

```cpp
#include <asc/atomic>
#include <asc/std/new>

__global__ void example(int* storage, unsigned int* output)
{
    // 仅启动1个block、1个线程；storage和output均为Host分配的GM。
    *storage = 7;
    asc::atomic_ref<int> cell(*storage);
    cell.store(7, asc::std::memory_order_relaxed);
    const int previous = cell.fetch_and(3, asc::std::memory_order_relaxed);
    output[0] = (previous == 7 && cell.load(asc::std::memory_order_relaxed) == 3) ? 1U : 0U;
}
```

完整工程及运行步骤见[《atomic_operations示例》](../../../../examples/atomic_operations/README.md)。

## 关联API

- [`asc::atomic_ref`](atomic_ref.md)
- [本头文件的接口列表](asc_atomic.md)
