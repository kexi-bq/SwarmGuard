// MeshRouter.cpp
#pragma once
#include "Packet.h"
#include <unordered_set>

struct Key {
    uint16_t id; uint32_t ts; uint8_t type;
    bool operator==(const Key& o) const { return id == o.id && ts == o.ts && type == o.type; }
};
struct KeyHash {
    size_t operator()(const Key& k) const {
        return (size_t)k.id ^ ((size_t)k.ts << 1) ^ k.type;
    }
};

class MeshRouter {
public:
    void markSeen(const Packet& p) {
        if (cache.size() > 1024) cache.clear();
        cache.insert({ p.node_id,p.ts,p.type });
    }
    bool seen(const Packet& p) const {
        return cache.find({ p.node_id,p.ts,p.type }) != cache.end();
    }
private:
    std::unordered_set<Key, KeyHash> cache;
};
