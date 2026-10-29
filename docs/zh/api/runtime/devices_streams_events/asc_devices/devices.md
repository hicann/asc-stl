# asc::devices

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

头文件路径为：`<asc/devices>`。

`asc::devices`按序号把最多`capacity`个Device引用写入调用方数组，并通过`count`返回Runtime报告的完整Device数量。

## 函数原型

```cpp
namespace asc {
bool devices(asc::device_ref* output, asc::std::uint32_t capacity, asc::std::uint32_t& count) noexcept;
}  // namespace asc
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 接收device_ref的调用方数组首地址：写入min(capacity, Device总数)个按序号递增的引用；capacity非0时不得为空。 |
| `capacity` | 输入 | 数组可容纳的device_ref个数：仅限制实际写入数量，不影响count报告的总数。 |
| `count` | 输出 | Runtime报告的Device总数经该引用写入：可能大于capacity（此时仅写入前capacity个引用）。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 仅可在Host查询或选择Device。
- 引用只保存设备序号且不拥有Runtime状态。
- 查询失败时输出参数保持原值，属性仅限当前接口列出的AI Core、Vector Core、Warp、UB、GM、L2与架构字段。

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
#include <asc/devices>
#include <vector>


void run_example()
{
    asc::std::uint32_t available = 0;
    check(asc::devices(nullptr, 0, available));
    check(available > 0);
    std::vector<asc::device_ref> output(available, asc::device_ref(99));
    asc::std::uint32_t total = 0;
    check(asc::devices(output.data(), available, total));
    check(total == available);
    for (asc::std::uint32_t i = 0; i < total; ++i) {
        check(output[i].ordinal() == i);
    }
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

- [本头文件的接口列表](asc_devices.md)
