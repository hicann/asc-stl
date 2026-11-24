# 头文件asc/iterator

提供常量、计数、索引、跨步、变换及组合访问。迭代器按值保存状态并借用数据，常量及函数可拥有自己的值。

## 使用方式

```cpp
#include <asc/iterator>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::constant_iterator](constant_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::counting_iterator](counting_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::discard_iterator](discard_iterator.md) | 类 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::make_constant_iterator](make_constant_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::make_counting_iterator](make_counting_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::make_discard_iterator](make_discard_iterator.md) | 函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::make_permutation_iterator](make_permutation_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::make_shuffle_iterator](make_shuffle_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::make_strided_iterator](make_strided_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::make_tabulate_output_iterator](make_tabulate_output_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::make_transform_input_output_iterator](make_transform_input_output_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::make_transform_iterator](make_transform_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::make_transform_output_iterator](make_transform_output_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::make_zip_function](make_zip_function.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::make_zip_iterator](make_zip_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::make_zip_transform_iterator](make_zip_transform_iterator.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::permutation_iterator](permutation_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::shuffle_iterator](shuffle_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::strided_iterator](strided_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::tabulate_output_iterator](tabulate_output_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::transform_input_output_iterator](transform_input_output_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::transform_iterator](transform_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::transform_output_iterator](transform_output_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::zip_function](zip_function.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::zip_iterator](zip_iterator.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::zip_transform_iterator](zip_transform_iterator.md) | 别名模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |

## 迭代器协议

所有迭代器提供 value_type、reference、difference_type、pointer、iterator_category 和 iterator_concept。
差值有符号。基本操作包括解引用和前后置递增；具备相应位置能力时提供前后置递减、+=、-=、两方向加法、偏移减法、距离、下标和六个比较。缺失能力的操作不参与重载。

| 适配器 | value_type / reference | C++17 类别 | C++20 概念上限 |
| --- | --- | --- | --- |
| constant | T / T | input | random_access |
| counting / shuffle | 值类型 / 值类型 | input | random_access |
| permutation | 数据值类型 / 底层引用或代理 | input | 随索引，至 random_access |
| strided | 底层值类型 / 底层引用或代理 | 真引用且底层满足时 random_access，否则 input | random_access |
| transform / zip_transform | 结果去 cv/ref / 函数结果 | input | 随底层，至 random_access |
| input_output | 读取值类型 / 读写代理 | input | 随底层，至 random_access |
| zip 可读组合 | 值 tuple / 组合代理 | input | 最弱分量，至 random_access |
| 只写适配器及只写 zip | void / 写代理 | output | output，另有适用位置操作 |

概念还要求对应公共引用、稳定读取、多遍和复杂度语义；不是仅看标签。所有适配器均不承诺 contiguous。
默认对象未绑定（discard 的默认位置0有效）；可赋值和销毁，支持判等的空默认对象互相相等，未绑定对象不可访问或推进。捕获 lambda 不必默认可构造或可赋值；其状态存储负责必要的重建。

const 迭代器对象不使底层数据只读。底层 const 转换保留地址空间。Host、SIMT、SIMD 的实际访问和函数须在相应位置合法；纯 Host 包含不依赖 SDK。低精度和打包类型按存储元素访问，不自动展开或转换。

读函数 const 调用且结果稳定；输出函数通过代理的可变快照调用。代理拥有位置和函数快照，底层借用生命期仍须有效。按值结果拥有值，引用不能指向已销毁的临时状态；箭头代理仅活到完整表达式结束。

iter_move 作用于逻辑读结果；iter_swap 和代理 swap 只在合法读写/移动/交换组合下提供。读写变换要求写后回读同值，重排要求独立目标和稳定寻址；重复索引或交叉别名不能凭静态概念取得排序保证。异常前已完成的逐项写入不回滚。

strided 接收 first、extent、stride，端点只保存逻辑位置。zip 由调用方给出共同长度；所有分量相等才相等，求距离时各位移一致。本头不发现最短范围、不申请存储或提交并行任务。

## 迁移说明

strided 的旧无界 iterator/stride 形式改为 first/extent/stride；base() 返回物理起点。counting 的 base() 改为 index()，初值与位置分开。zip.equal 改用 ==/!=；zip_transform 为组合别名。补齐完整协议，旧清单中的轻量操作描述不再作为接口限制。
