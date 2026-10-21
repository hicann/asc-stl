# asc::std::allocation_result::ptr

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

`asc::std::allocation_result::ptr`保存分配操作返回的存储指针。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 声明

所属类型：[`asc::std::allocation_result`](allocation_result.md)。

```cpp
// asc::std::allocation_result 类内的声明节选；模板形参和其他成员由所属类提供。
Pointer ptr;
```

## 约束说明

- 聚合保存分配地址与实际元素容量；本类型不取得所有权，也不自动构造、销毁或释放元素。
- `count`的单位是`Pointer`所指元素的个数，释放时遵守对应分配器的规则。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/memory>

bool example()
{
    int storage[3] = {1, 2, 3};
    asc::std::allocation_result<int*> result{storage, 3};
    return result.ptr[2] == 3 && result.count == 3;
}
```

## 关联API

- [`asc::std::allocation_result`](allocation_result.md)
- [本头文件的接口列表](asc_std_memory.md)
