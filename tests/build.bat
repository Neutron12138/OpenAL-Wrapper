@echo off

echo ----------Compling----------
g++ -finput-charset=utf-8 -fexec-charset=gbk "../al_wrapper/dll_main.cpp"^
    -o "al_wrapper.dll" -lopenal32 -shared

echo ----------End----------
pause
