# Header asc/functional

Value-returning extrema, input predicates, and operation-property queries. C++17 baseline with C++20 support.

## Usage

```cpp
#include <asc/functional>
```

## APIs (17 entries)

| API | Kind |
| --- | --- |
| [asc::maximum](maximum.md) | Class template |
| [asc::maximum::operator()](maximum_operator_call.md) | Member function |
| [asc::minimum](minimum.md) | Class template |
| [asc::minimum::operator()](minimum_operator_call.md) | Member function |
| [asc::equal_to_value](equal_to_value.md) | Class template |
| [asc::equal_to_value::equal_to_value](equal_to_value_equal_to_value.md) | Member function |
| [asc::equal_to_value::operator()](equal_to_value_operator_call.md) | Member function |
| [asc::always_true](always_true.md) | Class |
| [asc::always_true::operator()](always_true_operator_call.md) | Member function |
| [asc::always_false](always_false.md) | Class |
| [asc::always_false::operator()](always_false_operator_call.md) | Member function |
| [asc::is_associative_v](is_associative_v.md) | Variable template |
| [asc::is_commutative_v](is_commutative_v.md) | Variable template |
| [asc::has_identity_element_v](has_identity_element_v.md) | Variable template |
| [asc::has_absorbing_element_v](has_absorbing_element_v.md) | Variable template |
| [asc::identity_element](identity_element.md) | Function template |
| [asc::absorbing_element](absorbing_element.md) | Function template |

## Operation support table

Each template registers the matching typed form and the void transparent form. U denotes the five standard unsigned integer types, S their five signed counterparts, and I all standard integral types (including bool and character types; char8_t only in C++20). M/L are the maximum/lowest T values.

| Object template | T | Associative | Commutative | Identity | Absorbing |
| --- | --- | --- | --- | --- | --- |
| `asc::std::plus` | U | A | A | 0 | — |
| `asc::std::multiplies` | U | B | B | 1 | 0 |
| `asc::std::plus` | S | false | false | 0 | — |
| `asc::std::multiplies` | S | false | false | 1 | 0 |
| `asc::std::bit_and` | U | true | true | M | 0 |
| `asc::std::bit_or` | U | true | true | 0 | M |
| `asc::std::bit_xor` | U | true | true | 0 | — |
| `asc::std::logical_and` | bool | true | true | true | false |
| `asc::std::logical_or` | bool | true | true | false | true |
| `asc::maximum` | I | true | true | L | M |
| `asc::minimum` | I | true | true | M | L |

P=decltype(+T{}) is the promoted type. A requires unsigned P or M<=max(P)/2; B requires unsigned P or M<=max(P)/M. Compare exact nonnegative bounds without overflowing the registration expression. Convert every binary node back to T, including transparent standard operations returning a promoted type.

F(a,b)=T(Operator{}(a,b)) reads const lvalues. Associativity/commutativity require defined, closed operations throughout the full domain. Identities satisfy F(e,x)=F(x,e)=x and absorbing elements satisfy F(z,x)=F(x,z)=z; elements can be registered independently. Equivalence is built-in value equality.

Unlisted, cv/ref, mismatched, distinct host std, floating, low-precision, and user-defined pairs are false. User specialization is unsupported. false means no guarantee; element functions participate only for true has_* queries. Properties do not authorize discarding effects.

maximum/minimum compare once, prefer left on equivalence, and return values. Transparent calls compare original const lvalues before forwarding to the common value type. Mixed signedness and precision follow ordinary C++. Strict floating-point unordered comparisons select left and signed-zero ties retain the left sign, rather than fmin/fmax number-preference rules.

## Change notes

[Interface changes and migration](../../../../../release/functional_changes.md)
