# 产品版本与扩展接口交付标识

`<asc/version>` 提供日期版本 `CANN_ASC_STL` 和三个扩展模块的交付标识，并包含
`<asc/std/version>`。用户可检查最低库版本，或按交付标识选择扩展接口代码。
最低要求为 C++17，同时支持 C++20；在 Host、SIMD、SIMT 中均可独立包含。

| 信息 | 含义 |
| --- | --- |
| `CANN_ASC_STL` | 固定的公历发行日期 `YYYYMMDD`，当前值为 `20261023`。整数比较保持日期先后顺序。 |
| `CANN_ASC_STL_HAS_*` | 当前发行包是否已交付约定的全部基础接口并通过适用验收，始终为 `0` 或 `1`。 |
| `CANN_ASC_STL_LIB_*` | 标准层某项特性的修订版本，由标准层按语言和编译器条件维护。 |

四个产品宏由 `include/asc/__version/product.h` 统一定义。同一发行包在各编译模式和
语言模式下取值一致，调用方的 `__DATE__` 和编译时间不影响它们。日期使用有效公历
日期，年份为 1000–9999；同一天的源码快照通过发行提交区分。

标准层使用独立的 `CANN_ASC_STL_LIB_*` 前缀。例如 `CANN_ASC_STL_LIB_type_identity`
的 `201806L` 表示该标准特性的修订版本，与产品发行日期分别维护。Host 程序可同时
包含 `<version>` 和 `<asc/version>`；宿主的 `__cpp_lib_*` 继续报告宿主标准库的实现。

## 使用示例

```cpp
#include <asc/version>

// 20260101 is an illustrative minimum release date.
#if CANN_ASC_STL < 20260101
#error "ASC-STL release 20260101 or newer is required"
#endif

#if CANN_ASC_STL_HAS_PIPELINE
constexpr bool select_pipeline_code = true;
#else
constexpr bool select_pipeline_code = false;
#endif
static_assert(select_pipeline_code == (CANN_ASC_STL_HAS_PIPELINE == 1));
```

使用 `#if` 判断交付标识的值。值为 `0` 时选择替代路径；值为 `1` 时，实际调用仍遵循
该模块的执行位置、芯片、类型、地址空间和操作支持条件。Host 能读取交付标识，
Device 操作按其支持的 Device 模式调用。

## 当前交付记录

随源码提供的 [extension_features.json](../../release/extension_features.json) 是宏值与
交付依据的登记表。当前 numeric_types 已交付基础接口并完成适用验收，标识为 `1`；
pipeline 和 cache 的基础接口继续按各自 Issue 推进。

| 宏 | 基础接口与模块 Issue | 当前值 |
| --- | --- | --- |
| `CANN_ASC_STL_HAS_PIPELINE` | [#105](https://gitcode.com/cann/asc-stl/issues/105)：SIMT 线程组流水线 | `0` |
| `CANN_ASC_STL_HAS_NUMERIC_TYPES` | [#85](https://gitcode.com/cann/asc-stl/issues/85)：扩展数值类型与标量转换 | `1` |
| `CANN_ASC_STL_HAS_CACHE` | [#99](https://gitcode.com/cann/asc-stl/issues/99)：缓存控制 | `0` |

本次将产品宏统一为上述日期宏和三个交付标识，替换旧分段版本宏及设备策略、
collectives 标识；pipeline 标识按 #105 的 SIMT 基础接口重新登记。

## 模块交付与发布维护

模块 Issue 和模块 API 文档共同定义基础接口：明确 API 签名、行为、使用条件及需要
通过的适用验收。首次交付时将这份接口说明冻结到 `docs/release/`，登记相对路径和
SHA256；后续新增接口及首次交付日期在模块文档中记录。

模块交付变更同时更新私有宏定义、登记表、API 文档、验收记录和发布说明。将宏改为
`1` 时，登记表须提供以下字段：

| 字段 | 要求 |
| --- | --- |
| `issue` | 对应模块 Issue，保持上表所列关联。 |
| `baseline` | 冻结接口说明的 `path` 和 `sha256`。路径相对于 `docs/release/`。 |
| `implementation_commit` | 完整的实现提交号。 |
| `acceptance` | 验收 JSON 的 `path` 和 `sha256`，同样相对于 `docs/release/`。 |
| `first_release_date` | 首次交付该基础接口的日期，不晚于当前包日期。 |

验收 JSON 的 `implementation_commit` 与登记表一致，`cases` 列出适用用例，每项含
唯一的 `name`、`status: "PASS"` 和 `returncode: 0`。验收记录应引用实际命令、环境和
日志，由模块交付核对其是否覆盖基础接口。尚未验收或只有跳过记录时保持 `0`，并在
`reason` 说明当前状态。

发布流程在固定源码提交上运行：

```bash
scripts/ci-release-check.sh --scope software --stage version --report-dir <new-report-directory>
```

此检查也在每次补充发布检查前执行，并纳入 Quick 的静态检查。检查日历日期、三个
标识的范围、宏与登记值、模块 Issue、交付依据及文件摘要。错误记录或缺失依据导致
非零退出并中止该发布检查；模块功能验收按其接口说明执行。

发行日期由发布流程固定更新，保持日期宏与登记表的 `release_date` 一致。
CMake 安装将登记表及其冻结资料复制到 `share/asc_stl/docs/release/`，并在相同的 `docs/zh/guide/` 与
`docs/en/guide/` 目录结构中提供本指南。
