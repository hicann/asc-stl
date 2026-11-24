# Standard library feature revisions

`<asc/std/version>` describes `asc::std`. Each standard name `__cpp_lib_x` maps to
`CANN_ASC_STL_LIB_x`, retaining the suffix spelling and standard `YYYYMML` integer.
For example, `__cpp_lib_type_identity` maps to `CANN_ASC_STL_LIB_type_identity == 201806L`.
These object-like macros support preprocessing and revision thresholds. Unsupported
features are undefined rather than defined as zero.

`CANN_ASC_STL_HAS_*` remains a 0/1 query for selected interface subsets, without a
full-feature conformance claim. `CANN_ASC_STL_DETAIL_*` is private implementation
vocabulary. Product release and extension information remains in `<asc/version>`;
release dates are not standard feature revision values.

Definitions describe the current translation unit's language, compiler builtins and
execution configuration. Unless stated otherwise, backports are queryable in C++17/20
on Host and AI Core SIMD/SIMT. Host support does not imply Device support. Supported
compilers are GCC, Clang and CANN BiSheng; builtin conditions are probed on the compiler.

## Reported revisions

Each standard name below maps to its public ASC-STL name by the rule above. The
reported value is the highest audited revision; a newer language mode does not
silently enable later revisions.

| Standard macro | Reported value | Feature header | Revision requirements and implementation | Definition condition |
| --- | --- | --- | --- | --- |
| `__cpp_lib_addressof_constexpr` | `201603L` | `<asc/std/memory>` | Constant true address, bypassing overloaded operator& | __builtin_addressof (or the GCC path) |
| `__cpp_lib_apply` | `201603L` | `<asc/std/tuple>` | Index expansion and INVOKE; excludes the 202506 metaprogramming additions | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_as_const` | `201510L` | `<asc/std/utility>` | Preserve lvalue identity and delete the const-rvalue overload | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_bit_cast` | `201806L` | `<asc/std/bit>` | Equal size, trivial-copy constraints, constant evaluation, nondefault-constructible destination | constexpr bit_cast builtin; absent for memcpy fallback |
| `__cpp_lib_bitops` | `201907L` | `<asc/std/bit>` | Counting, rotation and zero boundaries for unsigned integers | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_bool_constant` | `201505L` | `<asc/std/type_traits>` | integral_constant alias for Boolean constants | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_bounded_array_traits` | `201902L` | `<asc/std/type_traits>` | Bounded and unbounded array traits and variable templates | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_byte` | `201603L` | `<asc/std/cstddef>` | byte enum, bitwise/shift operators and to_integer | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_clamp` | `201603L` | `<asc/std/algorithm>` | Default/custom comparison and a reference to the selected argument | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_constexpr_numeric` | `201911L` | `<asc/std/numeric>` | Constant evaluation for accumulation, inner product, reduction, scans, adjacent difference and iota | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_endian` | `201907L` | `<asc/std/bit>` | little/big/native enum values from the current target byte order | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_exchange_function` | `201304L` | `<asc/std/utility>` | Move the old value, assign the replacement and return the old value | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_gcd_lcm` | `201606L` | `<asc/std/numeric>` | Mixed integral types, signs, zero and common result type | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_has_unique_object_representations` | `201606L` | `<asc/std/type_traits>` | Complete object-representation query and variable template | Compiler __has_unique_object_representations builtin |
| `__cpp_lib_int_pow2` | `202002L` | `<asc/std/bit>` | has_single_bit/bit_ceil/bit_floor/bit_width, including zero and boundaries | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_integer_comparison_functions` | `202002L` | `<asc/std/utility>` | Six signed/unsigned-safe comparisons and in_range | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_integer_sequence` | `201304L` | `<asc/std/utility>` | Integer/index sequences and generating aliases | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_integral_constant_callable` | `201304L` | `<asc/std/type_traits>` | constexpr call operator on integral constants | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_invoke` | `201411L` | `<asc/std/functional>` | Ordinary callables and member pointers with objects, pointers and reference_wrapper | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_invoke_r` | `202106L` | `<asc/std/functional>` | Constrained result conversion, void discard and noexcept | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_is_aggregate` | `201703L` | `<asc/std/type_traits>` | Aggregate query and variable template | Compiler __is_aggregate builtin |
| `__cpp_lib_is_constant_evaluated` | `201811L` | `<asc/std/type_traits>` | Distinguish manifest constant evaluation from runtime evaluation | Reliable is_constant_evaluated builtin; absent otherwise |
| `__cpp_lib_is_final` | `201402L` | `<asc/std/type_traits>` | final class query and variable template | Compiler __is_final builtin |
| `__cpp_lib_is_invocable` | `201703L` | `<asc/std/type_traits>` | INVOKE result, invocability/nothrow traits and variable templates | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_is_nothrow_convertible` | `201806L` | `<asc/std/type_traits>` | Implicit conversion exception query, including void and invalid conversions | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_is_null_pointer` | `201309L` | `<asc/std/type_traits>` | nullptr_t query, including cv qualifiers | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_is_scoped_enum` | `202011L` | `<asc/std/type_traits>` | Scoped enum query, safe for non-enums | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_is_swappable` | `201603L` | `<asc/std/type_traits>` | Bidirectional ADL swap, exception queries, non-swappable and void inputs | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_launder` | `201606L` | `<asc/std/new>` | Compiler object-lifetime/pointer optimization barrier | __builtin_launder (or the GCC path) |
| `__cpp_lib_logical_traits` | `201510L` | `<asc/std/type_traits>` | conjunction/disjunction/negation with lazy short-circuiting | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_make_from_tuple` | `201606L` | `<asc/std/tuple>` | Direct construction from forwarded tuple elements | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_make_reverse_iterator` | `201402L` | `<asc/std/iterator>` | Reverse iterator factory | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_not_fn` | `201603L` | `<asc/std/functional>` | Stored callable, four cv/ref call forms and failure cases; excludes 202306 stateless forms | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_raw_memory_algorithms` | `201606L` | `<asc/std/memory>` | Uninitialized move/default/value construction, destruction and rollback; excludes the 202411 constexpr revision | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_remove_cvref` | `201711L` | `<asc/std/type_traits>` | Remove references and top-level cv while preserving array shape | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_robust_nonmodifying_seq_ops` | `201304L` | `<asc/std/algorithm>` | Two-range equal/mismatch/is_permutation overloads | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_sample` | `201603L` | `<asc/std/algorithm>` | Input/forward dispatch and bounded uniform sampling | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_shift` | `201806L` | `<asc/std/algorithm>` | Classic shift_left/right with forward/bidirectional traversal; excludes 202202 ranges overloads | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_source_location` | `201907L` | `<asc/std/source_location>` | Immediate current, default/copy construction and four observers | Host C++20 with consteval and call-site builtins; absent in C++17/Device |
| `__cpp_lib_ssize` | `201902L` | `<asc/std/iterator>` | Signed sizes for containers and built-in arrays | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_to_address` | `201711L` | `<asc/std/memory>` | Raw pointers, pointer_traits customization and recursive operator-> | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_to_array` | `201907L` | `<asc/std/array>` | Copy/move built-in arrays, strip cv and reject multidimensional arrays | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_to_underlying` | `202102L` | `<asc/std/utility>` | constexpr/noexcept enum conversion to the exact underlying type | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_tuple_element_t` | `201402L` | `<asc/std/tuple>` | tuple_element alias and cv propagation | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_tuples_by_type` | `201304L` | `<asc/std/utility>`, `<asc/std/tuple>` | Type-based pair/tuple access with unique-type constraints and cv/ref preservation | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_type_identity` | `201806L` | `<asc/std/type_traits>` | Non-deduced type wrapper and alias | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_unreachable` | `202202L` | `<asc/std/utility>` | noreturn, noexcept unreachable marker | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_unwrap_ref` | `201811L` | `<asc/std/type_traits>` | reference_wrapper unwrapping and decay combination | C++17/20; Host, SIMD, SIMT |
| `__cpp_lib_void_t` | `201411L` | `<asc/std/type_traits>` | Map any valid type pack to void | C++17/20; Host, SIMD, SIMT |

## Withheld features

Documented subsets remain usable under their API contracts. This table does not remove or revise them. Adaptations without a standard feature macro use capability queries only.

| Standard macro suffix | Standard revisions | Gap / reason for withholding |
| --- | --- | --- |
| `span` | 202002; 202311 | Static-extent iterator/count and dynamic-to-static span conversions lack required explicitness; newer at is absent |
| `mdspan, submdspan` | 202207/202406; 202306/202411 | C++17/20 use operator(); standard multidimensional operator[] requires native language support, and slicing/layouts remain subsets |
| `expected` | 202202; 202211 | bad_expected_access exception interface is absent; monadic methods do not imply full support |
| `optional` | 201606; 202106; 202110; 202506 | Checked access through `value()` and the `bad_optional_access` exception are absent |
| `variant` | 201606; 202102; 202106 | No bad_variant_access; invalid access traps |
| `inplace_vector` | 202406 | Fixed-capacity subset lacks insert and the full standard exception surface |
| `allocate_at_least` | 202302 | Free-function backport lacks the standard allocator_traits member and standard allocator |
| `format` | 201907 and later | Selected formatting facilities do not cover format/wformat, locales and the full formatter protocol |
| `ranges` | 201911 and later | Views and selected ranges algorithms do not constitute the complete algorithm/protocol set |
| `philox_engine` | 202406 | Missing SeedSequence construction/seeding and stream I/O requirements |
| `math_constants` | 201907 | Variable templates specialize only float, not double/long double |
| `concepts` | 202002; 202207 | C++17 uses Boolean predicates; C++20 same_as lacks standard symmetric subsumption |
| `forward_like` | 202207 | Currently copies volatile from T; the standard merges const and reference category |
| `byteswap` | 202110 | Explicitly excludes bool, differing from the standard integral participation set |
| `array_constexpr` | 201603; 201811 | array lacks members such as at; constexpr traversal alone does not establish the revision |
| `nonmember_container_access` | 201411 | empty/data lack initializer_list overloads |
| `transformation_trait_aliases, type_trait_variable_templates` | 201304; 201510 | C++17 lacks family members including result_of_t and is_literal_type_v |
| `destroying_delete` | 201806 | Library tag alone does not enable the language mechanism for std::destroying_delete_t |
| `allocator_traits_is_always_equal` | 201411 | Explicit allocators and container propagation/exception contracts are subsets; vector move assignment is unconditionally noexcept |
| `scoped_lock, shared_mutex, shared_timed_mutex` | 201703; 201505; 201402 | Nonthrowing lock subsets/wrappers; scoped_lock terminates on try_lock exceptions, and full standard mutex types are absent |
| `atomic_*, barrier, latch, semaphore` | Per-macro standard revisions | Execution, type, waiting and scheduling adaptations remain subsets; no full-standard claim is added |
| `execution, parallel_algorithm` | 201603/201902; 201603 | Execution-policy vocabulary does not establish all standard parallel algorithm overloads |
| `chrono, string_view, to_chars, and other families` | Per-macro standard revisions | chrono and text/allocator interfaces are restricted; character conversion, associative-container and other revision-wide claims remain unestablished and undefined |

## Sources and maintenance

The fixed references are [N4861 (C++20) §17.3.2](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/n4861.pdf),
[N4950 (C++23) §17.3.2](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4950.pdf) and
[N5014 (August 2025 C++26 draft) §17.3.2](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2025/n5014.pdf),
[version.syn] and the relevant component clauses. Audit all requirements before raising a revision,
and update the definitions, table and tests together. In particular, not_fn 202306,
shift 202202 and raw memory algorithms 202411 do not follow from their older revisions.

Definitions are maintained centrally and shared by version and feature headers.
ASC-STL neither forwards Host version values nor defines Host __cpp_lib_* names;
both vocabularies can coexist in any include order. The retired
CANN_ASC_STL_ENABLE_LEGACY_STD_FEATURE_MACROS switch is inert. Migrate old checks to
CANN_ASC_STL_LIB_source_location / CANN_ASC_STL_LIB_unreachable, or retain HAS queries for subsets.

Checks cover both languages, independent/repeated/interleaved inclusion, Host macro
snapshots, missing builtins and revision thresholds, with independent calls through
public feature headers. Host C++20 source_location::current is consteval; C++17/Device
retain the constexpr subset and do not receive its standard revision macro.
Device compilation does not establish hardware runtime acceptance.

Coexistence tests probe each Host header for the selected compiler and record only
missing Host combinations as NOT_APPLICABLE. ASC revision, gate, macro isolation and
interface checks always run; a present Host header that fails preprocessing still fails the test.
