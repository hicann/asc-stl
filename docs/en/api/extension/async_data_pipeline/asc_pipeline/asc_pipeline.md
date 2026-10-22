# Header asc/pipeline

Organizes submission, waiting, and pipeline stage switching for asynchronous data transfers between GM and UB, using event IDs provided by the caller

## Usage

```cpp
#include <asc/pipeline>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::copy_async](copy_async.md) | Function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::make_pipeline](make_pipeline.md) | Function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_event_id](pipeline_event_id.md) | Type alias | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref](pipeline_ref.md) | Class | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::consumer_release](pipeline_ref_consumer_release.md) | Member function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::consumer_wait](pipeline_ref_consumer_wait.md) | Member function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::load_event](pipeline_ref_load_event.md) | Member function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::`operator=`](pipeline_ref_operator_assign.md) | Member function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::pipeline_ref](pipeline_ref_pipeline_ref.md) | Constructor | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::producer_acquire](pipeline_ref_producer_acquire.md) | Member function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::producer_commit](pipeline_ref_producer_commit.md) | Member function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::stages](pipeline_ref_stages.md) | Member function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::store_event](pipeline_ref_store_event.md) | Member function | C++17+ | AI Core SIMD programming | Ascend 950 |
| [asc::pipeline_ref::wait](pipeline_ref_wait.md) | Member function | C++17+ | AI Core SIMD programming | Ascend 950 |
