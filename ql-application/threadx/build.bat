@echo off

setlocal EnableDelayedExpansion
set CURDIR=%~dp0
set target=%1

set /P EXT_FLASH_SIZE=<..\..\ql-config\config\EXT_FLASH.ini

if "%target%" == "clean" (
	gnumake -f Makefile clean TOP_DIR=" %CURDIR%\"
) else (
	echo %EXT_FLASH_SIZE%|findstr "NO_EXTFLASH" >nul
	if !errorlevel! neq 1 (
		set APP_INPSRAM=DISABLE
	) else (
		set APP_INPSRAM=ENABLE
	)
	gnumake -f Makefile TOP_DIR=" %CURDIR%\"
)
exit /b 0