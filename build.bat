@echo off

REM Eğer bin dizini mevcut değilse oluştur
if not exist bin mkdir bin

REM main.cpp dosyasını derle ve bin dizininde my_program.exe dosyasını oluştur
g++ -o bin\tpl src\main.cpp

REM Derleme tamamlandığında mesaj ver
echo Build completed. Executable is in the 'bin' directory.

REM bin dizinindeki my_program.exe dosyasını çalıştır
bin\tpl.exe
