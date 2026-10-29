# ASC-STL

面向昇腾设备编程的C++ 标准库 —— 纯头文件实现，为Host与Device提供统一的公共Header组织

简体中文 | [English](README_en.md)

[📖 api文档](docs/zh/api/README.md) | [📚 路线图](docs/zh/roadmap/roadmap_v1_0_0.md) | [🧪 快速入门](docs/zh/quick_start.md) | [📄 LICENSE](LICENSE) | [🤝 贡献指南](CONTRIBUTING.md)

## 🔥 当前可用状态

**当前可使用 `master` 开发分支中已经实现的标准层功能：`asc::std` 覆盖现有 16 类能力、74 个公共头。** 具体功能和限制见下文[标准层当前功能范围](#标准层当前功能范围)。昇腾扩展层与 Runtime 层正在持续完善。

当前为 `master` 开发版，源码版本标识为 `1.0.0`。目前，仓库尚无正式 [tag](https://gitcode.com/cann/asc-stl/tags) 或 [Release](https://gitcode.com/cann/asc-stl/releases)，正式发布时间待公布。

### 🚀 发布与完善计划

| 对象 | 当前状态 | 后续安排 |
| --- | --- | --- |
| `master` 开发分支 | 标准层已有功能可按文档使用；扩展层和 Runtime 层持续完善 | 持续更新实现、API 约束、示例和回归 |
| `v1.0.0` 首个正式版本 | 尚未发布 | 发布时同步更新 tag、Release 和功能说明 |
| 后续迭代 | 规划中 | 分批完善扩展/Runtime 能力、质量和文档 |

### 📖 文档

- [当前标准层功能范围](#标准层当前功能范围) · [标准层完整 API 支持列表](docs/zh/api/standard/standard.md)。
- [ASC-STL v1.0.0 支持范围说明](docs/zh/roadmap/roadmap_v1_0_0.md)。
- [API 参考文档](docs/zh/api/README.md)：各接口的语言模式、可用位置、约束和示例。

## 🚀 概述

### 设计目标

昇腾设备计算函数（Kernel）开发需要类型系统、容器与视图、算法、数值、原子、同步、内存和并行操作等通用C++ 功能。ASC-STL以**纯头文件库**形式提供这些能力，不生成独立的动态库或静态库：

- **标准习惯直达Kernel**：类型、算法、数值等通用能力以标准C++ 风格提供，Host与Device共用同一套公共Header组织；
- **平台能力显式表达**：GM/UB地址空间、设备执行层次、设备原子与线程同步、Device并行算法等昇腾平台特性，均有明确、显式的公共接口；
- **Runtime能力封装**：设备、Stream/Event、核函数调用与内存资源等运行时能力以公共C++ 接口提供，不直接暴露底层Runtime API类型。

### 接口组成

| 接口 | 命名空间 / 包含路径 | 覆盖范围 | 当前状态 |
| --- | --- | --- | --- |
| C++ 标准库接口 | `asc::std` · `<asc/std/...>` | 语言支持、概念、诊断、内存管理、元编程、通用工具、容器、迭代器、范围、算法、字符串、文本处理、数值、日期和时间、输入/输出、并发支持共16类 | 已有功能可按文档使用 |
| 昇腾扩展接口 | `asc` · `<asc/...>` | 设备原子操作与线程同步、异步数据搬运、地址空间与内存视图、多维数据视图与搬运、设备执行层次与集体操作、Device并行算法及设备侧数值与类型工具共9类 | 已有部分实现，持续完善 |
| Runtime接口 | `asc` · `<asc/...>` | 设备/Stream/Event管理、核函数调用、Device执行策略与执行要求、内存资源/内存池/缓冲区共4类 | 已有部分实现，持续完善 |


### 整体架构

![图1 ASC-STL设计架构](docs/zh/figures/asc_stl_design_architecture_v3.png)

- ASC-STL为纯头文件C++ 库，接口分为C++ 标准库接口、昇腾扩展接口和Runtime接口三部分；
- 设备侧编程能力基于CANN Ascend C提供，代码由毕昇编译器（基于Clang 15.0.5）编译，运行于昇腾 950PR / 950DT 系列处理器；
- 运行时依赖CANN Runtime（AscendCL Runtime API）与NPU驱动，提供设备管理、核函数调用、内存管理及设备访问能力。

### 如何选择能力

- 写通用的类型、算法、数值与同步逻辑 → 使用 **C++ 标准库接口**（按下文标准层范围使用）；
- 操作GM/UB内存、设备原子与线程协作、Device并行算法 → 使用 **昇腾扩展接口**（已有部分实现，持续完善）；
- 管理设备、Stream/Event与核函数调用 → 使用 **Runtime接口**（已有部分实现，持续完善）。

## 🔍 目录结构

ASC-STL采用纯头文件库结构。公共Header集中在`include/asc/`；测试、CMake配置和检查脚本分别位于独立目录。

```text
asc-stl/
├── include/
│   └── asc/                         # ASC-STL 公共 Header 根目录
│       ├── __config                 # 统一配置入口
│       ├── std/                     # C++ 标准库接口：<asc/std/...>
│       │   └── ...                  # 其余内部实现目录（__ 前缀）
│       ├── algorithm                # Device 并行算法
│       ├── atomic                   # 设备原子操作
│       ├── collectives              # 线程组协作操作
│       ├── execution                # Device 执行策略聚合入口
│       ├── memory                   # GM、UB 和内存视图
│       ├── stream                   # stream 和 event 管理
│       └── ...                      # 其他设备能力公共 Header
├── docs/                            # 项目文档与产品路线图
├── test/                            # Host、Device 与仿真测试
├── cmake/                           # CMake 安装和导出配置
├── scripts/                         # 构建检查脚本
├── CMakeLists.txt                   # 顶层 CMake 配置
├── version.cmake                    # 版本定义
├── build.sh                         # 构建与测试入口脚本
├── README.md                        # 项目说明
└── LICENSE                          # 产品许可证
```

`include/asc/std/`下的公共头以`<asc/std/...>`形式提供标准库能力入口；`include/asc/`下其余公共头以`<asc/...>`形式提供昇腾扩展与Runtime能力入口。

## ⚡️ 快速入门

若您希望快速体验 ASC-STL 的使用过程，请访问 [快速入门](docs/zh/quick_start.md)：介绍环境搭建、Host 侧与 Kernel 侧（核函数）的使用方式、编译执行与本地验证，含经测试验证的 Host / Kernel 示例。

使用方式概览：ASC-STL 自身采用纯头文件形式，不单独构建库文件。普通Host算法与类型设施可直接包含公共头使用；调用依赖AscendCL的Runtime接口还须安装相应CANN运行时并链接`ascendcl`，按接口要求初始化设备与资源。Host侧需要支持C++17的编译器及相应系统库，Kernel编译与真机运行需要CANN，详见[软硬件配套说明](#-软硬件配套说明)。

### 环境要求

| 依赖 | 版本 / 说明 |
| --- | --- |
| CANN | 9.2.0 |
| 毕昇CCE / clang | 15.0.5 |
| g++ | 产品最低使用C++17；完整Host测试同时需要C++20支持 |
| CMake | ≥ 3.20 |
| 处理器 | 昇腾 950PR / 950DT 系列处理器 |

CANN同一版本的不同构建可能采用不同SDK目录布局。设备层查询会优先包含
`c_api/utils/sys_var.h`，缺少时使用`c_api/sys_var/sys_var.h`；两者均缺少时会给出
编译错误。Tensor描述符的64位乘法溢出检查采用32位分段运算，避免旧版BiSheng
在动态描述符路径生成设备侧不可用的`__multi3`链接符号；公共接口和状态码保持不变。

Host标准库接口还依赖配套的C库和C++ 标准库。C++20 `<asc/std/cuchar>`的
`c8rtomb`、`mbrtoc8`需要系统`<cuchar>`实际导出这两个接口；GNU/Linux通常需要
glibc 2.36或更新版本，以及构建时启用了相应能力的libstdc++。只升级编译器不足以
满足要求，应在同一环境中检查编译、链接和运行。Ubuntu 24.04的GCC 13/glibc 2.39
可提供这组接口；不要把新版glibc全局注入旧CANN环境。完整Host门禁会检查
C++17/C++20两种模式，不应因系统库缺失而跳过测试。

### C++语言兼容

C++17是最低语言模式，C++20继续受支持。能够以普通模板表达的较新库接口按已选子集回移；concept判定在C++17为布尔变量模板，C++20为原生concept。语言语法、Host/Device调用位置和常量求值能力分别判断。

`<asc/std/version>`提供值为0或1的`CANN_ASC_STL_HAS_*`能力宏。旧的标准名特性宏默认由Host标准库管理，ASC旧判断代码可通过显式兼容开关迁移。具体接口、配置与迁移方式见[语言模式与兼容性](docs/zh/guide/cpp_compatibility.md)。

### 直接包含（Host示例）

```cpp
// sample.cpp —— 仅依赖头文件，无需链接库
#include <asc/std/optional>
#include <asc/std/type_traits>

int main() {
    static_assert(asc::std::is_integral_v<int>);
    asc::std::optional<int> value = 42;
    return *value == 42 ? 0 : 1;
}
```

```bash
g++ -std=c++17 -Wall -Wextra -I asc-stl/include sample.cpp -o sample && ./sample
```

### CMake集成

```cmake
add_subdirectory(asc-stl)

target_link_libraries(your_target PRIVATE asc_stl::asc_stl)   # INTERFACE 目标，只传 include 路径
```

### 构建与运行测试

```bash
# 方式一：构建入口脚本（默认安装头文件与 CMake 配置到 build/install）
bash build.sh

# 方式二：Host 门禁（风格检查、头文件自包含、C++17/C++20 Host 语义 UT；需要 Python 3）
bash scripts/ci-quick-check.sh

# 方式三：CMake + CTest（显式开启测试目标；设备编译与仿真门禁需 CANN 环境并通过 build.sh --device-compile / --cannsim 开启）
cmake -B build -DBUILD_TESTING=ON && cmake --build build -j && cd build && ctest
```

真实设备回归使用 `bash scripts/ci-hardware-check.sh`，默认执行 C++17/C++20 各三轮。

## 💻 软硬件配套说明

ASC-STL 所需的软硬件环境依赖如下：

- 昇腾产品：[昇腾 950PR / 950DT 系列处理器](https://www.hiascend.com/hardware/processor)
- CPU 架构：`aarch64` / `x86_64`
- 系统：支持的 Linux（进行[兼容性查询](https://www.hiascend.com/hardware/compatibility)）
- 软件依赖：
  - CANN 9.2.0 及以上（毕昇CCE/clang 15.0.5 与 AscendCL Runtime 随 CANN 提供）
  - CMake ≥ 3.20

不同 ASC-STL 版本可支持的硬件平台及所需的 [CANN](https://www.hiascend.com/developer/download/community/result?module=cann) 版本如下表：

<table style="width: 75%; margin: 0 auto;">
  <colgroup>
    <col style="width: 30%">
    <col style="width: 30%">
    <col style="width: 40%">
  </colgroup>
  <thead>
      <tr>
          <th>ASC-STL 版本</th>
          <th>支持 CANN 包版本</th>
          <th>支持昇腾产品</th>
      </tr>
  </thead>
  <tbody style="text-align: center">
      <tr>
          <td>master 开发分支（版本标识 1.0.0）</td>
          <td>社区版 9.2.0 及以上</td>
          <td><a href="https://www.hiascend.com/hardware/processor">昇腾 950PR / 950DT 系列处理器</a></td>
      </tr>
  </tbody>
</table>

## 🧰 IDE支持

工程已配置`CMAKE_EXPORT_COMPILE_COMMANDS`，构建后会在构建目录生成`compile_commands.json`，供clangd / VS Code等IDE使用。纯头文件库自身没有编译单元，该数据库由测试编译目标产生：

```bash
cmake -B build            # 生成 build/compile_commands.json
ln -sf build/compile_commands.json .
```

设备侧代码的条件编译宏由CCE工具链注入；IDE线上预览Device路径的配置指引待定。

## 📊 版本状态与功能清单

### 标准层当前功能范围

下表列出当前标准层的全部 **74 个公共头**，沿用现有 **16 类**分类。头文件均以 `<asc/std/...>` 包含，接口位于 `asc::std`。

| 现有分类 | 公共头 | 当前可使用的功能范围 |
| --- | --- | --- |
| [语言支持库](docs/zh/api/standard/language_support/language_support.md) | `cfloat` `climits` `cstddef` `cstdint` `exception` `compare` `new` `limits` `source_location` `version` `ciso646` `cstdalign` `cstdbool` | 基础类型与数值宏、比较类别、源码位置、能力检测，以及终止和 placement new 等已列出的语言支持接口。 |
| [概念库](docs/zh/api/standard/concepts/concepts.md) | `concepts` | 类型与表达式判定；C++17 提供布尔变量模板，C++20 可使用原生 concept。 |
| [诊断库](docs/zh/api/standard/diagnostics/diagnostics.md) | `cassert` `cerrno` `system_error` | 断言、错误码宏，以及 error_code、error_condition 和错误类别。 |
| [内存管理库](docs/zh/api/standard/memory_management/memory_management.md) | `memory` `scoped_allocator` | 指针与分配器特征、分配器协议、对象构造/销毁及未初始化内存算法。 |
| [元编程库](docs/zh/api/standard/metaprogramming/metaprogramming.md) | `type_traits` `ratio` | 类型查询、类型变换、编译期常量与有理数运算。 |
| [通用工具库](docs/zh/api/standard/utilities/utilities.md) | `utility` `functional` `tuple` `optional` `variant` `expected` `bit` `bitset` `cstdlib` | 移动/转发/交换、函数对象、值组合与可选值、结果与错误表示、位操作和位集合等工具。 |
| [容器库](docs/zh/api/standard/containers/containers.md) | `array` `vector` `deque` `list` `forward_list` `inplace_vector` `map` `set` `unordered_map` `unordered_set` `queue` `stack` `span` `mdspan` | 固定容量与动态容器、关联容器、适配器及连续/多维视图，动态容器使用显式分配器。 |
| [迭代器库](docs/zh/api/standard/iterators/iterators.md) | `iterator` | 迭代器属性、遍历辅助、插入/逆向/移动等迭代器适配。 |
| [范围库](docs/zh/api/standard/ranges/ranges.md) | `ranges` | 范围访问与判定、范围视图及过滤、变换、截取等视图组合。 |
| [算法库](docs/zh/api/standard/algorithms/algorithms.md) | `algorithm` `execution` | 遍历、查找、比较、复制、变换、分区、排序、二分、集合、堆与排列等算法，以及执行策略词汇。 |
| [字符串库](docs/zh/api/standard/strings/strings.md) | `cstring` `string` `string_view` | C 字符串/字节操作、显式分配器 basic_string、字符特征及字符串视图。 |
| [文本处理库](docs/zh/api/standard/text_processing/text_processing.md) | `cctype` `charconv` `cuchar` `cwchar` `cwctype` `format` | 字符分类、字符/数值转换、宽字符与多字节处理，以及 format_to 等格式化输出接口。 |
| [数值库](docs/zh/api/standard/numerics/numerics.md) | `cmath` `complex` `ccomplex` `ctgmath` `numbers` `linalg` `random` `numeric` | 标量数学、复数、数学常量、随机引擎/分布、数值算法；linalg 当前提供缩放、共轭、转置等视图适配。 |
| [日期和时间库](docs/zh/api/standard/chrono/chrono.md) | `chrono` `ctime` | 时间段、时间点、日历与转换；计时与时间转换。 |
| [输入/输出库](docs/zh/api/standard/input_output/input_output.md) | `cinttypes` | 定宽整数格式宏与 intmax_t 相关工具。 |
| [并发支持库](docs/zh/api/standard/concurrency/concurrency.md) | `atomic` `barrier` `latch` `semaphore` `mutex` `shared_mutex` | 原子、屏障、倒计数和信号量，以及 RAII 锁管理。 |

## 📖 相关资源

### 文档

| 文档 | 说明 |
| --- | --- |
| [快速入门](docs/zh/quick_start.md) | 环境搭建、Host/Kernel 使用方式与本地验证，含经测试验证的示例 |
| [v1.0.0 支持范围说明](docs/zh/roadmap/roadmap_v1_0_0.md) | 当前标准层功能及扩展层、Runtime 层的完善方向 |
| [贡献指南](CONTRIBUTING.md) | 贡献流程、贡献场景与代码/测试要求 |
| [API参考文档](docs/zh/api/README.md) | ASC-STL公开接口的参考文档入口：标准库、昇腾扩展与Runtime |

## 👥 合作贡献者

- 武汉理工大学熊盛武老师团队
- 路雄博、蒋振宇、王亦柯

## 📝 相关信息

- **安全声明**：[SECURITY.md](SECURITY.md)；
- **许可证**：[Apache License 2.0](LICENSE)。
