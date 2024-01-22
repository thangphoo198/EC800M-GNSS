#ifndef _QL_LCD_H_
#define _QL_LCD_H_

typedef enum QL_SPI_LCD_CLK_ENUM {
	QL_SPI_LCD_CLK_6_5M = 0,
	QL_SPI_LCD_CLK_13M ,
	QL_SPI_LCD_CLK_26M ,
	QL_SPI_LCD_CLK_52M ,
	QL_SPI_LCD_CLK_3_25M, // the following three options is only for craneM
	QL_SPI_LCD_CLK_1_625M,
	QL_SPI_LCD_CLK_812_5k,
	QL_SPI_CLK_LIMIT
}QL_SPI_LCD_CLK_E;

enum{
	LCD_WORK_MODE_POLLING,
	LCD_WORK_MODE_DMA,
	LCD_WORK_MODE_LIMIT
};
    
enum{
	LCD_TYPE_RGB = 0,
	LCD_TYPE_FSTN = 1,
	LCD_TYPE_LIMIT
};

enum {
    QL_LCD_CMD = 0,
    QL_LCD_DATA,
    QL_LCD_DELAY,
};

enum{
	QL_SPI_FORMAT_RGB565 = 0,
	QL_SPI_FORMAT_RGB666 = 1,
	QL_SPI_FORMAT_RGB666_2_3 = 2,
	QL_SPI_FORMAT_RGB888 = 3,
	QL_SPI_FORMAT_RGB888_2_3 = 4,
	QL_SPI_FORMAT_LIMIT
};

enum{
	QL_SPI_EDGE_RISING = 0,
	QL_SPI_EDGE_FALLING = 1,
	QL_SPI_EDGE_LIMIT
};

enum{
	QL_SPI_ENDIAN_LSB = 0,
	QL_SPI_ENDIAN_MSB = 1,
	QL_SPI_ENDIAN_LIMIT
};

enum{
	QL_LCD_CAP_NORMALE = 0,
	QL_LCD_CAP_FAKE = 1,
	QL_LCD_CAP_POWERON = 2,
	QL_LCD_CAP_NOTE = 4, /*has no te signal*/
	QL_LCD_CAP_LIMIT
};

typedef struct ql_spi_lcd_write_struct {
	unsigned char type;		/* SPI_WRITE_CMD / SPI_WRITE_DATA / SPI_WRITE_DELAY */
	unsigned char value;
	unsigned char data_length;	/* Only for SPI_WRITE_CMD */
}ql_spi_lcd_write_t;

typedef struct ql_lcd_data_struct 
{
    ql_spi_lcd_write_t* init_para;          //lcd��ʼ����������ѡ
	unsigned int        init_para_len;      //��ʼ����������
	unsigned short      width;              //lcd��
	unsigned short      height;             //lcd��
	unsigned char       lcd_cmd_col_set;    //��ѡ
	unsigned char       lcd_cmd_row_set;    //��ѡ
	unsigned char       lcd_cmd_mem_wr;     //��ѡ
	unsigned int        te_signal;          //te����
	unsigned int 	    spi_wclk;           //дʱ���ʱ��
	unsigned int 	    spi_rclk;           //��ʱ���ʱ��
	unsigned int 	    lcd_id;             //lcd_id
	unsigned short      format;             //ˢͼ��ʽֻ֧��rgb565
    unsigned short      type;               //rgb or �ڰ���
	unsigned short      sample_edge;        //spi���ؼ��
	unsigned short      endian;             //��С������
	unsigned short      line_num;	        //4 or 3
	unsigned short      data_line;          //1 or 2
	unsigned char       work_mode;          //����ģʽdmaorpolling
}ql_lcd_data_t;


typedef enum
{
    LCD_SLEEP,
    LCD_WAKE_UP,
}QL_LCD_SLEEP;
    
/***********************************************************************
 *
 * Name:  ql_lcd_init 
 *
 * Description: ��ʼ��lcd����spi������
 *
 * Parameters:  ��ʼ������
 *              
 * Returns:     0��send_success
 *              other: faile
 * Notes:
 *
 ***********************************************************************/
int ql_lcd_init(ql_lcd_data_t *lcd_data);
/***********************************************************************
 *
 * Name:  ql_lcd_clear_screen
 *
 * Description: ��������
 *
 * Parameters:  rgb565ɫ��ֵ
 *              
 * Returns:     0��send_success
 *              other: faile
 * Notes:
 *
 ***********************************************************************/
int ql_lcd_clear_screen(unsigned short bg_color); 

/***********************************************************************
 *
 * Name:  ql_lcd_clear_screen
 *
 * Description: ��������
 *
 * Parameters:  ����lcd����
 *              
 * Returns:     0��send_success
 *              other: faile
 * Notes:
 *
 ***********************************************************************/
 
int ql_lcd_wakeup(unsigned int level);
/***********************************************************************
 *
 * Name:  ql_lcd_display_on
 *
 * Description: ��ʼˢ��
 *
 * Parameters:  none
 *              
 * Returns:     0��send_success
 *              other: faile
 * Notes:
 *
 ***********************************************************************/
int ql_lcd_display_on(void);

/***********************************************************************
 *
 * Name:  ql_lcd_display_off
 *
 * Description: ֹͣˢ��
 *
 * Parameters:  ����lcd����
 *              
 * Returns:     0��send_success
 *              other: faile
 * Notes:
 *
 ***********************************************************************/
int ql_lcd_display_off(void);
/***********************************************************************
 *
 * Name:  ql_spi_lcd_write_cmd
 *
 * Description: ��lcdдָ��
 *
 * Parameters:  Ҫд��ָ��
 *              
 * Returns:     0��send_success
 *              other: faile
 * Notes:
 *
 ***********************************************************************/
int ql_spi_lcd_write_cmd(unsigned char cmd);
/***********************************************************************
 *
 * Name:  qql_spi_lcd_write_data
 *
 * Description: ��lcdд����
 *
 * Parameters:  Ҫд������
 *              
 * Returns:     0��send_success
 *              other: faile
 * Notes:
 *
 ***********************************************************************/
int ql_spi_lcd_write_data(unsigned char data);
/***********************************************************************
 *
 * Name:  ql_lcd_updata_config
 *
 * Description: ����lcd��������
 *
 * Parameters:  ��ʼ������
 *              
 * Returns:     0��send_success
 *              other: faile
 * Notes:
 *
 ***********************************************************************/
int ql_lcd_updata_config(ql_lcd_data_t *lcd_data);
/***********************************************************************
 *
 * Name:  ql_lcd_write_sync
 *
 * Description: lcdˢͼ����
 *
 * Parameters:  pbuffer��ͼƬbuffer
 *              start_x��ͼƬ��ʼλ�ú�����
 *              start_y��ͼƬ��ʼλ��������
 *              end_x��   ͼƬ����λ�ú�����
 *              end_y��   ͼƬ����λ��������
 * Returns:     0��send_success
 *              other: faile
 * Notes:
 *
 ***********************************************************************/
int ql_lcd_write_sync(unsigned char *pbuffer, unsigned short start_x, unsigned short start_y, unsigned short end_x, unsigned short end_y);

/***********************************************************************
 *
 * Name:  ql_lcd_read_id
 *
 * Description: ��ȡlcdоƬid
 *
 * Parameters:  none
 *              
 * Returns:     0��send_success
 *              other: faile
 * Notes:
 *
 ***********************************************************************/
unsigned int ql_lcd_read_id(void);

#endif

