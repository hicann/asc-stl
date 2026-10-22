# Device Execution Hierarchy, Collective Operations, and Dynamic Work Acquisition

Thread hierarchy queries, collective operations, and work acquisition.

| Header | Description |
| --- | --- |
| [asc/hierarchy](asc_hierarchy/asc_hierarchy.md) | Provides dimension, size, and index queries for thread grids, thread blocks, warps, and threads, as well as sub-block index and count queries in AI Core SIMD programming |
| [asc/warp](asc_warp/asc_warp.md) | Provides voting, value matching, data exchange (shuffle), and reduction within a warp |
| [asc/collectives](asc_collectives/asc_collectives.md) | Provides thread block reduction, scan, broadcast, and condition checks in AI Core SIMT programming, as well as UB range reduction and scan in AI Core SIMD programming |
| [asc/work_queue](asc_work_queue/asc_work_queue.md) | Acquires non-overlapping work ranges for sub-blocks in AI Core SIMD programming and warps in AI Core SIMT programming, based on a GM atomic cursor provided by the caller |
