# asc::stream_ref::stream_ref

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

默认构造函数创建空Stream引用；带参构造函数包装给定原生句柄但不取得其所有权。

## 函数原型

所属类型：[`asc::stream_ref`](stream_ref.md)。

### 原型1

```cpp
// asc::stream_ref 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr stream_ref() noexcept;
```

### 原型2

```cpp
// asc::stream_ref 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr explicit stream_ref(asc::stream_ref::native_handle_type handle) noexcept;
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `handle` | 输入 | Runtime原生句柄（native_handle_type，不透明void指针），不是包装器对象；adopt接管所有权，ref构造仅借用。 |

## 返回值说明

无返回值。

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


void run_example()
{
    asc::stream_ref empty;
    check(!empty);
    asc::stream owner;
    check(asc::make_stream(owner));
    asc::stream_ref view(owner.native_handle());
    check(view && view.native_handle() == owner.native_handle());
    finish(view);
    check(owner.close());
    // view does not own the handle and must not be used after owner.close().
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
