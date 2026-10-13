# asc::stream::stream

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

头文件路径为：`<asc/stream>`。

默认构造函数创建不持有句柄的Stream；移动构造函数从另一个对象取得原生句柄并将源对象置空。

## 函数原型

所属类型：[`asc::stream`](stream.md)。

### 原型1

```cpp
// asc::stream 类内的声明节选；模板形参和其他成员由所属类提供。
stream() noexcept;
```

### 原型2

```cpp
// asc::stream 类内的声明节选；模板形参和其他成员由所属类提供。
stream(asc::stream&& other) noexcept;
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

## 返回值说明

无返回值。

## 约束说明

- 仅可在Host使用且对象不可复制。
- 移动操作转移资源所有权。
- close()负责同步并销毁自身资源，失败时保留所有权。
- 析构函数会尝试完成本地清理。

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/stream>

template <class... Args>
asc::stream make_object(Args&&... args)
{
    return asc::stream(static_cast<Args&&>(args)...);
}
```

对应完整工程使用`C++17`；请在目标工具链及设备上编译和运行。

完整示例源码：[stream_event.cpp](../../../../examples/stream_event.cpp)。

## 关联API

- [`asc::stream`](stream.md)
- [本头文件的接口列表](asc_stream.md)
