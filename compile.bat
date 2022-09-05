clear

cd build

@REM vcvarsall x64

@REM cmake  -DCMAKE_GENERATOR_PLATFORM=x64 ..

cmake -DCMAKE_BUILD_TYPE=Release -G"NMake Makefiles" ..

cmake --build .

cmake --install .

@REM rd /s /q  E:\Works\zhkd\QtAppCMake\bin\Release\configuration

@REM xcopy E:\Works\zhkd\QtAppCMake\PluginsVegetables\PlateOpenGL\OpenGLStart\res E:\Works\zhkd\QtAppCMake\bin\Release\res /y /e /i /q

@REM ..\bin\Release\App.exe
