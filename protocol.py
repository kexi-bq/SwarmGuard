import struct
from dataclasses import dataclass

CRC_POLY = 0x1021

def crc16_ccitt(data: bytes) -> int:
    crc = 0xFFFF
    for b in data:
        crc ^= (b << 8) & 0xFFFF
        for _ in range(8):
            crc = ((crc << 1) ^ CRC_POLY) & 0xFFFF if (crc & 0x8000) else (crc << 1) & 0xFFFF
    return crc

@dataclass
class Packet:
    ver:int; type:int; node_id:int; ttl:int; hop:int; ts:int; flags:int; payload:bytes

    @staticmethod
    def decode(raw: bytes):
        if len(raw) < 12: return None
        body, crc = raw[:-2], raw[-2:]
        recv = struct.unpack(">H", crc)[0]
        calc = crc16_ccitt(body)
        if recv != calc: return None
        ver, typ, node_id, ttl, hop, ts, flags = struct.unpack(">BBHBBIB", body[:12])
        payload = body[12:]
        return Packet(ver, typ, node_id, ttl, hop, ts, flags, payload)
