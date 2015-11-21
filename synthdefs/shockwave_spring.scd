
Spec.specs.put(\springfac, ControlSpec(0.1, 1500, 'lin'));
Spec.specs.put(\damp, ControlSpec(0.00001, 0.2, 'exp'));

SynthDef("shockwave-spring", { | springfac = 10, damp = 0.0008 amp = 0.5|

	var f; //modulated input force
	var s;
	var env = Env([0, 0.2, 0], [0.02, 0.02, 0.02],[-5, 5, 5]);

	f = Pulse.ar(0.5) * EnvGen.kr(env);
	s = Spring.ar(f, springfac, damp);
	DetectSilence.ar(s, doneAction:2);
	Out.ar([0,1],amp*s);
}).add;
