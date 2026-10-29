# asc::make_stream

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

`asc::make_stream`按指定优先级创建Runtime Stream，并把所有权写入空的`stream`对象；输出对象已持有句柄或创建失败时返回false。

该接口的可用位置为Host。

## 函数原型

```cpp
namespace asc {
bool make_stream(asc::stream& output, asc::std::uint32_t priority = 0) noexcept;
} // namespace asc
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 待接收新建Stream的空stream对象引用：须尚未持有句柄，成功后获得新Runtime Stream的所有权；已持有句柄时直接返回失败。 |
| `priority` | 输入 | 新建Stream的优先级（uint32_t，传给底层Runtime；0为常规优先级）。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- `output`非空（已持有句柄）时本接口拒绝执行，直接返回`false`，不创建新的Runtime Stream，也不修改`output`。
- output失败时保持不变。

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
    check(!stream);
    check(asc::make_stream(stream, 0));
    check(static_cast<bool>(stream));
    check(!asc::make_stream(stream));
    asc::std::uint32_t priority = 99;
    check(stream.priority(priority) && priority == 0);
    finish(stream);
    check(stream.close() && !stream);
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
