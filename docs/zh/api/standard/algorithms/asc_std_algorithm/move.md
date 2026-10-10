# asc::std::move

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

头文件路径为：`<asc/std/algorithm>`、`<asc/std/utility>`。

`asc::std::move` 的一参数形式把对象转换为保留原类型限定的右值引用；三参数形式把输入范围的元素按顺序移动到输出范围。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型 1

```cpp
template<class T> [[nodiscard]] constexpr asc::std::remove_reference_t<T>&& asc::std::move(T&& value) noexcept;
```

此原型对应头文件：`<asc/std/utility>`。

### 原型 2

```cpp
template<class InputIterator, class OutputIterator> constexpr OutputIterator asc::std::move(InputIterator first, InputIterator last, OutputIterator result);
```

此原型对应头文件：`<asc/std/algorithm>`。

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 待进行值类别转换的对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待转换为右值引用的对象；返回引用不延长对象生命周期。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型。 |
| `OutputIterator` | 写入目标范围的迭代器类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器。 |
| `last` | 输入 | 输入范围的结束迭代器，不包含该位置。 |
| `result` | 输出 | 输出范围的起始迭代器；目标存储须有足够容量。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `asc::std::remove_reference_t<T>&&` | 返回引用同一对象的右值引用；该引用不延长原对象生命周期。 |
| 原型 2 | `OutputIterator` | 返回输出范围中最后一个写入元素之后的位置。 |

## 约束说明

- 一参数形式只进行值类别转换，返回引用不延长原对象生命周期
- 三参数形式要求 [first, last) 是有效范围、输出范围容量充足，且源与目标不得以违反标准前置条件的方式重叠。

## 调用示例

以下 Host 片段分别检查右值引用转换和范围移动的可观察结果。

```cpp
#include <asc/std/algorithm>

#include <asc/std/utility>

bool example()
{
    int value = 3;
    int&& reference = asc::std::move(value);
    reference = 4;

    int input[] = {1, 2, 3};
    int output[3] = {};
    const auto end = asc::std::move(input, input + 3, output);
    return value == 4 && end == output + 3 && output[2] == 3;
}
```
