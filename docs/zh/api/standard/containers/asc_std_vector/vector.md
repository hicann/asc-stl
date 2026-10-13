# asc::std::vector

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

头文件路径为：`<asc/std/vector>`。

`asc::std::vector`在连续存储中保存可增长的元素序列。

标准语义参考：[cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector)。

## 声明

```cpp
namespace asc::std {
template<class T, class Allocator> class vector;
} // namespace asc::std
```

## 约束说明

- vector<T,A>显式allocator构造。
- empty/size/capacity/data/begin/end/`operator[]`/front/back。
- reserve与容量内push_back/emplace_back/pop_back/clear。
- 同allocator或允许传播域的移动构造/赋值与析构。
- 仅A为Device可调、容量充足、元素和allocator操作不抛出异常的域。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <memory>
#include <asc/std/vector>

bool example()
{
    asc::std::vector<int, ::std::allocator<int>> values(::std::allocator<int>{});
    values.push_back(1);
    values.push_back(3);
    values[1] = 7;
    return values.size() == 2 && values[0] == 1 && values[1] == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_vector.md)
