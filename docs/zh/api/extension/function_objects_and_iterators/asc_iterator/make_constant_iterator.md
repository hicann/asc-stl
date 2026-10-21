# asc::make_constant_iterator

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

头文件路径为：`<asc/iterator>`。

`asc::make_constant_iterator`创建始终产生指定值的constant_iterator。

## 函数原型

```cpp
namespace asc {
template <class T, class Index = asc::std::ptrdiff_t>
constexpr asc::constant_iterator<T, Index> make_constant_iterator(T value, Index index = 0);
}  // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 常量迭代器保存并在每次解引用时提供的值类型。 |
| `Index` | 迭代器内部索引类型，默认ptrdiff_t：仅用于位置计数与迭代器差值。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 解引用恒返回的常量值：迭代器任意位置的读取结果均为该值。 |
| `index` | 输入 | 初始索引，默认0：仅影响迭代器位置与差值，不影响解引用结果。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::constant_iterator<T, Index>` | 返回保存调用方参数的迭代器适配器；所保存函数对象若捕获外部引用，该引用须在使用期间有效。 |

## 约束说明

- 提供惰性、非拥有的迭代器适配器及其工厂。
- 操作数必须在当前执行位置有效。

## 调用示例

以下Host示例使用具体输入，在对象存活期内检查结果。

```cpp
#include <asc/iterator>
bool example()
{
    auto iterator = asc::make_constant_iterator(7);
    ++iterator;
    return *iterator == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_iterator.md)
