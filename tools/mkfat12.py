#!/usr/bin/env python3
import struct

# Создаёт образ FAT12 (1.44 МБ)
with open("floppy.img", "wb") as f:
    f.write(b"\x00" * 1474560)  # 1.44 МБ

    # Записываем BPB (упрощённо)
    bpb = struct.pack(
        "<3s8sHBHBHHBHHH",
        b"\xEB\x3C\x90",  # jump
        b"FLOPPAOS",      # OEM
        512,             # sector size
        1,               # sectors per cluster
        1,               # reserved sectors
        2,               # FAT count
        224,             # root entries
        2880,            # total sectors
        0xF0,            # media
        9,               # sectors per FAT
    )
    f.seek(0x0B)
    f.write(bpb)
    f.seek(510)
    f.write(b"\x55\xAA")  # сигнатура
