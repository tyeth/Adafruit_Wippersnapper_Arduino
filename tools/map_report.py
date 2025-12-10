import argparse
import collections
import pathlib
from typing import Dict

SectionTotals = Dict[str, int]

def classify_path(path: str) -> str:
    """Return a friendly library/group label based on the object path."""
    norm = path.replace("\\", "/")
    if "/libraries/" in norm:
        rest = norm.split("/libraries/", 1)[1]
        if "/objs.a" in rest:
            rest = rest.split("/objs.a", 1)[0]
        elif rest.endswith(".a"):
            rest = rest.rsplit(".a", 1)[0]
        return rest
    if "/sketch/" in norm:
        return "sketch"
    if "/core/" in norm:
        return "core"
    if "/packages/esp8266/" in norm and "/lib/" in norm:
        rest = norm.split("/lib/", 1)[1]
        return "sdk/" + rest.split(".a", 1)[0]
    return pathlib.Path(norm).name


def categorize_section(section: str) -> str | None:
    """Map section name to flash/iram/dram buckets."""
    if not section:
        return None
    if section.startswith((".debug", ".comment", ".group")):
        return None
    if section.startswith((".irom0", ".rodata", ".gnu.linkonce.r")):
        return "flash"
    if section.startswith((".text", ".literal", ".iram", ".xt.lit", ".xt.prop")):
        return "iram"
    if section.startswith((".data", ".bss", ".ctors", ".dtors", ".jcr", ".noinit")):
        return "dram"
    return None


def parse_map(map_path: pathlib.Path) -> Dict[str, SectionTotals]:
    stats: Dict[str, SectionTotals] = collections.defaultdict(
        lambda: {"flash": 0, "iram": 0, "dram": 0, "total": 0}
    )
    section = None

    with map_path.open(errors="ignore") as fh:
        for line in fh:
            if line.startswith(" ."):
                parts = line.strip().split()
                section = parts[0] if parts else None
                continue

            if section and line.lstrip().startswith("0x"):
                parts = line.split()
                if (
                    len(parts) >= 3
                    and parts[0].startswith("0x")
                    and parts[1].startswith("0x")
                ):
                    size = int(parts[1], 16)
                    bucket = categorize_section(section)
                    if bucket:
                        lib = classify_path(parts[2])
                        stats[lib][bucket] += size
                        stats[lib]["total"] += size
                section = None

    return stats


def print_table(title: str, rows: list[tuple[str, SectionTotals]], key: str) -> None:
    print(title)
    for name, data in rows:
        flash_kb = data["flash"] / 1024
        iram_kb = data["iram"] / 1024
        dram_kb = data["dram"] / 1024
        print(
            f"{name:60s} total={data['total']/1024:7.1f}k flash={flash_kb:6.1f}k "
            f"iram={iram_kb:6.1f}k dram={dram_kb:6.1f}k"
        )
    print()


def main() -> None:
    parser = argparse.ArgumentParser(description="Summarize a linker map file.")
    parser.add_argument("map", type=pathlib.Path)
    parser.add_argument("--top", type=int, default=25)
    args = parser.parse_args()

    stats = parse_map(args.map)
    items = sorted(stats.items(), key=lambda kv: kv[1]["total"], reverse=True)
    flash_sorted = sorted(stats.items(), key=lambda kv: kv[1]["flash"], reverse=True)
    dram_sorted = sorted(stats.items(), key=lambda kv: kv[1]["dram"], reverse=True)

    print_table(f"Top {min(args.top, len(items))} by total", items[: args.top], "total")
    print_table(
        f"Top {min(args.top, len(flash_sorted))} by flash", flash_sorted[: args.top], "flash"
    )
    print_table(
        f"Top {min(args.top, len(dram_sorted))} by DRAM", dram_sorted[: args.top], "dram"
    )


if __name__ == "__main__":
    main()
