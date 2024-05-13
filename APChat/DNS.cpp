#include "DNS.h"

DNSServer DNS::dnsServer;

void DNS::onSetup() {
  dnsServer.start(53, "*", ip);
}

void DNS::onLoop() {
  dnsServer.processNextRequest();
}
