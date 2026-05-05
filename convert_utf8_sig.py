#!/usr/bin/env python3

# -----------------------------------------------------------------------------
# 用法说明：
#   将 C/C++ 源码文件转换为 UTF-8 with signature（BOM，utf-8-sig）。
#
# 默认处理扩展名：
#   .h .c .cpp .hpp .cc .cxx .hh
#
# 示例命令：
#   python convert_source_to_utf8_sig.py --root .
#   python convert_source_to_utf8_sig.py --root . --dry-run
#   python convert_source_to_utf8_sig.py --root . --ext .h .c .cpp .hpp .cc .cxx .hh
# -----------------------------------------------------------------------------

from __future__ import annotations

import argparse
from pathlib import Path


DEFAULT_EXTENSIONS = [".h", ".c", ".cpp", ".hpp", ".cc", ".cxx", ".hh"]
DEFAULT_SKIP_DIRS = {".git", ".vs", ".vscode", ".idea", "build", "cmake-build-debug", "cmake-build-release"}
DECODE_CANDIDATES = ["utf-8-sig", "utf-8", "gb18030", "cp936", "latin-1"]


def looks_binary(data: bytes) -> bool:
    return b"\x00" in data


def decode_text(data: bytes) -> tuple[str, str]:
    for enc in DECODE_CANDIDATES:
        try:
            return data.decode(enc), enc
        except UnicodeDecodeError:
            continue
    # latin-1 对 0-255 字节是无损映射，理论上总能解码成功，
    # 这里作为兜底保障，避免因编码识别失败导致脚本中断。
    return data.decode("latin-1"), "latin-1"


def iter_target_files(root: Path, exts: set[str]):
    for path in root.rglob("*"):
        if not path.is_file():
            continue
        if any(part in DEFAULT_SKIP_DIRS for part in path.parts):
            continue
        if path.suffix.lower() in exts:
            yield path


def convert_file(path: Path, dry_run: bool) -> tuple[str, str]:
    try:
        raw = path.read_bytes()
    except Exception as exc:  # noqa: BLE001
        return "failed", f"read_error: {exc}"

    if looks_binary(raw):
        return "skipped_binary", "contains_null_byte"

    text, used_enc = decode_text(raw)
    new_raw = text.encode("utf-8-sig")

    if raw == new_raw:
        return "unchanged", used_enc

    if not dry_run:
        try:
            path.write_bytes(new_raw)
        except Exception as exc:  # noqa: BLE001
            return "failed", f"write_error: {exc}"
    return "converted", used_enc


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="将源码文件转换为 UTF-8 with signature（BOM）。",
        epilog=(
            "使用示例：\n"
            "  python convert_source_to_utf8_sig.py --root .\n"
            "  python convert_source_to_utf8_sig.py --root . --dry-run\n"
            "  python convert_source_to_utf8_sig.py --root . --ext .h .c .cpp .hpp .cc .cxx .hh\n"
        ),
        formatter_class=argparse.RawTextHelpFormatter,
    )
    parser.add_argument(
        "--root",
        default=".",
        help="要扫描的根目录（默认：当前目录）。",
    )
    parser.add_argument(
        "--ext",
        nargs="+",
        default=DEFAULT_EXTENSIONS,
        help="要包含的文件扩展名，例如 .h .c .cpp .hpp .cc .cxx .hh",
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="仅输出变更统计，不写入文件。",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    root = Path(args.root).resolve()
    exts = {e.lower() if e.startswith(".") else f".{e.lower()}" for e in args.ext}

    stats = {
        "converted": 0,
        "unchanged": 0,
        "skipped_binary": 0,
        "failed": 0,
    }

    failed_records: list[tuple[Path, str]] = []
    total = 0

    for file_path in iter_target_files(root, exts):
        total += 1
        status, detail = convert_file(file_path, args.dry_run)
        stats[status] += 1
        if status == "failed":
            failed_records.append((file_path, detail))

    print(f"根目录: {root}")
    print(f"扩展名: {', '.join(sorted(exts))}")
    print(f"仅预览(dry-run): {args.dry_run}")
    print(f"扫描文件数: {total}")
    print(f"已转换: {stats['converted']}")
    print(f"未变化: {stats['unchanged']}")
    print(f"已跳过(二进制): {stats['skipped_binary']}")
    print(f"失败数: {stats['failed']}")

    if failed_records:
        print("\n失败文件列表:")
        for file_path, reason in failed_records:
            print(f"- {file_path}: {reason}")

    return 0 if stats["failed"] == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
