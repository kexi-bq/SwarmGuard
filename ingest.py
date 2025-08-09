from protocol import Packet
from lora import Lora
import time, requests

seen = set()
def key(p: Packet): return (p.node_id, p.ts, p.type)

def main():
    lora = Lora()
    lora.begin()
    while True:
        raw = lora.recv()
        if not raw:
            time.sleep(0.05); continue
        p = Packet.decode(raw)
        if not p: 
            continue
        if key(p) in seen: 
            continue
        seen.add(key(p))
        if len(seen) > 5000: 
            seen.clear()

        if p.type == 1:  # HEARTBEAT
            batt_mv = (p.payload[0] << 8) | p.payload[1]
            rssi = int(p.payload[2]) - 256 if p.payload[2] > 127 else p.payload[2]
            print(f"HB from {p.node_id:04X}: batt={batt_mv}mV rssi={rssi} ttl={p.ttl} hop={p.hop}")

        elif p.type == 2:  # EVENT
            cls = p.payload[0]; conf = p.payload[1]
            print(f"EVENT {cls=} {conf=} from {p.node_id:04X}")

        # пример: отправка в их веб-АПИ
        # requests.post(WEB_URL, json={...})

if __name__ == "__main__":
    main()
