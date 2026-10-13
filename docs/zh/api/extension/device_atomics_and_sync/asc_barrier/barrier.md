# asc::barrier

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

头文件路径为：`<asc/barrier>`。

`asc::barrier`提供可重复使用的分阶段线程屏障，并在每一阶段完成时调用完成函数。

## 声明

```cpp
namespace asc {
template<asc::memory_scope Scope, class CompletionFunction = asc::detail::barrier_empty_completion> class barrier;
} // namespace asc
```

## 约束说明

- 使用C++17。
- 在AI Core SIMT编程 中操作调用方管理的GM状态。
- Scope必须为asc::memory_scope::block或asc::memory_scope::device。
- 所有阻塞参与者必须能够并发推进。
- 复制构造和复制赋值已删除。

## 调用示例

以下片段用于D-SIMT编译。barrier位于已初始化的共享GM存储；期望计数与本轮参与线程数一致，同一block的全部参与者必须到达。完成后才能进入下一阶段。

```cpp
#include <asc/barrier>

__aicore__ void example(asc::barrier<asc::memory_scope::block>& barrier)
{
    barrier.arrive_and_wait();
}
```

## 关联API

- [本头文件的接口列表](asc_barrier.md)
