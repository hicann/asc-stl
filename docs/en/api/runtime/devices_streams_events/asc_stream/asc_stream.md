# Header asc/stream

Provides Stream and Event creation and adoption, non-owning references, synchronization and completion-status queries, Event dependencies between Streams, and Event timing

## Usage

```cpp
#include <asc/stream>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [`asc::operator!=` (Function)](../asc_devices/operator_not_equal.md) | Function | C++17+ | Host | Ascend 950 |
| [`asc::operator==` (Function)](../asc_devices/operator_equal.md) | Function | C++17+ | Host | Ascend 950 |
| [asc::adopt_event](adopt_event.md) | Function | C++17+ | Host | Ascend 950 |
| [asc::adopt_stream](adopt_stream.md) | Function | C++17+ | Host | Ascend 950 |
| [asc::elapsed_time](elapsed_time.md) | Function | C++17+ | Host | Ascend 950 |
| [asc::event](event.md) | Class | C++17+ | Host | Ascend 950 |
| [asc::event::close](event_close.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::event::event](event_event.md) | Constructor | C++17+ | Host | Ascend 950 |
| [asc::event::`operator=`](event_operator_assign.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::event::release](event_release.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::event::~event](event_destructor_event.md) | Destructor | C++17+ | Host | Ascend 950 |
| [asc::event_ref](event_ref.md) | Class | C++17+ | Host | Ascend 950 |
| [asc::event_ref::event_ref](event_ref_event_ref.md) | Constructor | C++17+ | Host | Ascend 950 |
| [asc::event_ref::is_done](event_ref_is_done.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::event_ref::native_handle](event_ref_native_handle.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::event_ref::operator bool](event_ref_operator_bool.md) | Conversion function | C++17+ | Host | Ascend 950 |
| [asc::event_ref::record](event_ref_record.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::event_ref::synchronize](event_ref_synchronize.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::make_event](make_event.md) | Function | C++17+ | Host | Ascend 950 |
| [asc::make_stream](make_stream.md) | Function | C++17+ | Host | Ascend 950 |
| [asc::stream](stream.md) | Class | C++17+ | Host | Ascend 950 |
| [asc::stream::close](stream_close.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::stream::`operator=`](stream_operator_assign.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::stream::release](stream_release.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::stream::stream](stream_stream.md) | Constructor | C++17+ | Host | Ascend 950 |
| [asc::stream::~stream](stream_destructor_stream.md) | Destructor | C++17+ | Host | Ascend 950 |
| [asc::stream_ref](stream_ref.md) | Class | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::is_done](stream_ref_is_done.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::native_handle](stream_ref_native_handle.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::operator bool](stream_ref_operator_bool.md) | Conversion function | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::priority](stream_ref_priority.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::stream_ref](stream_ref_stream_ref.md) | Constructor | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::synchronize](stream_ref_synchronize.md) | Member function | C++17+ | Host | Ascend 950 |
| [asc::stream_ref::wait](stream_ref_wait.md) | Member function | C++17+ | Host | Ascend 950 |
