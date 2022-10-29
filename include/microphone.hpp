#ifndef MICROPHONE_HPP
#define MICROPHONE_HPP

#include "../include/microphone.hpp"
#include <PDM.h>

#define MICROPHONE_SAMPLE_SIZE 16384

// Buffer to read samples into, each sample is 16-bits
extern char sampleBuffer[MICROPHONE_SAMPLE_SIZE];

// Number of audio bytes read(two bytes per sample)
extern volatile int cur;

void microphone_setup();


#endif 