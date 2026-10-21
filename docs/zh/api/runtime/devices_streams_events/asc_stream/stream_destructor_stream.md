# asc::stream::~stream

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

`asc::stream`析构函数同步并销毁仍由对象持有的Runtime Stream句柄；已释放或为空时不执行Runtime操作。

## 函数原型

所属类型：[`asc::stream`](stream.md)。

```cpp
// asc::stream 类内的声明节选；模板形参和其他成员由所属类提供。
~stream();
```

## 参数说明

无参数。

## 返回值说明

无返回值。

## 约束说明

- 仅可在Host使用且对象不可复制。
- 移动操作转移资源所有权。
- close()负责同步并销毁自身资源，失败时保留所有权。
- 析构函数会尝试完成本地清理。

## 调用示例

以下示例只在显式管理的对齐原始存储中手动析构。普通自动变量应通过作用域退出析构；需要检查资源清理状态时先调用close。

```cpp
#include <asc/stream>
#include <asc/std/new>
bool example()
{
    alignas(asc::stream) unsigned char storage[sizeof(asc::stream)];
    auto* object = ::new (static_cast<void*>(storage)) asc::stream;
    const bool initially_empty = !static_cast<bool>(*object);
    object->~stream();
    // storage是原始字节存储，不会再次隐式析构同一对象。
    return initially_empty;
}
```

## 关联API

- [`asc::stream`](stream.md)
- [本头文件的接口列表](asc_stream.md)
