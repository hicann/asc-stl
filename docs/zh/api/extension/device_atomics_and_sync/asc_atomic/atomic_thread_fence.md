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

`asc::atomic_thread_fence` 在 AI Core SIMT 编程中按指定内存序和作用域建立线程栅栏；`relaxed` 不执行栅栏，`release` 建立发布顺序。

## 函数原型

```cpp
void asc::atomic_thread_fence(asc::std::memory_order order, asc::memory_scope scope) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `order` | 输入 | 仅支持 `asc::std::memory_order_relaxed` 或 `asc::std::memory_order_release`；其他取值不属于交付范围。 |
| `scope` | 输入 | 选择 `asc::memory_scope::block` 或 `asc::memory_scope::device`，分别表示线程块或设备作用域。 |

## 返回值说明

无返回值。

## 约束说明

- 仅可在 AI Core SIMT 编程中调用
- order 仅为 relaxed 或 release，scope 仅为 block 或 device

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/atomic>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

__aicore__ void example()
{
    // 在设备作用域发布此前的写入。
    asc::atomic_thread_fence(asc::std::memory_order_release, asc::memory_scope::device);
}
```
