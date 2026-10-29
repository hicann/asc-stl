# asc::event::`operator=`

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

`asc::event::operator=`交换当前对象与源对象持有的Runtime Event句柄，完成所有权移动。

## 函数原型

所属类型：[`asc::event`](event.md)。

```cpp
// asc::event 类内的声明节选；模板形参和其他成员由所属类提供。
asc::event& operator=(asc::event&& other) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待移动的拥有者，须传入右值（如static_cast<所属类型&&>(other)）；赋值交换两个句柄，原目标句柄由other继续持有，复制赋值不可用。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::event&` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- 仅可在Host使用且对象不可复制。
- 移动操作转移资源所有权。
- close()负责同步并销毁自身资源，失败时保留所有权。
- 析构函数会尝试完成本地清理。

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
    asc::event source;
    asc::event target;
    check(asc::make_stream(stream));
    check(asc::make_event(source) && asc::make_event(target));
    void* source_handle = source.native_handle();
    void* target_handle = target.native_handle();
    asc::event& result = (target = static_cast<asc::event&&>(source));
    check(&result == &target && target.native_handle() == source_handle);
    check(source.native_handle() == target_handle);
    check(source.record(stream) && target.record(stream));
    finish(stream);
    check(source.close() && target.close() && stream.close());
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

- [`asc::event`](event.md)
- [本头文件的接口列表](asc_stream.md)
