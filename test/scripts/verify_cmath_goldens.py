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

"""Verify checked-in goldens independently of the public C++ implementations."""
import argparse
from decimal import Decimal, ROUND_HALF_EVEN, localcontext
import logging
from math import factorial, isqrt
from pathlib import Path
import re
import struct

LOGGER = logging.getLogger(__name__)


def exact_integer(operation, left, right, width):
    if operation == "c":
        return -((-left) // right)
    if operation == "f":
        return left // right
    if operation == "r":
        return -((-left) // right) * right
    if operation == "p":
        return pow(left, right)
    if operation == "s":
        return isqrt(left)
    if operation == "m":
        return (left * right) >> width
    raise ValueError(f"Unknown operation {operation}")


def verify_integers(root):
    widths = {"i8": 8, "u8": 8, "i16": 16, "u16": 16, "i32": 32, "u32": 32, "ill": 64, "ull": 64}
    rows = (root / "test/cases/asc/cmath/integer-goldens.txt").read_text().splitlines()
    for line in rows:
        key, operation, left, right, golden = line.split()
        width = widths.get(key)
        if width is None:
            raise ValueError(f"Unknown integer type key: {key}")
        expected = exact_integer(operation, int(left), int(right), width)
        if int(golden) != expected:
            raise ValueError(f"Wrong integer golden: {line}")
    return len(rows)


def decimal_pi():
    series = Decimal(0)
    for index in range(12):
        numerator = (-1) ** index * factorial(6 * index) * (13591409 + 545140134 * index)
        denominator = factorial(3 * index) * factorial(index) ** 3 * 640320 ** (3 * index)
        series += Decimal(numerator) / Decimal(denominator)
    return Decimal(426880) * Decimal(10005).sqrt() / series


def float32(value):
    return struct.unpack("<f", struct.pack("<f", float(value)))[0]


def decimal_sincos(value, pi):
    if value == 0:
        return value, 1.0
    # These binary32 inputs are exact integer ratios. The caller's 150-digit
    # context represents their decimal expansions without rounding.
    numerator, denominator = value.as_integer_ratio()
    angle = Decimal(numerator) / Decimal(denominator)
    reduced = angle - (angle / (2 * pi)).to_integral_value(rounding=ROUND_HALF_EVEN) * 2 * pi
    sine = term = reduced
    cosine = cosine_term = Decimal(1)
    for index in range(1, 120):
        term = -term * reduced * reduced / Decimal((2 * index) * (2 * index + 1))
        cosine_term = -cosine_term * reduced * reduced / Decimal((2 * index - 1) * (2 * index))
        sine += term
        cosine += cosine_term
    return float32(sine), float32(cosine)


def verify_trigonometry(root):
    text = (root / "test/support/cmath_trig_goldens.h").read_text()
    count = 0
    with localcontext() as context:
        context.prec = 150
        pi = decimal_pi()
        for row in re.findall(r"\{([^{}]+)\}", text, re.DOTALL):
            if "__builtin" in row:
                continue
            value, sine, cosine = (float.fromhex(token.strip().removesuffix("f")) for token in row.split(","))
            expected_sine, expected_cosine = decimal_sincos(value, pi)
            if struct.pack("<ff", sine, cosine) != struct.pack("<ff", expected_sine, expected_cosine):
                raise ValueError(f"Wrong trigonometric golden for {value.hex()}")
            count += 1
    return count


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[2])
    args = parser.parse_args()
    integers = verify_integers(args.root)
    trigonometry = verify_trigonometry(args.root)
    LOGGER.info("PASS: %s exact integer rows and %s decimal trigonometric vectors", integers, trigonometry)


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    main()
