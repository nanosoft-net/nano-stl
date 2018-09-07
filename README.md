# Nano STL
Nano STL is an open source ligthweight C++ STL like library targeting 16 to 32bits microcontrollers.

Its main characteristics are:

* C++98 compliant
* No dynamic memory allocation
* Implementation of the following containers
  * Array
  * Vector
  * List
* Optional support of iterators

## Supported architectures

Nano STL has no dependencies towards any Operating System nor any microcontroller.
It may be used on any architecture which has a C++98 compliant compiler.

## Building Nano STL

Nano STL source code release uses Nano Build as build system.
Nano Build is a makefile based build system which simplifies cross platform / cross target compilation.
The generated binaries files are in ELF format and are ready to use with a debugger (example : J-link + GdbServer).
If you need to get ihex files or raw binary files you can use the GNU objcopy utility to convert Nano Build output file to the wanted format.
Nano STL demo applications and Nano STL source code can also be built using custom makefile or custom IDE project.

### Building using Nano Build

#### Pre-requisites

The GNU Make 4.1 or greater utility must be installed and must be on the operating system PATH variable.
If using the python build script, Python 2.7 must be installed.

#### Configuring Nano Build

The path to the compilers must be configured in the build/make/compiler directory.
Each compiler files refers to a single compiler and must be written using the Makefile syntax :

* arm-gcc-cortex-m.compiler : GCC compiler for ARM Cortex-M CPUs
* arm-iar.compiler : IAR Systems compiler for ARM CPUs
* arm-keil.compiler : ARM Keil compiler for ARM CPUs
* mingw.compiler : MingGW compiler for Windows
* gnu-gcc.compiler : GNU GCC compiler for Linux

#### Building using the build python script

The build.py script at the root of Nano Build can be use to build multiple project at a time or to build projects without having to navigate in the Makefile directories.


usage: build.py [-h] -t target -p package [package ...] -c command
                [command ...] [-j jobs] [-l] [-v] [-d]

Nano Build tool v1.0

optional arguments:
  -h, --help            show this help message and exit
  -t target             [string] Target name
  -p package [package ...]
                        [string] Packages to build
  -c command [command ...]
                        [string] Build command, ex: all|all+|clean|clean+
  -j jobs               [int] Number of build jobs
  -l                    List all available packages and targets
  -v                    Verbose mode
  -d                    Header dependency check




The following command will list all the available projects and all the available build targets (a target is the association of a compiler and a CPU):

build.py -l

Packages list:
 - apps.demo_app
 - libs.nano-stl

Target list:
 - gcc-linux
 - mingw-windows
 
 
 The following command will build the demo application for Windows using the MinGW compiler:

build -t mingw-windows -p apps.demo -c all+

The following command will clean the demo application for Windows using the MinGW compiler:

build -t mingw-windows -p apps.demo -c clean+

The following command will build all the demo applications for Windows using the MinGW compiler:
 
build -t mingw-windows -p apps.* -c all+


The build output can be found in the following folder : build/apps/app_name/bin/target_name

#### Building directly from the Makefiles

To build a project directly from a makefile, you have to open a terminal in the Makefile directory and use the following command lines.

The following command will build the demo application for Windows using the MinGW compiler:

make TARGET=mingw-windows all+

The following command will clean the demo application for Windows using the MinGW compiler:

make TARGET=mingw-windows clean+

## Demos applications

### Demo environment

The demo applications have been tested on the following boards:

* Windows 10

using the following compilers:

* MinGW 7.1 for Windows (MinGW - http://www.mingw.org/)

### Demos

* demo : example of all containers and iterators usage
