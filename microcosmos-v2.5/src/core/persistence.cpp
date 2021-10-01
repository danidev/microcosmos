#include "persistence.h"

void persistence_setup(const char* dsp) {
  // clear presistence memory if dsp mismatch
  byte eepromName[8];
  byte dspName[8];
  bool mismatch = false;
  for (byte i = 0; i < 8; i++) {
    eepromName[i] = storage_eeprom_read(i);
    if (i < strlen(dsp)) {
      dspName[i] = dsp[i];
    } else {
      dspName[i] = '_';
    }

    Serial.printf("eeprom:%c dsp:%c\n", eepromName[i], dspName[i]);

    if (eepromName[i] != dspName[i]) {
      mismatch = true;
    }
  }

  if (mismatch) {
    Serial.printf("mismatch!\n");
    storage_eeprom_clear();
    for (byte i = 0; i < 8; i++) {
      storage_eeprom_write(i, dspName[i]);
    }
  }
  // end persistence */
}
