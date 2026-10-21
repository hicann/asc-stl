# asc::barrier::barrier

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

`asc::barrier::barrier`使用调用方提供的参数初始化`asc::barrier`对象。

## 函数原型

所属类型：[`asc::barrier`](barrier.md)。

```cpp
// asc::barrier 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr explicit barrier(asc::std::ptrdiff_t expected, CompletionFunction completion = CompletionFunction()) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `expected` | 输入 | 每阶段期望到达的参与者数量：全部到达后触发完成函数并进入下一阶段；须在[0, max()]内。 |
| `completion` | 输入 | 阶段完成函数：本阶段全部参与者到达后、进入下一阶段前调用；默认为空实现。 |

## 返回值说明

无返回值。

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

#include <asc/std/new>

__aicore__ void example(asc::barrier<asc::memory_scope::block>* gm_storage)
{
    // gm_storage 是调用方提供且对齐的 GM 存储。
    ::new (static_cast<void*>(gm_storage)) asc::barrier<asc::memory_scope::block>(1);
}
```

## 关联API

- [`asc::barrier`](barrier.md)
- [本头文件的接口列表](asc_barrier.md)
