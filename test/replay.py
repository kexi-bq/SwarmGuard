import time, pathlib
from protocol import Packet

def load_frames(dirp="tests/pcap"):
    for p in sorted(pathlib.Path(dirp).glob("*.bin")):
        yield p.read_bytes()

def main():
    for raw in load_frames():
        p = Packet.decode(raw)
        print("OK" if p else "BAD", len(raw))
        time.sleep(0.1)

if __name__ == "__main__":
    main()
