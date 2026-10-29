# asc::std::atomic::compare_exchange_strong

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

`asc::std::atomic::compare_exchange_strong`比较当前值与expected；相等时写入desired，否则更新expected。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 函数原型

所属类型：[`asc::std::atomic`](atomic.md)。

### 原型1

```cpp
// asc::std::atomic 类内的声明节选；模板形参和其他成员由所属类提供。
bool compare_exchange_strong(T& expected, T desired, memory_order success) noexcept;
```

### 原型2

```cpp
// asc::std::atomic 类内的声明节选；模板形参和其他成员由所属类提供。
bool compare_exchange_strong(T& expected, T desired, memory_order success, memory_order failure) noexcept;
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `expected` | 输入/输出 | 提供预期值或目标值；比较失败时函数把观察到的当前原子值写入`expected`；strong形式不允许伪失败，weak形式允许伪失败（值相等也可能返回`false`）。 |
| `desired` | 输入 | 比较相等时写入原子对象的目标值。 |
| `success` | 输入 | 比较交换成功分支使用的内存序，约束交换写入的可见性顺序。 |
### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `expected` | 输入/输出 | 提供预期值或目标值；比较失败时函数把观察到的当前原子值写入`expected`；strong形式不允许伪失败，weak形式允许伪失败（值相等也可能返回`false`）。 |
| `desired` | 输入 | 比较相等时写入原子对象的目标值。 |
| `success` | 输入 | 比较交换成功分支使用的内存序，约束交换写入的可见性顺序。 |
| `failure` | 输入 | 比较交换失败分支（仅读取）使用的内存序；不得为release或acq_rel，且不得强于success。 |
## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `bool` | 条件成立时返回`true`，否则返回`false`。 |
| 原型2 | `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 原子操作可在Host和AI Core SIMT编程中调用；SIMT线程共享的原子对象须位于GM，并在并发访问前完成初始化。
- 比较失败时将观察到的当前值写回`expected`；调用方须提供可写且在调用期间有效的预期值对象。
- 两内存序参数形式的`failure`不得为`memory_order_release`或`memory_order_acq_rel`，且不得强于成功内存序。

## 调用示例

以下Host片段演示原子操作；设备端对象须放在本页规定的有效内存空间。

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic<int> value{1};
    int expected = 1;
    const bool changed =
        value.compare_exchange_strong(expected, 2, asc::std::memory_order_acq_rel, asc::std::memory_order_acquire);
    return changed && value.load() == 2 && expected == 1;
}
```

## 关联API

- [`asc::std::atomic`](atomic.md)
- [本头文件的接口列表](asc_std_atomic.md)
