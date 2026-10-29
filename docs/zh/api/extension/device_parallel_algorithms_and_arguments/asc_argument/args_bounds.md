# asc::args::bounds

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

头文件路径为：`<asc/argument>`。

`asc::args::bounds`创建编译期或运行期参数边界对象。

## 函数原型

### 原型1

```cpp
namespace asc::args {
template <auto Lower, auto Upper>
constexpr asc::args::static_bounds<Lower, Upper> bounds() noexcept;
}  // namespace asc::args
```

### 原型2

```cpp
namespace asc::args {
template <class T>
constexpr asc::args::runtime_bounds<T> bounds(T lower, T upper) noexcept;
}  // namespace asc::args
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Lower` | 编译期边界下限：作为static_bounds<Lower, Upper> 的lower()，要求Lower ≤ Upper。 |
| `Upper` | 编译期边界上限：作为static_bounds<Lower, Upper> 的upper()。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 运行期边界值的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lower` | 输入 | 运行期边界下限：存入返回的runtime_bounds<T> 并经lower()查询。 |
| `upper` | 输入 | 运行期边界上限：存入返回的runtime_bounds<T> 并经upper()查询。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `asc::args::static_bounds<Lower, Upper>` | 返回编译期或运行期参数边界对象。 |
| 原型2 | `asc::args::runtime_bounds<T>` | 返回编译期或运行期参数边界对象。 |

## 约束说明

- 运行期边界按值保存，调用方须保证lower不大于upper；构造或查询不执行参数范围检查。编译期bounds的Lower必须不大于Upper。

- 使用C++17，可在Host、AI Core SIMD编程 和AI Core SIMT编程中使用。

## 调用示例

以下Host示例使用具体类型或维度，检查独立的预期值；不查询正在运行的Device执行上下文。

```cpp
#include <asc/argument>
#include <asc/std/type_traits>

bool example()
{
    constexpr auto fixed = asc::args::bounds<0, 10>();
    static_assert(asc::std::is_same_v<decltype(fixed), const asc::args::static_bounds<0, 10>>);
    static_assert(fixed.lower() == 0 && fixed.upper() == 10);
    const auto dynamic = asc::args::bounds(0, 10);
    return dynamic.lower() == 0 && dynamic.upper() == 10;
}
```

## 关联API

- [本头文件的接口列表](asc_argument.md)
