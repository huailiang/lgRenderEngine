
set CURRENT_DIR=%~dp0
set PROJECT_NAME=project

echo %CURRENT_DIR%%PROJECT_NAME%
if not exist %CURRENT_DIR%%PROJECT_NAME% (
    mkdir %CURRENT_DIR%%PROJECT_NAME%
)
cd %CURRENT_DIR%%PROJECT_NAME%

rem Generate VS2017 project.
cmake ../ -G "Visual Studio 15 2017 Win64"
pause
