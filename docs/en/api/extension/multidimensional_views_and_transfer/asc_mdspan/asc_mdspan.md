# Header asc/mdspan

Provides non-owning multidimensional data views covering Host, GM, and UB in AI Core SIMD programming; supports Host-side data structure conversion when DLPack is available

## Usage

```cpp
#include <asc/mdspan>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::dlpack_tensor](dlpack_tensor.md) | Class template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::dstrides](dstrides.md) | Alias template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::dynamic_stride](dynamic_stride.md) | Variable | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::gm_accessor](gm_accessor.md) | Class template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::gm_mdspan](gm_mdspan.md) | Alias template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::host_accessor](host_accessor.md) | Class template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::host_mdspan](host_mdspan.md) | Alias template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_device_accessible_v](is_device_accessible_v.md) | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_gm_accessor_v](is_gm_accessor_v.md) | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_gm_mdspan_v](is_gm_mdspan_v.md) | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_host_accessible_v](is_host_accessible_v.md) | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_host_accessor_v](is_host_accessor_v.md) | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_host_mdspan_v](is_host_mdspan_v.md) | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_restrict_accessor_v](is_restrict_accessor_v.md) | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_restrict_mdspan_v](is_restrict_mdspan_v.md) | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_ub_accessor_v](is_ub_accessor_v.md) | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::is_ub_mdspan_v](is_ub_mdspan_v.md) | Variable template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::layout_stride_relaxed](layout_stride_relaxed.md) | Class | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::restrict_accessor](restrict_accessor.md) | Class template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::restrict_mdspan](restrict_mdspan.md) | Alias template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::steps](steps.md) | Alias template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::strides](strides.md) | Class template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::to_dlpack_tensor](to_dlpack_tensor.md) | Function template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::to_gm_mdspan](to_gm_mdspan.md) | Function template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::to_host_mdspan](to_host_mdspan.md) | Function template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::ub_accessor](ub_accessor.md) | Class template | C++17+ | See individual members or overloads | Ascend 950 |
| [asc::ub_mdspan](ub_mdspan.md) | Alias template | C++17+ | See individual members or overloads | Ascend 950 |
