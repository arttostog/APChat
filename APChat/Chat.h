#pragma once

#include <ArduinoJson.h>
#include "Arduino.h"
#include "Settings.h"

class Chat {
  public:
    static void addMessageToChatLog(String nick, String message);
    static String getChatLog();
    struct ChatLog {
      String nick;
      String message;
    };
  private:
    static ChatLog chatLog[MAX_LOGS_COUNT];
    static char logPointer;
};
