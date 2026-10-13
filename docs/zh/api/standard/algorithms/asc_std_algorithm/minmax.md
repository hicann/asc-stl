# asc::std::minmax

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

`asc::std::minmax`同时返回最小值和最大值；无策略形式在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class T, class Compare> [[nodiscard]] constexpr pair<const T&, const T&> minmax(const T& a, const T& b, Compare comp);
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr pair<const T&, const T&> minmax(const T& a, const T& b);
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 输入范围元素或参与运算的值类型。 |
| `Compare` | 定义元素先后顺序的比较对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `a` | 输入 | 提供“同时返回最小值和最大值”使用的对象引用；被引用对象须在调用期间有效。 |
| `b` | 输入 | 提供“同时返回最小值和最大值”使用的对象引用；被引用对象须在调用期间有效。 |
| `comp` | 输入 | 用于确定元素顺序的比较对象。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 输入范围元素或参与运算的值类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `a` | 输入 | 提供“同时返回最小值和最大值”使用的对象引用；被引用对象须在调用期间有效。 |
| `b` | 输入 | 提供“同时返回最小值和最大值”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `pair<const T &, const T &>` | 返回最小值和最大值。 |
| 原型2 | `pair<const T &, const T &>` | 返回最小值和最大值。 |

## 约束说明

- 提供顺序执行且不进行动态内存分配的重载。
- 标准执行策略重载采用顺序执行，并遵循标准允许的求值顺序。

## 调用示例

以下Host片段使用有效整数范围和足够容量的输出缓冲区演示调用。

```cpp
#include <asc/std/algorithm>

decltype(auto) example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    return asc::std::minmax(values[0], values[1]);
}
```

## 关联API

- [本头文件的接口列表](asc_std_algorithm.md)
