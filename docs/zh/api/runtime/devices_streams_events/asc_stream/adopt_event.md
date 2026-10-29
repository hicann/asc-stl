# asc::adopt_event

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

`asc::adopt_event`把非空的Runtime Event原生句柄所有权交给空的`event`对象，不创建新的Runtime资源。

该接口的可用位置为Host。

## 函数原型

```cpp
namespace asc {
bool adopt_event(asc::event_ref::native_handle_type handle, asc::event& output) noexcept;
}  // namespace asc
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `handle` | 输入 | Runtime原生句柄（native_handle_type，不透明void指针），不是包装器对象；adopt接管所有权，ref构造仅借用。 |
| `output` | 输出 | 提供“把非空的Runtime Event原生句柄所有权交给空的`event`对象，不创建新的Runtime资源”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 句柄不得为空，输出对象在调用前必须为空。
- 失败时输出保持不变，成功时转移资源所有权。

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


void run_example()
{
    asc::stream stream;
    check(asc::make_stream(stream));
    aclrtEvent handle = nullptr;
    check(aclrtCreateEvent(&handle) == ACL_SUCCESS);
    asc::event owner;
    if (!asc::adopt_event(handle, owner)) {
        check(aclrtDestroyEvent(handle) == ACL_SUCCESS);
        check(false);
    }
    check(owner.native_handle() == handle);
    check(owner.record(stream));
    finish(stream);
    // Ownership now belongs to owner; do not destroy handle separately.
    check(owner.close() && !owner);
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

- [本头文件的接口列表](asc_stream.md)
