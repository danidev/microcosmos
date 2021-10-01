declare name "MicrocosmosDsp";
import("stdfaust.lib");

map(x, in_min, in_max, out_min, out_max) = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
page(num, x) = hgroup("page%num", x);

// LOOPER SECTION
sampleRate = 48000;
maxTime = 1;
maxSamples = sampleRate * maxTime;

looperModule(num) = out
with {
  // PARAMETERS
  readSpeed = page(num, map(hslider("[0]read_speed_%num[style:knob]", 64, 0, 127, 1) : si.smoo, 0, 127, 0, 3));
  loopLength = page(num, map(hslider("[1]loop_length_%num[style:knob]", 127, 0, 127, 1) : si.smoo, 0, 127, 0, 1));
  volume = page(num, map(hslider("[2]volume_%num[style:knob]", 127, 0, 127, 1) : si.smoo, 0, 127, 0, 1));
  rate = page(num, hslider("[3]rate_%num[style:knob]", 1, 1, 20, 0.1));

  btnRecording = page(num, button("[4]rec_%num"));
  btnPlay = page(num, ba.toggle(button("[5]gate_%num")));
  stutterActive = page(num, ba.toggle(button("[6]stutter_%num")));

  // loop size is the duration while button is kept pressed
  loopSize = ba.sAndH(btnRecording, fi.pole(btnRecording, btnRecording)) : int : page(num, hbargraph("[7]loop_size_%num", 0, maxSamples));

  // rec index is from 0 to maxSamples while button is pressed
  recIndex = (+(1) : %(maxSamples)) ~ *(btnRecording) : int : page(num, hbargraph("[8]rec_index_%num", 0, maxSamples));

  // do not change loop size while recording
  prevLoopSize = loopSize : ba.sAndH(btnRecording == 0);
  memoLoopSize = prevLoopSize, loopSize : ba.selectn(2, btnRecording == 0);

  // avoid division by zero / NAN using max
  calculatedLoopLength = (memoLoopSize * loopLength), ma.EPSILON : max;

  // clamp to maxSamples
  clampedLoopLength = ba.if(calculatedLoopLength<maxSamples, calculatedLoopLength, maxSamples);

  // read index is from 0 to calculatedLoopLength continously
  readIndex = (+(1 * readSpeed) : %(clampedLoopLength)) ~_ : int : page(hbargraph("[9]read_index_%num", 0, maxSamples));

  looper = rwtable(maxSamples,0.0,recIndex,_,readIndex) * volume;


  stutter = os.lf_pulsetrainpos(rate, 0.5);

  out = looper * (1,stutter : ba.selectn(2, stutterActive)) * btnPlay;
};

process = _ <: (looperModule(1), looperModule(2)) :> _ <: _,_;
