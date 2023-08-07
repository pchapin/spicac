SpicaCpp
========

This is the C part of the [Spica meta-library](https://github.com/pchapin/spica).

The code in this library is intended to be cross platform and to support multiple build tools.
Specifically:

+ The `Makefile` is the main source of authority for building SpicaC. However, it assumes
  GNUmake and thus can't (easily) be used in some cases.
  
+ The `.vscode` folder contains setting information for Visual Studio Code that should allow
  VSCode to work properly on all of its supported platforms: Windows (with Cygwin), macOS, and
  Linux.
  
+ There are Eclipse/CDT project files, but they are configured for the Cygwin C/C++ tool chain
  and thus will only work as-is on Windows platforms with Cygwin installed.
  
+ There is a project file for Visual Studio that can be included into a solution for a larger
  system where SpicaC is being used. The Visual Studio solution file here also builds the
  SpicaC test and benchmark program(s).
  
+ There is a Code::Blocks projet file that can be included into a solution for a larger system
  where Code::Blocks is being used. The Code::Blocks workspace file here also builds the
  SpicaC test and benchmark program(s).
  
SpicaC currently assumes C 1999. However, some of the components may be conforming C 1990.
Accordingly there is an Open Watcom target definition file for the Open Watcom IDE (very
out-of-date), and there are makefiles for various Open Watcom targets under `owbuild`.

The API documentation for the library can built using Doxygen. It is left in a folder named
`api` (load `index.html` into a web browser to view the documentation). The `doc` folder
contains additional documentation.

Peter Chapin  
spicacality@kelseymountain.org  
