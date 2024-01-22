@echo off
set CURDIR=%~dp0
set module=%1

call build.bat clean
call build.bat app
call build.bat kernel %module%
call build.bat firmware

pause