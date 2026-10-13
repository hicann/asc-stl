#!/usr/bin/env python3

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

"""Identify container-visible compute nodes without confusing them with ACL IDs."""

import json
import logging
import os
from pathlib import Path
import re
import stat


LOGGER = logging.getLogger(__name__)


def hardware_device_identity(device_root=Path("/dev")):
    """Require one visible compute device; the existing runtime cases use ACL ID 0."""
    nodes = sorted(
        path for path in device_root.glob("davinci*")
        if re.fullmatch(r"davinci[0-9]+", path.name) and stat.S_ISCHR(path.stat().st_mode)
    )
    requested = os.environ.get("ASC_STL_HARDWARE_DEVICE_NODE")
    if requested and Path(requested) not in nodes:
        raise RuntimeError("Configured Ascend compute node is absent or not a character device")
    if len(nodes) != 1:
        raise RuntimeError(f"Expected one visible Ascend compute node; found {len(nodes)}")
    node = nodes[0]
    if not os.access(node, os.R_OK | os.W_OK):
        raise RuntimeError("Ascend compute node is not readable/writable by the current user")
    info = node.stat()
    return {
        "device_node": str(node),
        "device_major": os.major(info.st_rdev),
        "device_minor": os.minor(info.st_rdev),
        "runtime_device_id": 0,
    }


def main():
    try:
        LOGGER.info("%s", json.dumps(hardware_device_identity(), sort_keys=True))
    except (OSError, RuntimeError) as error:
        LOGGER.error("BLOCKED_ENVIRONMENT: %s", error)
        return 2
    return 0


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    raise SystemExit(main())
