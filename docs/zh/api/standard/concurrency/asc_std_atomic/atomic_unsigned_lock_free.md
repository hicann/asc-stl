# asc::std::atomic_unsigned_lock_free

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

头文件路径为：`<asc/std/atomic>`。

`asc::std::atomic_unsigned_lock_free`把指定基础整数或布尔类型绑定到当前交付的原子类型别名。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 声明

```cpp
namespace asc::std {
using atomic_unsigned_lock_free = atomic<unsigned int>;
} // namespace asc::std
```

## 约束说明

- 该别名表示对应整数或字符类型的[atomic](atomic.md)对象；对象的构造和原子操作可在Host或AI Core SIMT编程中进行。
- SIMT线程共享的原子对象须放在GM中，并在并发访问前完成初始化；仅声明别名不访问存储。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic_unsigned_lock_free cell{};
    cell.store(1, asc::std::memory_order_relaxed);
    return cell.load(asc::std::memory_order_relaxed) == 1;
}
```

## 关联API

- [本头文件的接口列表](asc_std_atomic.md)
