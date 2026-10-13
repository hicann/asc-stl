# ::operator new[]

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

头文件路径为：`<asc/std/new>`。

全局数组 placement `operator new[]` 使用调用方提供的存储地址，接口不分配内存。

标准语义参考：[cppreference `new`](https://en.cppreference.com/w/cpp/header/new)。

## 函数原型

```cpp
void* ::operator new[](asc::std::size_t, void* ptr) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `asc::std::size_t`（未命名） | 输入 | placement 形式的第一个参数，为未命名的 std::size_t 大小参数，表示请求构造数组所占用的总字节数；本接口不分配内存，不使用该值。 |
| `ptr` | 输入 | 提供“全局数组 placement `operator new[]` 使用调用方提供的存储地址，接口不分配内存”所需的数据地址；可访问范围和生命周期须满足约束。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `void*` | 返回调用方提供的定位存储地址。 |

## 约束说明

- 提供 placement 对象生命周期和无动态分配的接口

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/new>

decltype(auto) example(void* storage)
{
    void* address = ::operator new[](sizeof(int), storage);
    return address;
}
```
