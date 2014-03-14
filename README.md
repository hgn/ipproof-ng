# ipproof-ng

A modern GUI for [ipproof](http://research.protocollabs.com/ipproof/).
Implementation starts with server side component, client side component
hopefully soon[TM].

The implementation is full compatible with original programs. Both, the new and
the new shinny GUI ipproof-ng can be freely mixed. The original command line
programs may be superior for automated tests where the GUI is better suited for
live analysis.

## Building

### Dependencies

Simple: QT5 toolchain.

### Windows

QT Creator and simple open *ipproof-ng.pro*. To distribute ipproof-ng QT
libraries must be shipped ad well! Another possibility is to build ipproof-ng
static.


### Linux


```
apt-get install qt5-qmake qt5-default
qmake
make
```


