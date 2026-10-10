# 头文件 asc/launch

提供在指定Stream上异步调用核函数，以及按Stream顺序提交Host回调函数（Host Callback）的功能

## 使用方式

```cpp
#include <asc/launch>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::aicore_launch_config](aicore_launch_config.md) | 类 | C++17+ | Host | Ascend 950 |
| [asc::aicore_launch_config::blocks](aicore_launch_config_blocks.md) | 变量 | C++17+ | Host | Ascend 950 |
| [asc::host_callback](host_callback.md) | 函数 | C++17+ | Host | Ascend 950 |
| [asc::host_callback_t](host_callback_t.md) | 类型别名 | C++17+ | Host | Ascend 950 |
| [asc::launch](launch.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::simt_launch_config](simt_launch_config.md) | 类 | C++17+ | Host | Ascend 950 |
| [asc::simt_launch_config::block](simt_launch_config_block.md) | 变量 | C++17+ | Host | Ascend 950 |
| [asc::simt_launch_config::dynamic_ub_bytes](simt_launch_config_dynamic_ub_bytes.md) | 变量 | C++17+ | Host | Ascend 950 |
| [asc::simt_launch_config::grid](simt_launch_config_grid.md) | 变量 | C++17+ | Host | Ascend 950 |
