# asc::std::upper_bound

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

`asc::std::upper_bound`在已排序范围中寻找大于目标的首个位置；在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template <class ForwardIterator, class T, class Compare>
[[nodiscard]] constexpr ForwardIterator upper_bound(
    ForwardIterator first, ForwardIterator last, const T& value, Compare comp);
}  // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template <class ForwardIterator, class T>
[[nodiscard]] constexpr ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value);
}  // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 待查找分界值的类型，须能作为comp的实参与元素比较。 |
| `Compare` | 比较器类型；调用形式为comp(value, elem)，返回bool且满足严格弱序。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 已排序输入范围的起始迭代器或指针。 |
| `last` | 输入 | 已排序输入范围的结束位置，不包含该位置。 |
| `value` | 输入 | 待查找的分界值；查找首个满足comp(value, elem)的元素位置。 |
| `comp` | 输入 | 比较器，按调用形式comp(value, elem)返回bool，true表示value排在elem前；须满足严格弱序，与范围排序规则一致。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 输入范围元素或参与运算的值类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 已排序输入范围的起始迭代器或指针。 |
| `last` | 输入 | 已排序输入范围的结束位置，不包含该位置。 |
| `value` | 输入 | 待查找的分界值；查找首个大于该值的元素位置。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `ForwardIterator` | 返回符合条件的元素位置；未找到时返回输入范围的结束位置。 |
| 原型2 | `ForwardIterator` | 返回符合条件的元素位置；未找到时返回输入范围的结束位置。 |

## 约束说明

- 提供顺序执行且不进行动态内存分配的重载。

- 支持普通迭代器以及 Device 的 GM／UB 对象指针；返回迭代器或指针保留输入的地址空间。
- Device 原生指针范围长度不超过 `2147483647` 时使用按区间收敛的 32 位内部索引循环，不依赖标量位计数内建；更大范围和非指针迭代器使用通用实现，公共类型及比较规则不变。

## 调用示例

以下Host示例在局部范围仍有效时检查结果和输出；函数返回可独立判断的布尔值。

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    auto result = asc::std::upper_bound(values, values + 8, 5);
    return result == values + 5;
}
```

## 关联API

- [本头文件的接口列表](asc_std_algorithm.md)
