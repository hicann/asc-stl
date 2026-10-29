# asc::copy_bytes

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

头文件路径为：`<asc/algorithm>`。

`asc::copy_bytes`按字节把一段Device可访问内存复制到目标地址，适合元素类型未知或需要显式控制字节数的场景。

## 函数原型

```cpp
namespace asc {
asc::execution_status copy_bytes(asc::stream_ref stream, void* destination, const void* source, asc::std::size_t bytes) noexcept;
} // namespace asc
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `stream` | 输入 | 用于按序提交异步工作的Stream。相关资源须保持有效，直至工作完成。 |
| `destination` | 输出 | 用于接收结果的目标存储。异步操作完成前，其存储须保持有效。 |
| `source` | 输入 | 源数据或源对象。异步操作完成前，其存储须保持有效。 |
| `bytes` | 输入 | 处理的数据量，单位为字节。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |

## 约束说明

- 仅可在Host调用。
- Stream必须有效。
- 源和目标须可由Device按指定方向访问、地址不得重叠，并在异步复制完成前保持有效。

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
#include <asc/algorithm>
#include <asc/buffer>


void run_example()
{
    asc::stream stream;
    check(asc::make_stream(stream));
    asc::device_memory_resource device_resource(0);
    asc::pinned_memory_resource host_resource;
    const asc::device_memory_resource_ref device_ref(device_resource);
    const asc::pinned_memory_resource_ref host_ref(host_resource);
    asc::device_buffer<unsigned char> device;
    asc::pinned_buffer<unsigned char> input;
    asc::pinned_buffer<unsigned char> output;
    check(asc::make_device_buffer(device, device_ref, stream, 4).success());
    check(asc::make_pinned_buffer(input, host_ref, stream, 4).success());
    check(asc::make_pinned_buffer(output, host_ref, stream, 4).success());
    const unsigned char expected[4] = {2, 4, 6, 8};
    for (int i = 0; i < 4; ++i) {
        input.data()[i] = expected[i];
    }
    check(asc::copy_bytes(stream, device.data(), input.data(), 4).success());
    check(asc::copy_bytes(stream, output.data(), device.data(), 4).success());
    finish(stream);
    for (int i = 0; i < 4; ++i) {
        check(output.data()[i] == expected[i]);
    }
    check(output.close().success() && input.close().success() && device.close().success());
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

- [`asc::execution_status`](../../../runtime/execution_policies_and_status/asc_execution/execution_status.md)：参数校验和任务提交状态；提交成功不表示异步工作已经完成。
