@echo off
cd bin
start /w generatorpgz.exe
xcopy config-p1 .\data /C /R /I /Y
xcopy config-p1-joy .\data /C /R /I /Y
xcopy projectpgz-vs2010.exe ..\CreatedGame\ /C /R /I /Y
xcopy data ..\CreatedGame\data\ /E /C /R /I /Y
xcopy openal32.dll ..\CreatedGame\ /C /R /I /Y
xcopy libsndfile-1.dll ..\CreatedGame\ /C /R /I /Y

cd ..\CreatedGame
rename projectpgz-vs2010.exe game.exe
start game.exe
