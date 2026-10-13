# asc::make_shuffle_iterator

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

`asc::make_shuffle_iterator`创建按确定性映射重排访问顺序的shuffle_iterator。

## 函数原型

```cpp
namespace asc {
template<class Bijection, class Index = asc::std::size_t> constexpr asc::shuffle_iterator<Index, Bijection> make_shuffle_iterator(Bijection bijection, Index start = 0);
} // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Bijection` | 确定性映射对象类型：以当前索引为输入计算重排后的访问结果。 |
| `Index` | 迭代器内部游标的索引类型，默认size_t。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `bijection` | 输入 | 确定性映射对象：解引用与下标结果为bijection(当前索引)。 |
| `start` | 输入 | 游标起始索引，默认0：随迭代递增并作为bijection的输入。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::shuffle_iterator<Index, Bijection>` | 返回保存调用方参数的迭代器适配器；底层范围须在使用期间保持有效。 |

## 约束说明

- 提供惰性、非拥有的迭代器适配器及其工厂。
- 操作数必须在当前执行位置有效。

## 调用示例

以下片段使用具体数组和可调用对象构造迭代器。实际使用时底层范围须保持有效。

```cpp
#include <asc/iterator>
#include <asc/std/cstddef>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

decltype(auto) example()
{
    int values[4] = {1, 2, 3, 4};
    int indices[4] = {3, 2, 1, 0};
    return asc::make_shuffle_iterator([](asc::std::size_t index) { return index; }, asc::std::size_t{0});
}
```

## 关联API

- [本头文件的接口列表](asc_iterator.md)
