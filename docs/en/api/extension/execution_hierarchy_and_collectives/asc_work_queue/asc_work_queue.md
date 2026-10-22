# Header asc/work_queue

Acquires non-overlapping work ranges for sub-blocks in AI Core SIMD programming and warps in AI Core SIMT programming, based on a GM atomic cursor provided by the caller

## Usage

```cpp
#include <asc/work_queue>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::acquire_work](acquire_work.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::make_work_queue](make_work_queue.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::work_chunk](work_chunk.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::work_cursor](work_cursor.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::work_queue_ref](work_queue_ref.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
