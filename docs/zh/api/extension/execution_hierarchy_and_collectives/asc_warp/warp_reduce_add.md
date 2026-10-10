# asc::warp_reduce_add

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

`asc::warp_reduce_add` 对当前 Warp 中所有参与 Lane 的 `value` 求和，并把同一归约结果返回给每个参与 Lane。该接口用于在不经过全局内存中转的情况下完成 Warp 内加法归约。

## 函数原型

### 原型 1

```cpp
float asc::warp_reduce_add(float value) noexcept;
```

### 原型 2

```cpp
int asc::warp_reduce_add(int value) noexcept;
```

### 原型 3

```cpp
unsigned int asc::warp_reduce_add(unsigned int value) noexcept;
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 当前 Lane 参与归约的值。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 当前 Lane 参与归约的值。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 当前 Lane 参与归约的值。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `float` | 返回所有参与 Lane 的 float 输入值之和。 |
| 原型 2 | `int` | 返回所有参与 Lane 的 int 输入值之和。 |
| 原型 3 | `unsigned int` | 返回所有参与 Lane 的 unsigned int 输入值之和。 |

## 约束说明

- 仅可在 AI Core SIMT 编程中调用
- 所有参与的活动线程必须以收敛控制流调用

## 调用示例

以下 AI Core SIMT 片段让每个 Lane 以自身编号参与加法归约，并检查所有参与 Lane 得到相同结果。

```cpp
#include <asc/warp>

__aicore__ bool example()
{
    const unsigned int lane = asc::lane_id();
    const unsigned int sum = asc::warp_reduce_add(lane);

    // 一个完整Warp的Lane编号为0至31，归约结果应为496。
    return sum == 496U;
}
```

对应完整工程使用 `C++17`，并通过Ascend 950 真机编译与运行验证。

完整示例源码：

- [CMakeLists.txt](../../../../examples/warp_collectives/CMakeLists.txt)
- [warp_example.h](../../../../examples/warp_collectives/warp_example.h)
- [kernel.asc](../../../../examples/warp_collectives/kernel.asc)
- [main.cpp](../../../../examples/warp_collectives/main.cpp)
