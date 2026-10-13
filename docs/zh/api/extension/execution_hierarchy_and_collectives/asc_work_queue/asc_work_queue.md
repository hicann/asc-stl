# 头文件asc/work_queue

基于调用方提供的GM原子游标，为AI Core SIMD编程的子块和AI Core SIMT编程的线程束获取互不重叠的任务区间

## 使用方式

```cpp
#include <asc/work_queue>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::acquire_work](acquire_work.md) | 函数模板 | C++17+ | AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::make_work_queue](make_work_queue.md) | 函数模板 | C++17+ | AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::work_chunk](work_chunk.md) | 类模板 | C++17+ | AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::work_queue_ref](work_queue_ref.md) | 类模板 | C++17+ | AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
