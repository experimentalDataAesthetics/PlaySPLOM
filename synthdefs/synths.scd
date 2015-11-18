/*s.boot;
s.scope(2);*/

// define any spec ranges for argument names used in SynthDefs
Spec.specs.put(\carfreq, ControlSpec(20, 20000, 'exp', 0, 440, " Hz"));
Spec.specs.put(\modfreq, ControlSpec(20, 20000, 'exp', 0, 440, " Hz"));

SynthDef("grain", { |out, amp=0.1, freq=440, sustain=0.01, pan|
	var snd = FSinOsc.ar(freq);
	var amp2 = amp * AmpComp.ir(freq.max(50)) * 0.5;
	var env = EnvGen.ar(Env.sine(sustain, amp2), doneAction: 2);
	OffsetOut.ar(out, Pan2.ar(snd * env, pan));
}, \ir ! 5).add;



SynthDef("noiseburst", { |out, amp=0.1, sustain=0.01, pan|
	var snd = PinkNoise.ar(1.0);
	var amp2 = amp * AmpComp.ir(1.max(50)) * 0.5;
	var env = EnvGen.ar(Env.sine(sustain, amp2), doneAction: 2);
	OffsetOut.ar(out, Pan2.ar(snd * env, pan));
}, \ir ! 5).add;


SynthDef("grain2", { |out, amp=0.1, freq=440, sustain=0.01, pan|
	var snd = FSinOsc.ar(freq);
	var amp2 = amp * AmpComp.ir(freq.max(50)) * 0.5;
	var env = EnvGen.ar(Env.perc(0.01, 0.09), doneAction: 2);
	OffsetOut.ar(out, Pan2.ar(snd * env, pan));
}, \ir ! 5).add;


SynthDef("grain3", { |out, amp=0.1, freq=440, sustain=0.01, pan|
	var snd = LFSaw.ar(freq);
	var amp2 = amp * AmpComp.ir(freq.max(50)) * 0.5;
	var env = EnvGen.ar(Env.perc(sustain, 0.09), doneAction: 2);
	OffsetOut.ar(out, Pan2.ar(snd * env, pan));
}, \ir ! 5).add;

SynthDef("grainFM", {|out, carfreq=440, modfreq=20, moddepth = 1, sustain=0.02, amp=0.1, pan|
	var env = EnvGen.ar(Env.sine(sustain, amp), doneAction: 2);
	var sound = SinOsc.ar(carfreq, SinOsc.ar(modfreq) * moddepth) * env;
	OffsetOut.ar(out, Pan2.ar(sound, pan))
}, \ir ! 5).add;
