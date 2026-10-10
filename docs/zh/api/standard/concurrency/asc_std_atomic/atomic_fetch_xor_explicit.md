# asc::std::atomic_fetch_xor_explicit

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

`asc::std::atomic_fetch_xor_explicit` 原子执行按位异或并返回修改前的值；内存序与地址空间须符合本页限制。

该接口的可用位置为 Host、AI Core SIMT 编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 函数原型

```cpp
template<class T> T asc::std::atomic_fetch_xor_explicit(atomic<T>* object, T value, memory_order order) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `object` | 输入 | 提供“原子执行按位异或并返回修改前的值”所需的数据地址；可访问范围和生命周期须满足约束。 |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |
| `order` | 输入 | 提供“原子执行按位异或并返回修改前的值”所需的输入对象；类型须满足所选原型约束。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回修改前的值。 |

## 约束说明

- 标准整数/字符owning atomic别名及列出自由函数
- bool/8/16位用32位内部存储
- 32/64位按有符号位模式分派
- Host 和 AI Core SIMT 编程 GM

## 调用示例

以下 Host 片段使用具体整数原子对象；设备端对象须位于可访问的全局内存。

```cpp
#include <asc/std/atomic>

decltype(auto) example()
{
    asc::std::atomic<int> value{1};
    return asc::std::atomic_fetch_xor_explicit(&value, 2, asc::std::memory_order_relaxed);
}
```
