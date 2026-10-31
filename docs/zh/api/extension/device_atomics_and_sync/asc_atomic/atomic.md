# asc::atomic

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

`asc::atomic`拥有一个可按指定内存作用域原子访问的值。

该接口的可用位置为AI Core SIMT编程。

## 声明

```cpp
namespace asc {
template <class T, asc::memory_scope Scope = asc::memory_scope::device>
class atomic;
}  // namespace asc
```

## 约束说明

- `T`须与`asc::std::int32_t`、`uint32_t`、`int64_t`或`uint64_t`中的一种完全相同，仅位宽相同不代表类型被接受。
- 原子单元须已初始化、自然对齐并位于所有参与者可见的GM中；参与并发访问时不得混用普通读写。
- atomic_ref不拥有单元，其底层对象须覆盖引用的全部使用和并发操作，不仅覆盖构造调用。

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
    auto* object = new (storage) asc::atomic<int>(7);
    auto& cell = *object;
    cell.store(7, asc::std::memory_order_relaxed);

    output[0] = (cell.load(asc::std::memory_order_relaxed) == 7) ? 1U : 0U;
}
```

完整工程及运行步骤见[《atomic_operations示例》](../../../../../../examples/extension/atomic_operations/README.md)。

## 关联API

- [本头文件的接口列表](asc_atomic.md)
