@echo off
cd bin
:: Start generator
start /w generatorpgz.exe
:: Copy extra stuff to data
xcopy config-p1 .\data /C /R /I /Y
xcopy config-p1-joy .\data /C /R /I /Y
xcopy prologue.txt .\data /C /R /I /Y
xcopy projectpgz-vs2010.exe ..\CreatedGame\ /C /R /I /Y
xcopy data ..\CreatedGame\data\ /E /C /R /I /Y
xcopy openal32.dll ..\CreatedGame\ /C /R /I /Y
xcopy libsndfile-1.dll ..\CreatedGame\ /C /R /I /Y
:: Execute created game
cd ..\CreatedGame
rename projectpgz-vs2010.exe game.exe
start game.exe
