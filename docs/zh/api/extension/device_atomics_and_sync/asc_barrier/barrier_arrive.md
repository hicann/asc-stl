# asc::barrier::arrive

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

`asc::barrier::arrive`减少当前阶段的未到达计数并返回该阶段的到达令牌。

## 函数原型

所属类型：[`asc::barrier`](barrier.md)。

```cpp
// asc::barrier 类内的声明节选；模板形参和其他成员由所属类提供。
asc::barrier_arrival_token arrive(asc::std::ptrdiff_t update = 1) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `update` | 输入 | 本次到达折算的参与者数量，默认1：未到达计数按该值减少，减至0时触发完成函数并开启下一阶段。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::barrier_arrival_token` | 返回该阶段的到达令牌。 |

## 约束说明

- 初始expected须在`[0, max()]`内；arrive的update须非负且不超过当前阶段剩余计数。expected为0时不能用正update到达；arrive_and_drop还要求后续期望计数当前为正。

- 使用C++17。
- 在AI Core SIMT编程 中操作调用方管理的GM状态。
- Scope必须为asc::memory_scope::block或asc::memory_scope::device。
- 所有阻塞参与者必须能够并发推进。
- 复制构造和复制赋值已删除。

## 调用示例

以下AI Core SIMT片段使用调用方管理的GM同步对象；参与者数量和前进条件须满足本页约束。

```cpp
#include <asc/barrier>

__aicore__ decltype(auto) example(asc::barrier<asc::memory_scope::block>* gm_barrier)
{
    // 对象位于 GM；阻塞操作只在所有参与者可并发推进时调用。
    return gm_barrier->arrive();
}
```

## 关联API

- [`asc::barrier`](barrier.md)
- [本头文件的接口列表](asc_barrier.md)
