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

"""Check worktree isolation with real rsync; standalone runs require it.

CTest may pass --allow-missing-rsync to report unavailable integration tooling
as skipped (exit 77), without treating an unexecuted regression as passed.
"""
import argparse
import logging
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

GIT = "/usr/bin/git"
LOGGER = logging.getLogger(__name__)
CODECHECK = Path(__file__).resolve().parents[2] / "scripts/quick_check_code.sh"


def source_identity(root):
    identity = {}
    for name, arguments in (("commit", ["rev-parse", "HEAD"]), ("tree", ["rev-parse", "HEAD^{tree}"]),
                            ("status", ["status", "--porcelain"])):
        identity[name] = subprocess.check_output([GIT, "-C", str(root), *arguments], text=True).strip()
    return identity


class CodeCheckIsolation(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)

    def test_codecheck_staging_cannot_commit_to_linked_worktree(self):
        repository = self.root / "repository"
        worktree = self.root / "worktree"
        fake_tools = self.root / "tools"
        repository.mkdir()
        fake_tools.mkdir()
        subprocess.run([GIT, "init", "--quiet", str(repository)], check=True)
        source = CODECHECK
        (repository / "scripts").mkdir()
        shutil.copy2(source, repository / "scripts/quick_check_code.sh")
        (repository / "README.md").write_text("original\n")
        (repository / ".gitignore").write_text(".env\n.env.*\n")
        subprocess.run([GIT, "-C", str(repository), "add", "."], check=True)
        commit = [GIT, "-C", str(repository), "-c", "user.name=Test", "-c", "user.email=test@example.invalid"]
        subprocess.run([*commit, "commit", "--quiet", "-m", "fixture"], check=True)
        subprocess.run([GIT, "-C", str(repository), "worktree", "add", "--quiet", "-b", "probe", str(worktree)],
                       check=True)
        (worktree / "README.md").write_text("uncommitted user change\n")
        # These are deliberately synthetic test fixtures, never user credentials.
        (worktree / ".env").write_text("DUMMY_TEST_VALUE=not-a-secret\n")
        (worktree / ".env.local").write_text("DUMMY_TEST_VALUE=not-a-secret\n")
        before = source_identity(worktree)
        git = [GIT, "-C", str(worktree)]
        branch = subprocess.check_output([*git, "symbolic-ref", "HEAD"])
        index = subprocess.check_output([*git, "ls-files", "--stage"])
        fake = fake_tools / "pre-commit"
        fake.write_text("#!/bin/sh\n[ ! -e .env ] && [ ! -e .env.local ]\n")
        fake.chmod(0o755)
        environment = dict(os.environ, PATH=str(fake_tools) + os.pathsep + os.environ["PATH"])
        result = subprocess.run([str(worktree / "scripts/quick_check_code.sh")], env=environment,
                                capture_output=True, text=True, check=False)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertEqual(source_identity(worktree), before)
        self.assertEqual(subprocess.check_output([*git, "symbolic-ref", "HEAD"]), branch)
        self.assertEqual(subprocess.check_output([*git, "ls-files", "--stage"]), index)
        self.assertTrue((worktree / ".env").is_file())
        self.assertTrue((worktree / ".env.local").is_file())
        self.assertEqual((worktree / "README.md").read_text(), "uncommitted user change\n")
        self.assertEqual((repository / "README.md").read_text(), "original\n")


def main():
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--allow-missing-rsync", action="store_true",
                        help="return CTest skip code 77 if rsync is unavailable")
    options, test_arguments = parser.parse_known_args()
    if shutil.which("rsync") is None:
        if options.allow_missing_rsync:
            LOGGER.warning("SKIP: rsync is unavailable; real worktree isolation regression was not run.")
            return 77
        parser.error("rsync is required for the real worktree isolation regression; no tests were run")
    program = unittest.main(argv=[sys.argv[0], *test_arguments], exit=False)
    return 0 if program.result.wasSuccessful() else 1


if __name__ == "__main__":
    sys.exit(main())
