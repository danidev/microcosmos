import("stdfaust.lib");

volume = hslider("vol", 0.5, 0, 1, 0.1);
pitch = hslider("note", 30, 0, 127, 1);
freq = ba.midikey2hz(pitch);
gate = button("gate");
snare = button("snare");
hat = button("hat");

random  = +(12345)~*(1103515245);
noise   = random/2147483647.0;
vsnare = noise * en.ar(0.01, 0.11, snare) : fi.resonlp(1200, 2, .95) * volume;
vhat = noise * en.ar(0.01, 0.05, hat) : fi.resonhp(3000, 4, .75) * volume;


bubble(f0,trig) = os.osc(f) * (exp(-damp*time) : si.smooth(0.99))
	with {
		damp = 0.23*f0 + 0.0014*f0^(3/2);
		f = f0*(1+sigma*time);
		sigma = eta * damp;
		eta = 0.005;
		time = 0 : (select2(trig>trig'):+(1)) ~ _ : ba.samp2sec;
	};

kick = bubble(freq, gate) * volume;

process = kick,vsnare,vhat :> _ <: _,_ ;
