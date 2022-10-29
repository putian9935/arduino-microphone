#include "../include/wifi_server.hpp"
#include "../include/arduino_secrets.h"
#include "../include/microphone.hpp"
#include "server_responses.hpp"

#define TEST_CHAR_OTHERWISE_INVALID(ch)                                        \
  while (!client.available())                                                  \
    ;                                                                          \
  c = client.read();                                                           \
  if (c != (ch))                                                               \
    return INVALID;

WiFiServer server(80);

// your network SSID (name)
static char ssid[] = SECRET_SSID;

// your network password (use for WPA, or use as key for WEP)
static char pass[] = SECRET_PASS;

// your network key index number (needed only for WEP)
static int status = WL_IDLE_STATUS;

void wifi_setup() {
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true)
      ;
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  status = WiFi.begin(ssid, pass);
  delay(2000);

  // attempt more if not connected
  while (status != WL_CONNECTED) {
    // wait 5 seconds for connection:
    delay(5000);
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

static request_type parse_get(WiFiClient &client) {
  char c;

  TEST_CHAR_OTHERWISE_INVALID('E');
  TEST_CHAR_OTHERWISE_INVALID('T');
  TEST_CHAR_OTHERWISE_INVALID(' ');
  TEST_CHAR_OTHERWISE_INVALID('/');

  while (!client.available())
    ;
  c = client.read();
  if (c == ' ')
    return PAGE;
  if (c != '1')
    return INVALID;

  while (!client.available())
    ;
  c = client.read();
  if (c == ' ')
    return AUDIO;
  return INVALID;
}

request_type parse_client_request(WiFiClient &client) {
  boolean currentLineIsBlank = true;
  request_type ret = INVALID;
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      if (ret == INVALID) {
        if (c == 'G') {
          ret = parse_get(client);
        }
      }
      if (c == '\n' && currentLineIsBlank) {
        break;
      }
      if (c == '\n') {
        currentLineIsBlank = true;
      } else if (c != '\r') {
        currentLineIsBlank = false;
      }
    }
  }
  return ret;
}

void webpage_handler(WiFiClient &client) {  client.write(page); }

void audio_handler(WiFiClient &client) {
  client.write(audio_header);
  uint8_t str[] = {
      82, 73, 70, 70, 255, 255, 255, 255, 87,  65,  86,  69,  102, 109, 116,
      32, 16, 0,  0,  0,   1,   0,   1,   0,   128, 62,  0,   0,   0,   125,
      0,  0,  2,  0,  16,  0,   100, 97,  116, 97,  255, 255, 255, 255,
  };
  for (int i = 0; i < 44; ++i)
    client.write(str[i]);

  while (client.connected()) {
    for (int i = 0; i < 2000; ++i) {
      cur = 0;
      while (cur < 256)
        ;
      client.write(sampleBuffer, 256);
    }
    Serial.println("done");
    break;
  }
}