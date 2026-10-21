# asc::lane_mask::operator&=

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

`asc::lane_mask::operator&=`把当前Lane掩码更新为与另一掩码按位与的结果。

## 函数原型

所属类型：[`asc::lane_mask`](lane_mask.md)。

```cpp
// asc::lane_mask 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr asc::lane_mask& operator&=(asc::lane_mask other) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 第二个掩码值；比较或位运算不修改此操作数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::lane_mask&` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- 掩码值的构造、观察和位运算可用于Host、D-SIMD与D-SIMT。
- 每一位对应Warp中编号0—31的一个Lane；1表示该Lane被选择。
- 掩码值本身不执行同步；把它用于Warp操作时还须满足该操作的参与者会合要求。

## 调用示例

以下Host示例使用具体掩码检查位运算及返回对象；掩码值操作本身不执行Warp同步。

```cpp
#include <asc/warp>
bool example()
{
    asc::lane_mask left(3u);
    asc::lane_mask right(5u);
    auto& result = (left &= right);
    return &result == &left && left.value() == 1u;
}
```

## 关联API

- [`asc::lane_mask`](lane_mask.md)：Warp内Lane的位集合；第i位对应编号为i的Lane。
