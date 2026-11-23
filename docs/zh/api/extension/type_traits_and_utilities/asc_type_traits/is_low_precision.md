# asc::is_low_precision

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

识别登记的低精度格式。十种ASC包装均为true，标准算术类型为false。

## 声明

```cpp
namespace asc {
template<class T> struct is_low_precision;
} // namespace asc
```

## 约束说明

最低C++17，同时支持C++20；完整类型、cv/ref、特化及编译条件见[本头约定](asc_type_traits.md)。

## 调用示例

```cpp
#include <asc/type_traits>

bool example()
{
    static_assert(asc::is_low_precision<asc::float16>::value);
    static_assert(asc::is_low_precision<const volatile asc::int4>::value);
    static_assert(!asc::is_low_precision<unsigned char>::value);
    return true;
}
```

## 关联API

- [asc/type_traits](asc_type_traits.md)
