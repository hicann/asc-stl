# Warp协作示例

以1个block、32个线程运行。所有lane收敛调用协作接口，Host等待Stream完成后检查32个结果均为0。

```bash
source /usr/local/Ascend/ascend-toolkit/set_env.sh
cmake -S . -B build -DASC_STL_INCLUDE_DIR=/path/to/asc-stl/include
cmake --build build
./build/asc_stl_warp_example
```

输出`PASS: warp collectives`且退出码为0表示检查通过。

- [核函数](kernel.asc)
- [Host资源管理](main.cpp)
- [构建配置](CMakeLists.txt)
