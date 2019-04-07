# MIT License

# Copyright (c) 2019 huailiang

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 2.8)

if ( WIN32 AND NOT ( CMAKE_SYSTEM_NAME STREQUAL "WindowsStore" ) AND NOT ANDROID)
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT" CACHE STRING "")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd" CACHE STRING "")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT" CACHE STRING "")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd" CACHE STRING "")
endif ()

project(lgRenderEngine)

set(CMAKE_BUILD_TYPE "Debug")
set(ENGINE_SRC_PATH ../code)

# message(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../library/libpng/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../library/sdl2/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../library/libpng/lib/mac)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../library/sdl2/lib/mac)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lz") 

set ( ENGINE_CORE ${ENGINE_SRC_PATH}/engine.c ${ENGINE_SRC_PATH}/main.c ${ENGINE_SRC_PATH}/scene.c ${ENGINE_SRC_PATH}/utils.c )


if (APPLE)
    if (IOS)
        set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD)")
        add_executable(lgRenderEngine STATIC ${ENGINE_CORE})
		set_xcode_property (lgRenderEngine IPHONEOS_DEPLOYMENT_TARGET "7.0")
    else ()
        set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD)")
        add_executable(lgRenderEngine ${ENGINE_CORE})
        target_link_libraries(lgRenderEngine libpng.a libSDL2.a)
    endif ()
else ( )
    add_library(lgRenderEngine SHARED ${ENGINE_CORE})
endif ( )


