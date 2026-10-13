# 头文件asc/execution.determinism.h

提供并行算法的结果确定性要求，用于指定相同输入是否需要产生可重复结果

## 使用方式

```cpp
#include <asc/execution.determinism.h>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::determinism](determinism.md) | 枚举 | C++17+ | Host | Ascend 950 |
| [asc::determinism::device_to_device](determinism_device_to_device.md) | 枚举值 | C++17+ | Host | Ascend 950 |
| [asc::determinism::not_guaranteed](determinism_not_guaranteed.md) | 枚举值 | C++17+ | Host | Ascend 950 |
| [asc::determinism::run_to_run](determinism_run_to_run.md) | 枚举值 | C++17+ | Host | Ascend 950 |
