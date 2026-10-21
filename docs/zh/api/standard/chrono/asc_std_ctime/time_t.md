# asc::std::time_t

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

头文件路径为：`<asc/std/ctime>`。

`asc::std::time_t`是日历时间数值类型；Host沿用平台time.h，Device提供long long类型但不提供墙钟time()入口。

标准语义参考：[cppreference `ctime`](https://en.cppreference.com/w/cpp/header/ctime)。

## 声明

Host使用系统`<time.h>`的同名类型；Device使用`long long`。

```cpp
namespace asc::std {
// Host
using ::time_t;
}
```

Device对应的类型声明为：

```cpp
namespace asc::std {
using time_t = long long;
}
```

## 约束说明

- Host使用标准时钟。
- AI Core SIMD编程中使用get_sys_cnt，AI Core SIMT编程中使用clock64。
- Device计数器频率为页面声明的1 GHz，difftime仅进行值计算。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/ctime>

bool example()
{
    asc::std::time_t start = 0;
    asc::std::time_t finish = 60;
    return asc::std::difftime(finish, start) == 60.0;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ctime.md)
