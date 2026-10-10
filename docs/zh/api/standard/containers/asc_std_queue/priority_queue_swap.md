# asc::std::priority_queue::swap

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

头文件路径为：`<asc/std/queue>`。

`asc::std::priority_queue::swap` 交换两个对象保存的状态或元素。

标准语义参考：[cppreference `queue`](https://en.cppreference.com/w/cpp/header/queue)。

## 函数原型

```cpp
constexpr void asc::std::priority_queue::swap(priority_queue<T, Container, Compare>& other) noexcept(noexcept(this->c.swap(other.c))&& noexcept(Compare(static_cast<Compare&&>(this->comp)))&& noexcept(this->comp = static_cast<Compare&&>(other.comp))&& noexcept(other.comp = static_cast<Compare&&>(this->comp)));
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

## 返回值说明

无返回值。

## 约束说明

- priority_queue<T,Container,Compare=less<typename Container::value_type>>的显式兼容Container合同：T必须等于Container::value_type，Container的构造/front/operator[]/push_back/emplace_back/pop_back/size/empty/swap及allocator操作必须在当前执行空间有效，Compare必须定义Device可调的strict-weak-order且可在已验证移动交换域使用
- 交付container_type/value_compare/value_type/size_type/reference/const_reference及protected c/comp，default/Compare/Container/copy/move/allocator构造及赋值，N4861两类InputIterator构造，empty/size/top、lvalue/rvalue push、void emplace、pop，member/non-member swap、uses_allocator特化，以及Compare+Container、InputIterator+Compare+Container、Compare+Container+Alloc三类显式Container CTAD
- 堆序语义为Host、AI Core SIMD 编程 和 AI Core SIMT 编程

## 调用示例

以下 Host 片段显式提供标准容器作为底层存储；设备端须提供可在目标位置调用的容器。

```cpp
#include <asc/std/queue>
#include <deque>
#include <functional>
#include <vector>

void example(asc::std::priority_queue<int, ::std::vector<int>, ::std::less<int>>& object, asc::std::priority_queue<int, ::std::vector<int>, ::std::less<int>>& other)
{
    object.swap(other);
}
```
