import("stdfaust.lib");

// 1. a square wave oscillator
/*
osc = os.pulsetrain(440, 0.5);
process = osc * 0.5 <: _,_;
*/


// 2. note to hz
/*
note = 64;
pitch = ba.midikey2hz(note);
osc = os.pulsetrain(pitch, 0.5);
process = osc * 0.5 <: _,_;
*/

// 3. UI parameter
/*
note = hslider("note", 64, 0, 127, 1);
pitch = ba.midikey2hz(note);
osc = os.pulsetrain(pitch, 0.5);
process = osc * 0.5 <: _,_;
*/

// 4. gate
/*
gate = button("gate");
note = hslider("note", 64, 0, 127, 1);
pitch = ba.midikey2hz(note);
osc = os.pulsetrain(pitch, 0.5);
process = osc * gate : _ * 0.5 <: _,_;
*/

// 5. AR envelope
/*
gate = button("[0]gate");
note = hslider("[1]note", 64, 0, 127, 1);
attack = hslider("[2]attack", 0.1, 0, 1, 0.1);
release = hslider("[3]release", 0.1, 0, 1, 0.1);
env = en.ar(attack, release, gate);
pitch = ba.midikey2hz(note);
osc = os.pulsetrain(pitch, 0.5);
process = osc * env : _ * 0.5 <: _,_;
*/

// 6. LP filter
/*
gate = ba.beat(120); //button("[0]gate");
note = hslider("[1]note", 64, 0, 127, 1);
attack = hslider("[2]attack", 0.1, 0.01, 1, 0.1);
release = hslider("[3]release", 0.1, 0, 1, 0.1);
cutoff = hslider("[4]cutoff", 5000, 50, 10000, 1) : si.smoo;
resonance = hslider("[5]resonance", 1, 1, 2, .9) : si.smoo;
env = en.ar(attack, release, gate);
pitch = ba.midikey2hz(note);
osc = os.pulsetrain(pitch, 0.5);
filter = fi.resonlp(cutoff, resonance, 0.9);
process = osc : filter : _ * env : _ * 0.5 <: _,_;
*/

// 7. Modulation with an LFO
gate = button("[0]gate");
note = hslider("[1]note", 64, 0, 127, 1);
attack = hslider("[2]attack", 0.1, 0.01, 1, 0.1) : si.smoo;
release = hslider("[3]release", 0.1, 0, 1, 0.1) : si.smoo;
cutoff = hslider("[4]cutoff", 5000, 50, 10000, 1) : si.smoo;
resonance = hslider("[5]resonance", 1, 1, 2, .9) : si.smoo;
lfoFreq = hslider("[6]LFO", 1, 0, 80, 0.1) : si.smoo;
cutoffAmount = hslider("[7]LFO->cutoff", 0, 0, 1, 0.1) : si.smoo;
pitchAmount = hslider("[8]LFO->pitch", 0, 0, 1, 0.1) : si.smoo;
env = en.ar(attack, release, gate);
lfo = os.lf_triangle(lfoFreq);
modulatedNote = note + (lfo * 24) * pitchAmount;
modulatedCutoff = cutoff + (lfo * 1000) * cutoffAmount;
pitch = ba.midikey2hz(modulatedNote);
osc = os.pulsetrain(pitch, 0.5);
filter = fi.resonlp(modulatedCutoff, resonance, 1);
process = osc : filter : _ * env : _ * 0.5 <: _,_;
