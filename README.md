embedded-commandline
====================

[![Build Status](https://travis-ci.org/martinhansdk/embedded-commandline.png)](https://travis-ci.org/martinhansdk/embedded-commandline)

A small library to implement command line interfaces on embedded systems.

Written in C++.

Goals
-----

To provide a simple way to implement command line interfaces for embedded devices.

* Portability - compile on Arduino, ARM, PIC or what ever you have
* Hardware agnostic - suitable for RS232, ethernet or anything else
* No dependencies - except a reasonably compliant C++ compiler, no STL
* No dynamic memory allocation - decide at compile time how much memory it should use
* Fully unit tested - unit tests run on Linux or Windows


Running the tests
-----------------

On Linux do this:

```Shell
git clone --recursive https://github.com/martinhansdk/embedded-commandline.git
cd build
cmake ..
make
test/test
```
    
