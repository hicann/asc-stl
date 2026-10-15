# ASC-STL 快速入门

本页介绍 ASC-STL 的使用方式：如何在主机侧（Host）与设备侧核函数（Kernel）中使用 ASC-STL，以及如何编译执行与本地验证。页面中全部示例代码均已在真实工具链下完成验证：Host 示例编译并运行通过，Kernel 示例通过 CANN 官方 AscendC 工具链完成设备编译与打包。

## 🧭 使用方式声明

ASC-STL 是**纯头文件 C++ 库**，使用方式可归纳为一句话：**把仓库 `include/` 目录加入编译包含路径，包含公共头即可使用**。

- **无库文件**：不产出任何静态库/动态库，没有链接步骤；
- **一套公共头，两侧共用**：Host 代码与 Kernel 代码包含同一套公共 Header，无需分别配置；
- **三类公共入口**：

| 接口 | 包含路径 | 典型使用位置 |
| --- | --- | --- |
| C++ 标准库接口 | `#include <asc/std/...>` | Host 与 Kernel 通用 |
| 昇腾扩展接口 | `#include <asc/...>` | Kernel 为主（设备原子/线程同步、异步数据搬运、地址空间与内存视图、设备执行层次、Device 并行算法等） |
| Runtime 接口 | `#include <asc/...>` | Host（设备/Stream/Event 管理、核函数调用、内存资源等） |

- **语言标准**：产品最低 C++17；依赖 C++20 语言特性的接口在 C++20 及以上语言模式下开放。

## 🔧 环境准备

| 依赖 | 版本 / 说明 |
| --- | --- |
| CANN | 9.2.0 及以上（含毕昇编译器与 AscendCL Runtime） |
| 毕昇 CCE / clang | 15.0.5（随 CANN 提供） |
| g++ | 支持 C++17 的版本（C++20 特性接口需 C++20 模式） |
| CMake | ≥ 3.20 |
| 处理器 | 昇腾950PR&&DT处理器 |

- Host 侧使用只需 ASC-STL 源码与支持 C++17 的编译器；
- Kernel 侧编译与真机运行需安装 CANN，并激活其环境：`source <CANN 安装路径>/set_env.sh`。

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

命令无需链接任何库即可成功。Host 侧可使用全部 C++ 标准库接口与 Runtime 接口。

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
// add_relu_kernel.cpp —— 设备侧核函数：融合算子 z = ReLU(x + y)，计算使用 ASC-STL 标准接口
#include "kernel_operator.h"

#include <asc/std/algorithm>

namespace {

constexpr uint32_t kElementCount = 64;

}  // namespace

extern "C" __global__ __aicore__ void add_relu_kernel(GM_ADDR x_gm, GM_ADDR y_gm, GM_ADDR z_gm)
{
    // 1. 绑定 Global Memory 输入/输出
    AscendC::GlobalTensor<float> x;
    AscendC::GlobalTensor<float> y;
    AscendC::GlobalTensor<float> z;
    x.SetGlobalBuffer(reinterpret_cast<__gm__ float*>(x_gm), kElementCount);
    y.SetGlobalBuffer(reinterpret_cast<__gm__ float*>(y_gm), kElementCount);
    z.SetGlobalBuffer(reinterpret_cast<__gm__ float*>(z_gm), kElementCount);

    // 2. 搭建搬运队列（UB ↔ GM）
    AscendC::TPipe pipe;
    AscendC::TQue<AscendC::TPosition::VECIN, 2> x_queue;
    AscendC::TQue<AscendC::TPosition::VECIN, 2> y_queue;
    AscendC::TQue<AscendC::TPosition::VECOUT, 2> z_queue;
    pipe.InitBuffer(x_queue, 2, kElementCount * sizeof(float));
    pipe.InitBuffer(y_queue, 2, kElementCount * sizeof(float));
    pipe.InitBuffer(z_queue, 2, kElementCount * sizeof(float));

    // 3. 搬入数据（EnQue/DeQue 完成 UB 数据同步）
    auto x_local = x_queue.AllocTensor<float>();
    auto y_local = y_queue.AllocTensor<float>();
    AscendC::DataCopy(x_local, x, kElementCount);
    AscendC::DataCopy(y_local, y, kElementCount);
    x_queue.EnQue(x_local);
    y_queue.EnQue(y_local);
    x_local = x_queue.DeQue<float>();
    y_local = y_queue.DeQue<float>();

    // 4. 逐元素 z = ReLU(x + y) —— 使用 ASC-STL 标准接口 asc::std::max
    auto z_local = z_queue.AllocTensor<float>();
    for (uint32_t index = 0; index < kElementCount; ++index) {
        const float sum = x_local.GetValue(index) + y_local.GetValue(index);
        z_local.SetValue(index, asc::std::max(sum, 0.0F));
    }

    // 5. 搬出数据
    z_queue.EnQue(z_local);
    auto z_done = z_queue.DeQue<float>();
    AscendC::DataCopy(z, z_done, kElementCount);
    x_queue.FreeTensor(x_local);
    y_queue.FreeTensor(y_local);
    z_queue.FreeTensor(z_done);
}
```

### 工程构建（`CMakeLists.txt`）

```cmake
cmake_minimum_required(VERSION 3.20)
project(add_relu_sample LANGUAGES C CXX)

# ASC-STL 源码位置（按实际路径调整）
set(ASC_STL_ROOT "/path/to/asc-stl" CACHE PATH "ASC-STL source root")
# 目标昇腾处理器型号（按实际板卡调整）
set(SOC_VERSION "Ascend950PR_9599" CACHE STRING "target SoC")
set(RUN_MODE npu CACHE STRING "AscendC run mode")
set(ASCEND_CANN_PACKAGE_PATH "$ENV{ASCEND_HOME_PATH}" CACHE PATH "CANN package")

# 引入 CANN 官方 AscendC 构建模块
include("$ENV{ASCEND_HOME_PATH}/compiler/tikcpp/ascendc_kernel_cmake/ascendc.cmake")

# 核函数以 ascendc_library 声明，ASC-STL 头文件通过 include 路径接入
ascendc_library(add_relu_kernel SHARED add_relu_kernel.cpp)
ascendc_compile_options(add_relu_kernel PRIVATE -std=c++17)
ascendc_include_directories(add_relu_kernel PRIVATE ${ASC_STL_ROOT}/include)
```

### 编译执行

```bash
source /usr/local/Ascend/cann/set_env.sh    # 激活 CANN 环境（路径按实际安装位置调整）
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

构建完成后得到 `build/lib/libadd_relu_kernel.so`，其中已包含 AIV 设备镜像与主机侧启动桩；宿主程序按 Ascend C 工程惯例加载该库，在 Stream 上发起核函数调用并回拷结果。

## 🧪 本地验证

ASC-STL 仓库自带完整验证入口，clone 后即可使用：

| 验证场景 | 命令 | 说明 |
| --- | --- | --- |
| Host 门禁 | `bash scripts/ci-quick-check.sh` | 风格检查、公共头自包含与 C++17/C++20 Host 语义测试，无需 CANN |
| CMake + CTest | `cmake -B build -DBUILD_TESTING=ON && cmake --build build -j && cd build && ctest` | Host 测试目标，无需 CANN |
| 设备编译门 | `bash build.sh --device-compile -p <CANN 路径>` | 验证公共头在 Kernel 模式下可编译（需已安装 CANN） |
| 仿真门 | `bash build.sh --cannsim -p <CANN 路径>` | cannsim 仿真执行核函数用例，验证数值行为（需已安装 CANN） |
| 真机回归 | `bash scripts/ci-hardware-check.sh` | 昇腾设备上的 C++17/C++20 真机回归 |
