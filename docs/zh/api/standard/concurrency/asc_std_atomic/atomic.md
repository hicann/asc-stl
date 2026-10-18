# asc::std::atomic

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

`asc::std::atomic`按规定内存序读取和更新保存的原子值。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 声明

```cpp
namespace asc::std {
template<class T> class atomic;
} // namespace asc::std
```

## 约束说明

- `T`须为当前实现支持的整数或字符类型，包括`bool`；不要将本模板视为任意可平凡复制类型的通用原子包装。
- 可在Host和AI Core SIMT编程中调用；不支持在AI Core SIMD编程中调用原子操作。
- SIMT参与线程共享的原子对象须放在GM中，并在并发访问前完成初始化；不得在各线程的局部对象上执行GM原子操作。
- `load`、`store`和比较交换分别有合法内存序要求，见各成员页；对象的构造和析构不提供并发同步。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic<int> counter(1);
    const int previous = counter.fetch_add(2);
    return previous == 1 && counter.load() == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_atomic.md)
