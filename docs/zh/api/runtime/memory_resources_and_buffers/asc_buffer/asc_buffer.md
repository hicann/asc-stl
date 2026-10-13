# 头文件asc/buffer

提供基于指定内存资源创建并管理连续内存的缓冲区（Buffer）

## 使用方式

```cpp
#include <asc/buffer>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::device_buffer](device_buffer.md) | 类模板 | C++17+ | Host | Ascend 950 |
| [asc::make_device_buffer](make_device_buffer.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::make_pinned_buffer](make_pinned_buffer.md) | 函数模板 | C++17+ | Host | Ascend 950 |
| [asc::pinned_buffer](pinned_buffer.md) | 类模板 | C++17+ | Host | Ascend 950 |
