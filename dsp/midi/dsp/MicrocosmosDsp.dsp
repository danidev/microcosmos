import("stdfaust.lib");

trigger = button("gate");
duty = hslider("duty", 0.5, 0, 1, 0.1);
attack = hslider("attack", 0.1, 0, 1, 0.1);
release = hslider("release", 0.1, 0, 1, 0.1);
note = hslider("note", 69, 0, 127, 1);
osc = os.pulsetrain(ba.midikey2hz(note), duty);
env = en.ar(attack, release, trigger);

process = osc * env <: _,_;
