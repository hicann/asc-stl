# asc::std::atomic::is_lock_free

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

`asc::std::atomic::is_lock_free`报告当前原子对象的操作是否无需锁后备实现。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 函数原型

所属类型：[`asc::std::atomic`](atomic.md)。

```cpp
// asc::std::atomic 类内的声明节选；模板形参和其他成员由所属类提供。
bool is_lock_free() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 标准整数/字符owning atomic别名及列出自由函数。
- bool/8/16位用32位内部存储。
- 32/64位按有符号位模式分派。
- Host和AI Core SIMT编程GM。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic<int> cell{3};
    const bool lock_free = cell.is_lock_free();
    // 始终无锁的类型，在运行时也必须报告无锁。
    return (!asc::std::atomic<int>::is_always_lock_free || lock_free) && cell.load() == 3;
}
```

## 关联API

- [`asc::std::atomic`](atomic.md)
- [本头文件的接口列表](asc_std_atomic.md)
