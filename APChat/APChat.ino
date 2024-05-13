#include "WiFiConfig.h"
#include "DNS.h"
#include "ChatServer.h"

void setup() {
  WiFiConfig::onSetup();
  DNS::onSetup();
  ChatServer::onSetup();
}

void loop() {
  DNS::onLoop();
}
