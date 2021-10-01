import("stdfaust.lib");

page(num, x) = hgroup("page%num", x);

note = hslider("note", 64, 0, 127, 1);
gate = button("gate");

duty = page(1, hslider("[0]duty[style:knob]", 0.5, 0, 1, .1) : si.smoo);
osc1vol = page(1, hslider("[1]vol_a[style:knob]", 0.5, 0, 1, 0.1) : si.smoo);
osc2vol = page(1, hslider("[2]vol_b[style:knob]", 0, 0, 1, 0.1) : si.smoo);
osc3vol = page(1, hslider("[3]vol_c[style:knob]", 0, 0, 1, 0.1) : si.smoo);

cutoff = page(2, hslider("[0]cutoff[style:knob]", 5000, 50, 10000, 0.1) : si.smoo);
resonance = page(2, hslider("[1]resonance[style:knob]", 1, 1, 15, 0.1) : si.smoo);
noiseVol = page(2, hslider("[2]noise[style:knob]", 0, 0, 1, 0.1) : si.smoo);

env1A = page(3, hslider("[0]1a[style:knob]", 0.01, 0.01, 4.5, 0.1) : si.smoo);
env1D = page(3, hslider("[1]2d[style:knob]", 0.01, 0.01, 4.5, 0.1) : si.smoo);
env1S = page(3, hslider("[2]3s[style:knob]", 1, 0, 1, 0.1) : si.smoo);
env1R = page(3, hslider("[3]4r[style:knob]", 0.01, 0.01, 4.5, 0.1) : si.smoo);

envPitch = page(4, hslider("[0]pitch_env[style:knob]", 0, 0, 1, 0.1) : si.smoo);
envDuty = page(4, hslider("[1]duty_env[style:knob]", 0, 0, 1, 0.1) : si.smoo);
envFilter = page(4, hslider("[2]cutoff_env[style:knob]", 0, 0, 1, 0.1) : si.smoo);

lfoSpeed = page(5, hslider("[0]lfo_1_freq[style:knob]", 1, 0.01, 8.0, 0.1) : si.smoo);
lfoPitch = page(5, hslider("[1]pitch_lfo[style:knob]", 0, 0, 1, 0.1) : si.smoo);
lfoDuty = page(5, hslider("[2]duty_lfo[style:knob]", 0, 0, 1, 0.1) : si.smoo);
lfoFilter = page(5, hslider("[3]cutoff_lfo[style:knob]", 0, 0, 1, 0.1) : si.smoo);

// modulations
lfo = os.lf_triangle(lfoSpeed);
env = en.adsr(env1A, env1D, env1S, env1R, gate);

freq = ba.midikey2hz(note) + ba.midikey2hz(note) * lfo * lfoPitch + ba.midikey2hz(note) * env * envPitch;
pwm = duty + duty * lfo * lfoDuty + duty * env * envDuty;
filterFreq = cutoff + cutoff * lfo * lfoFilter + cutoff * env * envFilter;

osc1 = os.pulsetrain(freq, pwm);
osc2 = os.sawtooth(freq);
osc3 = os.pulsetrain(freq/2, 0.5);
noise = no.noise;

mixer = osc1 * osc1vol, osc2 * osc2vol, osc3 * osc3vol, noise * noiseVol :> _;

filter = fi.resonlp(filterFreq, resonance, 0.9);

process = mixer : filter * env <: _,_;
