# asc::std::double_t

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

头文件路径为：`<asc/std/cmath>`。

`asc::std::double_t`标识浮点表达式的求值类型，不扩张本期Device数学函数精度。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 声明

```cpp
namespace asc::std {
using double_t = double;
} // namespace asc::std
```

## 约束说明

- 提供float函数重载、求值类型别名、比较函数、nanf和分类宏。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/cmath>
#include <asc/std/type_traits>

bool example()
{
    static_assert(asc::std::is_floating_point_v<asc::std::double_t>);
    asc::std::double_t half = 0.5;
    return half + half == 1.0;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
