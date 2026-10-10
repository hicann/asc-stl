# 头文件 asc/pipeline

使用调用方提供的事件ID，组织GM与UB之间的异步数据搬运提交、等待和流水线阶段切换

## 使用方式

```cpp
#include <asc/pipeline>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::copy_async](copy_async.md) | 函数 | C++17+ | AI Core SIMD 编程 | Ascend 950 |
| [asc::make_pipeline](make_pipeline.md) | 函数 | C++17+ | AI Core SIMD 编程 | Ascend 950 |
| [asc::pipeline_event_id](pipeline_event_id.md) | 类型别名 | C++17+ | AI Core SIMD 编程 | Ascend 950 |
| [asc::pipeline_ref](pipeline_ref.md) | 类 | C++17+ | AI Core SIMD 编程 | Ascend 950 |
| [asc::pipeline_ref::consumer_release](pipeline_ref_consumer_release.md) | 成员函数 | C++17+ | AI Core SIMD 编程 | Ascend 950 |
| [asc::pipeline_ref::consumer_wait](pipeline_ref_consumer_wait.md) | 成员函数 | C++17+ | AI Core SIMD 编程 | Ascend 950 |
| [asc::pipeline_ref::load_event](pipeline_ref_load_event.md) | 成员函数 | C++17+ | AI Core SIMD 编程 | Ascend 950 |
| [asc::pipeline_ref::operator=](pipeline_ref_operator_assign.md) | 成员函数 | C++17+ | AI Core SIMD 编程 | Ascend 950 |
| [asc::pipeline_ref::pipeline_ref](pipeline_ref_pipeline_ref.md) | 构造函数 | C++17+ | AI Core SIMD 编程 | Ascend 950 |
| [asc::pipeline_ref::producer_acquire](pipeline_ref_producer_acquire.md) | 成员函数 | C++17+ | AI Core SIMD 编程 | Ascend 950 |
| [asc::pipeline_ref::producer_commit](pipeline_ref_producer_commit.md) | 成员函数 | C++17+ | AI Core SIMD 编程 | Ascend 950 |
| [asc::pipeline_ref::stages](pipeline_ref_stages.md) | 成员函数 | C++17+ | AI Core SIMD 编程 | Ascend 950 |
| [asc::pipeline_ref::store_event](pipeline_ref_store_event.md) | 成员函数 | C++17+ | AI Core SIMD 编程 | Ascend 950 |
| [asc::pipeline_ref::wait](pipeline_ref_wait.md) | 成员函数 | C++17+ | AI Core SIMD 编程 | Ascend 950 |
