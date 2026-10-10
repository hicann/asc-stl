# 多维数据视图与搬运

多维索引、数据视图和张量搬运。

| 头文件 | 功能 |
| --- | --- |
| [asc/mdspan](asc_mdspan/asc_mdspan.md) | 提供非拥有多维数据视图，覆盖 Host、GM 以及 AI Core SIMD 编程中的 UB；DLPack 可用时支持 Host 侧数据结构转换 |
| [asc/tensor_copy](asc_tensor_copy/asc_tensor_copy.md) | 提供 AI Core SIMD 编程中支持 1 至 5 维形状、步长和填充的 GM 与 UB 异步数据搬运功能 |
