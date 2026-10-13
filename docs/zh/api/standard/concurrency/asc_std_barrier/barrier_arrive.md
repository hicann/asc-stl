# asc::std::barrier::arrive

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

`asc::std::barrier::arrive` 登记当前参与者到达同步阶段并返回阶段令牌。

该接口的可用位置为 Host、AI Core SIMT 编程。

标准语义参考：[cppreference `barrier`](https://en.cppreference.com/w/cpp/header/barrier)。

## 函数原型

```cpp
arrival_token asc::std::barrier::arrive(long long update);
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `update` | 输入 | 本次登记的到达数量，须为正数（缺省为 1）；单个阶段内的到达总数不得超过初始参与数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `arrival_token` | 返回阶段令牌。 |

## 约束说明

- Host 侧对象管理 Ascend 950 的 GM 状态
- 所有参与者必须能够并发推进，带等待的操作还要求完成条件可被满足

## 调用示例

以下 Host 片段使用一个可独立完成的参与者演示调用；多参与者场景须保证并发推进。

```cpp
#include <asc/std/barrier>

void example()
{
    asc::std::barrier<> barrier(1);
    auto token = barrier.arrive(1);
    barrier.wait(static_cast<asc::std::barrier<>::arrival_token&&>(token));
}
```
