#pragma once

#include <ArduinoJson.h>
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>
#include "Settings.h"
#include "Chat.h"

class ChatServer {
  private:
    static void defaultPage(AsyncWebServerRequest *request);
    static void sendMessage(AsyncWebServerRequest *request);
    static void getServerSettings(AsyncWebServerRequest *request);
    static AsyncWebServer server;
  public:
    static void onSetup();
};
