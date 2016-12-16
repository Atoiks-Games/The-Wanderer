# The Wanderer [![Build status](https://ci.appveyor.com/api/projects/status/645n6swvtyeqj0w8/branch/master?svg=true)](https://ci.appveyor.com/project/plankp/the-wanderer/branch/master) [![Build Status](https://drone.io/github.com/Atoiks-Games/The-Wanderer/status.png)](https://drone.io/github.com/Atoiks-Games/The-Wanderer/latest)

The continuation of the tbrg series

### Prebuilt versions

#### Linux

https://drone.io/github.com/Atoiks-Games/The-Wanderer/files

#### Windows

https://ci.appveyor.com/project/plankp/the-wanderer/build/artifacts

### Build Instructions

You must have an CMake installation that is at least version 2.8.12!

#### Linux or Msys2

* g++ at least 4.8
* Make

At the root directory of the project:

```
$ mkdir build
$ cd build
$ cmake -G "Unix Makefiles" ..
$ make
```

A binary with the name of `the_wanderer` should appear. Run it!

#### Windows

* MSVC at least 19.0
* msbuild

At the root directory of the project:

```
> mkdir build
> cd build
> cmake -G "Visual Studio 14 2015" ..
> msbuild .\THE_WANDERER.sln
```

A binary with the name `the_wanderer.exe` should appear under `Debug`. Run it!
