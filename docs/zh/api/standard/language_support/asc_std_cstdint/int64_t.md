# asc::std::int64_t

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

头文件路径为：`<asc/std/cstdint>`。

`asc::std::int64_t`提供对应位宽、符号性或指针宽度的整数类型别名。

标准语义参考：[cppreference `cstdint`](https://en.cppreference.com/w/cpp/header/cstdint)。

## 声明

```cpp
namespace asc::std {
using int64_t = Int64t;
} // namespace asc::std
```

## 约束说明

- 仅提供Ascend 950与Host ABI中实际存在的类型和宏。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/cstdint>
#include <asc/std/type_traits>

bool example()
{
    using Integer = asc::std::int64_t;
    static_assert(asc::std::is_integral_v<Integer>);
    static_assert(asc::std::is_signed_v<Integer> == true);
    Integer left = 2;
    Integer right = 3;
    return left + right == 5;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cstdint.md)
