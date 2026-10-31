# asc::parallel::generate

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

头文件路径为：`<asc/algorithm>`。

`asc::parallel::generate`异步重复调用生成器，并用每次生成的值写入目标范围。

## 函数原型

```cpp
namespace asc::parallel {
template <class Forward, class Generator>
asc::execution_status generate(asc::device_policy policy, Forward first, Forward last, Generator generator) noexcept;
}  // namespace asc::parallel
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Forward` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `Generator` | 每次无参调用产生一个输出元素值的生成器类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `policy` | 输入 | Device执行策略，用于指定Stream、临时存储和执行要求。 |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `generator` | 输入 | 无参可调用对象，返回可赋给目标元素的值；可以产生常量或业务数据，不要求随机性。各Device线程保存自身的对象副本，不能依赖单一串行调用次序。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |

## 约束说明

- 公开前端要求Clang兼容的ASC翻译单元，并显式定义`CANN_ASC_STL_USE_SIMT_LAUNCH`；值1选择SIMT、值0选择SIMD。未定义时不提供这些parallel名字。

- 输入和输出的全部GM范围、标量结果以及实际消费的临时区须从提交前持续有效到该Stream任务完成。函数对象按值复制，但其捕获的Device指针也受相同存活期约束。
- 在同步或正确建立依赖之前，Host或其他Stream不得读写或释放这些存储；返回execution_status成功只代表已提交，不代表结果可读。

- 当前本页路径不使用policy临时区；传入空临时区不会仅因此拒绝提交。若调用方复用同一策略执行需要工作区的其他操作，应分别遵守对应操作的容量与对齐要求。

- 使用C++17，并从毕昇ASC翻译单元的Host侧提交。
- 输入范围必须连续、支持随机访问且可由Device访问。
- 可调用对象和传输值必须可平凡复制并可在AI Core调用。
- policy须绑定有效Stream；当前多数逐元素或顺序路径不消费临时存储，不应为这些路径额外分配scratch。
- 标量、数量或索引输出位于GM，并在Stream完成前保持有效。
- 仅检查实现可判定的Stream和部分输出空指针等条件；范围有效性、Device可访问性、地址空间和生存期是调用方前提，不保证任意无效地址都会在提交前返回错误。

## 调用示例

以下片段使用完整工程的Host资源上下文：initial为[1, 2, 3, 4]，第二范围为[1, 2, 3, 4]；prepare同步上传到GM，complete检查提交状态并有界等待Stream，read只在完成后读回。代码逐项检查独立预期结果。

完整工程、任务/流/进程时限和逐case记录见[并行算法示例](../../../../../../examples/extension/parallel_algorithms/README.md)。

```cpp
#include <asc/algorithm>
#include "parallel_example.h"

struct generator {
    __aicore__ int operator()() const
    {
        return 7;
    }
};

bool example(parallel_example_context& context)
{
    const int initial[] = {1, 2, 3, 4};
    const int second[] = {1, 2, 3, 4};
    if (!context.prepare(initial, second))
        return false;
    auto policy = context.policy();
    auto* input = context.input;
    const auto status = asc::parallel::generate(policy, input, input + 4, generator{});
    if (!context.complete(status))
        return false;
    int actual[4]{};
    const int expected[] = {7, 7, 7, 7};
    if (!context.read(context.input, actual))
        return false;
    for (unsigned index = 0; index < 4; ++index) {
        if (actual[index] != expected[index])
            return false;
    }
    return true;
}
```

## 关联API

- [`asc::execution_status`](../../../runtime/execution_policies_and_status/asc_execution/execution_status.md)：参数校验和任务提交状态；提交成功不表示异步工作已经完成。
- [`asc::device_policy`](../../../runtime/execution_policies_and_status/asc_execution_policy_h/device_policy.md)：指定Stream、临时存储和执行要求的Device执行策略。
