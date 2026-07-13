// ===========================================================================
// log_ring.h  -  Ringpuffer fuer Log-/Debug-Ausgaben (Service-Tab)
// ---------------------------------------------------------------------------
// Wird vom `logger: on_message:`-Trigger in timer-relais-c3.yaml gefuettert
// (das aktiviert zugleich ESPHomes Log-Listener) und vom Web-Endpunkt
// /api/log?level=&since= als JSON gelesen.
//
// Log-Level (ESPHome): 1=ERROR 2=WARN 3=INFO 4=CONFIG 5=DEBUG 6=VERBOSE.
// Anzeige-Filter: Zeilen mit level <= gewaehlter Stufe.
// ===========================================================================
#pragma once
#include "esphome.h"
#include <cstring>
#include <string>

namespace esphome {

static const int LOG_RING_N = 40;      // gepufferte Zeilen
static const int LOG_LINE_LEN = 116;   // max. Zeichen je Zeile

struct LogLine {
  uint32_t seq;      // fortlaufende Nummer (0 = leerer Slot)
  uint8_t level;
  char text[LOG_LINE_LEN];
};

static LogLine g_log[LOG_RING_N];      // statisch -> null-initialisiert
static uint32_t g_log_seq = 0;
static int g_log_head = 0;

// ANSI-Farbcodes und Steuerzeichen entfernen (der Logger faerbt Meldungen ein).
inline void log_sanitize(const char *src, char *dst, size_t n) {
  size_t o = 0;
  for (size_t i = 0; src && src[i] && o + 1 < n; i++) {
    unsigned char c = (unsigned char) src[i];
    if (c == 0x1b) { while (src[i] && src[i] != 'm') i++; continue; }  // \e[..m
    if (c < 0x20 || c == 0x7f) continue;
    dst[o++] = (char) c;
  }
  dst[o] = '\0';
}

inline void log_ring_push(uint8_t level, const char *tag, const char *message) {
  char combined[LOG_LINE_LEN];
  snprintf(combined, sizeof(combined), "%s: %s", tag ? tag : "", message ? message : "");
  LogLine &L = g_log[g_log_head];
  L.seq = ++g_log_seq;
  L.level = level;
  log_sanitize(combined, L.text, sizeof(L.text));
  g_log_head = (g_log_head + 1) % LOG_RING_N;
}

inline void json_append_escaped(std::string &out, const char *s) {
  for (size_t i = 0; s && s[i]; i++) {
    char c = s[i];
    if (c == '"' || c == '\\') { out += '\\'; out += c; }
    else out += c;
  }
}

// JSON der Zeilen mit level <= sel und seq > since (aelteste zuerst).
inline std::string log_ring_json(uint8_t sel, uint32_t since) {
  std::string out = "{\"ok\":true,\"seq\":";
  out += std::to_string((uint32_t) g_log_seq);
  out += ",\"lines\":[";
  bool first = true;
  for (int i = 0; i < LOG_RING_N; i++) {
    int idx = (g_log_head + i) % LOG_RING_N;
    const LogLine &L = g_log[idx];
    if (L.seq == 0 || L.seq <= since) continue;
    if (L.level == 0 || L.level > sel) continue;
    if (!first) out += ',';
    first = false;
    out += "{\"s\":"; out += std::to_string(L.seq);
    out += ",\"l\":"; out += std::to_string((int) L.level);
    out += ",\"t\":\""; json_append_escaped(out, L.text); out += "\"}";
  }
  out += "]}";
  return out;
}

}  // namespace esphome
