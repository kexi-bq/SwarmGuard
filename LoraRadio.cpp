// LoraRadio.h
#pragma once
#include <RadioLib.h>

class LoraRadio {
public:
    LoraRadio(uint8_t cs, uint8_t dio0, uint8_t rst) : radio(new Module(cs, dio0, rst)) {}
    bool begin() {
        int st = lora.begin(433.0, 125.0, 7, 5, 0x34, 17, 8, 0);
        return st == RADIOLIB_ERR_NONE;
    }
    int send(const uint8_t* b, size_t n) { return lora.transmit(b, n); }
    int recv(uint8_t* b, size_t n, size_t& out) {
        int st = lora.receive(b, n);
        if (st == RADIOLIB_ERR_NONE) { out = lora.getPacketLength(); return 0; }
        return st;
    }
    float rssi() const { return lora.getRSSI(); }
private:
    Module* radio;
    SX1278 lora = SX1278(radio);
};
