# asc::barrier_arrival_token

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

`asc::barrier_arrival_token`表示一次barrier到达操作所属的阶段，供后续wait使用。

## 声明

```cpp
namespace asc {
class barrier_arrival_token;
}  // namespace asc
```

## 约束说明

- 令牌须来自同一barrier的一次到达，并在对应阶段等待；它只保存阶段信息，不拥有共享GM状态。
- 令牌可按值复制，wait接受右值引用；共享barrier对象及参与者的前进要求见所属barrier页面。

## 调用示例

本片段展示到达令牌只用于其对应屏障阶段。单个参与线程完成该阶段后，Host同步读取output[0]应为1；多个参与者必须共同遵守屏障计数。

```cpp
#include <asc/barrier>
#include <asc/std/new>

__global__ void example(void* storage, unsigned int* output)
{
    // 以单线程启动；Host为barrier提供对齐的GM存储。
    using Barrier = asc::barrier<asc::memory_scope::device>;
    auto* barrier = new (storage) Barrier(1);
    asc::barrier_arrival_token token = barrier->arrive();
    barrier->wait(static_cast<asc::barrier_arrival_token&&>(token));
    output[0] = 1;
}
```

完整工程及运行步骤见[《atomic_operations示例》](../../../../examples/atomic_operations/README.md)。

## 关联API

- [本头文件的接口列表](asc_barrier.md)
