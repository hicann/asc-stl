# asc::std::atomic::storage_type

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

`asc::std::atomic::storage_type`标识原子对象保存的底层单元类型。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 声明

`storage_type`是当前整数或字符类型所用的32位或64位存储单元类型。以下通过公开别名获取`atomic<int>`对应的存储类型。

```cpp
using storage_type = asc::std::atomic<int>::storage_type;
```

## 约束说明

- 该别名为原子对象实际使用的整数存储类型，须以[atomic](atomic.md)支持的`T`实例化。
- `bool`及8位、16位数值使用32位存储单元；32位和64位数值使用相应位宽的存储单元。读取类型本身不执行原子操作。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/atomic>
#include <type_traits>
#include <cstddef>
#include <utility>

using alias_type = typename asc::std::atomic<int>::storage_type;
static_assert(::std::is_same_v<alias_type, __INT32_TYPE__>);
```

## 关联API

- [`asc::std::atomic`](atomic.md)
- [本头文件的接口列表](asc_std_atomic.md)
