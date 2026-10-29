# asc::make_device_buffer

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

`asc::make_device_buffer`使用调用方提供的Device内存资源创建`device_buffer<T>`。接口可只分配存储，也可使用单个值或连续Host范围初始化元素；操作状态通过`execution_status`返回。

## 函数原型

### 原型1

```cpp
namespace asc {
template <class T>
asc::execution_status make_device_buffer(asc::device_buffer<T>& output, const asc::device_memory_resource_ref& resource,
    asc::stream_ref stream, asc::std::size_t element_count) noexcept;
}  // namespace asc
```

### 原型2

```cpp
namespace asc {
template <class T>
asc::execution_status make_device_buffer(asc::device_buffer<T>& output, const asc::device_memory_resource_ref& resource,
    asc::stream_ref stream, asc::std::size_t element_count, const T& value) noexcept;
}  // namespace asc
```

### 原型3

```cpp
namespace asc {
template <class T>
asc::execution_status make_device_buffer(asc::device_buffer<T>& output, const asc::device_memory_resource_ref& resource,
    asc::stream_ref stream, const T* first, const T* last) noexcept;
}  // namespace asc
```

### 原型4

```cpp
namespace asc {
template <class T>
asc::execution_status make_device_buffer(asc::device_buffer<T>& output, const asc::device_memory_resource_ref& resource,
    asc::stream_ref stream, const T* first, asc::std::size_t element_count) noexcept;
}  // namespace asc
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
| `output` | 输出 | 接收结果的device_buffer<T> 对象引用：进入替换阶段时先关闭旧缓冲；关闭失败保留原所有权并返回错误，成功分配后持有新缓冲。 |
| `resource` | 输入 | Device内存资源引用（device_memory_resource_ref）：缓冲存储由该资源分配，须在缓冲关闭前保持有效。 |
| `stream` | 输入 | 与缓冲关联的Stream引用：初始化复制等异步操作按该Stream提交；须保持有效直至相关异步工作完成。 |
| `element_count` | 输入 | 元素个数（以元素计）：原型1/2为待分配的元素数（为0时返回参数无效），原型4为从first复制的元素数。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 缓冲区的元素类型；元素数乘sizeof(T)为所需字节数，乘积须可表示。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 接收结果的device_buffer<T> 对象引用：进入替换阶段时先关闭旧缓冲；关闭失败保留原所有权并返回错误，成功分配后持有新缓冲。 |
| `resource` | 输入 | Device内存资源引用（device_memory_resource_ref）：缓冲存储由该资源分配，须在缓冲关闭前保持有效。 |
| `stream` | 输入 | 与缓冲关联的Stream引用：初始化复制等异步操作按该Stream提交；须保持有效直至相关异步工作完成。 |
| `element_count` | 输入 | 元素个数（以元素计）：原型1/2为待分配的元素数（为0时返回参数无效），原型4为从first复制的元素数。 |
| `value` | 输入 | 填充值：先经一次Host→Device复制上载，再以流序倍增的Device→Device复制填充全部元素。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 缓冲区的元素类型；元素数乘sizeof(T)为所需字节数，乘积须可表示。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 接收结果的device_buffer<T> 对象引用：进入替换阶段时先关闭旧缓冲；关闭失败保留原所有权并返回错误，成功分配后持有新缓冲。 |
| `resource` | 输入 | Device内存资源引用（device_memory_resource_ref）：缓冲存储由该资源分配，须在缓冲关闭前保持有效。 |
| `stream` | 输入 | 与缓冲关联的Stream引用：初始化复制等异步操作按该Stream提交；须保持有效直至相关异步工作完成。 |
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
| `output` | 输出 | 接收结果的device_buffer<T> 对象引用：进入替换阶段时先关闭旧缓冲；关闭失败保留原所有权并返回错误，成功分配后持有新缓冲。 |
| `resource` | 输入 | Device内存资源引用（device_memory_resource_ref）：缓冲存储由该资源分配，须在缓冲关闭前保持有效。 |
| `stream` | 输入 | 与缓冲关联的Stream引用：初始化复制等异步操作按该Stream提交；须保持有效直至相关异步工作完成。 |
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

- 单值Device填充也借用value的地址用于异步Host→Device复制。value（包括临时量）的存储须保持到该Stream复制完成；不得传入在返回后立即销毁的临时量后忽略等待。

- 关闭失败时原有分配和资源引用仍由当前对象持有，调用方可显式close重试。移动赋值仅在目标关闭成功后转移源对象；失败时两个对象均保留原所有权。
- 工厂进入替换阶段时先关闭旧缓冲；关闭失败直接返回该状态，不分配新缓冲。销毁或关闭前须保证使用存储的异步工作已完成。

- T必须为可平凡复制类型。
- output、resource和stream必须有效。
- 元素数量必须大于零。
- 异步初始化完成前输入范围、Stream和内存资源必须保持有效。

## 调用示例

以下完整示例使用真实CANN Runtime，选择设备0；运行前须确认该设备可用。异步等待限于10秒，失败即终止样例进程，避免释放仍被使用的资源；控制端须停止后续任务并重新检查设备状态。成功路径先完成工作，再关闭资源、重置设备并结束Runtime。

```cpp
#include <acl/acl.h>
#include <asc/stream>
#include <cstdlib>

void check(bool condition)
{
    if (!condition) {
        std::_Exit(2);
    }
}

void finish(asc::stream_ref stream)
{
    check(aclrtSynchronizeStreamWithTimeout(stream.native_handle(), 10000) == ACL_SUCCESS);
}
#include <asc/buffer>


void run_example()
{
    asc::stream stream;
    check(asc::make_stream(stream));
    asc::device_memory_resource device_resource(0);
    asc::pinned_memory_resource host_resource;
    const asc::device_memory_resource_ref resource(device_resource);
    const asc::pinned_memory_resource_ref pinned(host_resource);
    const int values[4] = {2, 4, 6, 8};
    asc::pinned_buffer<int> input;
    asc::pinned_buffer<int> output;
    check(asc::make_pinned_buffer(input, pinned, stream, values, values + 4).success());
    check(asc::make_pinned_buffer(output, pinned, stream, 16).success());
    asc::device_buffer<int> buffers[4];
    check(asc::make_device_buffer(buffers[0], resource, stream, 4).success());
    check(asc::fill_bytes(stream, buffers[0].data(), 0, buffers[0].size_bytes()).success());
    check(asc::make_device_buffer(buffers[1], resource, stream, 4, input.data()[0]).success());
    check(asc::make_device_buffer(buffers[2], resource, stream, input.data(), input.data() + 4).success());
    check(asc::make_device_buffer(buffers[3], resource, stream, input.data(), asc::std::size_t(4)).success());
    for (int i = 0; i < 4; ++i) {
        check(buffers[i].size() == 4 && buffers[i].size_bytes() == 4 * sizeof(int));
        check(asc::copy_bytes(stream, output.data() + i * 4, buffers[i].data(), buffers[i].size_bytes()).success());
    }
    finish(stream);
    const int expected[16] = {0, 0, 0, 0, 2, 2, 2, 2, 2, 4, 6, 8, 2, 4, 6, 8};
    for (int i = 0; i < 16; ++i) {
        check(output.data()[i] == expected[i]);
    }
    for (auto& buffer : buffers) {
        check(buffer.close().success());
    }
    check(output.close().success() && input.close().success());
    check(stream.close());
}

int main()
{
    if (aclInit(nullptr) != ACL_SUCCESS) {
        return 1;
    }
    if (!asc::set_current_device(asc::device_ref(0))) {
        check(aclFinalize() == ACL_SUCCESS);
        return 1;
    }
    run_example();
    const bool reset = aclrtResetDevice(0) == ACL_SUCCESS;
    const bool finalized = aclFinalize() == ACL_SUCCESS;
    return reset && finalized ? 0 : 1;
}
```

## 关联API

- [`asc::execution_status`](../../execution_policies_and_status/asc_execution/execution_status.md)：参数校验和任务提交状态；提交成功不表示异步工作已经完成。
