# asc::make_pinned_buffer

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

头文件路径为：`<asc/buffer>`。

`asc::make_pinned_buffer` 使用调用方提供的页锁定内存资源创建 `pinned_buffer<T>`。接口可只分配存储，也可使用单个值或连续 Host 范围初始化元素。

## 函数原型

### 原型 1

```cpp
template<class T> asc::execution_status asc::make_pinned_buffer(asc::pinned_buffer<T>& output, const asc::pinned_memory_resource_ref& resource, asc::stream_ref stream, asc::std::size_t element_count) noexcept;
```

### 原型 2

```cpp
template<class T> asc::execution_status asc::make_pinned_buffer(asc::pinned_buffer<T>& output, const asc::pinned_memory_resource_ref& resource, asc::stream_ref stream, asc::std::size_t element_count, const T& value) noexcept;
```

### 原型 3

```cpp
template<class T> asc::execution_status asc::make_pinned_buffer(asc::pinned_buffer<T>& output, const asc::pinned_memory_resource_ref& resource, asc::stream_ref stream, const T* first, const T* last) noexcept;
```

### 原型 4

```cpp
template<class T> asc::execution_status asc::make_pinned_buffer(asc::pinned_buffer<T>& output, const asc::pinned_memory_resource_ref& resource, asc::stream_ref stream, const T* first, asc::std::size_t element_count) noexcept;
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 提供“使用调用方提供的页锁定内存资源创建 `pinned_buffer<T>`”使用的对象引用；被引用对象须在调用期间有效。 |
| `resource` | 输入 | 由调用方提供并管理生命周期的内存资源。 |
| `stream` | 输入 | 用于按序提交异步工作的 Stream。相关资源须保持有效，直至工作完成。 |
| `element_count` | 输入 | 参与操作的元素数量。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 提供“使用调用方提供的页锁定内存资源创建 `pinned_buffer<T>`”使用的对象引用；被引用对象须在调用期间有效。 |
| `resource` | 输入 | 由调用方提供并管理生命周期的内存资源。 |
| `stream` | 输入 | 用于按序提交异步工作的 Stream。相关资源须保持有效，直至工作完成。 |
| `element_count` | 输入 | 参与操作的元素数量。 |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 提供“使用调用方提供的页锁定内存资源创建 `pinned_buffer<T>`”使用的对象引用；被引用对象须在调用期间有效。 |
| `resource` | 输入 | 由调用方提供并管理生命周期的内存资源。 |
| `stream` | 输入 | 用于按序提交异步工作的 Stream。相关资源须保持有效，直至工作完成。 |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 提供“使用调用方提供的页锁定内存资源创建 `pinned_buffer<T>`”使用的对象引用；被引用对象须在调用期间有效。 |
| `resource` | 输入 | 由调用方提供并管理生命周期的内存资源。 |
| `stream` | 输入 | 用于按序提交异步工作的 Stream。相关资源须保持有效，直至工作完成。 |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `element_count` | 输入 | 参与操作的元素数量。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |
| 原型 2 | `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |
| 原型 3 | `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |
| 原型 4 | `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |

## 约束说明

- T 必须为可平凡复制类型
- output、resource 和 stream 必须有效
- 元素数量必须大于零
- 输入范围必须连续且在调用期间保持有效

## 调用示例

以下 Host 片段由调用方提供有效内存资源和 Stream；缓冲区拥有分配结果。

```cpp
#include <asc/buffer>

decltype(auto) example(const asc::pinned_memory_resource_ref& resource, asc::stream_ref stream)
{
    asc::pinned_buffer<int> output;
    return asc::make_pinned_buffer(output, resource, stream, 4);
}
```
