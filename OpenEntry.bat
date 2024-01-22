@echo off
set CURDIR=%~dp0

echo                              __           ___                                         
echo                             /\ \__       /\_ \                                        
echo    __   __  __     __    ___\ \ ,_\    __\//\ \         ___   _____      __    ___    
echo  /'__`\/\ \/\ \  /'__`\ /'___\ \ \/  /'__`\\ \ \       / __`\/\ '__`\  /'__`\/' _ `\  
echo /\ \L\ \ \ \_\ \/\  __//\ \__/\ \ \_/\  __/ \_\ \_    /\ \L\ \ \ \L\ \/\  __//\ \/\ \ 
echo \ \___, \ \____/\ \____\ \____\\ \__\ \____\/\____\   \ \____/\ \ ,__/\ \____\ \_\ \_\
echo  \/___/\ \/___/  \/____/\/____/ \/__/\/____/\/____/    \/___/  \ \ \/  \/____/\/_/\/_/
echo       \ \_\                                                     \ \_\                 
echo        \/_/                                                      \/_/                 
       
set ex_fshsize=NO_EXTFLASH
echo       
echo ******************************************************                                                                                                                                                                                                   
echo 1.EC600MCN_LC
echo 2.EC600MCN_CC
echo 3.EC800MCN_LC
echo 4.EC800MCN_CC
echo 5.EC800MCN_GC
echo 6.EC800MCN_GD
echo ******************************************************
echo      
set /p QUEC_PROJECT=������Ҫ�������Ŀ���...
if %QUEC_PROJECT%==1 (
set quec_prj=EC600MCN_LC
) else if %QUEC_PROJECT%==2 (
set quec_prj=EC600MCN_CC
) else if %QUEC_PROJECT%==3 (
set quec_prj=EC800MCN_LC
) else if %QUEC_PROJECT%==4 (
set quec_prj=EC800MCN_CC
) else if %QUEC_PROJECT%==5 (
set quec_prj=EC800MCN_GC
) else if %QUEC_PROJECT%==6 (
set quec_prj=EC800MCN_GD
) else (
	goto ERR
)
echo ��ѡ�����ĿΪ%quec_prj%  

echo       
echo ******************************************************                                                                                                                                                                                                  
echo 1.LCD
echo 2.AMR
echo 3.MP3
echo 4.TTS
echo 5.MBEDTLS
echo ע������:���ӹ���Խ����ҪԤ�����ں˹̼���flash��ram�ռ�Խ��
echo ******************************************************
echo 
set MLCD=
set MAMR=
set MMP3=
set MTTS=
set MMBEDTLS=
set /p QUEC_MODULE=������Ҫ���ӹ��ܿ�����(��ͬʱ����)...
echo %QUEC_MODULE%|findstr "1" 
if %errorlevel%==0 (
	set MLCD=LCD_
)
echo %QUEC_MODULE%|findstr "2" 
if %errorlevel%==0 (
	set MAMR=AMR_
)
echo %QUEC_MODULE%|findstr "3" 
if %errorlevel%==0 (
	set MMP3=MP3_
)
echo %QUEC_MODULE%|findstr "4" 
if %errorlevel%==0 (
	set MTTS=TTS_
)
echo %QUEC_MODULE%|findstr "5" 
if %errorlevel%==0 (
	set MMBEDTLS=MBEDTLS_
)
set module=%MLCD%%MAMR%%MMP3%%MTTS%%MMBEDTLS%
echo %module%
set /p CUST_VER=���������ɵĹ̼������ƣ�����0��ʹ����ԶĬ�Ϲ̼�����   
echo �̼�����Ϊ%CUST_VER%  
if %CUST_VER%==0 (
	set cust_ver=
) else (
  set cust_ver=%CUST_VER%
)                                                                                                                                                                                                 

if "%quec_prj%"=="EC600MCN_CC" (
	goto ext
) else if "%quec_prj%"=="EC800MCN_CC" (
	goto ext
) else (
  goto build
)

:ext
echo      
echo ****************************************************** 
echo 0.NO_EXT_FLASH
echo 1.1M_EXT_FLASH
echo 2.2M_EXT_FLASH
echo ****************************************************** 
echo       
	set /p ext_flash=�������Ӧ���flash��С�����...
	if %ext_flash%==0 (
		set ex_fshsize=NO_EXTFLASH
	) else if %ext_flash%==1 (
		set ex_fshsize=EXT_FLASH_M01
	) else if %ext_flash%==2 (
		set ex_fshsize=EXT_FLASH_M02
	) else (
		goto ERR
	)
	
:build

call build.bat project_name %quec_prj% %cust_ver% %ex_fshsize%
call build_all.bat %module%
goto exit



:ERR
echo  _______   ________  ________  ________  ________     
echo |\  ___ \ |\   __  \|\   __  \|\   __  \|\   __  \    
echo \ \   __/|\ \  \|\  \ \  \|\  \ \  \|\  \ \  \|\  \   
echo  \ \  \_|/_\ \   _  _\ \   _  _\ \  \\\  \ \   _  _\  
echo   \ \  \_|\ \ \  \\  \\ \  \\  \\ \  \\\  \ \  \\  \| 
echo    \ \_______\ \__\\ _\\ \__\\ _\\ \_______\ \__\\ _\ 
echo     \|_______|\|__|\|__|\|__|\|__|\|_______|\|__|\|__|

:exit

                                                                            
                                                                                               
