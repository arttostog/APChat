#include "ChatServer.h"

AsyncWebServer ChatServer::server(80);

void ChatServer::defaultPage(AsyncWebServerRequest *request) {
  request->send(LittleFS, "/index.html", "text/html");
}

void ChatServer::sendMessage(AsyncWebServerRequest *request) 
{
  if (!request->hasParam("nick") || !request->hasParam("message")) {
    request->send(400);
    return;
  }
  
  String nick = request->getParam("nick")->value(), message = request->getParam("message")->value();
  if (nick == "" || nick.length() > MAX_NAME_SIZE || message == "" || message.length() > MAX_MESSAGE_SIZE) {
    request->send(400);
    return;
  }
  
  Chat::addMessageToChatLog(nick, message);
  request->send(200);
}

void ChatServer::getServerSettings(AsyncWebServerRequest *request) {
  JsonDocument jsonDocument;
  JsonObject obj = jsonDocument.createNestedObject();
  obj["max_logs_count"] = MAX_LOGS_COUNT;
  obj["max_name_size"] = MAX_NAME_SIZE;
  obj["max_message_size"] = MAX_MESSAGE_SIZE;
  String jsonString;
  serializeJson(jsonDocument, jsonString); 
  request->send(200, "application/json", jsonString);
}

void ChatServer::onSetup() {
  LittleFS.begin();
  
  server.on("/", defaultPage);
  server.on("/style.css", [] (AsyncWebServerRequest *request) {
    request->send(LittleFS, "/style.css", "text/css");
  });
  server.on("/script.js", [] (AsyncWebServerRequest *request) { 
    request->send(LittleFS, "/script.js", "application/javascript");
  });
  
  server.on("/chat/send", HTTP_POST, sendMessage);
  server.on("/chat/get", HTTP_POST, [] (AsyncWebServerRequest *request) {
    request->send(200, "application/json; charset=utf-8", Chat::getChatLog());
  });
  server.on("/chat/settings", HTTP_POST, getServerSettings);
  
  server.onNotFound(defaultPage);
  server.begin();
}
