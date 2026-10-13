# asc::memory_space_of

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

头文件路径为：`<asc/memory>`。

`asc::memory_space_of<T>`是可定制类型特征，用于取得受支持内存视图类型对应的`memory_space`；`gm_span`和`ub_span`分别映射到GM与UB。

## 声明

```cpp
namespace asc {
template<class T> struct memory_space_of;
} // namespace asc
```

## 约束说明

- 提供非拥有的地址空间视图、显式arena和临时存储。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/memory>

bool example()
{
    static_assert(asc::memory_space_of<asc::gm_span<int>>::value == asc::memory_space::global);
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_memory.md)
