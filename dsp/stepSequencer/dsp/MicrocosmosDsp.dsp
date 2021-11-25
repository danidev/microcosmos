import("stdfaust.lib");

pageGroup(page, x) = hgroup("%page", x);

// constants
steps = 8;

// main timer
speed = pageGroup(0, hslider("speed[style:knob]", 120, 20, 255, 1)) : si.smoo;
play = pageGroup(0, button("play")) : ba.toggle;

//values generator
valStep(num) = out
with {
  stepGroup(x) = vgroup("step%num", x);
  val = pageGroup(1, stepGroup(vslider("[%num]val%num[style:knob]", 0, 0,127, 1)));
  out = val;
};

//gates generator
gateStep(num) = out
with {
  stepGroup(x) = vgroup("step%num", x);
  gate = pageGroup(1, stepGroup(button("[%num]gate%num"))) : ba.toggle : pageGroup(2, vbargraph("[%num]gate_view%num", 0, 1));
  out = gate;
};

// sequencer output
beat = ba.beat(speed * 4) * play;
step = beat : ba.pulse_countup(1) % steps : pageGroup(9, hbargraph("step", 0, steps-1));
val = par(i, steps, valStep(i)) : ba.selectn(steps, step);
gate = par(i, steps, gateStep(i)) : (ba.selectn(steps, step) * beat);

// basic synth
attack = pageGroup(3, hslider("[0]attack[style:knob]", 0.1, 0, 1, 0.1)) : si.smoo;
release = pageGroup(3, hslider("[1]release[style:knob]", 0.1, 0, 1, 0.1)) : si.smoo;
pwm = pageGroup(3, hslider("[2]pwm[style:knob]", 0.5, 0, 1, 0.1)) : si.smoo;

env = gate : en.ar(attack, release);
osc = os.pulsetrain(ba.midikey2hz(val), pwm);

process = osc * env <: _,_ ;
