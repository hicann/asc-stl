# asc::std::barrier::arrival_token

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

头文件路径为：`<asc/std/barrier>`。

`asc::std::barrier::arrival_token` 标识线程已到达的屏障阶段。

该接口的可用位置为 Host、AI Core SIMT 编程。

标准语义参考：[cppreference `barrier`](https://en.cppreference.com/w/cpp/header/barrier)。

## 声明

```cpp
class asc::std::barrier::arrival_token
```

## 约束说明

- Host 侧对象管理 Ascend 950 的 GM 状态
- 所有参与者必须能够并发推进，带等待的操作还要求完成条件可被满足

## 调用示例

以下片段通过具体容器或分布类型实例化嵌套类。

```cpp
#include <asc/std/barrier>

void use_type()
{
    using selected = typename asc::std::barrier<>::arrival_token;
    (void)sizeof(selected);
}
```
