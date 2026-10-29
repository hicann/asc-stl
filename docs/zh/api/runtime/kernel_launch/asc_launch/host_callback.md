# asc::host_callback

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

头文件路径为：`<asc/launch>`。

`asc::host_callback`按指定Stream的任务顺序提交Host回调。Stream或回调函数为空时返回参数无效，底层Runtime失败时保留原生状态码。

## 函数原型

```cpp
namespace asc {
asc::execution_status host_callback(asc::stream_ref stream, host_callback_t callback, void* data) noexcept;
} // namespace asc
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `stream` | 输入 | 用于按序提交异步工作的Stream。相关资源须保持有效，直至工作完成。 |
| `callback` | 输入 | 回调函数指针（host_callback_t = void(*)(void*)）：轮到该Stream队列项时在Host执行；为空时返回参数无效。 |
| `data` | 输入 | 回调执行时透传的用户数据指针：生命周期须覆盖到回调在Stream上实际执行完毕。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |

## 约束说明

- 仅可在Host调用。
- Stream和回调函数必须有效。
- 回调及用户数据须保持有效直至执行，回调不得跨越C接口边界抛出异常。

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
#include <asc/launch>
#include <atomic>

void set_result(void* data)
{
    static_cast<std::atomic<int>*>(data)->store(7, std::memory_order_release);
}

void run_example()
{
    asc::stream stream;
    check(asc::make_stream(stream));
    std::atomic<int> result{0};
    check(asc::host_callback(stream, set_result, &result).success());
    finish(stream);
    check(result.load(std::memory_order_acquire) == 7);
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
