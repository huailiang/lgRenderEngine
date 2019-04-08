
A cross-platform soft render engine based on SDL2


## Requirement

- SDL2
- libpng


## Environment

- xcode 
- vs2017


## Build

you should be ensure cmake which is installed at your mac,  and generate xcode project use command as:

```bash
cd build
sh build_osx.sh
```

compile visual studio project on windows:

cd build directory, and click build_vs2017.bat


## Tips

libpng depends on zlib, so should be set -lz in "Other linker flags" at xcode project

## Reinferences

[resouces file format desc](/resources/readme.md)

sdl: http://www.libsdl.org

libpng: http://www.libpng.org/pub/png/libpng.html

cmake: https://cmake.org/