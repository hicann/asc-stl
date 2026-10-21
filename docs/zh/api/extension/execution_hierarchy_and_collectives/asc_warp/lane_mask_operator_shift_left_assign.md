# asc::lane_mask::`operator<<=`

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

`asc::lane_mask::operator<<=`把当前Lane掩码左移指定位置。

## 函数原型

所属类型：[`asc::lane_mask`](lane_mask.md)。

```cpp
// asc::lane_mask 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr asc::lane_mask& operator<<=(int shift) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `shift` | 输入 | 左移位数（0~31）：本对象的掩码按位左移（低位补0）后写回自身。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::lane_mask&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |

## 约束说明

- shift须在[0, 31]内；负值或不小于32的移位不属于有效调用。

- 掩码值的构造、观察和位运算可用于Host、D-SIMD与D-SIMT。
- 每一位对应Warp中编号0—31的一个Lane；1表示该Lane被选择。
- shift必须在[0, 31] 内；本值运算不执行Warp会合或内存同步。

## 调用示例

以下Host示例使用具体掩码检查位运算及返回对象；掩码值操作本身不执行Warp同步。

```cpp
#include <asc/warp>
bool example()
{
    asc::lane_mask left(3u);
    auto& result = (left <<= 1);
    return &result == &left && left.value() == 6u;
}
```

## 关联API

- [`asc::lane_mask`](lane_mask.md)：Warp内Lane的位集合；第i位对应编号为i的Lane。
