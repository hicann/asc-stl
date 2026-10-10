# asc::init

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

头文件路径为：`<asc/barrier>`。

`asc::init` 在调用方提供的存储中初始化 barrier 及其期望参与者数量。

## 函数原型

### 原型 1

```cpp
template<asc::memory_scope Scope, class CompletionFunction> void asc::init(asc::barrier<Scope, CompletionFunction>* object, asc::std::ptrdiff_t expected) noexcept;
```

### 原型 2

```cpp
template<asc::memory_scope Scope, class CompletionFunction> void asc::init(asc::barrier<Scope, CompletionFunction>* object, asc::std::ptrdiff_t expected, CompletionFunction completion) noexcept;
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Scope` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `CompletionFunction` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `object` | 输入 | 提供“在调用方提供的存储中初始化 barrier 及其期望参与者数量”所需的数据地址；可访问范围和生命周期须满足约束。 |
| `expected` | 输入 | 指定“在调用方提供的存储中初始化 barrier 及其期望参与者数量”使用的标量值；取值须满足声明和约束。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Scope` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `CompletionFunction` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `object` | 输入 | 提供“在调用方提供的存储中初始化 barrier 及其期望参与者数量”所需的数据地址；可访问范围和生命周期须满足约束。 |
| `expected` | 输入 | 指定“在调用方提供的存储中初始化 barrier 及其期望参与者数量”使用的标量值；取值须满足声明和约束。 |
| `completion` | 输入 | 用于确定元素顺序的比较对象。 |

## 返回值说明

无返回值。

## 约束说明

- 使用 C++17
- 在 AI Core SIMT 编程 中操作调用方管理的 GM 状态
- Scope 必须为 asc::memory_scope::block 或 asc::memory_scope::device
- 所有阻塞参与者必须能够并发推进
- 复制构造和复制赋值已删除

## 调用示例

以下片段在 AI Core SIMT 编程中初始化调用方提供的线程块 barrier；对象存储须在所有参与者使用期间有效。

```cpp
#include <asc/barrier>

__aicore__ void example(asc::barrier<asc::memory_scope::block>* object)
{
    asc::init(object, 32);
}
```
