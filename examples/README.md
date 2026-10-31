# ASC-STL示例

[English](README_en.md) | [快速入门](../docs/zh/quick_start.md)

每个示例只有一份源码，中英文文档共用。API页面链接到这里，提供完整程序、构建步骤
和结果检查。标准层示例使用已有Host能力；其余工程需要CANN及支持的昇腾设备才能执行。

## 示例索引

| 示例 | 主要接口 | 执行位置 |
| --- | --- | --- |
| [分配器特征与内外层访问](standard/allocator_traits/README.md) | `allocator_traits / scoped_allocator_adaptor` | Host |
| [显式分配器vector](standard/explicit_allocator_vector/README.md) | `vector / type_traits` | Host |
| [指针特征与对齐](standard/pointer_alignment/README.md) | `memory / pointer_traits` | Host |
| [完整Add + ReLU入门](quick_start/README.md) | `std::max / pipeline` | Host + AI Core SIMD |
| [Warp集体操作](extension/warp_collectives/README.md) | `warp` | Host + AI Core SIMT |
| [GM原子操作与屏障](extension/atomic_operations/README.md) | `atomic / barrier` | Host + AI Core SIMT |
| [GM与UB流水拷贝](extension/pipeline_copy/README.md) | `pipeline / memory` | Host + AI Core SIMD |
| [57个并行算法案例](extension/parallel_algorithms/README.md) | `algorithm / execution` | Host + AI Core SIMT |
| [Stream与Event生命周期](runtime/stream_event/README.md) | `devices / stream` | Host + CANN Runtime |

## 构建与运行Host示例

在仓库根目录执行以下命令。需要CMake 3.20或更新版本，以及支持C++17/20的编译器
和配套系统库；不需要安装CANN。

```bash
cmake -S examples -B build/examples17 -DASC_STL_EXAMPLE_STANDARD=17 -DCMAKE_BUILD_TYPE=Release
cmake --build build/examples17 -j2
ctest --test-dir build/examples17 --output-on-failure
```

C++20改用`-DASC_STL_EXAMPLE_STANDARD=20`及独立构建目录。三个Host案例都应通过。
各主题也支持单独CMake构建，具体命令见其README。allocator_traits包含编译期类型检查，
三个案例均包含运行时结果检查。

产品顶层CMake也支持`-DASC_STL_BUILD_EXAMPLES=ON`，默认为OFF。集成头文件库时可用
`BUILD_TESTING=OFF`关闭测试登记，显式启用的示例仍会构建。若在产品构建中只执行
这些测试，使用`ctest --test-dir <build> -R '^examples[.]' --output-on-failure`。

## 可选Runtime与Device构建

配置前先source实际安装的CANN `set_env.sh`。Kernel工程使用CANN的ASC或AscendC
CMake模块，目标为Ascend 950PR/950DT；各工程分别列出环境要求。Toolkit可用于编译，
执行还需要配套Runtime、驱动和可用设备。

```bash
cmake -S examples -B build/examples-device17 -DASC_STL_EXAMPLE_STANDARD=17 \
  -DASC_STL_BUILD_RUNTIME_EXAMPLES=ON -DASC_STL_BUILD_DEVICE_EXAMPLES=ON \
  -DCMAKE_ASC_ARCHITECTURES=dav-3510 -DSOC_VERSION=Ascend950PR_9599 -DCMAKE_BUILD_TYPE=Release
cmake --build build/examples-device17 -j2
```

两项选项默认均为OFF。构建与CTest都不会自动执行Runtime或Kernel程序。
Runtime可执行文件位于`runtime/stream_event/`；Kernel工程分别构建在`device/<name>/`，
可在对应构建目录按各示例说明显式运行。Kernel构建目标为`asc_stl_example_<name>`，
例如`asc_stl_example_quick_start`。并行算法工程使用专用runner记录57个案例。

## 示例约定

- 使用公共Header，给出明确输入、预期结果及失败退出码。
- 中英文README说明用途、支持环境、文件职责、编译运行步骤与预期结果，语言和
  执行模式要求应对应实际案例。
- `ASC_STL_EXAMPLE_STANDARD`选择17/20，`ASC_STL_INCLUDE_DIR`可指定其它include树；
  默认从示例位置解析本仓库的头文件。
- 编译、模拟和真机执行分别说明；编译成功不代表设备结果正确或具有性能收益。
- API说明和短代码片段保留在docs并链接到示例源码；回归与错误路径测试保留在test。
