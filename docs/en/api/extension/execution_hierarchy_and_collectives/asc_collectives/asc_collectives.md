# Header asc/collectives

Provides thread block reduction, scan, broadcast, and condition checks in AI Core SIMT programming, as well as UB range reduction and scan in AI Core SIMD programming

## Usage

```cpp
#include <asc/collectives>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::block_all](block_all.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_any](block_any.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_broadcast](block_broadcast.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_collective_workspace](block_collective_workspace.md) | Class template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_collective_workspace::size](block_collective_workspace_size.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_collective_workspace_bytes](block_collective_workspace_bytes.md) | Function template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_exclusive_scan](block_exclusive_scan.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_inclusive_scan](block_inclusive_scan.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_reduce_add](block_reduce_add.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_reduce_max](block_reduce_max.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::block_reduce_min](block_reduce_min.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::make_block_collective_workspace](make_block_collective_workspace.md) | Function template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::ub_exclusive_scan](ub_exclusive_scan.md) | Function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::ub_inclusive_scan](ub_inclusive_scan.md) | Function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::ub_reduce_add](ub_reduce_add.md) | Function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::ub_reduce_max](ub_reduce_max.md) | Function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::ub_reduce_min](ub_reduce_min.md) | Function | C++17+ | AI Core SIMD programming | Ascend 950 |
