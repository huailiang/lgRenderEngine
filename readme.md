
A cross-platform software render engine based on SDL2


## Requirement

- SDL2
- libpng


## Environment

- xcode on osx
- vs2017 on windows


## Build

1. you should be ensure cmake installed at your mac,  and generate xcode project using command as:

```bash
git clone git@github.com:huailiang/lgRenderEngine.git
cd lgRenderEngine
cd build
sh build_osx.sh
```

2. compile visual studio project on windows:

	`cd build directory, and click build_vs2017.bat`


## Tips

1. libpng depends on zlib, so should be set -lz in "Other linker flags" at xcode project

2. in function transform_homogenize, y is reduced by 1 because SDL_RenderDrawPoint draw point start with left-top pivot.


## Reinferences


tutor:	 

&emsp; 	1. [guide outline](/doc/readme.md)

&emsp;  2. [Frustum Culling](/doc/clip.md)

&emsp;  3. [Bresenham draw-line](/doc/Bresenham.md)

&emsp;  4. [triger center calcute](/doc/triger.md)

&emsp;  5. [transform matrix](/doc/transform.md)

resources: [asset format](/resources/readme.md)

sdl: http://www.libsdl.org

libpng: http://www.libpng.org/pub/png/libpng.html

cmake: https://cmake.org/
