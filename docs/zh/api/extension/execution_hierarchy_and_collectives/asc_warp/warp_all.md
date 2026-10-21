# asc::warp_all

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

头文件路径为：`<asc/warp>`。

`asc::warp_all`判断当前Warp的所有活动Lane谓词是否都为true。

## 函数原型

```cpp
namespace asc {
bool warp_all(bool predicate) noexcept;
}  // namespace asc
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `predicate` | 输入 | 本Lane或线程已经求得的bool投票值；接口直接集体处理此值，不调用谓词函数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 仅可在AI Core SIMT编程中调用。
- 所有参与的活动线程必须以收敛控制流调用。

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/warp>

__aicore__ decltype(auto) example(bool predicate)
{
    return asc::warp_all(predicate);
}
```

对应完整工程使用`C++17`；请在目标工具链及设备上编译和运行。

完整示例源码：

- [CMakeLists.txt](../../../../examples/warp_collectives/CMakeLists.txt)
- [warp_example.h](../../../../examples/warp_collectives/warp_example.h)
- [kernel.asc](../../../../examples/warp_collectives/kernel.asc)
- [main.cpp](../../../../examples/warp_collectives/main.cpp)

## 关联API

- [本头文件的接口列表](asc_warp.md)
