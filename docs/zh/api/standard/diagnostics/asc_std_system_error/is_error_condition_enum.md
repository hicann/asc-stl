# asc::std::is_error_condition_enum

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

头文件路径为：`<asc/std/system_error>`。

`asc::std::is_error_condition_enum`标记枚举类型可用于构造错误条件。

标准语义参考：[cppreference `system_error`](https://en.cppreference.com/w/cpp/header/system_error)。

## 声明

```cpp
namespace asc::std {
template<class T> struct is_error_condition_enum;
} // namespace asc::std
```

## 约束说明

- 提供invalid_argument、result_out_of_range和value_too_large错误值、对应特征及枚举比较操作。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/system_error>

bool example()
{
    static_assert(asc::std::is_error_condition_enum<asc::std::errc>::value);
    static_assert(!asc::std::is_error_condition_enum<int>::value);
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_std_system_error.md)
