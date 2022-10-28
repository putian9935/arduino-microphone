#include <PDM.h>

// default number of output channels
static const char channels = 1;

// default PCM output frequency
static const int frequency = 16000;

// Buffer to read samples into, each sample is 16-bits
char sampleBuffer[16384 * 8];

// Number of audio samples read
volatile int cur;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

  PDM.onReceive(onPDMdata);

  // set the gain
  PDM.setGain(100);

  if (!PDM.begin(channels, frequency)) {
    Serial.println("Failed to start PDM!");
    while (1)
      ;
  }
}

void loop() {
  if (Serial.available()) {
    Serial.read();

    // wait for first sample 
    cur = 0;
    while (cur < 16384 * 8)
      ;

    for (int length = 0; length < 5; ++length) {
      cur = 0;
      for (int end = 16384; end < 16384 * 9; end += 16384) {
        sampleBuffer[end - 2] = '\0';
        Serial.write(sampleBuffer + end - 16384, 16382);
        delay(100);
      }

      while (cur < 16384 * 8)
        ;
    }
  }
}

void onPDMdata() {
  int bytesAvailable = PDM.available();
  if (cur < 16384 * 8) {
    PDM.read(sampleBuffer + cur, bytesAvailable);
    cur += bytesAvailable;
  }
}
