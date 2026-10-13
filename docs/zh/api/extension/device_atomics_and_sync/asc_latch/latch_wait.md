# asc::latch::wait

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

头文件路径为：`<asc/latch>`。

`asc::latch::wait`等待latch计数归零。

## 函数原型

所属类型：[`asc::latch`](latch.md)。

```cpp
// asc::latch 类内的声明节选；模板形参和其他成员由所属类提供。
void wait() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

无返回值。

## 约束说明

- 使用C++17。
- 在AI Core SIMT编程 中操作调用方管理的GM状态。
- Scope必须为asc::memory_scope::block或asc::memory_scope::device。
- 所有阻塞参与者必须能够并发推进。
- 复制构造和复制赋值已删除。

## 调用示例

以下AI Core SIMT片段使用调用方管理的GM同步对象；参与者数量和前进条件须满足本页约束。

```cpp
#include <asc/latch>

__aicore__ void example(asc::latch<asc::memory_scope::block>* gm_latch)
{
    // 对象位于 GM；阻塞操作只在所有参与者可并发推进时调用。
    gm_latch->wait();
}
```

## 关联API

- [`asc::latch`](latch.md)
- [本头文件的接口列表](asc_latch.md)
