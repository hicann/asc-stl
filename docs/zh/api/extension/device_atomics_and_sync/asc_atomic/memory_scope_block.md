# asc::memory_scope::block

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

`asc::memory_scope::block`表示原子同步范围限定在同一Block内。

该接口的可用位置为AI Core SIMT编程。

## 声明

所属类型：[`asc::memory_scope`](memory_scope.md)。

```cpp
// asc::memory_scope 类内的声明节选；模板形参和其他成员由所属类提供。
block;
```

## 约束说明

- 仅提供block和device两种内存作用域。

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

    output[0] = (cell.load(asc::std::memory_order_relaxed) == 7) ? 1U : 0U;
}
```

完整工程及运行步骤见[《atomic_operations示例》](../../../../../../examples/extension/atomic_operations/README.md)。

## 关联API

- [`asc::memory_scope`](memory_scope.md)
- [本头文件的接口列表](asc_atomic.md)
