# asc::pinned_memory_resource_ref::pinned_memory_resource_ref

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

头文件路径为：`<asc/memory_resource>`。

默认构造函数创建无效引用；带参构造函数引用给定的 `pinned_memory_resource`，但不管理其生命周期。

## 函数原型

### 原型 1

```cpp
constexpr asc::pinned_memory_resource_ref::pinned_memory_resource_ref() noexcept;
```

### 原型 2

```cpp
constexpr explicit asc::pinned_memory_resource_ref::pinned_memory_resource_ref(asc::pinned_memory_resource& resource) noexcept;
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `resource` | 输入/输出 | 由调用方提供并管理生命周期的内存资源。 |

## 约束说明

- 仅可在 Host 调用
- 内存资源不抛出异常
- 分配大小、对齐和输出指针必须有效，释放时须使用同一资源及原始大小和对齐
- 资源及其引用的生命周期由调用方管理

## 调用示例

以下 Host 片段使用具体对象演示调用；涉及资源操作时须遵守本页的初始化和生命周期约束。

```cpp
#include <asc/memory_resource>

void example()
{
    asc::pinned_memory_resource_ref resource{};
    (void)resource.valid();
}
```
