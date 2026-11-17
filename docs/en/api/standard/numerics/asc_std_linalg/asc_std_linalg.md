# Header asc/std/linalg

Provides non-owning vector and matrix view transformations: scaling, conjugation, transposition, and conjugate transposition. The delivered subset does not include matrix multiplication, matrix-vector multiplication, inner-product, or norm-reduction algorithms; callers implement those computations.

Composed views apply transformations when elements are read, without allocating or filling a transformed temporary matrix. For example, the [conjugate-transpose covariance example](linalg_conjugate_transposed.md) uses `scaled(1/N, conjugate_transposed(A))` to express `Aᴴ/N`, then computes `AᴴA/N` with explicit reduction loops. Views borrow the original storage and must be used while that storage remains valid. Execution-space support for a composed call also depends on its element type, accessor, and any mathematical functions it calls.

## Usage

```cpp
#include <asc/std/linalg>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::std::linalg::conjugate_transposed](linalg_conjugate_transposed.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::conjugated](linalg_conjugated.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::conjugated_accessor](linalg_conjugated_accessor.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::access](linalg_conjugated_accessor_access.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::conjugated_accessor](linalg_conjugated_accessor_conjugated_accessor.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::data_handle_type](linalg_conjugated_accessor_data_handle_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::element_type](linalg_conjugated_accessor_element_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::nested_accessor](linalg_conjugated_accessor_nested_accessor.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::offset](linalg_conjugated_accessor_offset.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::offset_policy](linalg_conjugated_accessor_offset_policy.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::conjugated_accessor::reference](linalg_conjugated_accessor_reference.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::layout_transpose](linalg_layout_transpose.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::layout_transpose::mapping](linalg_layout_transpose_mapping.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::layout_transpose::nested_layout_type](linalg_layout_transpose_nested_layout_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::scaled](linalg_scaled.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::scaled_accessor](linalg_scaled_accessor.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::scaled_accessor::access](linalg_scaled_accessor_access.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::scaled_accessor::data_handle_type](linalg_scaled_accessor_data_handle_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::scaled_accessor::element_type](linalg_scaled_accessor_element_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::scaled_accessor::nested_accessor](linalg_scaled_accessor_nested_accessor.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::scaled_accessor::offset](linalg_scaled_accessor_offset.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::scaled_accessor::offset_policy](linalg_scaled_accessor_offset_policy.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::scaled_accessor::reference](linalg_scaled_accessor_reference.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::scaled_accessor::scaled_accessor](linalg_scaled_accessor_scaled_accessor.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::scaled_accessor::scaling_factor](linalg_scaled_accessor_scaling_factor.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linalg::transposed](linalg_transposed.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
