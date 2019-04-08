
set CURRENT_DIR=%~dp0
set PROJECT_NAME=project

echo %CURRENT_DIR%%PROJECT_NAME%
if not exist %CURRENT_DIR%%PROJECT_NAME% (
    mkdir %CURRENT_DIR%%PROJECT_NAME%
)
cd %CURRENT_DIR%%PROJECT_NAME%

rem Generate VS2017 project.
cmake ../ -G "Visual Studio 15 2017"

cd /d %~dp0

cd ../

copy /y "library\sdl2\lib\x86\SDL2.dll" "build/project/"

copy /y "library\libpng\lib\windows\libpng16.dll" "build/project/"

pause
