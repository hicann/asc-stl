# asc::std::cend

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

头文件路径为：`<asc/std/iterator>`。

`asc::std::cend`取得范围尾后常量迭代器。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

```cpp
namespace asc::std {
template<class C> constexpr auto cend(const C& c) noexcept(noexcept(asc::std::end(c))) -> decltype(asc::std::end(c));
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `C` | 被查询数组或容器的类型，须提供对应的范围访问操作。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `c` | 输入 | 提供“取得范围尾后常量迭代器”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `decltype(asc::std::end(c))` | 返回范围尾后常量迭代器。 |

## 约束说明

- 支持非I/O范围、数组和用户容器。

## 调用示例

以下Host片段使用具体数组或显式容器演示调用；迭代器须保持在有效范围内。

```cpp
#include <asc/std/iterator>

decltype(auto) example()
{
    int values[4] = {1, 2, 3, 4};
    return asc::std::cend(values);
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
