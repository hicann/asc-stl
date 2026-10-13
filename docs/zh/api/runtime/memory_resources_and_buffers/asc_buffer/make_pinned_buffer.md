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

`asc::make_pinned_buffer`使用调用方提供的页锁定内存资源创建`pinned_buffer<T>`。接口可只分配存储，也可使用单个值或连续Host范围初始化元素。

## 函数原型

### 原型1

```cpp
namespace asc {
template<class T> asc::execution_status make_pinned_buffer(asc::pinned_buffer<T>& output, const asc::pinned_memory_resource_ref& resource, asc::stream_ref stream, asc::std::size_t element_count) noexcept;
} // namespace asc
```

### 原型2

```cpp
namespace asc {
template<class T> asc::execution_status make_pinned_buffer(asc::pinned_buffer<T>& output, const asc::pinned_memory_resource_ref& resource, asc::stream_ref stream, asc::std::size_t element_count, const T& value) noexcept;
} // namespace asc
```

### 原型3

```cpp
namespace asc {
template<class T> asc::execution_status make_pinned_buffer(asc::pinned_buffer<T>& output, const asc::pinned_memory_resource_ref& resource, asc::stream_ref stream, const T* first, const T* last) noexcept;
} // namespace asc
```

### 原型4

```cpp
namespace asc {
template<class T> asc::execution_status make_pinned_buffer(asc::pinned_buffer<T>& output, const asc::pinned_memory_resource_ref& resource, asc::stream_ref stream, const T* first, asc::std::size_t element_count) noexcept;
} // namespace asc
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 缓冲区的元素类型；元素数乘sizeof(T)为所需字节数，乘积须可表示。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 接收结果的pinned_buffer<T> 对象引用：调用前持有的旧缓冲会被关闭，成功后持有新分配缓冲的所有权。 |
| `resource` | 输入 | 页锁定内存资源引用（pinned_memory_resource_ref）：缓冲存储由该资源分配，须在缓冲关闭前保持有效。 |
| `stream` | 输入 | 记录于缓冲状态的Stream引用：缓冲后续的流序操作按该Stream排序；须在缓冲生命周期内有效。 |
| `element_count` | 输入 | 元素个数（以元素计）：原型1/2为待分配的元素数（为0时返回参数无效），原型4为从first复制的元素数。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 缓冲区的元素类型；元素数乘sizeof(T)为所需字节数，乘积须可表示。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 接收结果的pinned_buffer<T> 对象引用：调用前持有的旧缓冲会被关闭，成功后持有新分配缓冲的所有权。 |
| `resource` | 输入 | 页锁定内存资源引用（pinned_memory_resource_ref）：缓冲存储由该资源分配，须在缓冲关闭前保持有效。 |
| `stream` | 输入 | 记录于缓冲状态的Stream引用：缓冲后续的流序操作按该Stream排序；须在缓冲生命周期内有效。 |
| `element_count` | 输入 | 元素个数（以元素计）：原型1/2为待分配的元素数（为0时返回参数无效），原型4为从first复制的元素数。 |
| `value` | 输入 | 填充值：页锁定内存可直接Host访问，分配后以Host循环把该值写入每个元素。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 缓冲区的元素类型；元素数乘sizeof(T)为所需字节数，乘积须可表示。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 接收结果的pinned_buffer<T> 对象引用：调用前持有的旧缓冲会被关闭，成功后持有新分配缓冲的所有权。 |
| `resource` | 输入 | 页锁定内存资源引用（pinned_memory_resource_ref）：缓冲存储由该资源分配，须在缓冲关闭前保持有效。 |
| `stream` | 输入 | 记录于缓冲状态的Stream引用：缓冲后续的流序操作按该Stream排序；须在缓冲生命周期内有效。 |
| `first` | 输入 | 待复制的Host连续元素范围首指针：原型3与last界定范围，原型4与element_count界定长度。 |
| `last` | 输入 | 待复制的Host连续元素范围末指针（排他）：不得为空且不得小于first。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 缓冲区的元素类型；元素数乘sizeof(T)为所需字节数，乘积须可表示。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 接收结果的pinned_buffer<T> 对象引用：调用前持有的旧缓冲会被关闭，成功后持有新分配缓冲的所有权。 |
| `resource` | 输入 | 页锁定内存资源引用（pinned_memory_resource_ref）：缓冲存储由该资源分配，须在缓冲关闭前保持有效。 |
| `stream` | 输入 | 记录于缓冲状态的Stream引用：缓冲后续的流序操作按该Stream排序；须在缓冲生命周期内有效。 |
| `first` | 输入 | 待复制的Host连续元素范围首指针：原型3与last界定范围，原型4与element_count界定长度。 |
| `element_count` | 输入 | 元素个数（以元素计）：原型1/2为待分配的元素数（为0时返回参数无效），原型4为从first复制的元素数。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |
| 原型2 | `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |
| 原型3 | `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |
| 原型4 | `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |

## 约束说明

- T必须为可平凡复制类型。
- output、resource和stream必须有效。
- 元素数量必须大于零。
- 输入范围必须连续且在调用期间保持有效。

## 调用示例

以下Host片段由调用方提供有效内存资源和Stream；缓冲区拥有分配结果。

```cpp
#include <asc/buffer>

decltype(auto) example(const asc::pinned_memory_resource_ref& resource, asc::stream_ref stream)
{
    asc::pinned_buffer<int> output;
    return asc::make_pinned_buffer(output, resource, stream, 4);
}
```

## 关联API

- [`asc::execution_status`](../../execution_policies_and_status/asc_execution/execution_status.md)：参数校验和任务提交状态；提交成功不表示异步工作已经完成。
