# Faselunare || Microcosmos

Microcosmos is a small (130X80mm) open-source electronic instrument, developed by Faselunare (Italy), aimed at prototyping electronic musical instruments and learning electronics, microcontroller programming and audio DSP.

Microcosmos is made on top of a Teensy 4.1 board and features several encoders, buttons, it has an OLED color display, SD Card, audio I/O, MIDI I/O on Mini Jack and MIDI over USBHost.

The audio DSP part is done with the [FAUST](https://faust.grame.fr/) language.

## Requirements

### Teensyduino IDE and SDKs

- [Teensyduino](https://www.pjrc.com/teensy/teensyduino.html)
- [Audio](https://www.pjrc.com/teensy/td_libs_Audio.html)
- [USBHost_t36](https://github.com/PaulStoffregen/USBHost_t36)

### Additional libraries

- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)

## Directory structure

- *dsp*: FAUST dsp scripts, exports for teensy and mapping files
- *microcosmos-v2.5*: current firmware source code

## How to use it

### Compile and run

In order to use the firmware, you have to open the *microcosmos-v2.5.ino* with the Teensyduino then compile and upload targeting the Teensy 4.0 platform.

### Change the DSP

On the *dsp* folder are placed some test scripts. Every test script must have its own *mapping.h* file to map the controls of the board to the FAUST params.

The script must be exported for the Teensy architecture and this can be done in several ways, the easiest one is using the [FAUST Web IDE](https://faustide.grame.fr/) or the [FAUST Web Editor](https://faustide.grame.fr/), alternatively you can clone and install FAUST from the [Git repository](https://github.com/grame-cncm/faust) and run the faust2teensy command.

After exporting the DSP script to the MicrocosmosDsp folder, you can include it in the microcosmos firmware. There is a *dsp.sh* bash script (linux and macos) to symlink the folder into the project folder, for instance:

```
dsp.sh drone_01
``` 

This Will symlink the content of **dsp/drone_01/dsp** folder to microcosmos-v2.5/src/dsp   



## Credits

Board developed and assembled By Francesco Mulassano and Alessandro Comanzo.
Software developed by Daniele Pagliero.

## License

This project is licensed under the terms of the GNU GENERAL PUBLIC LICENSE.
