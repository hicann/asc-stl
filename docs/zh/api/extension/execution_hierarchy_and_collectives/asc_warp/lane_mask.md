# asc::lane_mask

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

`asc::lane_mask`以32位位图表示一个Warp中参与操作的Lane集合。

Lane是线程束（Warp）内线程的通道编号，取值范围为0到31；掩码第i位对应编号为i的Lane，该位为1表示此Lane在集合中。当前线程自身的Lane编号可由[`asc::lane_id`](../asc_hierarchy/lane_id.md)获取，只包含当前Lane的掩码可由[`asc::lane_mask::this_lane`](lane_mask_this_lane.md)获取。

## 声明

```cpp
namespace asc {
class lane_mask;
} // namespace asc
```

## 约束说明

- 掩码值的构造、观察和位运算可用于Host、AI Core SIMD编程与AI Core SIMT编程。
- 每一位对应Warp中编号0—31的一个Lane；1表示该Lane被选择。
- 掩码值本身不执行同步；把它用于Warp操作时还须满足该操作的参与者会合要求。

## 调用示例

以1个block、32个线程启动，所有lane收敛执行本片段。output指向32个GM元素；同步完成后每项应为1。

```cpp
#include <asc/warp>

__global__ void example(unsigned int* output)
{
    const unsigned int lane = asc::lane_id();
    const asc::lane_mask mask = asc::lane_mask::this_lane();
    output[lane] = mask.value() == (1U << lane);
}
```

完整工程及运行步骤见[《warp_collectives示例》](../../../../../../examples/extension/warp_collectives/README.md)。

## 关联API

- [本头文件的接口列表](asc_warp.md)
