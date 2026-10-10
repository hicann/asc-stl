# 头文件 asc/std/memory

提供智能指针、分配器（allocator）、对象构造与销毁以及未初始化内存操作

## 使用方式

```cpp
#include <asc/std/memory>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::std::addressof](addressof.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::align](align.md) | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocation_result](allocation_result.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocation_result::count](allocation_result_count.md) | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocation_result::ptr](allocation_result_ptr.md) | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_arg](allocator_arg.md) | 变量 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_arg_t](allocator_arg_t.md) | 类 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_arg_t::allocator_arg_t](allocator_arg_t_allocator_arg_t.md) | 构造函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_arg_t::~allocator_arg_t](allocator_arg_t_destructor_allocator_arg_t.md) | 析构函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits](allocator_traits.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::allocate](allocator_traits_allocate.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::allocate_at_least](allocator_traits_allocate_at_least.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::allocator_type](allocator_traits_allocator_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::const_pointer](allocator_traits_const_pointer.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::const_void_pointer](allocator_traits_const_void_pointer.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::construct](allocator_traits_construct.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::deallocate](allocator_traits_deallocate.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::destroy](allocator_traits_destroy.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::difference_type](allocator_traits_difference_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::is_always_equal](allocator_traits_is_always_equal.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::max_size](allocator_traits_max_size.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::pointer](allocator_traits_pointer.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::propagate_on_container_copy_assignment](allocator_traits_propagate_on_container_copy_assignment.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::propagate_on_container_move_assignment](allocator_traits_propagate_on_container_move_assignment.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::propagate_on_container_swap](allocator_traits_propagate_on_container_swap.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::rebind_alloc](allocator_traits_rebind_alloc.md) | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::rebind_traits](allocator_traits_rebind_traits.md) | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::select_on_container_copy_construction](allocator_traits_select_on_container_copy_construction.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::size_type](allocator_traits_size_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::value_type](allocator_traits_value_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::allocator_traits::void_pointer](allocator_traits_void_pointer.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::assume_aligned](assume_aligned.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::construct_at](construct_at.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::destroy](destroy.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::destroy_at](destroy_at.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::destroy_n](destroy_n.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::is_sufficiently_aligned](is_sufficiently_aligned.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::launder](launder.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::make_obj_using_allocator](make_obj_using_allocator.md) | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pointer_traits](pointer_traits.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pointer_traits::difference_type](pointer_traits_difference_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pointer_traits::element_type](pointer_traits_element_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pointer_traits::pointer](pointer_traits_pointer.md) | 类型别名 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pointer_traits::pointer_to](pointer_traits_pointer_to.md) | 成员函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::pointer_traits::rebind](pointer_traits_rebind.md) | 别名模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::to_address](to_address.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_construct_using_allocator](uninitialized_construct_using_allocator.md) | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_copy](uninitialized_copy.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_copy_n](uninitialized_copy_n.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_default_construct](uninitialized_default_construct.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_default_construct_n](uninitialized_default_construct_n.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_fill](uninitialized_fill.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_fill_n](uninitialized_fill_n.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_move](uninitialized_move.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_move_n](uninitialized_move_n.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_value_construct](uninitialized_value_construct.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uninitialized_value_construct_n](uninitialized_value_construct_n.md) | 函数模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uses_allocator](uses_allocator.md) | 类模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uses_allocator_construction_args](uses_allocator_construction_args.md) | 函数 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
| [asc::std::uses_allocator_v](uses_allocator_v.md) | 变量模板 | C++17+ | Host、AI Core SIMD 编程、AI Core SIMT 编程 | Ascend 950 |
