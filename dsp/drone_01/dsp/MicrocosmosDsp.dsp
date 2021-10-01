import("stdfaust.lib");

sampleRate = 48000;

page(num, x) = hgroup("page%num", x);

trigger = ba.toggle(button("gate"));

voice(num) = out
with {
    // UI CODE
    note = page(num, hslider("[0]V%num NOTE[style:knob]", 69, 0, 127, 1));
    lfoFreq = page(num, hslider("[1]V%num LFO FREQ[style:knob]", 1, 0, 80, 0.1) : si.smoo);
    volume = page(num, hslider("[2]V%num VOLUME[style:knob]", 0.1, 0, 0.9, 0.1) : si.smoo);
    lfoAttenuator = page(num, hslider("[3]V%num LFO DEEP[style:knob]", 0, 0, 1, 0.1) : si.smoo);

    // DSP CODE
    lfo = os.lf_triangle(lfoFreq)*24 : page(num, hbargraph("[4]V%num LED LFO", -1, 1));
    pitch = ba.midikey2hz(note+lfo*lfoAttenuator);
    osc = os.triangle(pitch);
    out = osc * volume * trigger;
};

signal = voice(1) + voice(2) + voice(3);

time = page(4, hslider("[0]TIME[style:knob]", 250, 0, 1000, 1) / 1000);
feedback = page(4, hslider("[1]FEEDBACK[style:knob]", 0.5, 0, 1, 0.1));
amount = page(4, hslider("[2]AMOUNT[style:knob]", 0.5, 0, 1, 0.1));
delay = (signal : + ~@(time * sampleRate : int)*feedback) * amount;

process = signal + delay <: _,_;
