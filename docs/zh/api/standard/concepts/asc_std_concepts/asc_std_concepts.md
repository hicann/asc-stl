# 头文件asc/std/concepts

提供类型与表达式的编译期判定。C++17使用布尔变量模板，C++20及以上使用concept。

## 使用方式

```cpp
#include <asc/std/concepts>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::std::assignable_from](assignable_from.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::common_reference_with](common_reference_with.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::common_with](common_with.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::constructible_from](constructible_from.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::convertible_to](convertible_to.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::copy_constructible](copy_constructible.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::copyable](copyable.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::default_initializable](default_initializable.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::derived_from](derived_from.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::destructible](destructible.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::different_from](different_from.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::equality_comparable](equality_comparable.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::equality_comparable_with](equality_comparable_with.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::equivalence_relation](equivalence_relation.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::floating_point](floating_point.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::integral](integral.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::invocable](invocable.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::movable](movable.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::move_constructible](move_constructible.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::predicate](predicate.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::ranges::swap](ranges_swap.md) | 变量 | `C++17+` | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::regular](regular.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::regular_invocable](regular_invocable.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::relation](relation.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::same_as](same_as.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::semiregular](semiregular.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::signed_integral](signed_integral.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::strict_weak_order](strict_weak_order.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::swappable](swappable.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::swappable_with](swappable_with.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::totally_ordered](totally_ordered.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::totally_ordered_with](totally_ordered_with.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::unsigned_integral](unsigned_integral.md) | C++17：布尔变量模板；C++20+：概念 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
