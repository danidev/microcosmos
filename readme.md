# Faselunare || Microcosmos


**THIS IS A TEMPORARY REPOSITORY OF THE LAST PROTOTYPE.**
The official repository of this project will be published when the Microcosmos will be ready to production.

---![microcosmos_panel](https://user-images.githubusercontent.com/4963780/137288007-3839c66b-f938-47f7-9baa-17c5f186b67f.jpg)


Microcosmos is a small (130X80mm) open-source electronic instrument, developed by Faselunare (Italy), aimed at prototyping electronic musical instruments and learning electronics, microcontroller programming and audio DSP.

Microcosmos is made on top of a Teensy 4.1 board.
The audio DSP part is done with the [FAUST](https://faust.grame.fr/) language.

Main hardware features: 
- 5 encoders with RGB LEDS, 
- 5 backlit buttons, 
- OLED color display, 
- SD Card, 
- audio I/O, 
- MIDI I/O on Mini Jack 
- MIDI over USBHost.

## Requirements

### Teensyduino IDE and SDKs

- [Teensyduino](https://www.pjrc.com/teensy/teensyduino.html)
- [Audio](https://www.pjrc.com/teensy/td_libs_Audio.html)
- [USBHost_t36](https://github.com/PaulStoffregen/USBHost_t36)

### Additional libraries

- [Adafruit-ST7735-Library](https://github.com/adafruit/Adafruit-ST7735-Library)

## Directory structure

- *dsp*: FAUST dsp scripts, exports for teensy and mapping files
- *microcosmos-v2.5*: current firmware source code

## How to use it

### Compile and run

In order to use the firmware, you have to open the **microcosmos-v2.5.ino** with the Teensyduino then compile and upload targeting the Teensy 4.0 platform.

### Change the DSP

On the **dsp** folder are placed some test scripts. Every test script must have its own **mapping.h** file to map the controls of the board to the FAUST params.

### DSP folder structure

the folder that contains the resources of a dsp must have this structure

```
name_of_the_dsp           -> main folder
  dsp                     -> dsp containing folder (will be linked to the FW)
    MicrocosmosDsp        -> folder of the exported C++ FAUST DSP code
      MicrocosmosDsp.cpp  
      MicrocosmosDsp.h
    mapping.h             -> mapping file
    MicrocosmosDsp.dsp    -> the FAUST script
```

#### Export the FAUST script to Teensy

The script must be exported for the Teensy architecture and this can be done in several ways, the easiest one is using the [FAUST Web IDE](https://faustide.grame.fr/) or the [FAUST Web Editor](https://faustide.grame.fr/), alternatively you can clone and install FAUST from the [Git repository](https://github.com/grame-cncm/faust) and run the faust2teensy command.

#### Mapping Parameters

The mapping.h file is where the mapping beetween the FAUST parameters and the Microcosmos controls is defined, here is an example:

```
// EDIT THIS SECTION TO MAP DSP PARAMETERS
#define DSP "drone_001"             // dsp name used to store presets
#define VERSION "0"                 // (further use)
#define MENU_PAGES_LENGTH 4         // number of pages
#define PARAMS_PER_PAGE 4           // how many params are shown on a page
#define BUTTONS_MAPPING_LENGHT 10   // number of button mappings, default is 10
#define MIDI_NOTE_ENABLED false     // enable only if there are gate/note params
#define MIDI_CC_ENABLED true        // enable if params can be used by MIDI CC

#define MENU_PARAMS_LENGTH MENU_PAGES_LENGTH * PARAMS_PER_PAGE

// EVERY PAGE OF THE MENU MUST HAVE A STRING TITLE
const char* const PAGE_TITLES[MENU_PAGES_LENGTH] = {
  "VOICE 1",
  "VOICE 2",
  "VOICE 3",
  "DELAY"
};

// MENU PARAMETERS LIST
const MenuParam MENU_PARAMS[MENU_PARAMS_LENGTH] = {
  // faust param, display name, default value, min value, max value, CC
  {"V1 NOTE", "NOTE", 69, 0, 127, 21},
  {"V1 LFO FREQ", "LFO FREQ", 1, 0, 80, 22},
  {"V1 LFO DEEP", "LFO DEEP", 0, 0, 1, 23},
  {"V1 VOLUME", "VOLUME", 0.1, 0, 0.9, 24},

  {"V2 NOTE", "NOTE", 69, 0, 127, 25},
  {"V2 LFO FREQ", "LFO FREQ", 1, 0, 80, 26},
  {"V2 LFO DEEP","LFO DEEP", 0, 0, 1, 27},
  {"V2 VOLUME", "VOLUME", 0.1, 0, 0.9, 28},

  {"V3 NOTE", "NOTE", 69, 0, 127, 41},
  {"V3 LFO FREQ", "LFO FREQ", 1, 0, 80, 42},
  {"V3 LFO DEEP","LFO DEEP", 0, 0, 1, 43},
  {"V3 VOLUME", "VOLUME", 0.1, 0, 0.9, 44},

  {"TIME", "TIME", 250, 0, 1000, 45},
  {"FEEDBACK", "FEEDBACK", 0.5, 0.0, 1.0, 46},
  {"AMOUNT","AMOUNT", 0.5, 0.0, 1.0, 47},
  {"", "", 0, 0, 0, 0},
};

const ButtonMapping BUTTONS_MAPPING[BUTTONS_MAPPING_LENGHT] = {
  // encoder buttons
  {1, BUTTON_MODE_MENU_DOWN},
  {0},
  {0},
  {0},
  {0},
  // buttons
  {1, BUTTON_MODE_MENU_UP},
  {2, BUTTON_MODE_SINGLE, "gate", 64},
  {0},
  {0},
  {0},
};

// mode; param1[16]; min; max;
const LedsMapping LEDS_MAPPING[MENU_PAGES_LENGTH] = {
  {0},
  {0},
  {0},
  {0}
};

const byte FG_COLOR[3] {
  0x00, 0xFF, 0x00
};
```

All those variables must be set in order to compile the firmware without errors.

#### Link the DSP resources to the firmware

After exporting the DSP script to the MicrocosmosDsp folder and mapping the parameters, you can include it in the microcosmos firmware.
There is a **dsp.sh** bash script (linux and macos) to symlink the folder into the project folder, for instance:

```
dsp.sh drone_01
```

This Will symlink the content of **dsp/drone_01/dsp** folder to **microcosmos-v2.5/src/dsp**

arternatively you can do it by:

```
cd microcosmos-v2.5/src
ln -s ../../dsp/drone_001 dsp
```

## TODO

- fix encoders sensitivity (when turned too fast and then turned on the opposite direction the value doesn't change correctly)
- MIDI IN and OUT on serial port implementation
- find a way to overcome the mapping.h file with better FAUST integration
- change the firmware loading a new one from SD
- optimize I2C write operations (for LEDSs)
- extend drawing functionalities
- presets on SD card
- samples support
- write tutorial and documentation

## Credits

Board developed and assembled By Francesco Mulassano and Alessandro Comanzo.
Software developed by Daniele Pagliero.

## License

This project is licensed under the terms of the GNU GENERAL PUBLIC LICENSE.
