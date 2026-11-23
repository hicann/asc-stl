# asc::static_for

## Product Support

<!-- npu="950" id1 -->
- Ascend 950PR&950DT series products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 series products: Not supported
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2 series products: Not supported
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference series products AI Core: Not supported
<!-- end id5 -->
<!-- npu="310p" id6 -->
- Atlas inference series products Vector Core: Not supported
<!-- end id6 -->
<!-- npu="910" id7 -->
- Atlas training series products: Not supported
<!-- end id7 -->

## Description

Header: `<asc/utility>`.

`static_for` generates an ordered sequence of calls. Each call receives an `asc::std::integral_constant<IndexType, I>` whose `value` can be a template argument. Standard integer sequences represent indices; a runtime loop variable cannot supply this template argument.

The indices are determined at compile time, while callbacks may execute at runtime. A call can also be constant-evaluated when it satisfies the C++17/C++20 constant-expression rules. No instruction shape or performance improvement is guaranteed.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
template <auto Size, class Operator, class... Args>
constexpr void static_for(Operator&& operation, Args&&... args) noexcept(
    noexcept(static_for<decltype(Size), Size>(operation, static_cast<Args&&>(args)...)));
}  // namespace asc
```

### Prototype 2

```cpp
namespace asc {
template <auto Start, decltype(Start) End, decltype(Start) Step = decltype(Start){1}, class Operator, class... Args>
constexpr void static_for(Operator&& operation, Args&&... args) noexcept(
    noexcept(static_for<decltype(Start), Start, End, Step>(operation, static_cast<Args&&>(args)...)));
}  // namespace asc
```

### Prototype 3

```cpp
namespace asc {
template <class IndexType, IndexType Start, IndexType End, IndexType Step = IndexType{1}, class Operator, class... Args>
constexpr void static_for(Operator&& operation, Args&&... args) noexcept(
    noexcept(detail::static_for_range<IndexType, Start, End, Step>(operation, static_cast<Args&&>(args)...)));
}  // namespace asc
```

### Prototype 4

```cpp
namespace asc {
template <class SizeType, SizeType Size, class Operator, class... Args>
constexpr void static_for(Operator&& operation, Args&&... args) noexcept(
    noexcept(detail::static_for_count<SizeType, Size>(operation, static_cast<Args&&>(args)...)));
}  // namespace asc
```

## Parameters

| Parameter | Meaning |
| --- | --- |
| `Size` | Count endpoint: visit `[0, Size)`; a nonpositive count is empty. |
| `Start`, `End`, `Step` | Included start, excluded endpoint, and step, defaulting to 1. |
| `IndexType` / `SizeType` | Explicit index type; automatic forms deduce it from `Start` / `Size`. |
| `operation` | Borrowed callable, invoked repeatedly as the same lvalue. |
| `args...` | Additional arguments passed as `Args&&` on every call; the library neither copies nor retains them. |

## Return Value

Returns `void` and discards callback results. Each call and destruction of its temporary result finish before the next call. The function is `noexcept(true)` exactly when all visited call expressions, including argument construction and temporary-result destruction, are nonthrowing. An empty sequence is nonthrowing. Host exceptions propagate and prevent later calls.

## Constraints

- Requires C++17 and supports C++20. Indices are unqualified `signed char`, `short`, `int`, `long`, `long long`, or their unsigned counterparts, including aliases such as `size_t`. Plain `char`, `bool`, character types, enums, floating-point types, and extended integers are excluded from overload resolution.
- `End` and `Step` have the index type and must satisfy converted constant-expression rules. Unsigned indices cannot express a negative step; use a signed index for descending ranges.
- A positive step visits indices `< End`; a negative step visits indices `> End`, starting at `Start`. For example, `<1, 8, 3>` visits `1, 4, 7`, and `<5, 0, -2>` visits `5, 3, 1`. Equal endpoints or a mismatched direction produce an empty sequence. A zero step is always diagnosed.
- Only visited indices are formed. The mathematical successor after the last call need not be representable. Distance and minimum-negative-step calculations avoid signed overflow. Sequence length must fit `size_t` and compiler resource limits.
- The callable is borrowed without copying or moving and is invoked as an lvalue. A callable with only `operator() &&` requires an adapter. Calls use direct function-call syntax rather than member-pointer `invoke` semantics.
- The same rvalue argument is forwarded repeatedly. If a callback moves from it, later calls observe that moved-from state. Pass an lvalue or accept a const reference for repeated reads; construct a fresh value inside the callback when required.
- An empty sequence does not instantiate a callback expression or require a callable. Argument expressions and caller-owned temporary construction/destruction still occur normally.
- Host inclusion needs no SDK. SIMT and scalar SIMD calls require the callback, arguments, and storage accesses to be valid in that execution context. Device exception recovery and inter-thread synchronization are not provided.

## Example

This Host example uses each constant index as a `get<I>` template argument and checks runtime writes.

```cpp
#include <asc/utility>
#include <asc/std/tuple>

bool example()
{
    asc::std::tuple<int, float, long> fields{1, 2.0f, 3L};
    asc::static_for<3>([&](auto index) {
        asc::std::get<decltype(index)::value>(fields) = 0;
    });
    int sequence = 0;
    asc::static_for<1, 8, 3>([&](auto index) { sequence = sequence * 10 + index.value; });
    return asc::std::get<0>(fields) == 0 && asc::std::get<1>(fields) == 0.0f &&
        asc::std::get<2>(fields) == 0L && sequence == 147;
}
```

## Related APIs

- [Header API list](asc_utility.md)
