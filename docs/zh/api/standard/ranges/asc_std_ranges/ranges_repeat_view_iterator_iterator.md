# asc::std::ranges::repeat_view::iterator::iterator

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

`repeat_view::iterator`的默认构造，产生与默认值关联的迭代器。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

此页说明repeat_view返回的迭代器。类型名须通过decltype(view.begin())取得，iterator只是下列类内声明摘要使用的所属类型名。

### 原型1

```cpp
constexpr iterator() = default;
```

### 原型2

```cpp
constexpr explicit iterator(const T* value,
    conditional_t<is_same_v<Bound, unreachable_sentinel_t>, ptrdiff_t, Bound> position = {})
    noexcept(is_nothrow_copy_constructible_v<
        conditional_t<is_same_v<Bound, unreachable_sentinel_t>, ptrdiff_t, Bound>>);
```

## 参数说明

原型1无参数。原型2的value指向被重复的存活T对象，position是保存在迭代器中的当前位置，默认0；无界特化使用ptrdiff_t，有界特化使用Bound。

## 返回值说明

构造函数没有返回值；迭代器解引用返回所保存对象的const T&。

## 约束说明

- 默认构造的迭代器不关联对象，不得解引用。
- 有效迭代器所保存的对象须覆盖其访问期，位置算术不得超出可表示范围；常规迭代器通过view.begin()取得。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/ranges>

bool example()
{
    auto view = asc::std::ranges::views::repeat(7, 3);
    using iterator_type = decltype(view.begin());
    const iterator_type first(view.begin());
    const iterator_type copied(first);
    return copied == first && *copied == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
