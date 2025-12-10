import argparse
import collections
import pathlib
from typing import Dict

BUCKETS = (
    ("flash", (".irom0", ".rodata", ".gnu.linkonce.r")),
    ("iram", (".text", ".literal", ".iram", ".xt.lit", ".xt.prop")),
    ("dram", (".data", ".bss", ".ctors", ".dtors", ".jcr", ".noinit")),
)


def bucket_for(section: str | None) -> str | None:
    if not section or section.startswith((".debug", ".comment", ".group")):
        return None
    for name, prefixes in BUCKETS:
        if section.startswith(prefixes):
            return name
    return None


def short_name(path: str) -> str:
    norm = path.replace("\\", "/")
    # Strip archive noise "(file.o)"
    if "(" in norm and norm.endswith(")"):
        archive, member = norm.rsplit("(", 1)
        norm = archive + "(" + member[:-1]
    return norm.split("/components/", 1)[-1]


def collect(map_path: pathlib.Path, substring: str) -> Dict[str, Dict[str, int]]:
    stats: Dict[str, Dict[str, int]] = collections.defaultdict(
        lambda: {"flash": 0, "iram": 0, "dram": 0, "total": 0}
    )
    section = None
    needle = substring.replace("\\", "/")

    with map_path.open(errors="ignore") as fh:
        for raw in fh:
            line = raw.rstrip("\n")
            if line.startswith(" ."):
                section = line.strip().split()[0]
                continue
            if not section or not line.lstrip().startswith("0x"):
                continue
            parts = line.split()
            if len(parts) < 3 or not parts[0].startswith("0x") or not parts[1].startswith("0x"):
                section = None
                continue
            target = parts[2].replace("\\", "/")
            if needle not in target:
                section = None
                continue
            bucket = bucket_for(section)
            if not bucket:
                section = None
                continue
            size = int(parts[1], 16)
            key = short_name(target)
            stats[key][bucket] += size
            stats[key]["total"] += size
            section = None
    return stats


def print_rows(stats: Dict[str, Dict[str, int]], limit: int) -> None:
    rows = sorted(stats.items(), key=lambda kv: kv[1]["total"], reverse=True)
    print(f"Top {min(limit, len(rows))} objects containing substring")
    for name, data in rows[:limit]:
        print(
            f"{name:60s} total={data['total']/1024:6.1f}k flash={data['flash']/1024:5.1f}k "
            f"iram={data['iram']/1024:5.1f}k dram={data['dram']/1024:5.1f}k"
        )


def main() -> None:
    parser = argparse.ArgumentParser(description="Filter map entries by substring")
    parser.add_argument("map", type=pathlib.Path)
    parser.add_argument("substring", help="Substring to match in object path")
    parser.add_argument("--top", type=int, default=20)
    args = parser.parse_args()

    stats = collect(args.map, args.substring)
    print_rows(stats, args.top)


if __name__ == "__main__":
    main()
