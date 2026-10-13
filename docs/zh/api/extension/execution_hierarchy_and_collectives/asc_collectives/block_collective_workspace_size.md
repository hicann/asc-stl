# asc::block_collective_workspace::size

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

头文件路径为：`<asc/collectives>`。

`asc::block_collective_workspace::size`返回工作区可容纳的元素数量。

## 函数原型

```cpp
template<class T> constexpr asc::std::uint32_t asc::block_collective_workspace<T>::size() const noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 每个参与线程读写的元素类型，决定工作区的大小与对齐。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::std::uint32_t` | 返回工作区可容纳的元素数量。 |

## 约束说明

- 仅可在AI Core SIMT编程中调用。
- 同一Block的线程必须会合调用。
- 线程数、动态共享UB工作区及同步次序必须满足声明要求，工作区在调用期间不得被并发复用。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/collectives>

__aicore__ unsigned int example(unsigned int* dynamic_shared_pointer)
{
    auto workspace = asc::make_block_collective_workspace(dynamic_shared_pointer, 2u);
    return workspace.size();
}
```

## 关联API

- [本头文件的接口列表](asc_collectives.md)
