# asc::counting_semaphore::release

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

头文件路径为：`<asc/semaphore>`。

`asc::counting_semaphore::release` 按指定数量原子增加信号量许可并唤醒等待者。

## 函数原型

```cpp
void asc::counting_semaphore::release(asc::std::ptrdiff_t update = 1) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `update` | 输入 | 许可增加量，默认 1：按该值原子增加内部计数并唤醒等待者。 |

## 返回值说明

无返回值。

## 约束说明

- 使用 C++17
- 在 AI Core SIMT 编程 中操作调用方管理的 GM 状态
- Scope 必须为 asc::memory_scope::block 或 asc::memory_scope::device
- 所有阻塞参与者必须能够并发推进
- 复制构造和复制赋值已删除

## 调用示例

以下 AI Core SIMT 片段使用调用方管理的 GM 同步对象；参与者数量和前进条件须满足本页约束。

```cpp
#include <asc/semaphore>

__aicore__ void example(asc::counting_semaphore<asc::memory_scope::block, 4>* gm_counting_semaphore)
{
    // 对象位于 GM；阻塞操作只在所有参与者可并发推进时调用。
    gm_counting_semaphore->release();
}
```
