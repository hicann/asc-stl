# asc::std::barrier::arrival_token

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

`asc::std::barrier::arrival_token`标识线程已到达的屏障阶段。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `barrier`](https://en.cppreference.com/w/cpp/header/barrier)。

## 声明

所属类型：[`asc::std::barrier`](barrier.md)。

```cpp
// asc::std::barrier 类内的声明节选；模板形参和其他成员由所属类提供。
class arrival_token;
```

## 约束说明

- 令牌必须由同一个barrier的arrive操作取得，并关联当前或紧前一个有效阶段；不得使用其他屏障的令牌或跨越有效阶段的旧令牌。barrier对象在等待返回前须保持有效。

- Host对象使用本机普通内存及CPU原子操作，不管理NPU的GM状态。AI Core SIMT共享对象须位于GM，且在并发访问前完成初始化；不支持AI Core SIMD调用。
- 所有参与者必须能够并发推进，带等待的操作还要求完成条件可被满足。

## 调用示例

以下Host示例给出具体输入并检查结果；底层对象与存储在检查期间仍有效。

```cpp
#include <asc/std/barrier>

struct completion {
    int* phases;
    void operator()() noexcept { ++*phases; }
};

bool example()
{
    int phases = 0;
    asc::std::barrier<completion> barrier(1, completion{&phases});
    auto token = barrier.arrive();
    barrier.wait(static_cast<decltype(token)&&>(token));
    return phases == 1;
}
```

## 关联API

- [`asc::std::barrier`](barrier.md)
- [本头文件的接口列表](asc_std_barrier.md)
