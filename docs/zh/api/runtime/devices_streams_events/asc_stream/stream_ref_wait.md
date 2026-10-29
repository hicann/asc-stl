# asc::stream_ref::wait

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

`asc::stream_ref::wait`向该Stream提交对指定Event的等待，使后续任务在Event完成后执行。

## 函数原型

所属类型：[`asc::stream_ref`](stream_ref.md)。

```cpp
// asc::stream_ref 类内的声明节选；模板形参和其他成员由所属类提供。
bool wait(asc::event_ref event) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `event` | 输入 | 用于记录或等待执行进度的Event引用。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 提供可为空的非拥有Host引用。
- 原生句柄为不透明void指针。
- 仅当CANN Runtime调用成功时才更新查询结果和输出参数。

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
    asc::stream producer;
    asc::stream consumer;
    asc::event ready;
    check(asc::make_stream(producer) && asc::make_stream(consumer));
    check(asc::make_event(ready));
    asc::device_memory_resource device_resource(0);
    asc::pinned_memory_resource host_resource;
    asc::device_buffer<unsigned char> device;
    asc::pinned_buffer<unsigned char> output;
    check(asc::make_device_buffer(device, asc::device_memory_resource_ref(device_resource), producer, 4).success());
    check(asc::make_pinned_buffer(output, asc::pinned_memory_resource_ref(host_resource), consumer, 4).success());
    check(asc::fill_bytes(producer, device.data(), 0x2A, 4).success());
    check(ready.record(producer));
    check(asc::stream_ref(consumer.native_handle()).wait(ready));
    check(asc::copy_bytes(consumer, output.data(), device.data(), 4).success());
    finish(consumer);
    finish(producer);
    for (int i = 0; i < 4; ++i) {
        check(output.data()[i] == 0x2A);
    }
    check(output.close().success() && device.close().success());
    check(ready.close() && consumer.close() && producer.close());
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

- [`asc::stream_ref`](stream_ref.md)
- [本头文件的接口列表](asc_stream.md)
