import argparse
import collections
import pathlib
from typing import Dict

BUCKET_SECTIONS = {
    "flash": (".irom0", ".rodata", ".gnu.linkonce.r"),
    "iram": (".text", ".literal", ".iram", ".xt.lit", ".xt.prop"),
    "dram": (".data", ".bss", ".ctors", ".dtors", ".jcr", ".noinit"),
}


def bucket_for_section(section: str | None) -> str | None:
    if not section:
        return None
    if section.startswith((".debug", ".comment", ".group")):
        return None
    for bucket, prefixes in BUCKET_SECTIONS.items():
        if section.startswith(prefixes):
            return bucket
    return None


def clean_driver_name(target: str) -> str:
    norm = target.replace("\\", "/")
    marker = "components/i2c/drivers/"
    _, tail = norm.split(marker, 1)
    if "(Wipper" in tail:
        tail = tail.split("(", 1)[1].rstrip(")")
    return tail.replace(".o", "").replace(".cpp", "")


def collect(map_path: pathlib.Path) -> Dict[str, Dict[str, int]]:
    stats: Dict[str, Dict[str, int]] = collections.defaultdict(
        lambda: {"flash": 0, "iram": 0, "dram": 0, "total": 0}
    )
    section = None

    with map_path.open(errors="ignore") as fh:
        for raw in fh:
            line = raw.rstrip("\n")
            if line.startswith(" ."):
                parts = line.strip().split()
                section = parts[0] if parts else None
                continue
            if section and line.lstrip().startswith("0x"):
                parts = line.split()
                if len(parts) >= 3 and parts[0].startswith("0x") and parts[1].startswith("0x"):
                    target = parts[2]
                    if "components" not in target:
                        section = None
                        continue
                    if "components\\i2c\\drivers" not in target and "components/i2c/drivers" not in target:
                        section = None
                        continue
                    bucket = bucket_for_section(section)
                    if not bucket:
                        section = None
                        continue
                    size = int(parts[1], 16)
                    name = clean_driver_name(target)
                    stats[name][bucket] += size
                    stats[name]["total"] += size
                section = None
    return stats


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Break down memory usage for components/i2c/drivers object files"
    )
    parser.add_argument("map", type=pathlib.Path)
    parser.add_argument("--top", type=int, default=20)
    args = parser.parse_args()

    stats = collect(args.map)
    rows = sorted(stats.items(), key=lambda kv: kv[1]["total"], reverse=True)
    print(f"Top {min(args.top, len(rows))} I2C drivers by total size")
    for name, data in rows[: args.top]:
        print(
            f"{name:40s} total={data['total']/1024:6.1f}k flash={data['flash']/1024:5.1f}k "
            f"iram={data['iram']/1024:5.1f}k dram={data['dram']/1024:5.1f}k"
        )


if __name__ == "__main__":
    main()
