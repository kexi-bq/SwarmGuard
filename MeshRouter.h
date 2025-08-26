#pragma once
#include <Arduino.h>
#include "Packet.h"
#include "LoraRadio.h"

class MeshRouter {
public:
  explicit MeshRouter(LoraRadio& r) : radio_(r) {}
  void setNodeId(uint8_t id) { node_id_ = id; }
  bool sendTo(uint8_t dst, const uint8_t* data, uint8_t len, uint8_t ttl=8);
  bool poll(Packet& in);

private:
  LoraRadio& radio_;
  uint16_t seq_{0};
  uint8_t  node_id_{0};
};
