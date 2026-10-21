# asc::std::atomic_init

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

`asc::std::atomic_init`以给定值初始化原子对象。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 函数原型

```cpp
namespace asc::std {
template<class T> void atomic_init(atomic<T>* object, T value) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 原子对象存储的值类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `object` | 输入/输出 | 待初始化的原子对象的指针。 |
| `value` | 输入 | 写入原子对象的初始值。 |

## 返回值说明

无返回值。

## 约束说明

- 原子操作可在Host和AI Core SIMT编程中调用；SIMT线程共享的原子对象须位于GM，并在并发访问前完成初始化。
- `object`须指向有效的[atomic](atomic.md)对象，其值类型须与模板参数`T`一致。
- 当前实现以`memory_order_relaxed`存入初值；调用须在其他线程并发访问开始前完成。

## 调用示例

以下Host片段使用具体整数原子对象；设备端对象须位于可访问的全局内存。

```cpp
#include <asc/std/atomic>

void example()
{
    asc::std::atomic<int> value{1};
    asc::std::atomic_init(&value, 2);
}
```

## 关联API

- [本头文件的接口列表](asc_std_atomic.md)
