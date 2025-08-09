# SwarmGuard LoRa Protocol v0.1

Header (big-endian):
| ver(1) | type(1) | node_id(2) | seq(2) | ttl(1) | hop(1) | ts_unix(4) | flags(1) | payload | crc16(2) |

type:
- 0 HELLO
- 1 HEARTBEAT
- 2 EVENT
- 3 STATUS
- 4 ACK

flags (bitfield): b0=requires_ack, b1=encr, b2=gps_present, b3=low_batt

EVENT payload:
| cls(1) | conf(1) | batt_mv(2) | rssi(1) | lat_i32(4)? | lon_i32(4)? | alt_i16(2)? |

GPS: int32 = degrees * 1e7 (big-endian). CRC16-CCITT over everything except last 2 bytes.

Example hex (HEARTBEAT, node 0x1234):  
`01 01 12 34 00 2A 07 00 66 77 88 99 00 0E 10 5F 12 34`
