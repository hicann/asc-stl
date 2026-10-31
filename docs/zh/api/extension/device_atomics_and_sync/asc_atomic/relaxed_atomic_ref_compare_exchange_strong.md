# asc::relaxed_atomic_ref::compare_exchange_strong

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

头文件路径为：`<asc/atomic>`。

`asc::relaxed_atomic_ref::compare_exchange_strong`比较当前值与expected，相等时写入desired，否则回写实际值。

## 函数原型

所属类型：[`asc::relaxed_atomic_ref`](relaxed_atomic_ref.md)。

```cpp
// asc::relaxed_atomic_ref 类内的声明节选；模板形参和其他成员由所属类提供。
bool compare_exchange_strong(T& expected, T desired) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `expected` | 输入/输出 | 提供预期值或目标值；比较失败时函数把观察到的当前原子值写入`expected`；strong形式不允许伪失败，仅在实际比较失败时返回`false`。 |
| `desired` | 输入 | 比较相等时写入原子对象的目标值。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 底层单元须位于GM，不提供UB或线程私有存储原子操作；固定relaxed内存序不承担跨对象同步。

- 仅可在AI Core SIMT编程中调用。
- T必须为准确的32位或64位有符号／无符号整数类型，底层对象必须已初始化且满足其自然对齐。
- 引用不拥有对象；底层存储须在全部并发访问结束前保持有效，参与者不得混用非原子访问。
- 本接口使用relaxed内存序，不承担其他对象读写的发布或获取同步。

## 调用示例

以下SIMT核函数由单个线程初始化并访问一个GM原子单元；无其他并发访问，预期output[0]为1。Host须在核函数完成后读取结果。

```cpp
#include <asc/atomic>
#include <asc/std/new>

__global__ void example(int* storage, unsigned int* output)
{
    // 仅启动1个block、1个线程；storage和output均为Host分配的GM。
    *storage = 7;
    asc::relaxed_atomic_ref<int> cell(*storage);
    cell.store(7);
    int expected = 7;
    const bool exchanged = cell.compare_exchange_strong(expected, 11);
    output[0] = (exchanged && expected == 7 && cell.load() == 11) ? 1U : 0U;
}
```

完整工程及运行步骤见[《atomic_operations示例》](../../../../../../examples/extension/atomic_operations/README.md)。

## 关联API

- [`asc::relaxed_atomic_ref`](relaxed_atomic_ref.md)
- [本头文件的接口列表](asc_atomic.md)
