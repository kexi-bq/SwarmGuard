#pragma once
// --- Node identity ---
#define NODE_ID        0x1234
#define FW_VER         0x01

// --- LoRa radio params (SX1278/76) ---
#define LORA_FREQ_MHZ  433.0    // согласовать с Антонио
#define LORA_BW_KHZ    125.0
#define LORA_SF        7
#define LORA_CR        5        // 4/5
#define LORA_PWR_DBM   17

// --- Pins (пример для ESP32) ---
#define LORA_CS   18
#define LORA_DIO0 26
#define LORA_RST  14
// #define LORA_BUSY -1 // если нет

// --- Mesh behavior ---
#define HEARTBEAT_MS   15000
#define MAX_RETRIES    3
#define ACK_TIMEOUT_MS 600
#define DEFAULT_TTL    7
