# asc::warp_shuffle_result

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

`asc::warp_shuffle_result`同时保存Warp Shuffle取得的数据及源Lane是否有效。

该接口的可用位置为AI Core SIMT编程。

## 声明

```cpp
namespace asc {
template<class T> struct warp_shuffle_result;
} // namespace asc
```

## 约束说明

- T仅可为int、unsigned int、float、long long或unsigned long long。

## 调用示例

以1个block、32个线程启动，所有lane收敛执行本片段。output指向32个GM元素；同步完成后每项应为1。

```cpp
#include <asc/warp>

__global__ void example(unsigned int* output)
{
    const unsigned int lane = asc::lane_id();
    const asc::warp_shuffle_result<unsigned int> result = asc::warp_shuffle_idx<32>(lane, 0, asc::lane_mask::all());
    output[lane] = result.valid && result.data == 0;
}
```

完整工程及运行步骤见[《warp_collectives示例》](../../../../../../examples/extension/warp_collectives/README.md)。

## 关联API

- [本头文件的接口列表](asc_warp.md)
