# 标准算法和容器接口变化（未发布）

- `asc::std::char_traits::compare` 现在按码元顺序比较 `char16_t`、`char32_t` 和 `wchar_t` 字符序列。依赖默认字符特征的 `basic_string_view::compare` 也采用这一顺序。
- `asc::std::transform_inclusive_scan` 的文档说明了如何选择累加类型。将字节输入累加为 `int` 时，可传入 `int{0}` 作为初值。
- `asc::std::equal_range` 在前向范围上复用调用方提供的终点，省去一次遍历。使用过滤视图时可减少过滤谓词的调用。
- `asc::std::unordered_map` 和 `asc::std::unordered_set` 使用位掩码定位桶。插入触发扩桶时，复用待插入键的哈希值。
- `asc::std::deque` 一端弹出元素后，另一端的插入可以复用腾出的槽位，仍受容器容量与分配器可用空间限制。
- `asc::std::map` 和 `asc::std::set` 的迭代器支持后置 `it++`，返回推进前的位置。`asc::std::ranges::find` 可直接查找 set 的键，查找 map 的键时可传入键投影。
- GCC 9.5 在 Host C++17 模式下可以包含 `<asc/std/algorithm>` 并解析其依赖的作用域原子类型声明。

## Changes (unreleased)

- `asc::std::char_traits::compare` now compares `char16_t`, `char32_t`, and `wchar_t` sequences in code-unit order. `basic_string_view::compare` uses this order with the default character traits.
- The `asc::std::transform_inclusive_scan` documentation explains how to choose the accumulator type. To sum byte inputs in `int`, pass `int{0}` as the initial value.
- `asc::std::equal_range` reuses the supplied end iterator on forward ranges, saving one traversal. This can reduce filter predicate calls on a filtered view.
- `asc::std::unordered_map` and `asc::std::unordered_set` use a bit mask to select a bucket. An insertion that triggers a rehash reuses the new key’s hash value.
- After a pop at one end of `asc::std::deque`, an insertion at the other end can reuse the vacated slot, subject to container capacity and available allocator storage.
- Iterators of `asc::std::map` and `asc::std::set` support postfix `it++`, which returns the previous position. `asc::std::ranges::find` can search set keys directly or search map keys with a key projection.
- GCC 9.5 in Host C++17 mode can include `<asc/std/algorithm>` and parse the scoped atomic type declarations it depends on.
