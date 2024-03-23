# SDK说明

## 编译环境构建 

1. 编译kernel需要armcc编译工具。提供以下两种方式使用armcc。
    (1) 使用在ql-cross-tool\win32\owtoolchain目录下提供的ammcc编译工具，但需要在ql-cross-tool\win32\owtoolchain目录放入正版license。
	(2) 安装DS-5开发软件，并将armcc编译工具所在目录加入环境变量PATH中，添加变量ARMLMD_LICENSE_FILE到环境变量中，ARMLMD_LICENSE_FILE设置为armcc所使用的license；
2. 编译APP（ql-application）需要arm-gcc编译工具，SDK中已提供。

## 目录结构

### ql-sdk	根目录 

	---ql-config
		---quec-project	项目相关配置

	---ql-application 
		---threadx
			---api_map	从kernel测映射相关API到application
			---common	共用头文件及库
			---config	编译相关配置
			---interface app侧api接口以及示例代码
				---at
				---audio
				---camera
				---dev
				---driver
				---flash
				---fs
				---ftp
				---http
				---keypad
				---lcd
				---log
				---mbedtls
				---mqtt
				---network
				---ntp
				---os
				---ping
				---ssl
				---time
			---init		初始化

	---ql-cross-tool	交叉编译工具
		---win32	win32平台
			---host		主机工具 aboot
			---owtoolchain	交叉编译工具armmcc gcc gnumake

	---ql-kernel	系统内核代码及相关库
		---threadx	threadx系统
			---api_map	从kernel测映射相关API到application
			---audio
			---camera
			---common	共用头文件及库
			---config	编译相关配置
			---hal		外设驱动
			---init		启动相关代码
			---lcd
			---quec
			---quec_mbedtls	
			---tools	系统内核编译相关工具
	
	---ql-bootloader
		---boot33	bootloader

	---target 升级固件

## 编译指令：

1. ql-sdk目录下，执行 build.bat app		编译APP镜像(application)，若对app未做任何修改，可以不执行
2. ql-sdk目录下，执行 build.bat kernel		编译kernel，若对kernel未做任何修改，可以不执行
3. ql-sdk目录下，执行 build.bat bootloader	编译bootloader，若对bootloader未做任何修改，可以不执行
4. ql-sdk目录下，执行 build.bat firmware	生成固件

>> 注：未执行编译操作的组件，默认使用ql-sdk\ql-config\quec-project\aboot\images目录下的镜像


## Release History：

	
**[LTE01R06A02_C_SDK_A_BETA0527][01] 2022-05-27**
 --1，新增支持uart 256KHz 波特率的功能

**[LTE01R06A02_C_SDK_A_BETA0602][01] 2022-06-02**
 --1，新增支持SPI CLK  100KHZ~700KHZ 的功能
 --2 删除common\lib中的camera和lcd库，否则lcd和camera无法裁剪
 --3 解决调用ql_usb相关接口死机问题

**[LTE01R06A02_C_SDK_A_BETA0608][01] 2022-06-08**
 --1,新增LOGO侧获取时间count功能
 --2 800MCNGA项目增加GNSS功能
 --3,新增LOGO侧LCD显示功能

**[LTE01R06A02_C_SDK_A][02] 2022-06-08**

**[LTE01R06A02_C_SDK_A_BETA0610A][01] 2022-06-10**
 --1 800MCNGA项目增加GNSS功能
 --2,修复ADC不能正常读取

**[LTE01R06A02_C_SDK_A_BETA0613][01] 2022-06-13**

**[LTE01R06A02_C_SDK_A_BETA0614][01] 2022-06-14**
 --1，解决开机进行数据拨号失败的问题
 --2解决调用socket接口编译报错问题

**[LTE01R06A02V03_C_SDK_A][03] 2022-06-15**

**[LTE01R06A02_C_SDK_A_BETA0618][01] 2022-06-18**
 --1,新增获取SN2 功能
 --2,logo阶段新增SPI驱动
 --3,新增boot侧ADC功能

**[LTE01R06A02_C_SDK_A_BETA0620A][01] 2022-06-20**
 --1，新增支持双卡单待功能

**[LTE01R06A02_C_SDK_A_BETA0623][01] 2022-06-23**

**[LTE01R06A02_VOLTE_C_SDK_A_BETA0630][01] 2022-06-30**

**[LTE01R06A02_C_SDK_A_BETA0704][01] 2022-07-04**
 --1解决camera无法裁剪完全的问题,app侧lib库后缀名由.a修改为.lib
 --2，新增wifiscan功能

**[LTE01R06A02_VOLTE_C_SDK_A_BETA0705][01] 2022-07-05**

**[EC800MCNGAR06A01M08_OCPU_VOLTE_BETA0711][01] 2022-07-11**

**[LTE01R06A02_VOLTE_C_SDK_A_BETA0711][01] 2022-07-12**

**[LTE01R06A02_C_SDK_A_BETA0712][01] 2022-07-12**
 --1 优化软关机流程

**[LTE01R06A02_VOLTE_C_SDK_A_BETA0713][01] 2022-07-13**

**[LTE01R06A01_VOLTE_C_SDK_A][01] 2022-07-19**
 --1,OPEN版本取消网络模式灯和网络状态灯的控制

**[LTE01R06A03_C_SDK_A][01] 2022-07-21**

**[LTE01R06A03_C_SDK_A_BETA0723][01] 2022-07-23**

**[LTE01R06A03_C_SDK_A_BETA0726][01] 2022-07-26**

**[LTE01R06A03_C_SDK_A_THIN_BETA0805][01] 2022-08-05**

**[LTE01R06A03_C_SDK_A_BETA0811][01] 2022-08-11**

**[LTE01R06A03_C_SDK_A_BETA0815][01] 2022-08-15**
**[EC600MCNLAR06A03M08_OCPU_BL_BETA0819A][01] 2022-08-19**
**[LTE01R06A04_C_SDK_A][01] 2022-08-19**


**[LTE01R06A04_C_SDK_A_BETA0821][01] 2022-08-21**

**[EC600MCNLAR06A04M08_OCPU_BL_BETA0822A][01] 2022-08-22**

**[LTE01R06A02_VOLTE_C_SDK_A][01] 2022-08-23**

**[LTE01R06A04_C_SDK_A_BETA0826][01] 2022-08-26**

**[EC600MCNLAR06A04M08_OCPU_BL_BETA0829][01] 2022-08-29**

**[LTE01R06A02_VOLTE_C_SDK_A_BETA0831][01] 2022-08-31**

**[EC600MCNLAR06A01M08_OCPU_SIMB_BETA0906][01] 2022-09-07**

**[LTE01R06A04_C_SDK_A_BETA0907][01] 2022-09-07**

**[LTE01R06A02_VOLTE_C_SDK_A_BETA0913][01] 2022-09-14**

**[LTE01R06A04_C_SDK_A_BETA0921][01] 2022-09-19**
 --1,升级到最新的010.075Q基线

**[LTE01R06A02_VOLTE_C_SDK_A_BETA0921][01] 2022-09-21**

**[LTE01R06A05_C_SDK_A_BETA0924][01] 2022-09-24**

**[LTE01R98A01_C_SDK_A][02] 2022-09-24**

**[LTE01R06A05_C_SDK_A_BETA0928][01] 2022-09-28**

**[LTE01R06A02_VOLTE_C_SDK_A_BETA0928][01] 2022-09-28**

**[EC600MCNLAR06A01M08_OCPU][01] 2022-10-01**

**[EC600MCNLCR06A01M04_OCPU][01] 2022-10-01**

**[EC600MCNLCR06A01M08_OCPU][01] 2022-10-02**

**[LTE01R07A01_C_SDK_A_BETA1009][01] 2022-10-10**
 --1: 车网客户定制需求增加接口用于ap侧主动发起agps数据的接口

**[LTE01R07A01_C_SDK_A_BETA1104][01] 2022-11-04**

**[LTE01R07A01_C_SDK_A_BETA1110][01] 2022-11-10**

**[LTE01R07A01_C_SDK_A_BETA1114][01] 2022-11-14**

**[LTE01R07A01_C_SDK_A_BETA1115][01] 2022-11-15**

**[LTE01R07A01_C_SDK_A_BETA1122][01] 2022-11-22**
 --1,修复带asr_gps项目，不插usb时小系统升级可能死机问题
 --2,修复EC200MCNLA 配置AT+CNMI=1,3,后收不到短信的问题
 --3,新增温度值获取接口int ql_get_temperature_celsius_value(void)

**[LTE01R07A01_C_SDK_A][02] 2022-11-23**
 --1,修复带asr_gps项目，不插usb时小系统升级可能死机问题
 --2,修复EC200MCNLA 配置AT+CNMI=1,3,后收不到短信的问题
 --3,新增温度值获取接口int ql_get_temperature_celsius_value(void)

**[LTE01R07A01_C_SDK_A_BETA1125][01] 2022-11-25**

**[LTE01R07A01_C_SDK_A_BETA1201][01] 2022-12-01**

**[LTE01R07A01_C_SDK_A_BETA1222A][01] 2022-12-22**
 --1, 新增acctimer接口，实现us级别的定时

**[LTE01R07A01_C_SDK_A_BETA1227][01] 2022-12-27**

**[LTE01R07A01_C_SDK_A_TRACK_BETA0104][01] 2023-01-04**

**[LTE01R07A01_C_SDK_A_BETA0105][01] 2023-01-06**

**[LTE01R07A01_C_SDK_A_BETA0110][01] 2023-01-11**
 --1,优化OPEN SDK打包方式和DSP的存放位置

**[LTE01R07A01_C_SDK_A_BETA0112][01] 2023-01-12**
 --1,优化OPEN SDK打包方式和DSP的存放位置

**[LTE01R07A01_C_SDK_A_BETA0202][01] 2023-02-02**

**[LTE01R07A01_C_SDK_A_BETA0214][01] 2023-02-14**

**[LTE01R07A01_C_SDK_A_BETA0215][01] 2023-02-15**

**[LTE01R07A01_C_SDK_A_BETA0223][01] 2023-02-23**

**[LTE01R07A01_C_SDK_A_BETA0302][01] 2023-03-02**

**[LTE01R07A01_C_SDK_A_BETA0303][01] 2023-03-04**

**[LTE01R07A02_C_SDK_A_BETA0310][01] 2023-03-10**
 --1，添加AT+QSCLK=1,1指令功能

**[LTE01R07A02_C_SDK_A_BETA0325A][01] 2023-03-25**

**[LTE01R07A02_TRACKER_C_SDK_A][01] 2023-04-18**

**[New Version]**
