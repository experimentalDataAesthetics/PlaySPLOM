# Play SPLOM

__Scatter Plot Matrix Sonification__

## INSTALL

This project requires *openFrameworks* 0.9

  http://openframeworks.cc/download/

Download that and open a terminal at the top level folder.

You will need the *ofxDatGui* and *ofxJSON* addons:

    cd addons
    git clone https://github.com/braitsch/ofxDatGui.git
    git clone https://github.com/jefftimesten/ofxJSON.git

Then clone this repository into the `apps/myApps` directory of your *openFrameworks* copy:

    cd apps/myApps
    git clone https://github.com/experimentalDataAesthetics/PlaySPLOM.git

Then open the xcodeproj in apps/myApps/PlaySPLOM

Build and run that (target: PlaySPLOM, debug)


## Compatibility

Currently this runs on OS X 10.10+

We will target:

- OS X 10.7+ (same as *openFrameworks*)
- Windows

### SuperCollider

*SuperCollider* `scsynth` for OS X is included as well as all plugins it needs.

It is started as a separate process, isolated from any other *SuperCollider* you might have installed on your computer.

It is copied into the `PlaySPLOM.app/Resources` folder.

The other platforms will be included and supported later.


## Compiling SynthDefs

The SynthDefs are already compiled and included here, but if you want to write new ones then you need to compile those.

*supercollider.js* includes a tool for compiling *SuperCollider* files and compiling the SynthDefs including a JSON dump of all meta data for those.

The meta data file is used by PlaySPLOM to populate the menu and for it to know what arguments to send for each `SynthDef`.

Install *supercollider.js*:

    npm install -g supercolliderjs

Then compile-synthdefs

```shell
compile-synthdefs synthdefs/*.scd data/supercollider/synthdefs/
```
