#pragma once
#include <Arduino.h>

enum MsgType : uint8_t { HELLO = 0, HEARTBEAT = 1, EVENT = 2, STATUS = 3, ACK = 4 };

struct Packet {
    uint8_t ver = 1, type = 0;
    uint16_t node_id = 0;
    uint8_t ttl = 7, hop = 0;
    uint32_t ts = 0;
    uint8_t flags = 0;
    std::vector<uint8_t> payload;

    static uint16_t crc16(const uint8_t* d, size_t n) {
        uint16_t crc = 0xFFFF;
        for (size_t i = 0; i < n; i++) {
            crc ^= (uint16_t)d[i] << 8;
            for (int j = 0; j < 8; j++) crc = (crc & 0x8000) ? (crc << 1) ^ 0x1021 : (crc << 1);
        }
        return crc;
    }

    std::vector<uint8_t> encode() const {
        std::vector<uint8_t> b;
        b.reserve(16 + payload.size());
        auto push16 = [&](uint16_t v) { b.push_back(v >> 8); b.push_back(v & 0xFF); };
        auto push32 = [&](uint32_t v) { b.push_back((v >> 24) & 0xFF); b.push_back((v >> 16) & 0xFF);
        b.push_back((v >> 8) & 0xFF); b.push_back(v & 0xFF); };
        b.push_back(ver); b.push_back(type); push16(node_id);
        b.push_back(ttl); b.push_back(hop); push32(ts); b.push_back(flags);
        b.insert(b.end(), payload.begin(), payload.end());
        uint16_t c = crc16(b.data(), b.size());
        push16(c);
        return b;
    }

    static bool decode(const uint8_t* d, size_t n, Packet& out) {
        if (n < 12) return false;
        uint16_t recv_crc = (d[n - 2] << 8) | d[n - 1];
        uint16_t calc_crc = crc16(d, n - 2);
        if (recv_crc != calc_crc) return false;
        size_t i = 0;
        out.ver = d[i++]; out.type = d[i++]; out.node_id = (d[i] << 8) | d[i + 1]; i += 2;
        out.ttl = d[i++]; out.hop = d[i++]; out.ts = (d[i] << 24) | (d[i + 1] << 16) | (d[i + 2] << 8) | d[i + 3]; i += 4;
        out.flags = d[i++];
        out.payload.assign(d + i, d + (n - 2));
        return true;
    }
};
