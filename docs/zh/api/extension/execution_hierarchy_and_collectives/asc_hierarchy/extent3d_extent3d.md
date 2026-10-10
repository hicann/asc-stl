# asc::extent3d::extent3d

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

头文件路径为：`<asc/hierarchy>`。

`asc::extent3d::extent3d` 使用调用方提供的参数初始化 `asc::extent3d` 对象。

## 函数原型

```cpp
constexpr asc::extent3d::extent3d(unsigned int x = 1, unsigned int y = 1, unsigned int z = 1) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `x` | 输入 | 指定“使用调用方提供的参数初始化 `asc::extent3d` 对象”使用的标量值；取值须满足声明和约束。 |
| `y` | 输入 | 指定“使用调用方提供的参数初始化 `asc::extent3d` 对象”使用的标量值；取值须满足声明和约束。 |
| `z` | 输入 | 指定“使用调用方提供的参数初始化 `asc::extent3d` 对象”使用的标量值；取值须满足声明和约束。 |

## 约束说明

- 提供 C++17 constexpr Host/Device 层次结构接口
- 带 extent 的值要求每一维均非零
- extent 总数按无符号 64 位的 x*y*z 计算

## 调用示例

以下 Host 片段使用具体类型演示本页接口；对象和指针的有效期须满足本页约束。

```cpp
#include <asc/hierarchy>

void example()
{
    asc::extent3d dimensions(2, 3, 4);
    (void)dimensions.count();
}
```
