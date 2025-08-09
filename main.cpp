#include "Packet.h"
#include "LoraRadio.h"
#include "MeshRouter.h"

#define NODE_ID  0x1234
LoraRadio radio(LORA_CS, LORA_DIO0, LORA_RST);
MeshRouter mesh;

void sendHeartbeat() {
    Packet p; p.type = HEARTBEAT; p.node_id = NODE_ID; p.ts = uint32_t(time(nullptr));
    p.ttl = 7; p.hop = 0; p.flags = 0;
    uint16_t batt_mv = 3800; // TODO: read ADC
    p.payload = { uint8_t(batt_mv >> 8), uint8_t(batt_mv & 0xFF), uint8_t(int(radio.rssi())) };
    auto bytes = p.encode();
    radio.send(bytes.data(), bytes.size());
}

void setup() {
    Serial.begin(115200);
    if (!radio.begin()) { Serial.println("LoRa init failed"); while (1) delay(1000); }
}

unsigned long t0 = 0;
void loop() {
    // 1) Периодический heartbeat
    if (millis() - t0 > 15000) { sendHeartbeat(); t0 = millis(); }

    // 2) Приём/ретрансляция
    static uint8_t buf[256]; size_t got = 0;
    int st = radio.recv(buf, sizeof(buf), got);
    if (st == 0 && got > 0) {
        Packet in;
        if (Packet::decode(buf, got, in)) {
            if (mesh.seen(in)) return;
            mesh.markSeen(in);

            // печать для отладки
            Serial.printf("RX: type=%u from=%04X ttl=%u hop=%u len=%u\n",
                in.type, in.node_id, in.ttl, in.hop, (unsigned)in.payload.size());

            // ретрансляция, если ещё жив ttl
            if (in.ttl > 0) {
                in.ttl--; in.hop++;
                auto bytes = in.encode();
                radio.send(bytes.data(), bytes.size());
            }
        }
    }
}
