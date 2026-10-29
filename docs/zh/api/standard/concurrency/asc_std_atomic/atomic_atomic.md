# asc::std::atomic::atomic

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

`asc::std::atomic::atomic`按本页所列构造形态初始化`atomic`对象。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 函数原型

### 原型1

```cpp
atomic() noexcept;
```

### 原型2

```cpp
constexpr atomic(T value) noexcept;
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 原子对象的初值；构造时写入，使初始状态确定。 |

## 返回值说明

无返回值。

## 约束说明

- `T`须为[atomic](atomic.md)支持的整数或字符类型，包括`bool`；复制构造已删除。
- 构造须在Host或AI Core SIMT编程中进行；SIMT线程共享的原子对象须位于GM，并在并发访问开始前完成构造。
- 默认构造将存储初始化为零；带值构造保存传入值。构造本身不为其他线程建立同步。

## 调用示例

以下Host片段演示原子操作；设备端对象须放在本页规定的有效内存空间。

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic<int> zero{};
    asc::std::atomic<int> seven{7};
    return zero.load() == 0 && seven.load() == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_atomic.md)
