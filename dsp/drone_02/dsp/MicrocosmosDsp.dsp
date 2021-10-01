import("stdfaust.lib");

page(num, x) = hgroup("page%num", x);

fmin = 0;
fmax = 523.25;

gate = button("gate");

freq1 = page(1, hslider("[0]modulator[style:knob]", 440, fmin, fmax, 1));
freq2 = page(1, hslider("[1]carrier1[style:knob]", 440, fmin, fmax, 1));
freq3 = page(1, hslider("[2]carrier2[style:knob]", 440, fmin, fmax, 1));
cutoff = page(1, hslider("[3]cutoff[style:knob]", 0, 0, fmax, 1));

lfo = os.lf_trianglepos(0.001); //(hslider("lfo", 0.01, 0, 1, .01));

osc0 = os.triangle(freq1 + lfo * 523.25 / 4 : @(8));
osc1 = osc0 : +(1) : *(freq2 + lfo * 523.25 / 4 : @(16)) : os.triangle;
osc2 = osc0 : +(1) : *(freq3 + lfo * 523.25 / 4 : @(24)) : os.triangle;

filter = fi.resonbp(cutoff + cutoff * lfo + 1 , 0.8, 0.8);

/*sampleRate = 48000;
lfo2 = os.lf_trianglepos(0.6) * 100; // * 0.03;
delay(offset) = @(offset) : + ~(de.fdelay(sampleRate, lfo2*2))*0.3;

chorus = _<: (_,delay(0) * 0.8 :> _), (_,delay(512) * 0.8 :> _);*/

process = /*osc0 * 0.5 +*/ osc1 + osc2 : filter * gate <: _,_;
