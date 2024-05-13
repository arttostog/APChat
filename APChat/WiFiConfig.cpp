#include "WiFiConfig.h"

void WiFiConfig::onSetup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip, IPAddress(255, 255, 255, 0));
  WiFi.softAP(SSID, PASSWORD);
}