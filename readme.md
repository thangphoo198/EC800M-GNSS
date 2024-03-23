# SDK˵��

## ���뻷������ 

1. ����kernel��Ҫarmcc���빤�ߡ��ṩ�������ַ�ʽʹ��armcc��
    (1) ʹ����ql-cross-tool\win32\owtoolchainĿ¼���ṩ��ammcc���빤�ߣ�����Ҫ��ql-cross-tool\win32\owtoolchainĿ¼��������license��
	(2) ��װDS-5�������������armcc���빤������Ŀ¼���뻷������PATH�У���ӱ���ARMLMD_LICENSE_FILE�����������У�ARMLMD_LICENSE_FILE����Ϊarmcc��ʹ�õ�license��
2. ����APP��ql-application����Ҫarm-gcc���빤�ߣ�SDK�����ṩ��

## Ŀ¼�ṹ

### ql-sdk	��Ŀ¼ 

	---ql-config
		---quec-project	��Ŀ�������

	---ql-application 
		---threadx
			---api_map	��kernel��ӳ�����API��application
			---common	����ͷ�ļ�����
			---config	�����������
			---interface app��api�ӿ��Լ�ʾ������
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
			---init		��ʼ��

	---ql-cross-tool	������빤��
		---win32	win32ƽ̨
			---host		�������� aboot
			---owtoolchain	������빤��armmcc gcc gnumake

	---ql-kernel	ϵͳ�ں˴��뼰��ؿ�
		---threadx	threadxϵͳ
			---api_map	��kernel��ӳ�����API��application
			---audio
			---camera
			---common	����ͷ�ļ�����
			---config	�����������
			---hal		��������
			---init		������ش���
			---lcd
			---quec
			---quec_mbedtls	
			---tools	ϵͳ�ں˱�����ع���
	
	---ql-bootloader
		---boot33	bootloader

	---target �����̼�

## ����ָ�

1. ql-sdkĿ¼�£�ִ�� build.bat app		����APP����(application)������appδ���κ��޸ģ����Բ�ִ��
2. ql-sdkĿ¼�£�ִ�� build.bat kernel		����kernel������kernelδ���κ��޸ģ����Բ�ִ��
3. ql-sdkĿ¼�£�ִ�� build.bat bootloader	����bootloader������bootloaderδ���κ��޸ģ����Բ�ִ��
4. ql-sdkĿ¼�£�ִ�� build.bat firmware	���ɹ̼�

>> ע��δִ�б�������������Ĭ��ʹ��ql-sdk\ql-config\quec-project\aboot\imagesĿ¼�µľ���


## Release History��

	
**[LTE01R06A02_C_SDK_A_BETA0527][01] 2022-05-27**
 --1������֧��uart 256KHz �����ʵĹ���

**[LTE01R06A02_C_SDK_A_BETA0602][01] 2022-06-02**
 --1������֧��SPI CLK  100KHZ~700KHZ �Ĺ���
 --2 ɾ��common\lib�е�camera��lcd�⣬����lcd��camera�޷��ü�
 --3 �������ql_usb��ؽӿ���������

**[LTE01R06A02_C_SDK_A_BETA0608][01] 2022-06-08**
 --1,����LOGO���ȡʱ��count����
 --2 800MCNGA��Ŀ����GNSS����
 --3,����LOGO��LCD��ʾ����

**[LTE01R06A02_C_SDK_A][02] 2022-06-08**

**[LTE01R06A02_C_SDK_A_BETA0610A][01] 2022-06-10**
 --1 800MCNGA��Ŀ����GNSS����
 --2,�޸�ADC����������ȡ

**[LTE01R06A02_C_SDK_A_BETA0613][01] 2022-06-13**

**[LTE01R06A02_C_SDK_A_BETA0614][01] 2022-06-14**
 --1����������������ݲ���ʧ�ܵ�����
 --2�������socket�ӿڱ��뱨������

**[LTE01R06A02V03_C_SDK_A][03] 2022-06-15**

**[LTE01R06A02_C_SDK_A_BETA0618][01] 2022-06-18**
 --1,������ȡSN2 ����
 --2,logo�׶�����SPI����
 --3,����boot��ADC����

**[LTE01R06A02_C_SDK_A_BETA0620A][01] 2022-06-20**
 --1������֧��˫����������

**[LTE01R06A02_C_SDK_A_BETA0623][01] 2022-06-23**

**[LTE01R06A02_VOLTE_C_SDK_A_BETA0630][01] 2022-06-30**

**[LTE01R06A02_C_SDK_A_BETA0704][01] 2022-07-04**
 --1���camera�޷��ü���ȫ������,app��lib���׺����.a�޸�Ϊ.lib
 --2������wifiscan����

**[LTE01R06A02_VOLTE_C_SDK_A_BETA0705][01] 2022-07-05**

**[EC800MCNGAR06A01M08_OCPU_VOLTE_BETA0711][01] 2022-07-11**

**[LTE01R06A02_VOLTE_C_SDK_A_BETA0711][01] 2022-07-12**

**[LTE01R06A02_C_SDK_A_BETA0712][01] 2022-07-12**
 --1 �Ż���ػ�����

**[LTE01R06A02_VOLTE_C_SDK_A_BETA0713][01] 2022-07-13**

**[LTE01R06A01_VOLTE_C_SDK_A][01] 2022-07-19**
 --1,OPEN�汾ȡ������ģʽ�ƺ�����״̬�ƵĿ���

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
 --1,���������µ�010.075Q����

**[LTE01R06A02_VOLTE_C_SDK_A_BETA0921][01] 2022-09-21**

**[LTE01R06A05_C_SDK_A_BETA0924][01] 2022-09-24**

**[LTE01R98A01_C_SDK_A][02] 2022-09-24**

**[LTE01R06A05_C_SDK_A_BETA0928][01] 2022-09-28**

**[LTE01R06A02_VOLTE_C_SDK_A_BETA0928][01] 2022-09-28**

**[EC600MCNLAR06A01M08_OCPU][01] 2022-10-01**

**[EC600MCNLCR06A01M04_OCPU][01] 2022-10-01**

**[EC600MCNLCR06A01M08_OCPU][01] 2022-10-02**

**[LTE01R07A01_C_SDK_A_BETA1009][01] 2022-10-10**
 --1: �����ͻ������������ӽӿ�����ap����������agps���ݵĽӿ�

**[LTE01R07A01_C_SDK_A_BETA1104][01] 2022-11-04**

**[LTE01R07A01_C_SDK_A_BETA1110][01] 2022-11-10**

**[LTE01R07A01_C_SDK_A_BETA1114][01] 2022-11-14**

**[LTE01R07A01_C_SDK_A_BETA1115][01] 2022-11-15**

**[LTE01R07A01_C_SDK_A_BETA1122][01] 2022-11-22**
 --1,�޸���asr_gps��Ŀ������usbʱСϵͳ����������������
 --2,�޸�EC200MCNLA ����AT+CNMI=1,3,���ղ������ŵ�����
 --3,�����¶�ֵ��ȡ�ӿ�int ql_get_temperature_celsius_value(void)

**[LTE01R07A01_C_SDK_A][02] 2022-11-23**
 --1,�޸���asr_gps��Ŀ������usbʱСϵͳ����������������
 --2,�޸�EC200MCNLA ����AT+CNMI=1,3,���ղ������ŵ�����
 --3,�����¶�ֵ��ȡ�ӿ�int ql_get_temperature_celsius_value(void)

**[LTE01R07A01_C_SDK_A_BETA1125][01] 2022-11-25**

**[LTE01R07A01_C_SDK_A_BETA1201][01] 2022-12-01**

**[LTE01R07A01_C_SDK_A_BETA1222A][01] 2022-12-22**
 --1, ����acctimer�ӿڣ�ʵ��us����Ķ�ʱ

**[LTE01R07A01_C_SDK_A_BETA1227][01] 2022-12-27**

**[LTE01R07A01_C_SDK_A_TRACK_BETA0104][01] 2023-01-04**

**[LTE01R07A01_C_SDK_A_BETA0105][01] 2023-01-06**

**[LTE01R07A01_C_SDK_A_BETA0110][01] 2023-01-11**
 --1,�Ż�OPEN SDK�����ʽ��DSP�Ĵ��λ��

**[LTE01R07A01_C_SDK_A_BETA0112][01] 2023-01-12**
 --1,�Ż�OPEN SDK�����ʽ��DSP�Ĵ��λ��

**[LTE01R07A01_C_SDK_A_BETA0202][01] 2023-02-02**

**[LTE01R07A01_C_SDK_A_BETA0214][01] 2023-02-14**

**[LTE01R07A01_C_SDK_A_BETA0215][01] 2023-02-15**

**[LTE01R07A01_C_SDK_A_BETA0223][01] 2023-02-23**

**[LTE01R07A01_C_SDK_A_BETA0302][01] 2023-03-02**

**[LTE01R07A01_C_SDK_A_BETA0303][01] 2023-03-04**

**[LTE01R07A02_C_SDK_A_BETA0310][01] 2023-03-10**
 --1�����AT+QSCLK=1,1ָ���

**[LTE01R07A02_C_SDK_A_BETA0325A][01] 2023-03-25**

**[LTE01R07A02_TRACKER_C_SDK_A][01] 2023-04-18**

**[New Version]**
