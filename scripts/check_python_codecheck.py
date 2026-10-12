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

"""Mirror deterministic Python rules reported by the official CodeCheck."""

from __future__ import annotations

import ast
import io
import logging
import sys
import tokenize
from dataclasses import dataclass
from pathlib import Path


LOGGER = logging.getLogger(__name__)
MAX_FUNCTION_LINES = 50
MAX_FUNCTION_PARAMETERS = 5
MAX_FUNCTION_DEPTH = 4
MAX_LINE_LENGTH = 120


@dataclass(frozen=True, order=True)
class Violation:
    line: int
    rule: str
    message: str


def is_type_call(node: ast.AST) -> bool:
    return isinstance(node, ast.Call) and isinstance(node.func, ast.Name) and node.func.id == "type"


def non_comment_lines(lines: list[str], node: ast.AST) -> int:
    return sum(
        bool(line.strip()) and not line.lstrip().startswith("#")
        for line in lines[node.lineno - 1:node.end_lineno]
    )


def parameter_count(node: ast.FunctionDef | ast.AsyncFunctionDef) -> int:
    arguments = node.args
    return (
        len(arguments.posonlyargs)
        + len(arguments.args)
        + len(arguments.kwonlyargs)
        + int(arguments.vararg is not None)
        + int(arguments.kwarg is not None)
    )


def statement_depth(node: ast.FunctionDef | ast.AsyncFunctionDef) -> int:
    return max(
        (
            (child.col_offset - node.col_offset) // 4
            for child in ast.walk(node)
            if isinstance(child, ast.stmt) and child is not node
        ),
        default=0,
    )


def blank_lines_before(lines: list[str], line_number: int) -> int:
    count = 0
    for line in reversed(lines[: line_number - 1]):
        if line.strip():
            break
        count += 1
    return count


def ast_violations(text: str, path: Path) -> list[Violation]:
    tree = ast.parse(text, filename=str(path))
    lines = text.splitlines()
    violations: list[Violation] = []
    for node in ast.walk(tree):
        if isinstance(node, ast.Compare) and (
            is_type_call(node.left) or any(is_type_call(item) for item in node.comparators)
        ):
            violations.append(Violation(node.lineno, "G.TYP.08", "use isinstance() instead of comparing type()"))
        if isinstance(node, (ast.FunctionDef, ast.AsyncFunctionDef)):
            size = non_comment_lines(lines, node)
            if size > MAX_FUNCTION_LINES:
                violations.append(
                    Violation(
                        node.lineno,
                        "large-function",
                        f"function has {size} code lines (maximum {MAX_FUNCTION_LINES})",
                    )
                )
            parameters = parameter_count(node)
            if parameters > MAX_FUNCTION_PARAMETERS:
                violations.append(
                    Violation(
                        node.lineno,
                        "G.FNM.03",
                        f"function has {parameters} parameters (maximum {MAX_FUNCTION_PARAMETERS})",
                    )
                )
            depth = statement_depth(node)
            if depth > MAX_FUNCTION_DEPTH:
                violations.append(
                    Violation(
                        node.lineno,
                        "deep-function",
                        f"function nesting depth is {depth} (maximum {MAX_FUNCTION_DEPTH})",
                    )
                )
    for node in tree.body:
        if not isinstance(node, (ast.FunctionDef, ast.AsyncFunctionDef, ast.ClassDef)):
            continue
        first_line = min((decorator.lineno for decorator in node.decorator_list), default=node.lineno)
        if first_line > 1 and blank_lines_before(lines, first_line) < 2:
            violations.append(
                Violation(
                    node.lineno,
                    "G.FMT.03",
                    "top-level definition requires two preceding blank lines",
                )
            )
    return violations


def slice_spacing_violations(text: str) -> list[Violation]:
    violations: list[Violation] = []
    tokens = list(tokenize.generate_tokens(io.StringIO(text).readline))
    square_depth = 0
    previous: tokenize.TokenInfo | None = None
    ignored = {tokenize.ENCODING, tokenize.NL, tokenize.NEWLINE, tokenize.INDENT, tokenize.DEDENT}
    for token in tokens:
        if token.type == tokenize.OP and token.string == "[":
            square_depth += 1
        elif token.type == tokenize.OP and token.string == "]":
            square_depth = max(0, square_depth - 1)
        elif token.type == tokenize.OP and token.string == ":" and square_depth and previous is not None:
            if previous.end[0] == token.start[0] and previous.end[1] < token.start[1]:
                violations.append(Violation(token.start[0], "G.FMT.04", "remove whitespace before slice colon"))
        if token.type not in ignored:
            previous = token
    return violations


def line_length_violations(text: str) -> list[Violation]:
    return [
        Violation(number, "G.FMT.02", f"line has {len(line)} characters (maximum {MAX_LINE_LENGTH})")
        for number, line in enumerate(text.splitlines(), 1)
        if len(line) > MAX_LINE_LENGTH
    ]


def inspect_file(path: Path) -> list[Violation]:
    text = path.read_text(encoding="utf-8")
    return sorted(
        ast_violations(text, path)
        + slice_spacing_violations(text)
        + line_length_violations(text)
    )


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    findings = [
        (path, violation)
        for value in sys.argv[1:]
        for path in (Path(value),)
        if path.is_file()
        for violation in inspect_file(path)
    ]
    for path, violation in findings:
        LOGGER.error("%s:%d: %s: %s", path, violation.line, violation.rule, violation.message)
    if findings:
        return 1
    LOGGER.info("Python CodeCheck mirror passed (%d files)", len(sys.argv) - 1)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
