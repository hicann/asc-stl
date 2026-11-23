# Headerasc/type_traits

Six Boolean trait families identify formats, equality/relocation conditions and native pointee qualifiers. Standard classification remains in asc::std.

| API |
| --- |
| [asc::is_bitwise_comparable](is_bitwise_comparable.md) |
| [asc::is_bitwise_comparable_v](is_bitwise_comparable_v.md) |
| [asc::is_trivially_relocatable](is_trivially_relocatable.md) |
| [asc::is_trivially_relocatable_v](is_trivially_relocatable_v.md) |
| [asc::is_low_precision](is_low_precision.md) |
| [asc::is_low_precision_v](is_low_precision_v.md) |
| [asc::is_extended_floating_point](is_extended_floating_point.md) |
| [asc::is_extended_floating_point_v](is_extended_floating_point_v.md) |
| [asc::is_packed_numeric](is_packed_numeric.md) |
| [asc::is_packed_numeric_v](is_packed_numeric_v.md) |
| [asc::is_address_space_qualified](is_address_space_qualified.md) |
| [asc::is_address_space_qualified_v](is_address_space_qualified_v.md) |

## Contract

All classes derive from asc::std::bool_constant; variables are exact projections of ::value. Byte equality concerns only const-lvalue equality, not ordering. A true equality warrant requires trivial copying, unique representations, and a pure nonthrowing comparison independent of addresses and mutable external state. Floating signed zero/NaN, padding and user equality must follow their actual semantics. Types without equality and all ten initial wrappers default to false.

Ordinary classes/unions default to false for both object properties. Relocation admits only non-cv standard scalars or registered numeric types with trivial copying, rvalue construction and destruction. Only these two class templates may be fully specialized for complete user-defined classes/unions; keep Boolean trait form and identical definitions visible before first use in every translation unit. Do not specialize variables, cv/ref, arrays, pointers or standard/ASC/SDK types. Format/address queries have no customization hook.

Format queries ignore top-level cv, but references, arrays and unregistered types are false. Byte equality forwards const and rejects volatile/references/arrays. Relocation rejects top-level cv/references/arrays. Void/functions are false. Direct object-property queries on incomplete classes/unions (including cv) diagnose; pointer queries require no complete pointee. Late specialization is unsupported and cross-TU inconsistency may be undiagnosable.

## Formats

| Types | Low precision | Extended scalar float | Packed |
| --- | --- | --- | --- |
| float16, bfloat16, float8_e4m3fn, float8_e5m2, hifloat8 | true | true | false |
| float8_e8m0, int4 | true | false | false |
| float4_e2m1x2, float4_e1m2x2, int4x2 | true | false | true |

Standard arithmetic, ordinary aggregates/arrays and unregistered formats are false. Format identity grants no arithmetic/conversion capability. The numeric_types registry is shared and fully visible before queries; conversion implementations and CANN Runtime are not included.

## Frontends and address qualification

Host requires no SDK and supports C++17/C++20. Native adaptation initially targets Ascend950/CANN9.2.0-beta.2/BiSheng15. Native half/BF16/FP8/HiFloat8/FP4x2 identities are registered independently; SIMD int4x2_t is also low-precision and packed. Its 9.2 class representation is not trivially copyable; newer distinct builtin representations follow their actual properties. Ordinary vectors such as ::int4 and half2 are unregistered.

Pure SIMT erases GM/UB spellings, so qualification is false; mixed SIMT VFs and SIMD control code retain them. Only the immediate pointee is tested, preserving its cv. If G is a GM pointer, G* is false and __gm__ G* is true. Legal object/void pointers are supported. Unsupported frontends/qualifiers, qualified objects/references, member/function pointers and views are false. Pointer values and validity are not inferred; memory shares the private type-space identity.

## Lifetime boundary

No relocation algorithm is supplied. With the C++17 N4659 baseline, legally construct the destination and release/reuse source storage; a trivial destructor/pseudo-destructor call alone is not assumed to end the source lifetime. C++20 implicit-creation operations such as memcpy/memmove require suitable types and subobjects, and end the source lifetime separately. Ordinary byte loops gain no general creation permission.

Callers provide aligned, accessible, nonoverlapping storage and valid lifetimes, exclude base/potentially-overlapping subobjects and invalid union members, and prevent double destruction. Self-referential/owning classes default to false. A user relocation warrant requires all three trivial properties and no address repair/additional lifetime effects. Compiler relocation builtins do not widen the default set.
