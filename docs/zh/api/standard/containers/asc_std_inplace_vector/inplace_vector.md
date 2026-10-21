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

Host和Device均提供已列出的非抛出接口子集，基本值操作从C++17起可用。

标准语义参考：[cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector)。

## 声明

```cpp
namespace asc::std {
template<class T, asc::std::size_t Capacity> class inplace_vector;
} // namespace asc::std
```

## 约束说明

- 元素存储位于容器对象内，不动态分配；Capacity是编译期固定容量。
- Host和Device均提供所列非抛出子集，不提供`at`、`push_back`、`emplace_back`、`resize`或`try_append_range`。
- `try_push_back`和`try_emplace_back`返回`optional<T&>`；容量不足时返回空对象。`unchecked`插入要求调用方事先保证有剩余容量。
- 元素的对应构造、赋值和析构须满足非抛出使用域；constexpr声明不保证任意T和语言模式都能常量求值。

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
