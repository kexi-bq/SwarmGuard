# SwarmGuard Proto (ESP32 + SX1278 + Pi)

## Quick start
- ESP32: PlatformIO → `upload` (see `platformio.ini`)
- Pi gateway: `pip install -r requirements.txt` → `python ingest.py`

## Radio params (to align with Jocotoco)
- Freq: 433.0 MHz (TBD)
- BW: 125 kHz, SF7, CR 4/5, Pwr 17 dBm

## Files
- `Packet.h` — бинарный протокол + CRC
- `LoraRadio.cpp` — обёртка RadioLib
- `MeshRouter.cpp` — TTL, дедуп, ретрансляция
- `ingest.py` — приём пакетов на Pi
- `bridge.py` — отправка в веб (HTTP/MQTT)
- `PROTOCOL.md` — описание пакетов

## Wiring
см. `docs/wiring_esp32_sx1278.png`

## Event classes
см. `data/event_map.json`
