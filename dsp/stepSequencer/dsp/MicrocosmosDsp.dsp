import("stdfaust.lib");

page = 0;

valStep(num) = out
with {
  pageGroup(x) = hgroup("%page", x);
  stepGroup(x) = vgroup("step%num",x);
  val = pageGroup(stepGroup(vslider("[%num]val%num[style:knob]", 0, 0,127, 1)));
  out = val;
};

gateStep(num) = out
with {
  pageGroup(x) = hgroup("%page", x);
  stepGroup(x) = vgroup("step%num",x);
  gate = pageGroup(stepGroup(ba.toggle(button("[%num]gate%num"))));
  out = gate;
};

steps = 8;
step = ba.beat(hslider("speed", 120, 20, 255, 1) * 4) : ba.pulse_countup(1) % steps;

val = par(i, steps, valStep(i)) : ba.selectn(steps, step);
gate = par(i, steps, gateStep(i)) : ba.selectn(steps, step);
process = os.pulsetrain(ba.midikey2hz(val), 0.5) * gate <: _,_ ;
