# asc::std::equality_comparable

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

头文件路径为：`<asc/std/concepts>`。

`asc::std::equality_comparable`用于在编译期判断类型是否支持符合要求的相等和不等比较，自C++20起提供。泛型接口可用该概念限制模板参数，使不满足比较要求的类型在重载选择阶段被拒绝。

标准语义参考：[cppreference `concepts`](https://en.cppreference.com/w/cpp/header/concepts)。

## 声明

```cpp
namespace asc::std {
template<class T> concept equality_comparable;
} // namespace asc::std
```

## 约束说明

- T的相等和不等比较必须可转换为bool，并满足对称性、传递性和自反性要求。

## 调用示例

以下示例为用户自定义类型提供相等和不等比较，并在编译期检查该类型满足equality_comparable。

```cpp
#include <asc/std/concepts>

struct point {
    int x;

    friend constexpr bool operator==(point left, point right)
    {
        return left.x == right.x;
    }

    friend constexpr bool operator!=(point left, point right)
    {
        return !(left == right);
    }
};

static_assert(asc::std::equality_comparable<point>);
```

## 关联API

- [本头文件的接口列表](asc_std_concepts.md)
