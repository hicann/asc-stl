# asc::std::ranges::view_interface::operator[]

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

头文件路径为：`<asc/std/ranges>`。

`asc::std::ranges::view_interface::operator[]` 在调用方保证索引有效时访问指定元素。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

### 原型 1

```cpp
template<class RARange> constexpr decltype(auto) asc::std::ranges::view_interface::operator[](range_difference_t<RARange> index);
```

### 原型 2

```cpp
template<class RARange> constexpr decltype(auto) asc::std::ranges::view_interface::operator[](range_difference_t<RARange> index) const;
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `RARange` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `index` | 输入 | 提供“在调用方保证索引有效时访问指定元素”所需的输入对象；类型须满足所选原型约束。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `RARange` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `index` | 输入 | 提供“在调用方保证索引有效时访问指定元素”所需的输入对象；类型须满足所选原型约束。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `decltype(auto)` | 返回指定索引处的元素引用或代理值；索引必须有效。 |
| 原型 2 | `decltype(auto)` | 返回指定索引处的元素引用或代理值；索引必须有效。 |

## 约束说明

- C++20 视图不进行动态内存分配
- owning_view 仅拥有调用方传入的范围对象，不产生额外分配

## 调用示例

以下 Host 片段使用具体范围或访问器演示调用；底层存储在调用期间须保持有效。

```cpp
#include <asc/std/ranges>

decltype(auto) example()
{
    int values[4] = {1, 2, 3, 4};
    asc::std::ranges::ref_view<int[4]> view(values);
    return view[0];
}
```
