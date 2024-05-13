#include "Chat.h"

struct Chat::ChatLog Chat::chatLog[];
char Chat::logPointer = 0;

void Chat::addMessageToChatLog(String nick, String message) {
  if (logPointer == MAX_LOGS_COUNT) {
    for (char i = 0; i < MAX_LOGS_COUNT - 1; ++i)
      chatLog[i] = chatLog[i + 1];
    logPointer = MAX_LOGS_COUNT - 1;
  }
  chatLog[logPointer] = { nick, message };
  ++logPointer;
}

String Chat::getChatLog() {
  JsonDocument jsonDocument;
  for (Chat::ChatLog l: chatLog) {
    if (l.nick.length() == 0) continue;
    JsonObject obj = jsonDocument.createNestedObject();
    obj["nick"] = l.nick;
    obj["message"] = l.message;
  }
  String jsonString;
  serializeJson(jsonDocument, jsonString); 
  return jsonString;
}
