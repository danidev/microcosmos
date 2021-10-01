#include "audio.h"


MicrocosmosDsp microcosmosDsp;
AudioInputI2S  audioInput;
AudioOutputI2S audioOutput;
AudioControlSGTL5000 sgtl5000_1;

AudioAmplifier al;
AudioAmplifier ar;

// MONO IN STEREO OUT
AudioConnection pc1(audioInput, 0, microcosmosDsp, 0);
AudioConnection pc2(microcosmosDsp, 0, al, 0);
AudioConnection pc3(microcosmosDsp, 1, ar, 0);
AudioConnection pc4(al, 0, audioOutput, 0);
AudioConnection pc5(ar, 0, audioOutput, 1);

// BYPASS / TEST
// AudioConnection patchCord2(audioInput, 0, microcosmosDsp, 0);
// AudioConnection patchCord3(audioInput, 0, audioOutput, 0);
// AudioConnection patchCord4(audioInput, 1, audioOutput, 1);

// LEFT AUDIO IN RIGHT FAUST
// AudioConnection patchCord2(audioInput, 0, microcosmosDsp, 0);
// AudioConnection patchCord3(microcosmosDsp, 0, audioOutput, 0);
// AudioConnection patchCord4(audioInput, 0, audioOutput, 1);

void audio_setup() {
  // audio initialization
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.9);       // 0 to 1
  sgtl5000_1.lineOutLevel(13);  // 13 to 31

  al.gain(0.0);
  ar.gain(0.0);

  // sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  // sgtl5000_1.lineInLevel(5);
}

void audio_set_param(const char *path, float value) {
  microcosmosDsp.setParamValue(path, value);
}

float audio_get_param(const char *path) {
  return microcosmosDsp.getParamValue(path);
}

void audio_set_main_volume(float value) {
  al.gain(value);
  ar.gain(value);
}
