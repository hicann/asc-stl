# ASC-STL

#### 面向昇腾设备Kernel编程的C++标准库

## 1. 概述

### 1.1 项目介绍

ASC-STL是面向昇腾设备Kernel开发的纯头文件C++库，为Host与Device代码提供统一的公共Header组织，包括`asc::std`标准接口和`asc`扩展接口。

### 1.2 项目背景

昇腾设备计算函数（Kernel）开发需要类型系统、容器与视图、算法、数值、原子、同步、内存和并行操作等通用C++功能。ASC-STL以纯头文件库形式提供两类公共接口：对于标准C++已经定义的通用类型和算法，提供asc::std标准接口；对于标准C++没有定义的设备侧执行（Device）、任务队列（stream）、全局内存（Global Memory，GM）、统一缓冲区（Unified Buffer，UB）、线程层次和Device并行任务等平台概念，提供asc扩展接口。

ASC-STL面向主机侧代码（Host）和设备侧代码（Device）提供统一的公共头文件（以下简称公共Header）组织。当前工程基线为C++17，并支持在C++20语言模式下编译和使用；开发与运行环境包括CANN 9.2.0、毕昇CCE/clang 15.0.5和单设备昇腾AI处理器（Ascend 950）。

## 2. 总体设计

### 2.1 系统架构

![图1 ASC-STL设计架构](docs/images/asc-stl-design-architecture.png)

公共接口包括两个并列部分：asc::std标准接口提供标准C++风格的标准功能，公共Header位于`<asc/std/...>`；asc扩展接口提供与昇腾设备资源、内存层次和并行执行相关的扩展功能，公共Header位于`<asc/...>`。两类接口共同构成ASC-STL的公共功能范围。

标准功能包括基础语言与类型、容器与视图、算法与迭代、数值与时间以及标准原子与同步。扩展功能包括设备、stream与Kernel提交，原子操作与线程同步，GM/UB内存与数据搬运，线程位置与线程组协作，Device并行算法，以及数值、迭代器与类型工具。

ASC-STL依赖asc-devkit提供的AscendC和SIMT设备编程能力，并由毕昇编译器完成Host与Device代码的编译。程序运行时依赖CANN Runtime和CANN Driver提供设备管理、任务提交、内存管理及硬件驱动能力，最终运行于昇腾AI处理器。

### 2.2 模块划分

ASC-STL公共接口分为标准接口层和Ascend扩展层。

#### 2.2.1 标准接口层

| 模块 | 模块职责 |
| --- | --- |
| 基础语言与类型 | 提供C++基础类型、类型查询与变换、对象生命周期、函数调用、错误表示及通用值类型 |
| 容器与视图 | 提供拥有数据的容器、容器适配器以及对已有数据的非拥有视图 |
| 算法、范围与迭代 | 提供顺序算法、range处理、迭代器及标准执行策略类型 |
| 数值与时间 | 提供位操作、数学、数值算法、随机数、格式化和时间处理能力 |
| 标准原子与同步 | 提供标准原子操作、内存序以及屏障、锁和信号量等同步能力 |

#### 2.2.2 Ascend扩展层

| 模块 | 模块职责 |
| --- | --- |
| 设备、stream与Kernel提交 | 提供设备查询、stream与event管理、Kernel提交和Device执行策略描述 |
| 原子操作与线程同步 | 提供带Ascend地址空间和同步范围的原子、屏障、信号量及流水线能力 |
| GM/UB内存与数据搬运 | 提供GM、UB和Host内存描述、资源管理、buffer、内存池及多维数据搬运能力 |
| 线程位置与线程组协作 | 提供线程层次查询、warp与block协作以及动态任务领取能力 |
| Device并行算法 | 提供面向Device任务的并行变换、查找、归约、扫描、合并与排序能力 |
| 数值、迭代器与类型工具 | 提供并行算法参数、迭代器、数值、随机数、多维视图和编译期类型工具 |

### 2.3 目录结构

ASC-STL采用纯头文件库结构。公共Header集中在include/asc/，标准接口和Ascend扩展接口在同一公共根目录下组织；测试、CMake配置和持续集成脚本分别位于独立目录。

```text
asc-stl/
├── include/
│   └── asc/                         # ASC-STL公共Header根目录
│       ├── std/                     # 标准接口：<asc/std/...>
│       ├── algorithm                # Device并行算法
│       ├── atomic                  # Ascend原子操作
│       ├── collectives              # 线程组协作操作
│       ├── execution               # Device执行策略聚合入口
│       ├── memory                 # GM、UB和内存视图
│       ├── stream                  # stream和event管理
│       └── ...                      # 其他Ascend扩展公共Header
├── test/                            # Host、Device、cannsim与真机测试
├── cmake/                          # CMake安装和导出配置
├── scripts/                          # 构建检查与持续集成脚本
├── CMakeLists.txt                   # 顶层CMake配置
├── README.md                     # 项目说明
└── LICENSE                         # 产品许可证
```

include/asc/std/承载asc::std标准接口，include/asc/下除std/之外的公共Header承载asc扩展接口。

## 3. 详细设计

### 3.1 标准功能

标准接口层通过asc::std命名空间提供标准C++风格的公共功能。各公共Header按照标准Header边界组织，功能分为以下五类。

#### 3.1.1 基础语言与类型

| 公共入口 | 功能 |
| --- | --- |
| `<asc/std/cassert>` | 提供断言宏，用于检查运行期条件 |
| `<asc/std/cctype>` | 提供窄字符分类、大小写判断和大小写转换 |
| `<asc/std/cwctype>` | 提供宽字符分类、大小写判断和大小写转换 |
| `<asc/std/cerrno>` | 提供C兼容的errno错误码宏 |
| `<asc/std/cfloat>` | 提供浮点类型精度、范围和表示特征宏 |
| `<asc/std/cinttypes>` | 提供定宽整数格式宏和最大宽度整数转换 |
| `<asc/std/climits>` | 提供基础整数类型的取值范围宏 |
| `<asc/std/ciso646>` | 提供and、or、not等运算符的C兼容拼写 |
| `<asc/std/cstdalign>` | 提供对齐关键字的C兼容定义 |
| `<asc/std/cstdbool>` | 提供布尔类型的C兼容定义 |
| `<asc/std/cstddef>` | 提供size_t、ptrdiff_t、nullptr_t和byte等基础类型 |
| `<asc/std/cstdint>` | 提供有符号和无符号定宽整数类型 |
| `<asc/std/cstdlib>` | 提供数值转换、绝对值及其他C兼容通用工具 |
| `<asc/std/cstring>` | 提供C字符串和字节序列的复制、比较、查找与填充操作 |
| `<asc/std/cuchar>` | 提供多字节字符与UTF字符之间的转换 |
| `<asc/std/cwchar>` | 提供宽字符类型、转换和宽字符串操作 |
| `<asc/std/exception>` | 提供异常基础类型、终止处理和当前异常查询能力 |
| `<asc/std/compare>` | 提供三路比较结果类别和比较辅助工具 |
| `<asc/std/concepts>` | 提供标准concept和模板参数约束能力 |
| `<asc/std/functional>` | 提供函数对象、可调用对象包装、调用和绑定工具 |
| `<asc/std/new>` | 提供内存分配函数声明、placement new和相关类型 |
| `<asc/std/memory>` | 提供智能指针、allocator、对象构造销毁和未初始化内存操作 |
| `<asc/std/scoped_allocator>` | 提供向嵌套对象传递外层allocator的能力 |
| `<asc/std/limits>` | 提供数值类型的最小值、最大值、精度和表示属性 |
| `<asc/std/source_location>` | 提供文件名、函数名、行号和列号等源码位置描述 |
| `<asc/std/system_error>` | 提供错误码、错误条件和错误类别 |
| `<asc/std/tuple>` | 提供将多个不同类型值组合为一个对象的tuple能力 |
| `<asc/std/type_traits>` | 提供编译期类型判断、类型关系查询和类型变换 |
| `<asc/std/utility>` | 提供移动、转发、交换、整数序列和通用辅助工具 |
| `<asc/std/version>` | 提供标准功能对应的特性检测宏 |
| `<asc/std/expected>` | 提供同时表达成功结果或错误值的类型 |
| `<asc/std/optional>` | 提供可能包含或不包含值的对象 |
| `<asc/std/variant>` | 提供在多个候选类型之间保存一个当前值的类型安全联合对象 |

#### 3.1.2 容器与视图

| 公共入口 | 功能 |
| --- | --- |
| `<asc/std/array>` | 提供编译期固定长度的连续序列容器 |
| `<asc/std/inplace_vector>` | 提供容量固定、当前长度可变化的连续序列 |
| `<asc/std/vector>` | 提供连续存储并可动态改变长度的序列容器 |
| `<asc/std/deque>` | 提供支持首尾插入和删除的序列容器 |
| `<asc/std/forward_list>` | 提供单向链接的序列容器 |
| `<asc/std/list>` | 提供双向链接的序列容器 |
| `<asc/std/map>` | 提供按键排序的键值关联容器 |
| `<asc/std/set>` | 提供按键排序且键唯一的关联容器 |
| `<asc/std/unordered_map>` | 提供基于哈希组织的键值关联容器 |
| `<asc/std/unordered_set>` | 提供基于哈希组织且键唯一的关联容器 |
| `<asc/std/stack>` | 提供后进先出的容器适配器 |
| `<asc/std/queue>` | 提供先进先出队列和优先队列适配器 |
| `<asc/std/bitset>` | 提供编译期固定长度的位集合 |
| `<asc/std/string>` | 提供拥有字符序列的字符串类型 |
| `<asc/std/string_view>` | 提供对已有字符序列的非拥有只读视图 |
| `<asc/std/span>` | 提供对已有连续元素序列的非拥有视图 |
| `<asc/std/mdspan>` | 提供对已有多维数据的非拥有索引视图 |

#### 3.1.3 算法、范围与迭代

| 公共入口 | 功能 |
| --- | --- |
| `<asc/std/algorithm>` | 提供查找、比较、复制、变换、排序、分区和集合操作等标准顺序算法 |
| `<asc/std/ranges>` | 提供基于range的遍历、过滤、变换和视图组合能力 |
| `<asc/std/iterator>` | 提供迭代器、迭代器适配器、迭代器属性和遍历辅助工具 |
| `<asc/std/execution>` | 提供标准执行策略类型和对应常量 |

#### 3.1.4 数值与时间

| 公共入口 | 功能 |
| --- | --- |
| `<asc/std/bit>` | 提供计数、旋转、字节交换和位级转换等操作 |
| `<asc/std/charconv>` | 提供字符序列与数值之间的低开销转换 |
| `<asc/std/cmath>` | 提供常用标量数学函数和浮点分类能力 |
| `<asc/std/ccomplex>` | 提供C兼容复数类型和函数入口 |
| `<asc/std/complex>` | 提供复数类型、算术运算和复数数学函数 |
| `<asc/std/ctgmath>` | 根据参数类型选择对应的C数学或复数函数 |
| `<asc/std/numeric>` | 提供归约、扫描、内积、差分和序列生成等数值算法 |
| `<asc/std/linalg>` | 提供面向向量和矩阵视图的线性代数算法 |
| `<asc/std/format>` | 提供类型安全的格式字符串解析和格式化能力 |
| `<asc/std/numbers>` | 提供圆周率、自然常数等标准数学常量 |
| `<asc/std/random>` | 提供随机数引擎、分布和随机数生成辅助工具 |
| `<asc/std/ratio>` | 提供编译期有理数表示和运算 |
| `<asc/std/chrono>` | 提供时钟、时间点、时间段及其运算 |
| `<asc/std/ctime>` | 提供C兼容日期时间类型和函数 |

#### 3.1.5 标准原子与同步

| 公共入口 | 功能 |
| --- | --- |
| `<asc/std/atomic>` | 提供原子读写、交换、比较交换和标准内存序控制 |
| `<asc/std/barrier>` | 提供多个参与者按阶段汇合并重复使用的同步屏障 |
| `<asc/std/latch>` | 提供参与者完成后递减并等待计数归零的同步能力 |
| `<asc/std/semaphore>` | 提供基于计数控制并发访问数量的同步能力 |
| `<asc/std/mutex>` | 提供互斥访问接口和锁对象管理工具 |
| `<asc/std/shared_mutex>` | 提供多个读取者共享访问、写入者独占访问的同步能力 |

### 3.2 扩展功能

Ascend扩展层通过asc命名空间提供标准C++没有定义的昇腾设备扩展功能。公共接口直接表达设备资源、地址空间、线程层次和Device并行任务等平台概念。

#### 3.2.1 设备、stream与Kernel提交

| 公共入口 | 功能 |
| --- | --- |
| `<asc/devices>` | 提供Device枚举、选择和属性查询 |
| `<asc/stream>` | 提供stream和event的创建、借用、依赖建立、状态管理和执行计时 |
| `<asc/launch>` | 提供Kernel提交及Kernel完成后Host函数提交能力 |
| `<asc/execution>` | 统一导出Device执行策略及执行要求相关接口 |
| `<asc/execution.policy.h>` | 提供与stream、workspace等执行资源关联的Device执行策略 |
| `<asc/execution.require.h>` | 提供为Device执行策略附加执行要求的组合能力 |
| `<asc/execution.determinism.h>` | 描述并行算法结果是否必须具有可重复性 |
| `<asc/execution.output_ordering.h>` | 描述并行算法输出是否保持输入顺序 |
| `<asc/execution.tie_break.h>` | 描述多个结果同时满足条件时的选择规则 |

#### 3.2.2 原子操作与线程同步

| 公共入口 | 功能 |
| --- | --- |
| `<asc/atomic>` | 提供带GM或UB地址空间及block或device同步范围的原子操作 |
| `<asc/barrier>` | 提供block内或指定Device范围内的线程屏障 |
| `<asc/latch>` | 提供等待指定数量参与线程完成当前阶段的同步能力 |
| `<asc/semaphore>` | 提供限制同时进入指定执行区间的线程数量的同步能力 |
| `<asc/pipeline>` | 提供组织GM与UB异步搬运提交、等待和阶段切换的流水线能力 |

#### 3.2.3 GM/UB内存与数据搬运

| 公共入口 | 功能 |
| --- | --- |
| `<asc/memory>` | 提供GM、UB和Host内存视图以及地址空间查询能力 |
| `<asc/memory_resource>` | 提供显式内存资源抽象及内存申请、释放接口 |
| `<asc/memory_pool>` | 提供可复用内存块的池化管理能力 |
| `<asc/buffer>` | 提供基于指定内存资源创建、拥有和管理连续内存的buffer |
| `<asc/tensor_copy>` | 提供带形状、步长和边界处理的GM与UB多维数据搬运能力 |

#### 3.2.4 线程位置与线程组协作

| 公共入口 | 功能 |
| --- | --- |
| `<asc/hierarchy>` | 提供grid、block、thread和lane的数量及当前位置查询 |
| `<asc/warp>` | 提供warp内线程投票、匹配、数据交换、广播和归约能力 |
| `<asc/collectives>` | 提供block内线程共同执行的归约、扫描、广播和条件判断能力 |
| `<asc/work_queue>` | 提供多个线程从共享工作队列领取互不重叠任务区间的能力 |

#### 3.2.5 Device并行算法

| 公共入口 | 功能 |
| --- | --- |
| `<asc/algorithm>` | 提供并行变换、查找、归约、扫描、选择、分区、合并和排序等Device任务 |

#### 3.2.6 数值、迭代器与类型工具

| 公共入口 | 功能 |
| --- | --- |
| `<asc/argument>` | 提供立即值、延迟生成值、序列和取值范围等算法参数包装 |
| `<asc/functional>` | 提供最小值、最大值、结合性、交换性和单位元等并行算法函数对象及属性 |
| `<asc/iterator>` | 提供计数、常量、变换、组合、排列、跨步和输出等按需生成数据的迭代器 |
| `<asc/bit>` | 提供Ascend设备需要的位域提取、插入和其他位级操作 |
| `<asc/cmath>` | 提供Ascend设备可用的数学函数 |
| `<asc/numeric>` | 提供整数溢出检测、饱和计算和受检查的数值类型转换 |
| `<asc/random>` | 提供PCG64随机数引擎和可重复的一一映射能力 |
| `<asc/mdspan>` | 提供Host、GM和UB多维数据视图及与DLPack数据结构转换的能力 |
| `<asc/type_traits>` | 提供按位比较、扩展浮点和可直接搬移等Ascend相关类型判断 |
| `<asc/utility>` | 提供整数安全表示检查和固定次数编译期展开工具 |
| `<asc/version>` | 提供ASC-STL版本和扩展能力可用性检测信息 |

## 4. 贡献指南

### 4.1 参与贡献前

ASC-STL接受代码、测试、文档、缺陷修复和性能优化贡献。参与贡献前，应完成项目行为准则阅读和CLA（贡献者许可协议）签署。本章中的Issue表示问题单，PR表示代码合入申请，CI表示提交后自动运行的持续集成检查。

除简单缺陷修复外，新增功能、公共Header、API、重载、配置项或运行环境，应先提交Issue讨论方案。无法判断是否属于简单修复时，也应先通过Issue确认范围。

### 4.2 贡献场景

| 场景 | 提交前准备 |
| --- | --- |
| 缺陷修复 | 提供最小复现、预期行为、实际行为和环境信息 |
| 新功能或API | 说明使用场景、接口方案、支持边界、兼容性和测试计划 |
| 性能优化 | 提供优化前基线、测试环境、数据规模、结果和正确性证据 |
| 文档修订 | 指出原文位置、问题、修改依据及相关代码影响 |

安全问题不得在公开Issue中提交密钥、凭据、内网地址或完整私有日志，应按照项目安全流程报告。

### 4.3 开发与提交流程

1. 创建或认领Issue，确认问题和改动范围；

2. 同步目标分支并创建范围单一的开发分支；

3. 同步完成代码、测试和受影响文档；

4. 运行全部适用的本地检查，记录环境、命令和结果；

5. 提交PR，按照模板填写背景、目的、方案、关联Issue、测试结果和文档变化；

6. 根据审核意见修改，由正式CI验证PR最终内容；

7. 高风险Device改动补充昇腾AI处理器（Ascend 950）真机证据，全部适用检查通过后合入。

### 4.4 代码、测试与文档要求

1. 产品代码使用C++17基线，并保证公共Header能够被单独包含；

2. 公共标准名字位于asc::std，Ascend扩展名字位于asc；

3. 新增接口必须说明适用环境、输入输出、资源所有权、错误处理和公共行为；

4. 不支持的类型或运行环境应给出明确的编译期或运行期错误；

5. 缺陷修复应增加回归测试，新功能应覆盖正常、边界和错误场景；

6. 测试预期结果应由独立方法计算或人工确认，不得调用被测API自身生成；

7. 公共行为变化时，代码、测试、API说明和发布说明必须同步更新；

8. 代码格式、命名、注释和许可证要求以仓库当前配置及贡献规范为准。

产品根目录提供以下本地检查入口：

```text
scripts/ci-quick-check.sh
scripts/ci-device-compile-check.sh
scripts/ci-cannsim-check.sh
```

根据改动影响，执行相关的Host、Device和cannsim测试。原子操作、线程同步、GM/UB地址空间、线程组协作、浮点和并行算法等改动需要补充昇腾AI处理器（Ascend 950）真机验证。验证环境不可用时，应明确说明未验证内容和原因，不能将其记录为通过。

### 4.5 PR内容与合入条件

PR至少应包含：

1. 业务背景、问题描述和关联Issue；

2. 方案和用户可见影响；

3. 修改范围及新增或调整的API；

4. Host、Device、和cannsim结果；

5. 文档更新、已知限制和未覆盖风险；

6. 性能改动的基线与对比结果。

只有PR最终内容相关的CI检查全部通过、必要证据齐全、文档同步且审核意见关闭后，改动才具备合入条件。PR新增提交后，应重新确认测试结果。
