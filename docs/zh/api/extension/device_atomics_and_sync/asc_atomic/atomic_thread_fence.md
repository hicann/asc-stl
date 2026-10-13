# asc::atomic_thread_fence

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

`asc::atomic_thread_fence`在AI Core SIMT编程中按指定内存序和作用域建立线程栅栏；`relaxed`不执行栅栏，`release`建立发布顺序。

## 函数原型

```cpp
namespace asc {
void atomic_thread_fence(asc::std::memory_order order, asc::memory_scope scope) noexcept;
} // namespace asc
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `order` | 输入 | 仅接受`memory_order_relaxed`（无操作）或`memory_order_release`（发布栅栏）；其他值不受支持。 |
| `scope` | 输入 | 选择`asc::memory_scope::block`或`asc::memory_scope::device`，分别表示线程块或设备作用域。 |

## 返回值说明

无返回值。

## 约束说明

- 仅可在AI Core SIMT编程中调用。
- order仅为relaxed或release，scope仅为block或device。

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
    asc::atomic_thread_fence(asc::std::memory_order_release, asc::memory_scope::device);
    output[0] = (cell.load(asc::std::memory_order_relaxed) == 7) ? 1U : 0U;
}
```

完整工程及运行步骤见[《atomic_operations示例》](../../../../examples/atomic_operations/README.md)。

## 关联API

- [本头文件的接口列表](asc_atomic.md)
