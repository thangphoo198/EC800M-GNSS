@echo off
set CURDIR=%~dp0
set build_target=%1
set option=%2
set cust_ver=%3
set oem_def=%5
set ext_flash=%4

set ARMCC_PATH=
set PATH_TMP=
@for %%i in (armcc.exe) do (
	@if not "%%~$PATH:i"=="" ( 
		set PATH_TMP=%%~$PATH:i
		SETLOCAL ENABLEDELAYEDEXPANSION
		for /f "delims=" %%i in ('armcc --vsn') do (set ret=!ret!%%i;)
		(echo !ret! | findstr /C:"Software supplied by" >nul) && (echo !ret! | findstr /C:"ARM Compiler 5" >nul) && (ENDLOCAL & goto SITE1)
		ENDLOCAL
		goto SITE2
	) else (
		goto SITE2
	)
)
:SITE1
set PATH_TMP=%PATH_TMP:\armcc.exe=%
set ARMCC_PATH=%PATH_TMP%

:SITE2
set COMPILE_ENV_SET_FLAG=
set PATH=%SystemRoot%;%SystemRoot%\system32;

if "%QUECTEL_COMPILE_TOOLS_V1%"=="" (
    set QUECTEL_COMPILE_TOOLS_V1=%CURDIR%\ql-cross-tool\win32\owtoolchain
)
if "%ARMCC_PATH%"=="" (
    set ARMCC_PATH=%QUECTEL_COMPILE_TOOLS_V1%\ARM_Compiler_5\bin
    set ARMLMD_LICENSE_FILE=%QUECTEL_COMPILE_TOOLS_V1%\license.dat
)
set COMPILE_TOOLS_PATH=%PATH%;%ARMCC_PATH%;%QUECTEL_COMPILE_TOOLS_V1%;%QUECTEL_COMPILE_TOOLS_V1%\Perl\site\bin;%QUECTEL_COMPILE_TOOLS_V1%\Perl\bin;%QUECTEL_COMPILE_TOOLS_V1%\Gnumake;
if "%COMPILE_ENV_SET_FLAG%"==""  echo --------------set compile tools path------------------- && set PATH=%COMPILE_TOOLS_PATH% && set COMPILE_ENV_SET_FLAG=done
echo PATH:
echo %PATH%
echo -------------------------------------------------------
echo=

set compile_tools_file=%CURDIR%ql-cross-tool\win32\compile_tools.zip
set compile_tools_dir=%CURDIR%ql-cross-tool\win32\owtoolchain
set cmd_7z=%CURDIR%ql-cross-tool\win32\host\tools\7z\7z.exe

if not exist %compile_tools_dir% (
	echo ------------uncompress compile tools-------------
	%cmd_7z% x -y %compile_tools_file% -o%compile_tools_dir% || ( echo ------------uncompress compile tools failed------------- & goto END)
	echo ------------uncompress compile tools successfully-------------
)

if "%build_target%" == "app" (
	@call :compile_app %option%
)

if "%build_target%" == "bootloader" (
	@call :bootloader %option%
)

if "%build_target%" == "kernel" (
	@call :compile_kernel %option%
)

if "%build_target%" == "firmware" (
	@call :create_firmware %option%
)

if "%build_target%" == "project_name" (
	@call :project_name %option%
)

if "%build_target%" == "clean" (
	@call :bootloader clean
	@call :compile_app clean
	@call :compile_kernel clean
	@call :create_firmware clean
)

exit /b 0

:compile_app 
	pushd ql-application\threadx\
	@call build.bat %1
	popd
goto:eof

:bootloader 
	pushd ql-bootloader\boot33\
	@call build_bootloader_QUECTEL_OCPU_1606.bat %1
	popd
goto:eof

:create_firmware
	if "%1" == "clean" (
		if exist target (
			echo clean firmware 
			rd /s/q target
		)
	) else (
		@call ql-config\quec-project\scripts\win32\build_package.bat %CURDIR%
	)
goto:eof

:compile_kernel 
	pushd ql-kernel\threadx\
	@call build.bat %option%
	popd
goto:eof

:project_name 

	pushd ql-config\config\
	perl project_name.pl %option% %cust_ver% %ext_flash% %oem_def% 
	popd
goto:eof

:END
	
