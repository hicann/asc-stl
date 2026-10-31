# mdspan二维访问

[English](README_en.md) | [示例总览](../../README.md)

## 概述

同一线性存储1到6分别建立2×3的行主序和列主序视图。计算各视图的两行总和，然后通过行主序视图写入20，并从另一视图观察同一存储位置。

主要公共接口：mdspan、extents、layout_right、layout_left。

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
```

Host成功退出码为0。Device成功还须同时满足退出码0、cleanup_passed=1和ASC_STL_STANDARD_DEVICE_PASS；device_cplusplus在C++17为201703，C++20为202002。Host上传真实GM输入，Kernel计算并回写，Host以独立常量检查结果。

## 约束说明

改变布局只改变索引映射，不转置或复制数据；两组行和在写入20之前计算。C++17/20使用operator()访问。底层存储须覆盖布局范围；Device演示使用线程私有普通指针，不提供GM/UB访问器。

Device任务执行时限为10秒，Stream等待上限为10000毫秒，均检查返回值；外层timeout限制进程。同步失败时保留可能仍在使用的buffer，尝试reset/finalize并保持失败。设备错误或超时后停止后续投放，先检查设备状态。这些标量案例演示语义，不提供并行加速结论。

## 关联API

- [mdspan](../../../docs/zh/api/standard/containers/asc_std_mdspan/mdspan.md)
