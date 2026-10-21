# asc::std::allocation_result

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

头文件路径为：`<asc/std/memory>`。

`asc::std::allocation_result`同时保存分配得到的指针和实际元素数量。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 声明

```cpp
namespace asc::std {
template<class Pointer, class SizeType = asc::std::size_t> struct allocation_result;
} // namespace asc::std
```

## 约束说明

- 聚合保存分配地址与实际元素容量；本类型不取得所有权，也不自动构造、销毁或释放元素。
- `count`的单位是`Pointer`所指元素的个数，释放时遵守对应分配器的规则。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/memory>

bool example()
{
    int values[3] = {};
    asc::std::allocation_result<int*> result{values, 3};
    return result.ptr == values && result.count == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_memory.md)
