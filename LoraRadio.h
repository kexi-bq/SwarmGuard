#pragma once
#include <Arduino.h>
#include <RadioLib.h>
#include "Packet.h"

class LoraRadio {
public:
  explicit LoraRadio(Module* m) : radio_(m) {}
  bool begin(float freq_mhz, long bw_khz=125, int sf=7, int cr=5, int pwr_dbm=17);
  bool send(const Packet& p);
  bool recv(Packet& out, uint32_t timeout_ms);

private:
  SX1278 radio_; // или SX1276/SX127x по твоему модулю
};
