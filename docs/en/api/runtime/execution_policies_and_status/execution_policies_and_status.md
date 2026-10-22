# Device-Side Execution Policies, Execution Requirements, and Submission Status

Execution policies, runtime requirements, and asynchronous submission status.

| Header | Description |
| --- | --- |
| [asc/execution](asc_execution/asc_execution.md) | Uniformly exports the interfaces related to device-side execution policies, execution requirements, and submission status |
| [asc/execution.policy.h](asc_execution_policy_h/asc_execution_policy_h.md) | Provides device-side execution policies for associating a Stream, temporary workspace, and execution requirements |
| [asc/execution.require.h](asc_execution_require_h/asc_execution_require_h.md) | Provides composition facilities that attach execution requirements to a device-side execution policy |
| [asc/execution.determinism.h](asc_execution_determinism_h/asc_execution_determinism_h.md) | Provides result-determinism requirements for parallel algorithms, used to specify whether identical inputs must produce repeatable results |
| [asc/execution.output_ordering.h](asc_execution_output_ordering_h/asc_execution_output_ordering_h.md) | Provides output-ordering requirements for parallel algorithms |
| [asc/execution.tie_break.h](asc_execution_tie_break_h/asc_execution_tie_break_h.md) | Provides the selection rules applied when multiple results satisfy the condition at the same time |
