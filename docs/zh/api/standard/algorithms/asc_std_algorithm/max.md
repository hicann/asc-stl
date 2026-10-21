# asc::std::max

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

头文件路径为：`<asc/std/algorithm>`。

`asc::std::max`按比较关系返回较大值的引用；在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template <class T, class Compare>
[[nodiscard]] constexpr const T& max(const T& left, const T& right, Compare compare);
}  // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template <class T>
[[nodiscard]] constexpr const T& max(const T& left, const T& right);
}  // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 参与比较求较大值的操作数类型。 |
| `Compare` | 比较器类型；调用形式为compare(a, b)，返回bool。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与比较求较大值的左操作数；与right等价时返回本操作数。 |
| `right` | 输入 | 参与比较求较大值的右操作数。 |
| `compare` | 输入 | 比较器，按调用形式compare(left, right)返回bool，true表示left小于right；返回两者中较大者。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 参与比较求较大值的操作数类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与比较求较大值的左操作数；与right等价时返回本操作数。 |
| `right` | 输入 | 参与比较求较大值的右操作数。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `const T &` | 返回较大值的引用。 |
| 原型2 | `const T &` | 返回较大值的引用。 |

## 约束说明

- 提供顺序执行且不进行动态内存分配的重载。

## 调用示例

以下Host示例在局部范围仍有效时检查结果和输出；函数返回可独立判断的布尔值。

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    const auto& result = asc::std::max(values[0], values[1]);
    return &result == values + 1 && result == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_algorithm.md)
