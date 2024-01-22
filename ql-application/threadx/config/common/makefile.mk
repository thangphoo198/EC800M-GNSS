#-------------------------------------------------------------------------------
# Configure environment path
#-------------------------------------------------------------------------------
TOP_DIR:=$(TOP_DIR)
HOST_PLATFORM=win32
ROOT_DIR:=$(TOP_DIR)/../..
BUILD_DIR:=build
IMAGE_BUILD_DIR:=build
OBJ_DIR:=$(subst $(strip \),/,$(BUILD_DIR)/obj)
CUR_MAKEFILE := $(abspath $(firstword $(MAKEFILE_LIST)))
PACKAGE_PATH:=$(dir $(subst $(empty) ,?,$(CUR_MAKEFILE)))
PACKAGE_PATH:=$(subst ?, ,$(PACKAGE_PATH))
PACKAGE_PARENT_PATH_TMP:=$(dir $(realpath $(PACKAGE_PATH)))
PACKAGE_PARENT_PATH:=$(patsubst $(subst $(strip \),/,$(PACKAGE_PATH))%,%,$(PACKAGE_PARENT_PATH_TMP))
PACKAGE_NAME_TMP1=$(lastword $(subst $(strip /), ,$(PACKAGE_PATH)))
PACKAGE_NAME_TMP2=$(lastword $(subst $(strip /), ,$(PACKAGE_PARENT_PATH)))
PACKAGE_NAME:=$(PACKAGE_NAME_TMP1)
COMLIED_LIB_LIST_FILE:=$(TOP_DIR)\$(IMAGE_BUILD_DIR)/complied_lib.txt 

#-------------------------------------------------------------------------------
# Configure source code files to compile in the source code directories
#-------------------------------------------------------------------------------
COMMPILE_DIRS:=$(subst $(strip \),/,$(COMMPILE_DIRS))
TARGET_COMMPILE_DIRS:=$(patsubst %,%/target_compile_dir,$(COMMPILE_DIRS))
TARGET_CLEAN_DIRS:=$(patsubst %,%/target_clean_dir,$(COMMPILE_DIRS))

SRC_FILES:=$(subst $(strip \),/,$(SRC_FILES))
SRC_DIRS:=$(dir $(SRC_FILES))

OBJS_TMP:= $(SRC_FILES:.c=.o)
OBJS_TMP:=$(OBJS_TMP:.cpp=.o)
OBJS_TMP:=$(OBJS_TMP:.cc=.o)
OBJS_TMP:=$(OBJS_TMP:.cxx=.o)
OBJS_TMP:=$(OBJS_TMP:.S=.o)
OBJS_TMP:=$(OBJS_TMP:.s=.o)
OBJS_TMP:=$(patsubst %,$(subst $(strip \),/,$(OBJ_DIR))/%,$(OBJS_TMP))
OBJS:=$(OBJS_TMP)

DEF_FILES_TMP:= $(SRC_FILES:.c=.d)
DEF_FILES_TMP:=$(DEF_FILES_TMP:.cpp=.d)
DEF_FILES_TMP:=$(patsubst %,$(subst $(strip \),/,$(OBJ_DIR))/%,$(DEF_FILES_TMP))
DEF_FILES:=$(DEF_FILES_TMP)

#-------------------------------------------------------------------------------
# Configure GCC installation path, and GCC version.
# To execute "arm-none-eabi-gcc -v" in command line can get the current gcc version 
#-------------------------------------------------------------------------------
#COMPILE_TOOL_PATH:=$(ROOT_DIR)\quectel_build\tools\compile_tools
COMPILE_TOOL_PATH:=$(ROOT_DIR)\ql-cross-tool\$(HOST_PLATFORM)\owtoolchain
GCC_INSTALL_PATH=$(COMPILE_TOOL_PATH)\gcc-arm-none-eabi
GCC_STDLIB_TARGET_PATH=thumb\v7\nofp
GCC_VERSION:=9.2.1

NWELIB_NANO=


#-------------------------------------------------------------------------------
# Configure compiling utilities
#-------------------------------------------------------------------------------
CC:=$(GCC_INSTALL_PATH)\bin\arm-none-eabi-gcc.exe
CPP:=$(GCC_INSTALL_PATH)\bin\arm-none-eabi-g++.exe
LD:=$(GCC_INSTALL_PATH)\bin\arm-none-eabi-ld.exe
AR:=$(GCC_INSTALL_PATH)\bin\arm-none-eabi-ar.exe
OBJCOPY:=$(GCC_INSTALL_PATH)\bin\arm-none-eabi-objcopy.exe
MAKE:=$(COMPILE_TOOL_PATH)\gnumake\gnumake.exe
#CRC_BIN:=$(ROOT_DIR)\quectel_build\bin\crc_bin.exe
CRC_BIN:=$(ROOT_DIR)\ql-cross-tool\$(HOST_PLATFORM)\host\tools\crc_bin.exe

#-------------------------------------------------------------------------------
# Configure standard reference library
#-------------------------------------------------------------------------------
ifeq ($(NWELIB_NANO),)
STDLIB:=\
	$(GCC_INSTALL_PATH)\arm-none-eabi\lib\$(GCC_STDLIB_TARGET_PATH)\libc.a \
	$(GCC_INSTALL_PATH)\arm-none-eabi\lib\$(GCC_STDLIB_TARGET_PATH)\libstdc++.a \
	$(GCC_INSTALL_PATH)\arm-none-eabi\lib\$(GCC_STDLIB_TARGET_PATH)\libg.a

else
STDLIB:=\
	$(GCC_INSTALL_PATH)\arm-none-eabi\lib\$(GCC_STDLIB_TARGET_PATH)\libc_nano.a \
	$(GCC_INSTALL_PATH)\arm-none-eabi\lib\$(GCC_STDLIB_TARGET_PATH)\libstdc++_nano.a \
	$(GCC_INSTALL_PATH)\arm-none-eabi\lib\$(GCC_STDLIB_TARGET_PATH)\libg_nano.a
endif

STDLIB+=\
	$(GCC_INSTALL_PATH)\lib\gcc\arm-none-eabi\$(GCC_VERSION)\$(GCC_STDLIB_TARGET_PATH)\libgcc.a \
	$(GCC_INSTALL_PATH)\arm-none-eabi\lib\$(GCC_STDLIB_TARGET_PATH)\libnosys.a \
	$(GCC_INSTALL_PATH)\arm-none-eabi\lib\$(GCC_STDLIB_TARGET_PATH)\libm.a


#-------------------------------------------------------------------------------
# Flag that indicate don't compile functions those built in GCC
#-------------------------------------------------------------------------------
FNO_BUILTIN_FLAGS := -fno-builtin-printf \
					   -fno-builtin-time \
					   -fno-builtin-gmtime \
					   -fno-builtin-gettimeofday \
					   -fno-builtin-mktime \
					   -fno-builtin-puts

#-------------------------------------------------------------------------------
# Configure compiling options
#-------------------------------------------------------------------------------
SFLAGS:=-c -mlong-calls  -mcpu=cortex-r4 -mfloat-abi=soft   -mlittle-endian -mthumb -mthumb-interwork  -Wall -Os
CFLAGS:=-c -MMD -mlong-calls  -mcpu=cortex-r4 -mfloat-abi=soft   -mlittle-endian -mthumb -mthumb-interwork  -Wall -ffunction-sections -fdata-sections $(FNO_BUILTIN_FLAGS) -D__OCPU_COMPILER_GCC__ -D_WANT_USE_LONG_TIME_T -std=c99 -g -Os
CPPFLAGS:=-c -MMD -mlong-calls  -mcpu=cortex-r4 -mfloat-abi=soft   -mlittle-endian -mthumb -mthumb-interwork  -Wall -ffunction-sections -fdata-sections $(FNO_BUILTIN_FLAGS) -D__OCPU_COMPILER_GCC__ -D_WANT_USE_LONG_TIME_T -std=c++11  -g -Os
ifneq (,$(findstring ENABLE,${APP_INPSRAM}))
LDFLAGS:= -gc-sections -T$(TOP_DIR)\config\common\app_linkscript_in_psram.ld -nostdlib 
else
LDFLAGS:= -gc-sections -T$(TOP_DIR)\config\common\app_linkscript.ld -nostdlib 
endif
ARFLAG:=-rc
OBJCOPYFLAGS:=


ifneq ($(NWELIB_NANO),)
CFLAGS+= --specs=nano.specs -u _scanf_float -u _printf_float
CPPFLAGS+= --specs=nano.specs -u _scanf_float -u _printf_float
LDFLAGS+= -u _scanf_float -u _printf_float
endif


#-------------------------------------------------------------------------------
# Definition for compiling procedure
#-------------------------------------------------------------------------------
.PHONY: all clean CreateDir compile_lib_list


ifeq ($(MAKEFILE_PATH),)
#-------------------------------------------------------------------------------
# Top makefile
#------------------------------------------------------------------------------- 

PREPARE:=CreateDir
IAMGE:=app

all: $(PREPARE) $(IAMGE)


CreateDir:
	@if not exist $(IMAGE_BUILD_DIR) ( md $(subst $(strip /),\,$(IMAGE_BUILD_DIR)))
	@if exist $(COMLIED_LIB_LIST_FILE) (@echo clean $(COMLIED_LIB_LIST_FILE) & del /s/q $(subst $(strip /),\,$(COMLIED_LIB_LIST_FILE)))
	@echo= > $(COMLIED_LIB_LIST_FILE)
	@if exist $(IMAGE_BUILD_DIR)/$(IAMGE).bin (del /s/q $(subst $(strip /),\,$(IMAGE_BUILD_DIR)/$(IAMGE).bin))
	@if exist $(IMAGE_BUILD_DIR)/$(IAMGE).elf (del /s/q $(subst $(strip /),\,$(IMAGE_BUILD_DIR)/$(IAMGE).elf))
	@if exist $(IMAGE_BUILD_DIR)/$(IAMGE).map (del /s/q $(subst $(strip /),\,$(IMAGE_BUILD_DIR)/$(IAMGE).map))

clean: $(TARGET_CLEAN_DIRS)
	@if exist $(IMAGE_BUILD_DIR) (@echo clean $(IMAGE_BUILD_DIR) & rd /s/q $(subst $(strip /),\,$(IMAGE_BUILD_DIR)))

%/target_clean_dir:%
	@echo ---------------clean [$<]-------------------
	gnumake -C $< -f Makefile clean TOP_DIR=$(TOP_DIR)

#-------------------------------------------------------------------------------
# Top makefile end
#-------------------------------------------------------------------------------  

else

#-------------------------------------------------------------------------------
# Package makefile
#------------------------------------------------------------------------------- 

PREPARE:=CreateDir
TARGET:=$(BUILD_DIR)/$(subst $(strip /),-,$(PACKAGE_NAME)).lib

all:$(PREPARE) compile_lib_list

CreateDir:
	@if not exist $(BUILD_DIR) (md $(subst $(strip /),\,$(BUILD_DIR)))
	@if not exist $(OBJ_DIR) (md $(subst $(strip /),\,$(OBJ_DIR)))
	@for /d %%y in ($(subst $(strip /),\,$(SRC_DIRS))) do ( \
		@if not exist $(OBJ_DIR)\%%y ( \
			(@echo creating direcotry $(OBJ_DIR)\%%y) & (md $(subst $(strip /),\,$(OBJ_DIR)\%%y)) \
		) \
	)

clean:
	@if exist $(BUILD_DIR) (@echo clean $(BUILD_DIR) & rd /s/q $(BUILD_DIR))
	@if exist $(TARGET) (@echo clean $(TARGET) & rd /s/q $(TARGET))

#-------------------------------------------------------------------------------
# Package makefile end
#------------------------------------------------------------------------------- 
endif


$(IAMGE): $(IMAGE_BUILD_DIR)/$(IAMGE).elf
	@echo --------------objcopy [$(IMAGE_BUILD_DIR)/$(IAMGE).bin]-------------
	$(OBJCOPY) $(OBJCOPYFLAGS) -O binary $<  $(IMAGE_BUILD_DIR)/$(IAMGE).bin
	$(CRC_BIN) $(IMAGE_BUILD_DIR)/$(IAMGE).bin
	@echo ----------------------------------------------------
	@echo - GCC Compiling Finished Sucessfully.
	@echo - The target image is in the '$(BUILD_DIR)' directory.
	@echo ----------------------------------------------------

$(IMAGE_BUILD_DIR)/$(IAMGE).elf: $(TARGET_COMMPILE_DIRS)
	@echo --------------link [$@]----------------------
	@SETLOCAL ENABLEDELAYEDEXPANSION & \
	(for /f "delims=" %%i in ('type $(subst $(strip /),\,$(COMLIED_LIB_LIST_FILE))') do (set ret=!ret!%%i)) & \
	(echo $(LD) $(LDFLAGS) $(U_LDFLAGS) -Map $(IMAGE_BUILD_DIR)/$(IAMGE).map -o $@ --whole-archive !ret! $(DEFAULT_LIBS) --no-whole-archive $(U_LIBS) $(STDLIB)) & \
	($(LD) $(LDFLAGS) $(U_LDFLAGS) -Map $(IMAGE_BUILD_DIR)/$(IAMGE).map -o $@ --whole-archive !ret! $(DEFAULT_LIBS) --no-whole-archive $(U_LIBS) $(STDLIB)) & \
	ENDLOCAL

%/target_compile_dir:%
	@echo -----------------compile [$<]--------------------
	gnumake -C $< -f Makefile TOP_DIR=$(TOP_DIR)

compile_lib_list:$(TARGET)
	@echo $(PACKAGE_PATH)/$(TARGET) >> $(COMLIED_LIB_LIST_FILE)
ifneq ($(U_LIBS),)
	@for /d %%y in ($(subst $(strip /),\,$(U_LIBS))) do ( \
		(@echo %%y >> $(COMLIED_LIB_LIST_FILE)) \
	)
endif

$(TARGET):$(OBJS)
	@echo ---------------create lib [$@]-------------------
	$(AR) $(ARFLAG) $@ $^

$(OBJ_DIR)/%.o: %.S
	$(CC)  $(SFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: %.s
	$(CC)  $(SFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $(U_FLAGS) $(INC_DIRS) -o $@ $<

$(OBJ_DIR)/%.o: %.cpp
	$(CPP) $(CPPFLAGS) $(DFLAGS) $(U_CPPFLAGS) $(INC_DIRS)  -o $@ $<

$(OBJ_DIR)/%.o: %.cc
	$(CPP) $(CPPFLAGS) $(DFLAGS) $(U_CPPFLAGS) $(INC_DIRS)  -o $@ $<

$(OBJ_DIR)/%.o: %.cxx
	$(CPP) $(CPPFLAGS) $(DFLAGS) $(U_CPPFLAGS) $(INC_DIRS)  -o $@ $<

-include $(DEF_FILES)
