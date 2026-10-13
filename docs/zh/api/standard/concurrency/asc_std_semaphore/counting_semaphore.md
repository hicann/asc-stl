# asc::std::counting_semaphore

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

头文件路径为：`<asc/std/semaphore>`。

`asc::std::counting_semaphore`用许可计数协调线程获取与释放资源。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `semaphore`](https://en.cppreference.com/w/cpp/header/semaphore)。

## 声明

```cpp
namespace asc::std {
template<long long LeastMaxValue> class counting_semaphore;
} // namespace asc::std
```

## 约束说明

- Host侧对象管理Ascend 950的GM状态。
- 所有参与者必须能够并发推进，带等待的操作还要求完成条件可被满足。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/semaphore>

bool example()
{
    asc::std::counting_semaphore<2> permits(1);
    if (!permits.try_acquire()) return false;
    if (permits.try_acquire()) return false;
    permits.release();
    return permits.try_acquire();
}
```

## 关联API

- [本头文件的接口列表](asc_std_semaphore.md)
