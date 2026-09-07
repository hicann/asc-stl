# ASC-STL Development Roadmap (Stage 2 · 设备编程能力)

> **里程碑**：ASC-STL v1.1.0 · **负责人**：待定 · **状态**：滚动更新，随进展持续修订描述
>
> 版本目标：**v1.1.0**

ASC-STL 阶段一交付了与平台无关的通用编程能力。本阶段在其类型与工具底座上补齐**设备编程能力**：对标准 C++ 未定义的昇腾平台概念——需kernel能力支持的头文件提供直接、显式的公共接口表达与操作能力。

本阶段目标是让 Kernel 开发者完整获得设备资源表达、内存体系操作与线程协同能力。

## Focus

- **设备与任务提交**：设备查询、stream/event 管理、Kernel 提交与执行策略组合
- **内存与数据搬运**：GM/UB/Host 内存视图、内存资源、池化与多维搬运
- **设备原子与线程同步**：带地址空间与同步范围的原子、屏障、流水线
- **线程层次与组协作**：层次查询、warp 协作
- **设备侧数值与类型工具**：位操作、数学、数值安全与随机数能力

## 设备与任务提交

### 设备查询

- **Goal**：提供 Device 枚举、选择与属性查询能力。
- **Key Features**：
  - `<asc/devices>` 设备枚举与属性查询
- **Owner**：待定
- **Issue**：#X

### stream 与 event

- **Goal**：提供任务队列与事件的完整生命周期管理。
- **Key Features**：
  - stream/event 创建、借用与依赖建立
  - 状态管理与执行计时
- **Owner**：待定
- **Issue**：#X

### Kernel 提交

- **Goal**：提供 Kernel 提交与完成后 Host 函数提交能力。
- **Key Features**：
  - `<asc/launch>` Kernel 提交入口
  - 完成回调（Host 函数）提交
- **Owner**：待定
- **Issue**：#X

### 执行策略与执行要求

- **Goal**：提供 Device 执行策略及其执行要求的组合描述能力。
- **Key Features**：
  - `<asc/execution>` 聚合入口与 `<asc/execution.policy.h>` 策略
  - `<asc/execution.require.h>` 执行要求组合
  - 确定性 / 输出序 / 决胜规则描述（determinism / output_ordering / tie_break）
- **Owner**：待定
- **Issue**：#X

## 内存与数据搬运

### 内存视图与地址空间

- **Goal**：提供 GM、UB 与 Host 内存的统一描述及地址空间查询。
- **Key Features**：
  - `<asc/memory>` 内存视图族
  - 地址空间查询与安全访问约束
- **Owner**：待定
- **Issue**：#X

### 内存资源与池化

- **Goal**：提供显式内存资源抽象与可复用内存管理。
- **Key Features**：
  - `<asc/memory_resource>` 显式内存资源与申请/释放接口
  - `<asc/memory_pool>` 可复用内存块池化
  - `<asc/buffer>` 连续内存 buffer 的创建、所有权与管理
- **Owner**：待定
- **Issue**：#X

### 多维搬运与视图

- **Goal**：提供带形状、步长与边界处理的多维数据搬运能力。
- **Key Features**：
  - `<asc/tensor_copy>` GM/UB 多维数据搬运
  - `<asc/mdspan>` Host/GM/UB 多维视图与 DLPack 转换
- **Owner**：待定
- **Issue**：#X

## 设备原子与线程同步

### 地址空间原子

- **Goal**：提供带 GM/UB 地址空间与 block/device 同步范围的原子操作。
- **Key Features**：
  - `<asc/atomic>` 地址空间 + 同步范围二维原子能力
  - 高风险改动真机证据准入
- **Owner**：待定
- **Issue**：#X

### 屏障与信号量

- **Goal**：提供设备侧线程汇合与并发数量控制的同步原语。
- **Key Features**：
  - `<asc/barrier>` block 内 / Device 范围线程屏障
  - `<asc/latch>`、`<asc/semaphore>` 阶段汇合与并发控制
- **Owner**：待定
- **Issue**：#X

### 异步搬运流水线

- **Goal**：提供组织 GM 与 UB 异步搬运提交、等待与阶段切换的流水线能力。
- **Key Features**：
  - `<asc/pipeline>` 流水线阶段编排
  - 与 `<asc/tensor_copy>` 的 API 边界划分（待定）
- **Owner**：待定
- **Issue**：#X

## 线程层次与组协作

### 线程层次查询

- **Goal**：提供当前位置查询。
- **Key Features**：
  - `<asc/hierarchy>` 线程层次信息
- **Owner**：待定
- **Issue**：#X

### warp 协作

- **Goal**：提供 warp 内线程投票、匹配、数据交换、广播与归约能力。
- **Key Features**：
  - `<asc/warp>` warp 级协作操作族
- **Owner**：待定
- **Issue**：#X

## 设备侧数值与类型工具

### 位操作与数学

- **Goal**：提供昇腾设备需要的位级操作与数学函数。
- **Key Features**：
  - `<asc/bit>` 位域提取、插入等位级操作
  - `<asc/cmath>` 设备可用数学函数
- **Owner**：待定
- **Issue**：#X

### 数值安全与随机数

- **Goal**：提供整数溢出检测、饱和计算与可重复随机数能力。
- **Key Features**：
  - `<asc/numeric>` 溢出检测、饱和计算、受检查转换
  - `<asc/random>` PCG64 引擎与可重复一一映射
- **Owner**：待定
- **Issue**：#X

### 类型判断与工具

- **Goal**：提供昇腾相关编译期类型判断与整数安全工具。
- **Key Features**：
  - `<asc/type_traits>` 按位比较、扩展浮点、可直接搬移等判断
  - `<asc/utility>` 整数安全表示与编译期定次展开
  - `<asc/version>` 版本与扩展能力检测
- **Owner**：待定
- **Issue**：#X


