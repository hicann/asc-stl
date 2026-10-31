# asc::lane_mask::all_greater

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

`asc::lane_mask::all_greater`返回Lane编号大于当前Lane的掩码。

## 函数原型

所属类型：[`asc::lane_mask`](lane_mask.md)。

```cpp
// asc::lane_mask 类内的声明节选；模板形参和其他成员由所属类提供。
static asc::lane_mask all_greater() noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::lane_mask` | 返回Lane编号大于当前Lane的掩码。 |

## 约束说明

- 相对位置集合与本次调用的活动Lane集合相交；分歧控制流中的非活动Lane不会仅因编号关系而被加入。全Warp收敛时才等于全部32位编号的相对掩码。

- 仅可在AI Core SIMT编程中调用。
- 每一位对应Warp中编号0—31的一个Lane；1表示该Lane被选择。
- 仅在AI Core SIMT编程中查询当前Warp；活跃位集合以本次调用位置为准。
- 掩码值本身不执行同步；把它用于Warp操作时还须满足该操作的参与者会合要求。

## 调用示例

以1个block、32个线程启动，所有lane收敛执行本片段。output指向32个GM元素；同步完成后每项应为1。

```cpp
#include <asc/warp>

__global__ void example(unsigned int* output)
{
    const unsigned int lane = asc::lane_id();
    const asc::lane_mask mask = asc::lane_mask::all_greater();
    output[lane] = mask.value() == ((lane == 31U ? 0U : 0xffffffffU << (lane + 1U)));
}
```

完整工程及运行步骤见[《warp_collectives示例》](../../../../../../examples/extension/warp_collectives/README.md)。

## 关联API

- [`asc::lane_mask`](lane_mask.md)：Warp内Lane的位集合；第i位对应编号为i的Lane。
