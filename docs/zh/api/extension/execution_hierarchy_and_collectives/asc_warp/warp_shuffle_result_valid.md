# asc::warp_shuffle_result::valid

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

`asc::warp_shuffle_result::valid` 标记 Warp Shuffle 的源 Lane 是否有效并参与操作。

该接口的可用位置为 AI Core SIMT 编程。

## 声明

```cpp
bool asc::warp_shuffle_result<T>::valid
```

## 约束说明

- T 仅可为 int、unsigned int、float、long long 或 unsigned long long

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/warp>

template <class T>
__aicore__ void example(const asc::warp_shuffle_result<T>& object)
{
    (void)object.valid;
}
```

对应完整工程使用 `C++17`，并通过Ascend 950 真机编译与运行验证。

完整示例源码：

- [CMakeLists.txt](../../../../examples/warp_collectives/CMakeLists.txt)
- [warp_example.h](../../../../examples/warp_collectives/warp_example.h)
- [kernel.asc](../../../../examples/warp_collectives/kernel.asc)
- [main.cpp](../../../../examples/warp_collectives/main.cpp)
