# asc::std::basic_string

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

Header: `<asc/std/string>`.

`asc::std::basic_string` owns and manages a contiguous character sequence.

Standard semantics reference: [cppreference `string`](https://en.cppreference.com/w/cpp/header/string).

## Declaration

```cpp
namespace asc::std {
template<class CharT, class Traits, class Allocator> class basic_string;
} // namespace asc::std
```

## Constraints

- Null-terminated input may come from this object's character storage, including the object's whole string or a suffix. Appending preserves the source location when capacity growth is required; character-pointer assignment reads the source length before modifying the contents; re-obtain externally borrowed pointers invalidated by reallocation after the operation completes.
- The space required for the new length plus the terminating null character must be representable; if it cannot be represented, terminate is called, and allocator operations must still satisfy this type's non-throwing usage domain.

- Explicit-allocator construction of basic_string<char,Traits,A>.
- Assignment from a null-terminated const CharT* pointer (operator=(const CharT*), which appends after overwriting the original content); copy and move assignment are not delivered.
- append/push_back/clear for plain/local character sources.
- size/capacity/data/c_str/iteration/indexing and destruction.
- Only the sufficient-capacity and non-throwing exception domains.

## Toolchain Verification Boundaries in AI Core SIMT Programming

Under the pure AI Core SIMT programming `-O3` configuration of CANN 9.2.0-beta.2 and BiSheng 15.0.5 (compiler fingerprint `c4866a4d…f84c6a`), the combined single-kernel regression covering long strings, local arenas, and multiple self- or suffix-aliasing operations has not yet passed. The original C++17 workload has been compiled, but a device address access fault occurred on real hardware (device error 355; the log recorded a GM address exceeding 48 bits); a specific member function has not yet been uniquely identified, and it has not been shown that all local arenas are affected.

The current phased regression places long-string objects and arenas in GM and treats the allocation-free local short string optimization (SSO) scenario as a separate phase. The support tables and the local SSO results do not indicate that arbitrary local arena combinations have passed; such combinations must be verified separately on the target toolchain and runtime domain. The exact passing scope is governed by the complete validation records of the selected product version, and the phased results do not indicate that the original single-kernel form has been restored. See the [B027 runtime verification notes](../../../../../../test/support/README.md#b027-simt-phased-fixtures-for-full-semantics).

## Example

The following Host example uses an explicit allocator and observes operations whose input comes from the string itself while the string is alive.

```cpp
#include <memory>
#include <asc/std/string>

bool example()
{
    ::std::allocator<char> allocator;
    using S = asc::std::basic_string<char, asc::std::char_traits<char>, ::std::allocator<char>>;
    S value("abcdefghijklmnopqrstuvwx", allocator);
    value.append(value.data());
    if (value.size() != 48) return false;
    value = value.c_str();
    if (value.size() != 48) return false;
    value = value.data() + 1;
    return value.size() == 47 && value.front() == 'b' && value.back() == 'x';
}
```

## Related APIs

- [API list for this header](asc_std_string.md)
