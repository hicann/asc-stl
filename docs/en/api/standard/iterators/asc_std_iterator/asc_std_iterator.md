# Header asc/std/iterator

Provides iterators, iterator adaptors, iterator properties, and traversal helpers.

## Usage

```cpp
#include <asc/std/iterator>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::std::iter_swap](../../algorithms/asc_std_algorithm/iter_swap.md) | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::advance](advance.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::back_insert_iterator](back_insert_iterator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::back_insert_iterator::back_insert_iterator](back_insert_iterator_back_insert_iterator.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::back_insert_iterator::container_type](back_insert_iterator_container_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::back_insert_iterator::difference_type](back_insert_iterator_difference_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::back_insert_iterator::iterator_category](back_insert_iterator_iterator_category.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::back_insert_iterator::`operator*`](back_insert_iterator_operator_dereference.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::back_insert_iterator::`operator++`](back_insert_iterator_operator_increment.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::back_insert_iterator::`operator=`](back_insert_iterator_operator_assign.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::back_insert_iterator::pointer](back_insert_iterator_pointer.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::back_insert_iterator::reference](back_insert_iterator_reference.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::back_insert_iterator::value_type](back_insert_iterator_value_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::back_inserter](back_inserter.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::begin](begin.md) | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::bidirectional_iterator](bidirectional_iterator.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::bidirectional_iterator_tag](bidirectional_iterator_tag.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::cbegin](cbegin.md) | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::cend](cend.md) | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::common_iterator](common_iterator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::common_iterator::common_iterator](common_iterator_common_iterator.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::common_iterator::`operator*`](common_iterator_operator_dereference.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::common_iterator::`operator++`](common_iterator_operator_increment.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::common_iterator::`operator-`>](common_iterator_operator_arrow.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::common_iterator::`operator=`](common_iterator_operator_assign.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::contiguous_iterator](contiguous_iterator.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::contiguous_iterator_tag](contiguous_iterator_tag.md) | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::counted_iterator](counted_iterator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::counted_iterator::base](counted_iterator_base.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::counted_iterator::count](counted_iterator_count.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::counted_iterator::counted_iterator](counted_iterator_counted_iterator.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::counted_iterator::difference_type](counted_iterator_difference_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::counted_iterator::iterator_type](counted_iterator_iterator_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::counted_iterator::`operator*`](counted_iterator_operator_dereference.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::counted_iterator::`operator+`](counted_iterator_operator_plus.md) | Member and associated non-member functions | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::counted_iterator::`operator++`](counted_iterator_operator_increment.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::counted_iterator::`operator+=`](counted_iterator_operator_plus_assign.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::counted_iterator::`operator-`](counted_iterator_operator_minus.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::counted_iterator::`operator--`](counted_iterator_operator_decrement.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::counted_iterator::`operator-=`](counted_iterator_operator_minus_assign.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::counted_iterator::`operator-`>](counted_iterator_operator_arrow.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::counted_iterator::`operator=`](counted_iterator_operator_assign.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::counted_iterator::operator\[\]](counted_iterator_operator_subscript.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::crbegin](crbegin.md) | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::crend](crend.md) | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::data](data.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::default_sentinel](default_sentinel.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::default_sentinel_t](default_sentinel_t.md) | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::disable_sized_sentinel_for](disable_sized_sentinel_for.md) | Variable template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::distance](distance.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::empty](empty.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::end](end.md) | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::forward_iterator](forward_iterator.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::forward_iterator_tag](forward_iterator_tag.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::front_insert_iterator](front_insert_iterator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::front_insert_iterator::container_type](front_insert_iterator_container_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::front_insert_iterator::difference_type](front_insert_iterator_difference_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::front_insert_iterator::front_insert_iterator](front_insert_iterator_front_insert_iterator.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::front_insert_iterator::iterator_category](front_insert_iterator_iterator_category.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::front_insert_iterator::`operator*`](front_insert_iterator_operator_dereference.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::front_insert_iterator::`operator++`](front_insert_iterator_operator_increment.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::front_insert_iterator::`operator=`](front_insert_iterator_operator_assign.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::front_insert_iterator::pointer](front_insert_iterator_pointer.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::front_insert_iterator::reference](front_insert_iterator_reference.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::front_insert_iterator::value_type](front_insert_iterator_value_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::front_inserter](front_inserter.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::incrementable](incrementable.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::incrementable_traits](incrementable_traits.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::incrementable_traits::difference_type](incrementable_traits_difference_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::indirect_binary_predicate](indirect_binary_predicate.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::indirect_equivalence_relation](indirect_equivalence_relation.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::indirect_result_t](indirect_result_t.md) | Alias template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::indirect_strict_weak_order](indirect_strict_weak_order.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::indirect_unary_predicate](indirect_unary_predicate.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::indirectly_comparable](indirectly_comparable.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::indirectly_copyable](indirectly_copyable.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::indirectly_copyable_storable](indirectly_copyable_storable.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::indirectly_movable](indirectly_movable.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::indirectly_movable_storable](indirectly_movable_storable.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::indirectly_readable](indirectly_readable.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::indirectly_readable_traits](indirectly_readable_traits.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::indirectly_readable_traits::value_type](indirectly_readable_traits_value_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::indirectly_regular_unary_invocable](indirectly_regular_unary_invocable.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::indirectly_swappable](indirectly_swappable.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::indirectly_unary_invocable](indirectly_unary_invocable.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::indirectly_writable](indirectly_writable.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::input_iterator](input_iterator.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::input_iterator_tag](input_iterator_tag.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::input_or_output_iterator](input_or_output_iterator.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::insert_iterator](insert_iterator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::insert_iterator::container_type](insert_iterator_container_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::insert_iterator::difference_type](insert_iterator_difference_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::insert_iterator::insert_iterator](insert_iterator_insert_iterator.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::insert_iterator::iterator_category](insert_iterator_iterator_category.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::insert_iterator::`operator*`](insert_iterator_operator_dereference.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::insert_iterator::`operator++`](insert_iterator_operator_increment.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::insert_iterator::`operator=`](insert_iterator_operator_assign.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::insert_iterator::pointer](insert_iterator_pointer.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::insert_iterator::reference](insert_iterator_reference.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::insert_iterator::value_type](insert_iterator_value_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::inserter](inserter.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iter_common_reference_t](iter_common_reference_t.md) | Alias template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iter_difference_t](iter_difference_t.md) | Alias template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iter_move](iter_move.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iter_reference_t](iter_reference_t.md) | Alias template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iter_rvalue_reference_t](iter_rvalue_reference_t.md) | Alias template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iter_value_t](iter_value_t.md) | Alias template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iterator](iterator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iterator::difference_type](iterator_difference_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iterator::iterator_category](iterator_iterator_category.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iterator::pointer](iterator_pointer.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iterator::reference](iterator_reference.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iterator::value_type](iterator_value_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iterator_traits](iterator_traits.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iterator_traits::difference_type](iterator_traits_difference_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iterator_traits::iterator_category](iterator_traits_iterator_category.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iterator_traits::iterator_concept](iterator_traits_iterator_concept.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iterator_traits::pointer](iterator_traits_pointer.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iterator_traits::reference](iterator_traits_reference.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::iterator_traits::value_type](iterator_traits_value_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::make_move_iterator](make_move_iterator.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::make_reverse_iterator](make_reverse_iterator.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::mergeable](mergeable.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator](move_iterator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator::base](move_iterator_base.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator::difference_type](move_iterator_difference_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator::iterator_concept](move_iterator_iterator_concept.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator::iterator_type](move_iterator_iterator_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator::move_iterator](move_iterator_move_iterator.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator::`operator*`](move_iterator_operator_dereference.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator::`operator+`](move_iterator_operator_plus.md) | Member and associated non-member functions | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator::`operator++`](move_iterator_operator_increment.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator::`operator+=`](move_iterator_operator_plus_assign.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator::`operator-`](move_iterator_operator_minus.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator::`operator--`](move_iterator_operator_decrement.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator::`operator-=`](move_iterator_operator_minus_assign.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator::`operator-`>](move_iterator_operator_arrow.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator::`operator=`](move_iterator_operator_assign.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator::operator\[\]](move_iterator_operator_subscript.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator::pointer](move_iterator_pointer.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator::reference](move_iterator_reference.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_iterator::value_type](move_iterator_value_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_sentinel](move_sentinel.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_sentinel::base](move_sentinel_base.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_sentinel::move_sentinel](move_sentinel_move_sentinel.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::move_sentinel::`operator=`](move_sentinel_operator_assign.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::next](next.md) | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [`asc::std::operator!=` (move_iterator overload) (Function template)](operator_not_equal.md) | Function template | `C++17+` | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [`asc::std::operator-` (move_iterator/move_sentinel/common_iterator/counted_iterator/reverse_iterator overload) (Function template)](operator_minus.md) | Function template | `C++17+` | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [`asc::std::operator==` (move_iterator overload) (Function template)](operator_equal.md) | Function template | `C++17+` | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::output_iterator](output_iterator.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::output_iterator_tag](output_iterator_tag.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::permutable](permutable.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::prev](prev.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::projected](projected.md) | Alias template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::random_access_iterator](random_access_iterator.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::random_access_iterator_tag](random_access_iterator_tag.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::ranges::advance](ranges_advance.md) | Variable | `C++17+` | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::ranges::iter_swap](ranges_iter_swap.md) | Variable | `C++17+` | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::ranges::next](ranges_next.md) | Variable | `C++17+` | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::ranges::prev](ranges_prev.md) | Variable | `C++17+` | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::rbegin](rbegin.md) | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::rend](rend.md) | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator](reverse_iterator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::base](reverse_iterator_base.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::difference_type](reverse_iterator_difference_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::iterator_category](reverse_iterator_iterator_category.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::iterator_concept](reverse_iterator_iterator_concept.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::iterator_type](reverse_iterator_iterator_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::`operator*`](reverse_iterator_operator_dereference.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::`operator+`](reverse_iterator_operator_plus.md) | Member and associated non-member functions | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::`operator++`](reverse_iterator_operator_increment.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::`operator+=`](reverse_iterator_operator_plus_assign.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::`operator-`](reverse_iterator_operator_minus.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::`operator--`](reverse_iterator_operator_decrement.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::`operator-=`](reverse_iterator_operator_minus_assign.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::`operator-`>](reverse_iterator_operator_arrow.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::`operator=`](reverse_iterator_operator_assign.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::operator\[\]](reverse_iterator_operator_subscript.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::pointer](reverse_iterator_pointer.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::reference](reverse_iterator_reference.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::reverse_iterator](reverse_iterator_reverse_iterator.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::reverse_iterator::value_type](reverse_iterator_value_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::sentinel_for](sentinel_for.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::size](size.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::sized_sentinel_for](sized_sentinel_for.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::sortable](sortable.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::ssize](ssize.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::unreachable_sentinel](unreachable_sentinel.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::unreachable_sentinel_t](unreachable_sentinel_t.md) | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::weakly_incrementable](weakly_incrementable.md) | C++17: Boolean variable template; C++20+: Concept | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
