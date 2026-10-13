# asc::std::adopt_lock_t

## 产品支持情况

<!-- npu="950" id1 -->
- Ascend 950PR&950DT系列产品：支持
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3系列产品：不支持
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2系列产品：不支持
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2推理产品：不支持
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas推理系列产品AI Core：不支持
<!-- end id5 -->
<!-- npu="310p" id6 -->
- Atlas推理系列产品Vector Core：不支持
<!-- end id6 -->
<!-- npu="910" id7 -->
- Atlas训练系列产品：不支持
<!-- end id7 -->

## 功能说明

头文件路径为：`<asc/std/mutex>`。

`asc::std::adopt_lock_t`标记锁包装器构造时采用的获取方式。

标准语义参考：[cppreference `mutex`](https://en.cppreference.com/w/cpp/header/mutex)。

## 声明

```cpp
namespace asc::std {
struct adopt_lock_t;
} // namespace asc::std
```

## 约束说明

- defer_lock_t、try_to_lock_t、adopt_lock_t及对应defer_lock、try_to_lock、adopt_lock三个inline constexpr对象。
- 纯类型与对象，不拥有或操作锁。
- Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/mutex>
#include <mutex>

bool example()
{
    ::std::mutex mutex;
    mutex.lock();
    asc::std::unique_lock<::std::mutex> guard(mutex, asc::std::adopt_lock);
    const bool owned = guard.owns_lock();
    guard.unlock();
    return owned && !guard.owns_lock();
}
```

## 关联API

- [本头文件的接口列表](asc_std_mutex.md)
