# 多维数据视图与搬运

多维索引、数据视图和张量搬运。

| 头文件 | 功能 |
| --- | --- |
| [asc/mdspan](asc_mdspan/asc_mdspan.md) | 提供非拥有多维数据视图，覆盖Host、GM以及AI Core SIMD编程中的UB；DLPack可用时支持Host侧数据结构转换 |
| [asc/tensor_copy](asc_tensor_copy/asc_tensor_copy.md) | 提供AI Core SIMD编程中支持1至5维形状、步长和填充的GM与UB异步数据搬运功能 |
