# GM与UB流水拷贝示例

本工程需要Ascend 950、CANN与ASC CMake支持。Host在设备0分配GM、启动单个AI Core核函数，将256个整数拷贝到UB并加1，再拷回GM。退出码为0且输出`PASS: pipeline_copy`表示所有结果符合预期。

```bash
source /usr/local/Ascend/ascend-toolkit/set_env.sh
cmake -S . -B build -DASC_STL_INCLUDE_DIR=/path/to/asc-stl/include -DASC_STL_EXAMPLE_STANDARD=17
cmake --build build
./build/asc_stl_pipeline_copy
```

将语言选项改为20可使用C++20。Host等待Stream完成后才读取输出并释放存储；存储在所有异步访问结束前保持有效。

- [核函数](kernel.asc)
- [Host资源管理](main.cpp)
- [构建配置](CMakeLists.txt)
