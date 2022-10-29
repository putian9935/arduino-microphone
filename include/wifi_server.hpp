#ifndef WIFI_SERVER_H
#define WIFI_SERVER_H

#include <WiFiNINA.h> 

extern WiFiServer server;

typedef enum {
  PAGE, AUDIO, INVALID
} request_type;

void wifi_setup(); 
void printWifiStatus();

request_type parse_client_request(WiFiClient&);

void webpage_handler(WiFiClient&);
void audio_handler(WiFiClient &);
#endif 