# asc::lane_mask::operator^

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

`asc::lane_mask::operator^`返回两个Lane掩码的按位异或结果。

## 函数原型

所属类型：[`asc::lane_mask`](lane_mask.md)。

```cpp
// asc::lane_mask 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr asc::lane_mask operator^(asc::lane_mask other) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::lane_mask` | 返回两个Lane掩码的按位异或结果。 |

## 约束说明

- 掩码值的构造、观察和位运算可用于Host、D-SIMD与D-SIMT。
- 每一位对应Warp中编号0—31的一个Lane；1表示该Lane被选择。
- 掩码值本身不执行同步；把它用于Warp操作时还须满足该操作的参与者会合要求。

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/warp>

template <class Object, class... Args>
__aicore__ decltype(auto) example(Object& object, Args&&... args)
{
    return object.operator^(static_cast<Args&&>(args)...);
}
```

对应完整工程使用`C++17`；请在目标工具链及设备上编译和运行。

完整示例源码：

- [CMakeLists.txt](../../../../examples/warp_collectives/CMakeLists.txt)
- [warp_example.h](../../../../examples/warp_collectives/warp_example.h)
- [kernel.asc](../../../../examples/warp_collectives/kernel.asc)
- [main.cpp](../../../../examples/warp_collectives/main.cpp)

## 关联API

- [`asc::lane_mask`](lane_mask.md)：Warp内Lane的位集合；第i位对应编号为i的Lane。
