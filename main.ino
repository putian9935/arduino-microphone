#include "include/microphone.hpp"
#include "include/wifi_server.hpp"


void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  wifi_setup();
  microphone_setup();
}

void loop() {
  WiFiClient client = server.available();
  if(client) {
    Serial.println("new client");
    // an HTTP request ends with a blank line
    request_type req = parse_client_request(client);
    if(req == PAGE) {
      webpage_handler(client);
    }
    else if(req == AUDIO) {
      audio_handler(client);
    }
    delay(1);
    client.stop();
  }
}
