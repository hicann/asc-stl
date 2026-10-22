# Header asc/std/memory

Provides smart pointers, allocators, object construction and destruction, and uninitialized memory operations

## Usage

```cpp
#include <asc/std/memory>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::std::addressof](addressof.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::align](align.md) | Function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocate_at_least](allocate_at_least.md) | Function template | `C++17+` | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocation_result](allocation_result.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocation_result::count](allocation_result_count.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocation_result::ptr](allocation_result_ptr.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_arg](allocator_arg.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_arg_t](allocator_arg_t.md) | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_arg_t::allocator_arg_t](allocator_arg_t_allocator_arg_t.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_arg_t::~allocator_arg_t](allocator_arg_t_destructor_allocator_arg_t.md) | Destructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits](allocator_traits.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::allocate](allocator_traits_allocate.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::allocate_at_least](allocator_traits_allocate_at_least.md) | Compatibility note | Not currently provided separately | See available alternatives on the page | Ascend 950 |
| [asc::std::allocator_traits::allocator_type](allocator_traits_allocator_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::const_pointer](allocator_traits_const_pointer.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::const_void_pointer](allocator_traits_const_void_pointer.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::construct](allocator_traits_construct.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::deallocate](allocator_traits_deallocate.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::destroy](allocator_traits_destroy.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::difference_type](allocator_traits_difference_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::is_always_equal](allocator_traits_is_always_equal.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::max_size](allocator_traits_max_size.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::pointer](allocator_traits_pointer.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::propagate_on_container_copy_assignment](allocator_traits_propagate_on_container_copy_assignment.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::propagate_on_container_move_assignment](allocator_traits_propagate_on_container_move_assignment.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::propagate_on_container_swap](allocator_traits_propagate_on_container_swap.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::rebind_alloc](allocator_traits_rebind_alloc.md) | Alias template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::rebind_traits](allocator_traits_rebind_traits.md) | Alias template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::select_on_container_copy_construction](allocator_traits_select_on_container_copy_construction.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::size_type](allocator_traits_size_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::value_type](allocator_traits_value_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::allocator_traits::void_pointer](allocator_traits_void_pointer.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::assume_aligned](assume_aligned.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::construct_at](construct_at.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::destroy](destroy.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::destroy_at](destroy_at.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::destroy_n](destroy_n.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::is_sufficiently_aligned](is_sufficiently_aligned.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::make_obj_using_allocator](make_obj_using_allocator.md) | Compatibility note | Not currently provided separately | See available alternatives on the page | Ascend 950 |
| [asc::std::pointer_traits](pointer_traits.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::pointer_traits::difference_type](pointer_traits_difference_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::pointer_traits::element_type](pointer_traits_element_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::pointer_traits::pointer](pointer_traits_pointer.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::pointer_traits::pointer_to](pointer_traits_pointer_to.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::pointer_traits::rebind](pointer_traits_rebind.md) | Alias template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::to_address](to_address.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uninitialized_construct_using_allocator](uninitialized_construct_using_allocator.md) | Compatibility note | Not currently provided separately | See available alternatives on the page | Ascend 950 |
| [asc::std::uninitialized_copy](uninitialized_copy.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uninitialized_copy_n](uninitialized_copy_n.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uninitialized_default_construct](uninitialized_default_construct.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uninitialized_default_construct_n](uninitialized_default_construct_n.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uninitialized_fill](uninitialized_fill.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uninitialized_fill_n](uninitialized_fill_n.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uninitialized_move](uninitialized_move.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uninitialized_move_n](uninitialized_move_n.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uninitialized_value_construct](uninitialized_value_construct.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uninitialized_value_construct_n](uninitialized_value_construct_n.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uses_allocator](uses_allocator.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uses_allocator_construction_args](uses_allocator_construction_args.md) | Compatibility note | Not currently provided separately | See available alternatives on the page | Ascend 950 |
| [asc::std::uses_allocator_v](uses_allocator_v.md) | Variable template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |

## Related Interfaces

[`asc::std::launder`](launder.md) is provided by `<asc/std/new>`; this header must be explicitly included when using it.
