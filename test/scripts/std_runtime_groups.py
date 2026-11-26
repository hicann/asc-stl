# Copyright 2026 湖北多样性算力应用创新研究院 (Hubei Institute for Heterogeneous Computing Applications)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from pathlib import Path
import sys


def main():
    """Print the tests assigned to each SIMT executable in the runtime gates."""
    case_root = Path(__file__).resolve().parents[1] / "cases" / "asc" / "std"
    headers = sorted(path.parent.name for path in case_root.glob("*/device_checks.h"))
    if not headers:
        raise SystemExit("No per-header SIMT checks were found")

    batch_size = 8
    for start in range(0, len(headers), batch_size):
        group = headers[start:start + batch_size]
        sys.stdout.write(f"{group[0]}-{group[-1]}:{','.join(group)}\n")


if __name__ == "__main__":
    main()
