# Header asc/memory_resource

Provides resource objects for device memory and Host pinned memory, non-owning references, and explicit allocation and deallocation interfaces.

## Usage

```cpp
#include <asc/memory_resource>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::device_memory_resource](device_memory_resource.md) | Class | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource::allocate](device_memory_resource_allocate.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource::deallocate](device_memory_resource_deallocate.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource::device_memory_resource](device_memory_resource_device_memory_resource.md) | Constructor | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource::device_ordinal](device_memory_resource_device_ordinal.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource::properties](device_memory_resource_properties.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref](device_memory_resource_ref.md) | Class | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::allocate](device_memory_resource_ref_allocate.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::deallocate](device_memory_resource_ref_deallocate.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::device_memory_resource_ref](device_memory_resource_ref_device_memory_resource_ref.md) | Constructor | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::device_ordinal](device_memory_resource_ref_device_ordinal.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::`operator!=`](device_memory_resource_ref_operator_not_equal.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::`operator==`](device_memory_resource_ref_operator_equal.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::properties](device_memory_resource_ref_properties.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::device_memory_resource_ref::valid](device_memory_resource_ref_valid.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::memory_resource_properties](memory_resource_properties.md) | Class | C++17+ | Host | Ascend 950 |
| [asc::memory_resource_properties::device_accessible](memory_resource_properties_device_accessible.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::memory_resource_properties::host_accessible](memory_resource_properties_host_accessible.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::memory_resource_properties::maximum_alignment](memory_resource_properties_maximum_alignment.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::memory_resource_properties::memory_resource_properties](memory_resource_properties_memory_resource_properties.md) | Constructor | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource](pinned_memory_resource.md) | Class | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource::allocate](pinned_memory_resource_allocate.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource::deallocate](pinned_memory_resource_deallocate.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource::pinned_memory_resource](pinned_memory_resource_pinned_memory_resource.md) | Constructor | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource::properties](pinned_memory_resource_properties.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref](pinned_memory_resource_ref.md) | Class | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::allocate](pinned_memory_resource_ref_allocate.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::deallocate](pinned_memory_resource_ref_deallocate.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::`operator!=`](pinned_memory_resource_ref_operator_not_equal.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::`operator==`](pinned_memory_resource_ref_operator_equal.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::pinned_memory_resource_ref](pinned_memory_resource_ref_pinned_memory_resource_ref.md) | Constructor | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::properties](pinned_memory_resource_ref_properties.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::pinned_memory_resource_ref::valid](pinned_memory_resource_ref_valid.md) | Member function | C++17+ | Host | Ascend 950 |
