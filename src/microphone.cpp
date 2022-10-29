#include "../include/microphone.hpp"

// default number of output channels
static const char channels = 1;

// default PCM output frequency
static const int frequency = 16000;

char sampleBuffer[MICROPHONE_SAMPLE_SIZE];
volatile int cur;

static void onPDMdata() {
  int bytesAvailable = PDM.available();
  if (cur < 256) {
    PDM.read(sampleBuffer + cur, bytesAvailable);
    cur += bytesAvailable;
  }
}

void microphone_setup() {
  PDM.onReceive(onPDMdata);

  // set the gain
  PDM.setGain(400);

  if (!PDM.begin(channels, frequency)) {
    Serial.println("Failed to start PDM!");
    while (1)
      ;
  }
}
