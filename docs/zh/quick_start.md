# ASC-STL 快速入门

本页介绍如何在Host与设备Kernel中使用ASC-STL。先运行无需CANN的Host示例，再使用完整设备工程完成输入上传、Kernel启动、结果校验和资源释放。编译成功只证明可以生成程序，设备运行还需要受支持且可用的NPU。

[English](../en/quick_start.md) | [接口子集与语言兼容](guide/cpp_compatibility.md)

## 🧭 使用方式声明

ASC-STL 是**纯头文件 C++ 库**，使用方式可归纳为一句话：**把仓库 `include/` 目录加入编译包含路径，包含公共头即可使用**。

- **无独立库文件**：ASC-STL自身不产出静态库或动态库；依赖AscendCL的Runtime调用仍需链接外部运行库；
- **一套公共头，两侧共用**：Host 代码与 Kernel 代码包含同一套公共 Header，无需分别配置；
- **三类公共入口**：

| 接口 | 包含路径 | 典型使用位置 |
| --- | --- | --- |
| C++ 标准库接口 | `#include <asc/std/...>` | Host 与 Kernel 通用 |
| 昇腾扩展接口 | `#include <asc/...>` | Kernel 为主（设备原子/线程同步、异步数据搬运、地址空间与内存视图、设备执行层次、Device 并行算法等） |
| Runtime 接口 | `#include <asc/...>` | Host（设备/Stream/Event 管理、核函数调用、内存资源等） |

- **语言标准**：产品最低C++17，并维护C++20；接口的语言模式、执行位置、分配器和类型限制以各API页为准。
- **范围**：提供所列标准库接口子集，不是Host `std`的完整替代。例如`vector`需要显式分配器，部分拷贝操作不提供。

## 🔧 环境准备

| 依赖 | 版本 / 说明 |
| --- | --- |
| CANN | 当前验证使用9.2.0-beta.2；编译需Toolkit，执行另需匹配的驱动和Runtime |
| 毕昇 CCE / clang | 15.0.5（随 CANN 提供） |
| g++ | 支持 C++17 的版本（C++20 特性接口需 C++20 模式） |
| CMake | ≥ 3.20 |
| 处理器 | 昇腾950PR&&DT处理器 |

- 本页Host示例只需ASC-STL源码与支持C++17的编译器；完整Host门禁还依赖[系统库条件](guide/cpp_compatibility.md)；
- Kernel侧需激活CANN环境：`source <CANN 安装路径>/set_env.sh`。相同版本标签可能对应不同组件构建；验证结果须匹配实际SDK与编译器身份，不能外推为所有后续版本均兼容。

获取代码：

```bash
git clone https://gitcode.com/cann/asc-stl.git
```

## 💻 Host 侧使用方式

### 方式一：直接包含（无需构建）

```cpp
// host_sample.cpp —— ASC-STL 是纯头文件库：包含公共头即可使用，无需链接任何库
#include <asc/std/algorithm>
#include <asc/std/optional>
#include <asc/std/type_traits>

int main() {
    static_assert(asc::std::is_integral_v<int>);

    int data[8] = {5, 3, 8, 1, 9, 2, 7, 4};
    asc::std::sort(data, data + 8);

    asc::std::optional<int> largest = data[7];
    return (asc::std::is_sorted(data, data + 8) && *largest == 9) ? 0 : 1;
}
```

```bash
g++ -std=c++17 -Wall -Wextra -I asc-stl/include host_sample.cpp -o host_sample && ./host_sample
```

本例只使用不依赖Runtime的标准库设施，因此不需要额外链接AscendCL。Host调用依赖CANN的Runtime接口时，还须链接`ascendcl`并完成对应的设备和资源初始化；不同接口的调用位置和可用范围见各API页面。

### 方式二：CMake 集成

```cmake
cmake_minimum_required(VERSION 3.20)
project(host_app LANGUAGES CXX)

add_subdirectory(asc-stl EXCLUDE_FROM_ALL)

add_executable(host_app host_sample.cpp)
target_link_libraries(host_app PRIVATE asc_stl::asc_stl)   # INTERFACE 目标，只传 include 路径
```

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build && ./build/host_app
```

## ⚡ Kernel 侧使用方式（在核函数中使用 ASC-STL）

Kernel 侧代码由 CANN 毕昇编译器编译。在现有 Ascend C 核函数工程中接入 ASC-STL 只需一步：把 ASC-STL 的 `include/` 加入核函数目标的包含路径，即可在核函数内使用 `asc::std` 等接口。

### 核函数示例（`add_relu_kernel.cpp`，融合算子 z = ReLU(x + y)）

```cpp
#include <asc/pipeline>
#include <asc/std/algorithm>

#include "basic_api/kernel_tensor.h"

extern "C" __global__ __aicore__ void add_relu_kernel(__gm__ float* x, __gm__ float* y, __gm__ float* z)
{
    constexpr unsigned int count = 64;
    __ubuf__ float x_local[count];
    __ubuf__ float y_local[count];
    __ubuf__ float z_local[count];
    // This kernel owns event IDs 2 and 3; they are not shared with TPipe/TQue.
    asc::pipeline_ref pipeline(2, 3);
    pipeline.producer_acquire(0);
    asc::copy_async(pipeline, 0, asc::ub_span<float>(x_local, count), asc::gm_span<const float>(x, count));
    asc::copy_async(pipeline, 0, asc::ub_span<float>(y_local, count), asc::gm_span<const float>(y, count));
    pipeline.producer_commit(0);
    pipeline.consumer_wait(0);
    for (unsigned int index = 0; index < count; ++index)
        // NOLINTNEXTLINE(build/include_what_you_use)
        z_local[index] = asc::std::max(x_local[index] + y_local[index], 0.0F);
    pipeline.consumer_release(0);
    asc::copy_async(pipeline, 0, asc::gm_span<float>(z, count), asc::ub_span<const float>(z_local, count));
    pipeline.wait();
}
```

### 完整工程：编译、启动与校验

仓库中的[完整入门工程](examples/quick_start/README.md)包含以上Kernel及
[Host程序](examples/quick_start/main.cpp)。Host程序构造64组正、负和零值输入，
通过AscendCL分配GM和Stream、上传输入、调用CANN生成的启动函数、同步并回拷结果。
Host golden直接计算`sum > 0 ? sum : 0`，不调用被测的`asc::std::max`。
它检查每个元素及资源释放的返回码，任何失败均返回非零。

从克隆后的仓库根目录执行：

```bash
cd asc-stl
source /usr/local/Ascend/ascend-toolkit/set_env.sh  # 换成实际安装路径
cmake -S docs/zh/examples/quick_start -B build/quick-start-17 \
  -DASC_STL_EXAMPLE_STANDARD=17 -DSOC_VERSION=Ascend950PR_9599 \
  -DCMAKE_BUILD_TYPE=Release
cmake --build build/quick-start-17 -j2
timeout --signal=TERM --kill-after=10s 60s build/quick-start-17/asc_stl_quick_start
```

`SOC_VERSION`须匹配实际受支持的950设备。程序使用ACL逻辑设备0，不把容器中
`/dev/davinciN`的后缀当作逻辑设备号。没有NPU时可以完成构建，但不能把无法运行记为通过。
成功运行必须返回0，并输出：

```text
cleanup_passed=1
elements=64 mismatches=0
ASC_STL_QUICK_START_PASS
```

构建C++20时使用独立目录`build/quick-start-20`，并将
`-DASC_STL_EXAMPLE_STANDARD=17`改为`20`；其余步骤相同。
任务和Stream同步都设置10秒时限，外层进程时限仍须保留。
发生设备错误或超时时先检查环境，不能通过反复重试获得通过结果。

此示例展示一个小规模标量Kernel的完整接入路径，不是向量化性能示例。
后续可继续运行[GM/UB流水拷贝](examples/pipeline_copy/README.md)和
[并行算法](examples/parallel_algorithms/README.md)工程。

## 🧪 本地验证

ASC-STL 仓库自带完整验证入口，clone 后即可使用：

| 验证场景 | 命令 | 说明 |
| --- | --- | --- |
| Host 门禁 | `bash scripts/ci-quick-check.sh` | 风格检查、公共头自包含与 C++17/C++20 Host 语义测试，无需 CANN |
| CMake + CTest | `cmake -B build -DBUILD_TESTING=ON && cmake --build build -j && cd build && ctest` | Host 测试目标，无需 CANN |
| 设备编译门 | `bash build.sh --device-compile -p <CANN 路径>` | 验证公共头在 Kernel 模式下可编译（需已安装 CANN） |
| 仿真门 | `bash build.sh --cannsim -p <CANN 路径>` | cannsim 仿真执行核函数用例，验证数值行为（需已安装 CANN） |
| 真机回归 | `bash scripts/ci-hardware-check.sh` | 昇腾设备上的 C++17/C++20 真机回归 |
