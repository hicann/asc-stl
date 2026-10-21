# asc::is_ub_accessor_v

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

头文件路径为：`<asc/mdspan>`。

`asc::is_ub_accessor_v`表示类型是否为UB mdspan访问器。

## 声明

```cpp
namespace asc {
template <class T>
inline constexpr bool is_ub_accessor_v = false;
}  // namespace asc
```

## 约束说明

- 这是编译期类型查询，不读写元素、查询Runtime或建立设备同步；可用类型仍受相应执行位置门控。

- 声明代码展示主模板；对应包装器或mdspan类型由头文件的特化识别。类型匹配不自动移除cv/ref限定，查询不访问实际数据或设备。


## 调用示例

以下片段用具体模板实参读取接口值。

```cpp
#include <asc/mdspan>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

inline constexpr auto example = asc::is_ub_accessor_v<asc::ub_accessor<asc::std::default_accessor<int>>>;
```

## 关联API

- [本头文件的接口列表](asc_mdspan.md)
