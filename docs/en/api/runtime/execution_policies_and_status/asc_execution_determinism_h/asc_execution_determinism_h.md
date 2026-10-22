# Header asc/execution.determinism.h

Provides result-determinism requirements for parallel algorithms, used to specify whether identical inputs must produce repeatable results

## Usage

```cpp
#include <asc/execution.determinism.h>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::determinism](determinism.md) | Enum | C++17+ | Host | Ascend 950 |
| [asc::determinism::device_to_device](determinism_device_to_device.md) | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::determinism::not_guaranteed](determinism_not_guaranteed.md) | Enumerator | C++17+ | Host | Ascend 950 |
| [asc::determinism::run_to_run](determinism_run_to_run.md) | Enumerator | C++17+ | Host | Ascend 950 |
