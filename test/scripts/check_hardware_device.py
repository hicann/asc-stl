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

"""Host-only tests for device discovery; no NPU execution or device creation."""

import importlib.util
import os
from pathlib import Path
import tempfile
import unittest
from unittest import mock


SCRIPT = Path(__file__).resolve().parents[2] / "scripts" / "hardware_device.py"
SPEC = importlib.util.spec_from_file_location("asc_stl_hardware_device", SCRIPT)
DEVICE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(DEVICE)


class HardwareDeviceTests(unittest.TestCase):
    def setUp(self):
        directory = tempfile.TemporaryDirectory(prefix="asc-stl-devices-")
        self.addCleanup(directory.cleanup)
        self.root = Path(directory.name)
        environment = mock.patch.dict(os.environ, {"ASC_STL_HARDWARE_DEVICE_NODE": ""})
        environment.start()
        self.addCleanup(environment.stop)

    def add_device(self, name):
        node = self.root / name
        node.symlink_to("/dev/null")
        return node

    def test_zero_and_nonzero_nodes_keep_logical_id_zero(self):
        for name in ("davinci0", "davinci4"):
            with self.subTest(name=name):
                node = self.add_device(name)
                identity = DEVICE.hardware_device_identity(self.root)
                self.assertEqual(identity["device_node"], str(node))
                self.assertEqual(identity["runtime_device_id"], 0)
                info = Path("/dev/null").stat()
                self.assertEqual(identity["device_major"], os.major(info.st_rdev))
                self.assertEqual(identity["device_minor"], os.minor(info.st_rdev))
                node.unlink()

    def test_manager_and_regular_file_are_not_compute_devices(self):
        self.add_device("davinci_manager")
        (self.root / "davinci0").write_text("not a character device", encoding="utf-8")
        with self.assertRaisesRegex(RuntimeError, "found 0"):
            DEVICE.hardware_device_identity(self.root)

    def test_no_device_is_blocked(self):
        with self.assertRaisesRegex(RuntimeError, "found 0"):
            DEVICE.hardware_device_identity(self.root)

    def test_multiple_nodes_are_ambiguous_even_with_requested_node(self):
        first = self.add_device("davinci0")
        self.add_device("davinci4")
        os.environ["ASC_STL_HARDWARE_DEVICE_NODE"] = str(first)
        with self.assertRaisesRegex(RuntimeError, "found 2"):
            DEVICE.hardware_device_identity(self.root)

    def test_permissions_are_checked(self):
        self.add_device("davinci4")
        with mock.patch.object(DEVICE.os, "access", return_value=False):
            with self.assertRaisesRegex(RuntimeError, "not readable/writable"):
                DEVICE.hardware_device_identity(self.root)

    def test_matching_requested_node_is_allowed(self):
        node = self.add_device("davinci4")
        os.environ["ASC_STL_HARDWARE_DEVICE_NODE"] = str(node)
        self.assertEqual(DEVICE.hardware_device_identity(self.root)["device_node"], str(node))

    def test_stale_requested_node_is_blocked(self):
        self.add_device("davinci4")
        os.environ["ASC_STL_HARDWARE_DEVICE_NODE"] = str(self.root / "davinci0")
        with self.assertRaisesRegex(RuntimeError, "Configured"):
            DEVICE.hardware_device_identity(self.root)

    def test_broken_node_is_not_silently_ignored(self):
        (self.root / "davinci4").symlink_to(self.root / "missing")
        with self.assertRaises(OSError):
            DEVICE.hardware_device_identity(self.root)

    def test_cli_reports_environment_errors_with_exit_two(self):
        for error in (OSError("unavailable"), RuntimeError("ambiguous")):
            with mock.patch.object(DEVICE, "hardware_device_identity", side_effect=error):
                with self.assertLogs(DEVICE.LOGGER, level="ERROR") as messages:
                    self.assertEqual(DEVICE.main(), 2)
                self.assertIn("BLOCKED_ENVIRONMENT", messages.output[0])

    def test_cli_reports_identity(self):
        expected = {"device_node": "/dev/davinci4", "runtime_device_id": 0}
        with mock.patch.object(DEVICE, "hardware_device_identity", return_value=expected):
            with self.assertLogs(DEVICE.LOGGER, level="INFO") as messages:
                self.assertEqual(DEVICE.main(), 0)
            self.assertIn('"runtime_device_id": 0', messages.output[0])


if __name__ == "__main__":
    unittest.main()
