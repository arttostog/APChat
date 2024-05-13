#pragma once

#include <DNSServer.h>
#include "Settings.h"

class DNS {
  public:
    static void onSetup();
    static void onLoop();
  private:
    static DNSServer dnsServer;
};
