# 头文件 asc/stream

提供Stream和Event的创建与接管、非拥有引用、同步与完成状态查询、Stream间的Event依赖和Event计时功能

## 使用方式

```cpp
#include <asc/stream>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::operator!=（函数）](../asc_devices/operator_not_equal.md) | 函数 | C++17+ | Host | Ascend 950 |
| [asc::operator==（函数）](../asc_devices/operator_equal.md) | 函数 | C++17+ | Host | Ascend 950 |
| [asc::adopt_event](adopt_event.md) | 函数 | C++17+ | Host | Ascend 950 |
| [asc::adopt_stream](adopt_stream.md) | 函数 | C++17+ | Host | Ascend 950 |
| [asc::elapsed_time](elapsed_time.md) | 函数 | C++17+ | Host | Ascend 950 |
| [asc::event](event.md) | 类 | C++17+ | Host | Ascend 950 |
| [asc::event::close](event_close.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::event::event](event_event.md) | 构造函数 | C++17+ | Host | Ascend 950 |
| [asc::event::operator=](event_operator_assign.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::event::release](event_release.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::event::~event](event_destructor_event.md) | 析构函数 | C++17+ | Host | Ascend 950 |
| [asc::event_ref](event_ref.md) | 类 | C++17+ | Host | Ascend 950 |
| [asc::event_ref::event_ref](event_ref_event_ref.md) | 构造函数 | C++17+ | Host | Ascend 950 |
| [asc::event_ref::is_done](event_ref_is_done.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::event_ref::native_handle](event_ref_native_handle.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::event_ref::operator bool](event_ref_operator_bool.md) | 转换函数 | C++17+ | Host | Ascend 950 |
| [asc::event_ref::record](event_ref_record.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::event_ref::synchronize](event_ref_synchronize.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::make_event](make_event.md) | 函数 | C++17+ | Host | Ascend 950 |
| [asc::make_stream](make_stream.md) | 函数 | C++17+ | Host | Ascend 950 |
| [asc::stream](stream.md) | 类 | C++17+ | Host | Ascend 950 |
| [asc::stream::close](stream_close.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::stream::operator=](stream_operator_assign.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::stream::release](stream_release.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::stream::stream](stream_stream.md) | 构造函数 | C++17+ | Host | Ascend 950 |
| [asc::stream::~stream](stream_destructor_stream.md) | 析构函数 | C++17+ | Host | Ascend 950 |
| [asc::stream_ref](stream_ref.md) | 类 | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::is_done](stream_ref_is_done.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::native_handle](stream_ref_native_handle.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::operator bool](stream_ref_operator_bool.md) | 转换函数 | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::priority](stream_ref_priority.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::stream_ref](stream_ref_stream_ref.md) | 构造函数 | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::synchronize](stream_ref_synchronize.md) | 成员函数 | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::wait](stream_ref_wait.md) | 成员函数 | C++17+ | Host | Ascend 950 |
