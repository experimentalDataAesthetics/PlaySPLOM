# Play SPLOM - scatter plot matrix sonification

## INSTALL

This project requires openFrameworks 0.9 and probably an up to date XCode.

Until 0.9 is officially release you can fetch a pre-release version from the nightly builds:

http://openframeworks.cc/download/

Clone this repository into the apps/myApps directory of your openFrameworks copy:

`of_v20151008_osx_release/apps/myApps/`

Then open the xcodeproj and build.

### SuperCollider

SuperCollider scsynth for OS X is included as well as all plugins it needs.
It is started as a separate process, isolated from any other SuperCollider you might have installed on your computer.
It is copied into the .app Resources folder.

The other platforms will be included and supported later.


## Compiling SynthDefs

supercollider.js includes a tool for compiling SuperCollider files and compiling the synth defs including a JSON dump of all meta data for those.

Install supercolliderjs (`npm install -g supercolliderjs`)

```shell
compile-synthdefs synthdefs/*.scd data/supercollider/synthdefs/
```
