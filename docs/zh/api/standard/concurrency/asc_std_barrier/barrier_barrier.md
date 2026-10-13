# asc::std::barrier::barrier

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

头文件路径为：`<asc/std/barrier>`。

`asc::std::barrier::barrier`按本页所列构造形态初始化`barrier`对象。

`completion`为阶段完成函数对象：每轮（phase）所有参与线程到达屏障且到达计数计满时，由其中一个线程以无参形式调用；完成函数的调用必须不抛出异常。未显式提供时使用不做任何操作的默认完成函数。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `barrier`](https://en.cppreference.com/w/cpp/header/barrier)。

## 函数原型

```cpp
barrier(long long expected, CompletionFunction completion);
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `expected` | 输入 | 初始参与线程数，须为正数；每个阶段的到达计数达到该值时触发完成函数并开启下一阶段。 |
| `completion` | 输入 | 阶段完成函数；在每阶段全部参与者到达后被调用一次，缺省为空完成函数。 |
## 返回值说明

无返回值。

## 约束说明

- Host侧对象管理Ascend 950的GM状态。
- 所有参与者必须能够并发推进，带等待的操作还要求完成条件可被满足。

## 调用示例

以下Host片段使用一个可独立完成的参与者演示调用；多参与者场景须保证并发推进。

```cpp
#include <asc/std/barrier>

void example()
{
    asc::std::barrier<> barrier(1);
    barrier.arrive_and_wait();
}
```

## 关联API

- [本头文件的接口列表](asc_std_barrier.md)
