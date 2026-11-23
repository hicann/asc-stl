# asc::in_range

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

头文件路径为：`<asc/utility>`。

检查 `value` 是否位于包含两端点的数值闭区间 `[first, last]`。标准 `asc::std::in_range<R>(value)` 判断整数能否由类型 `R` 表示，两者用途不同。

## 函数原型

```cpp
namespace asc {
template <class T>
constexpr bool in_range(T value, T first, T last) noexcept;
}  // namespace asc
```

## 参数说明

| 参数 | 含义 |
| --- | --- |
| `T` | 三参数推导为相同的受支持数值类型，不进行公共类型推导。 |
| `value` | 待检查的数值，按值传入。 |
| `first`、`last` | 包含在区间内的下、上端点；顺序颠倒时返回 false。 |

## 返回值说明

先比较 `first <= value`，为 true 时再比较 `value <= last`。返回 `bool`，不进行减法或区间外的整数转换。端点相等时只接受该值；`first > last` 返回 false。

任一浮点输入为 NaN 时返回 false；无穷按正常顺序比较；正负零相等。编译选项须保留这些浮点比较语义。内建比较不抛 C++ 异常，因此本接口无条件 `noexcept`；满足语言规则时可常量求值。

## 约束说明

- 最低 C++17，支持 C++20。整数仅包括 `signed char`、`short`、`int`、`long`、`long long` 及其无符号对应类型。Host 还支持 `float`、`double`、`long double`，Device 浮点只支持 `float`。
- 普通 `char`、`bool`、字符专用类型、枚举、指针、用户比较类型及扩展整型不参与重载。参数推导忽略顶层 cv；显式指定 `T` 时由调用方负责普通参数转换的精度、可表示性及异常。
- Host 独立包含无需 CANN SDK。Device 用于受支持的 SIMT 或 SIMD 标量上下文；类型及浮点比较须在该位置有效，无异常恢复。

## 调用示例

```cpp
#include <asc/utility>

bool verify_example()
{
    return asc::in_range(4, 1, 4) && !asc::in_range(4, 5, 1) && !asc::in_range(8, 1, 4);
}
```

## 关联API

- [本头文件的接口列表](asc_utility.md)
