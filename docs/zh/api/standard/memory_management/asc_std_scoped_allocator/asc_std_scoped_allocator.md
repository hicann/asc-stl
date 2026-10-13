# 头文件asc/std/scoped_allocator

提供向嵌套对象传递外层分配器的功能

## 使用方式

```cpp
#include <asc/std/scoped_allocator>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::std::scoped_allocator_adaptor](scoped_allocator_adaptor.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::allocate](scoped_allocator_adaptor_allocate.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::const_pointer](scoped_allocator_adaptor_const_pointer.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::const_void_pointer](scoped_allocator_adaptor_const_void_pointer.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::construct](scoped_allocator_adaptor_construct.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::deallocate](scoped_allocator_adaptor_deallocate.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::destroy](scoped_allocator_adaptor_destroy.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::difference_type](scoped_allocator_adaptor_difference_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::inner_allocator](scoped_allocator_adaptor_inner_allocator.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::inner_allocator_type](scoped_allocator_adaptor_inner_allocator_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::is_always_equal](scoped_allocator_adaptor_is_always_equal.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::max_size](scoped_allocator_adaptor_max_size.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::`operator=`](scoped_allocator_adaptor_operator_assign.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::outer_allocator](scoped_allocator_adaptor_outer_allocator.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::outer_allocator_type](scoped_allocator_adaptor_outer_allocator_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::outer_traits](scoped_allocator_adaptor_outer_traits.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::pointer](scoped_allocator_adaptor_pointer.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::propagate_on_container_copy_assignment](scoped_allocator_adaptor_propagate_on_container_copy_assignment.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::propagate_on_container_move_assignment](scoped_allocator_adaptor_propagate_on_container_move_assignment.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::propagate_on_container_swap](scoped_allocator_adaptor_propagate_on_container_swap.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::rebind](scoped_allocator_adaptor_rebind.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::scoped_allocator_adaptor](scoped_allocator_adaptor_scoped_allocator_adaptor.md) | 构造函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::select_on_container_copy_construction](scoped_allocator_adaptor_select_on_container_copy_construction.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::size_type](scoped_allocator_adaptor_size_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::value_type](scoped_allocator_adaptor_value_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::scoped_allocator_adaptor::void_pointer](scoped_allocator_adaptor_void_pointer.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [`asc::std::operator==`（scoped_allocator）](operator_equal.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [`asc::std::operator!=`（scoped_allocator）](operator_not_equal.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
