# mdspan二维访问与带padding张量裁剪转置

[English](README_en.md) | [示例总览](../../README.md)

## 概述

同一线性存储1到6分别建立2×3的行主序和列主序视图。计算各视图的两行总和，然后通过行主序视图写入20，并从另一视图观察同一存储位置。

同时执行一个张量预处理算子：输入为2×3×4张量，batch/row/column的元素跨步为24/7/1，存储跨度为42；按batch选取、行区间裁剪、列步进采样，再将裁剪结果转置写入连续输出。8组参数覆盖两批数据、完整裁剪、非零列起点、不能整除的步长、大于区间长度的步长及3种空切片。

主要公共接口：mdspan、extents、dextents、layout_right、layout_left、layout_stride、submdspan、strided_slice、pair、span::subspan。

## 支持环境

- Host：支持C++17/20的编译器及配套系统库，CMake 3.20或更新版本，无需CANN。
- Device：Ascend 950PR/950DT、提供ASC CMake模块和毕昇编译器的CANN、配套驱动和Runtime，以及可用逻辑设备0。使用SIMT，由一个活动线程完成计算。

## 文件职责

- [example.h](example.h)：Host和Device共用的计算逻辑。
- [example_types.h](example_types.h)：普通输入/输出类型。
- [check.h](check.h)：Host输入、独立预期值及输出检查。
- [共用Host入口](../../common/standard_host_main.cpp)：构造输入、调用计算并检查结果。
- [共享Kernel](../../common/standard_kernel.asc)与[Host启动程序](../../common/standard_device_main.cpp)：上传、启动、有界等待、回读和清理。
- [CMakeLists.txt](CMakeLists.txt)：独立构建。

## Host编译运行

在仓库根目录执行：

```bash
cmake -S examples/standard/mdspan_matrix -B build/mdspan_matrix17 -DASC_STL_EXAMPLE_STANDARD=17 -DCMAKE_BUILD_TYPE=Release
cmake --build build/mdspan_matrix17 -j2
build/mdspan_matrix17/asc_stl_mdspan_matrix
ctest --test-dir build/mdspan_matrix17 --output-on-failure
```

## Device编译运行

source实际安装的CANN set_env.sh后，在仓库根目录执行：

```bash
cmake -S examples/standard/mdspan_matrix -B build/mdspan_matrix-device17 \
  -DASC_STL_EXAMPLE_DEVICE=ON -DASC_STL_EXAMPLE_STANDARD=17 \
  -DCMAKE_ASC_ARCHITECTURES=dav-3510 -DCMAKE_BUILD_TYPE=Release
cmake --build build/mdspan_matrix-device17 --target asc_stl_mdspan_matrix_device -j2
timeout --signal=TERM --kill-after=10s 60s build/mdspan_matrix-device17/asc_stl_mdspan_matrix_device
```

C++20改用语言选项20及独立构建目录。CTest只执行Host程序，NPU运行须显式调用。

## 预期结果

Host和Device应得到相同的计算结果：

```text
row_major_sums=6,15 column_major_sums=9,12
shared_storage=20 column_view=20
padded_crop_transpose_cases=8 elements=26 guards=PASS
```

Host成功退出码为0。Device成功还须同时满足退出码0、cleanup_passed=1和ASC_STL_STANDARD_DEVICE_PASS；device_cplusplus在C++17为201703，C++20为202002。Host上传真实GM输入，Kernel计算并回写，Host以独立常量检查结果。

## 算子逻辑与简化依据

手写地址计算时，输出元素需要组合batch跨步、行跨步、裁剪起点、采样步长与转置索引：

```cpp
output[column * rows + row] = input[batch * 24 + (row_first + row) * 7 +
    column_offset + column * column_stride];
```

本示例在创建源映射时集中描述24/7/1跨步，用`submdspan`组合裁剪规则，再让循环直接表达坐标变换：

```cpp
transposed(column, row) = crop(row, column);
```

`span::subspan`为每组输出划分独立窗口。预期值在Host使用源坐标枚举和原始地址公式独立计算，检查26个输出元素、各裁剪形状与所有未用输出位置的哨兵。库中的映射和切片实现不作为预期值来源。此用法减少了计算循环中反复拼接地址的负担，不承诺总代码行数减少或执行加速。

`strided_slice{offset, extent, stride}`中的`extent`表示覆盖的源区间长度；实际元素数为`extent == 0 ? 0 : 1 + (extent - 1) / stride`。例如列区间`{1, 3, 2}`选择源列1、3，共两列。空切片不访问元素，但仍保留相应的空结果维度。

## 约束说明

改变布局只改变索引映射，不转置或复制数据；两组行和在写入20之前计算。C++17/20使用operator()访问。底层存储须覆盖布局范围；Device演示使用纯SIMT普通指针，不使用显式GM/UB访问器；张量输入来自Host上传的设备存储。8组小尺寸案例由同一活动线程执行，用于验证组合语义。

Device任务执行时限为10秒，Stream等待上限为10000毫秒，均检查返回值；外层timeout限制进程。同步失败时保留可能仍在使用的buffer，尝试reset/finalize并保持失败。设备错误或超时后停止后续投放，先检查设备状态。这些标量案例演示语义，不提供并行加速结论。

## 关联API

- [mdspan](../../../docs/zh/api/standard/containers/asc_std_mdspan/mdspan.md)
- [submdspan](../../../docs/zh/api/standard/containers/asc_std_mdspan/submdspan.md)
- [strided_slice](../../../docs/zh/api/standard/containers/asc_std_mdspan/strided_slice.md)
