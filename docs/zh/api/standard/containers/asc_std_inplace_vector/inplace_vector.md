# asc::std::inplace_vector

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

头文件路径为：`<asc/std/inplace_vector>`。

`asc::std::inplace_vector`在对象内的固定容量存储中保存元素。

该接口的可用位置为Host（完整接口）、Device（非抛出子集）。

标准语义参考：[cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector)。

## 声明

```cpp
namespace asc::std {
template<class T, asc::std::size_t Capacity> class inplace_vector;
} // namespace asc::std
```

## 约束说明

- 最终C++26标准inplace_vector/erase/erase_if合同：Host交付除P4022R0已删除try_append_range外的完整构造、赋值、迭代、访问、修改（含投抛成员 at/push_back/emplace_back/resize，越界抛 out_of_range、容量已满抛 bad_alloc）、try/unchecked、六个比较运算符与三路比较、swap、容量、零容量empty/trivial与constexpr/约束合同。
- Device交付固定容量内联存储的非抛子合同，包括观察/迭代/operator[]/front/back、不抛出异常拷移赋值析构、try/unchecked后插、pop_back/clear、不抛出异常 erase/erase_if/swap、相等与不抛出异常三路比较、完整零容量核心。
- Host 提供完整接口，设备端仅提供不抛出异常的接口。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/inplace_vector>

bool example()
{
    asc::std::inplace_vector<int, 4> values;
    if (!values.try_push_back(1)) return false;
    if (!values.try_push_back(3)) return false;
    return values.size() == 2 && values[0] == 1 && values[1] == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_inplace_vector.md)
