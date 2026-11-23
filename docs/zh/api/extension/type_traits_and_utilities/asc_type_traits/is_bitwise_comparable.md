# asc::is_bitwise_comparable

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

`<asc/type_traits>`

查询对象字节相等能否替代const同类型左值的相等比较。默认仅考虑bool以外、可平凡复制且表示唯一的标准整数。volatile、引用、数组、浮点、枚举、指针、无相等运算及一般类默认false。

## 声明

```cpp
namespace asc {
template<class T> struct is_bitwise_comparable;
} // namespace asc
```

## 约束说明

最低C++17，同时支持C++20；完整类型、cv/ref、特化及编译条件见[本头约定](asc_type_traits.md)。

## 调用示例

```cpp
#include <asc/type_traits>

bool example()
{
    static_assert(asc::is_bitwise_comparable<unsigned char>::value);
    static_assert(!asc::is_bitwise_comparable<bool>::value);
    static_assert(!asc::is_bitwise_comparable<float>::value);
    return true;
}
```

## 关联API

- [asc/type_traits](asc_type_traits.md)
