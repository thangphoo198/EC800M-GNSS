/*================================================================
  Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

#ifndef _QL_FS_H
#define _QL_FS_H

#include "ql_type.h"
#include "lfs.h"

#define QFS_ID_MAX     3

typedef unsigned int FILE_ID;

typedef struct
{
	int fs_id;
	lfs_file_t file;
} QFILE;

typedef struct
{
	int fs_id;
	lfs_dir_t dir;
} QDIR;

#define U_DISK_SYM	'U'
#define B_DISK_SYM	'B'

/*-----------------------------------------------------------------------------------------
 * Function: Format file system according to disk character
 *
 * Parameter:
 *    <fs_id>: 	[IN] Disk character.
 *		
 * Return:
 *    LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_fs_format(char disk_sym);

/*-----------------------------------------------------------------------------------------
 * Function: Mount file system according to disk character
 *
 * Parameter:
 *    <fs_id>: 	[IN] Disk character.
 *		
 * Return:
 *    LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_fs_mount(char disk_sym);

/*-----------------------------------------------------------------------------------------
 * Function: Unmount file system according to disk character
 *
 * Parameter:
 *    <fs_id>: 	[IN] Disk character.
 *		
 * Return:
 *    LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_fs_unmount(char disk_sym);

/*-----------------------------------------------------------------------------------------
 * Function: Get file system size according to disk character
 *
 * Parameter:
 *    <fs_id>: 	[IN] Disk character.
 *		
 * Return:
 *    LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_fs_size(char disk_sym);

/*-----------------------------------------------------------------------------------------
 * Function: Get file system used size according to disk character
 *
 * Parameter:
 *    <fs_id>: 	[IN] Disk character.
 *		
 * Return:
 *    LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_fs_used_size(char disk_sym);

/*-----------------------------------------------------------------------------------------
 * Function: Get file system free size according to disk character
 *
 * Parameter:
 *    <fs_id>: 	[IN] Disk character.
 *		
 * Return:
 *    LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_fs_free_size(char disk_sym);

/*-----------------------------------------------------------------------------------------
 * Function: Open file in the file system
 *
 * Parameter:
 *    <fs_id>: 	[IN] Disk character.
 *    <mode>: 	[IN] Open mode .
 *		
 * Return:
 *    File stream.
-----------------------------------------------------------------------------------------*/
QFILE * ql_fopen(const char *fname, const char *mode);

/*-----------------------------------------------------------------------------------------
 * Function: Open file in the file system
 *
 * Parameter:
 *    <fp>: 	[IN] File stream.
 *		
 * Return:
 *   LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_fclose(QFILE * fp);

/*-----------------------------------------------------------------------------------------
 * Function: Synchronization File in the file system
 *
 * Parameter:
 *    <fp>: 	[IN] File stream.
 *		
 * Return:
 *    LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_fsync(QFILE * fp);

/*-----------------------------------------------------------------------------------------
 * Function: Read file
 *
 * Parameter:
 *    <buffer>: [OUT] File read buff.
 *    <size>: 	[IN] File read size.
 *    <num>:	[IN] File read format size.
 *    <fp>: 	[IN] File stream.
 *		
 * Return:
 *    Real read size.
-----------------------------------------------------------------------------------------*/
int ql_fread(void * buffer, size_t size, size_t num, QFILE * fp);

/*-----------------------------------------------------------------------------------------
 * Function: Write file
 *
 * Parameter:
 *    <buffer>: [IN] File write buff.
 *    <size>: 	[IN] File write size.
 *    <num>:	[IN] File write format size.
 *    <fp>: 	[IN] File stream.
 *		
 * Return:
 *    Real write size.
-----------------------------------------------------------------------------------------*/
int ql_fwrite(void * buffer, size_t size, size_t num, QFILE * fp);

/*-----------------------------------------------------------------------------------------
 * Function: Write one character into file
 *
 * Parameter:
 *    <chr>: [IN] File write character.
 *    <fp>:  [IN] File stream.
 *		
 * Return:
 *    Real write size.
-----------------------------------------------------------------------------------------*/
int ql_fputc(int chr, QFILE *fp);

/*-----------------------------------------------------------------------------------------
 * Function: Write string into file
 *
 * Parameter:
 *    <chr>: [IN] File write string.
 *    <fp>:  [IN] File stream.
 *		
 * Return:
 *    Real write size.
-----------------------------------------------------------------------------------------*/
int ql_fputs(const char *str, QFILE *fp);

/*-----------------------------------------------------------------------------------------
 * Function: Format write string into file
 *
 * Parameter:
 *    <fp>:     [IN] File stream.
 *    <format>: [IN] File format.
 *		
 * Return:
 *    Real write size.
-----------------------------------------------------------------------------------------*/
int ql_fprintf(QFILE *fp, const char *format, ...);

/*-----------------------------------------------------------------------------------------
 * Function: Read one character from file
 *
 * Parameter:
 *    <fp>:  [IN] File stream.
 *		
 * Return:
 *    Read character.
-----------------------------------------------------------------------------------------*/
int ql_fgetc(QFILE *fp);

/*-----------------------------------------------------------------------------------------
 * Function: Read string from file
 *
 * Parameter:
 *    <fpstr>:  [OUT] Read buff.
 *    <n>:      [IN] Read lengths.
 *    <fp>:     [IN] File stream.
 *		
 * Return:
 *    Read string.
-----------------------------------------------------------------------------------------*/
char *ql_fgets(char *str, int n, QFILE *fp);

/*-----------------------------------------------------------------------------------------
 * Function: Format read string from file
 *
 * Parameter:
 *    <fp>:     [IN] File stream.
 *    <format>: [IN] File format.
 *		
 * Return:
 *    Real read size.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_fscanf(QFILE *fp, const char *format, ...);


/*-----------------------------------------------------------------------------------------
 * Function: Relocate file pointer
 *
 * Parameter:
 *    <fp>:         [IN] File stream.
 *    <offset>: 	[IN] off set.
 *    <origin>:     [IN] Starting position.
 *		
 * Return:
 *     LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_fseek(QFILE *fp, long offset, int origin);

/*-----------------------------------------------------------------------------------------
 * Function: File truncate
 *
 * Parameter:
 *    <fp>:         [IN] File stream.
 *    <length>:    [IN] truncate size.
 *		
 * Return:
 *    LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_ftruncate(QFILE *fp, u32 length);

/*-----------------------------------------------------------------------------------------
 * Function: Get the current location of the file pointer
 *
 * Parameter:
 *    <fp>:         [IN] File stream.
 *		
 * Return:
 *    Current location of the file pointer.
-----------------------------------------------------------------------------------------*/
long ql_ftell(QFILE *fp);

/*-----------------------------------------------------------------------------------------
 * Function: Set file location to given stream
 *
 * Parameter:
 *    <fp>:         [IN] File stream.
 *		
 * Return:
 *    
-----------------------------------------------------------------------------------------*/
int ql_frewind(QFILE *fp);

/*-----------------------------------------------------------------------------------------
 * Function: Get file size
 *
 * Parameter:
 *    <fp>:         [IN] File stream.
 *		
 * Return:
 *    File size.
-----------------------------------------------------------------------------------------*/
int ql_fsize(QFILE *fp);

/*-----------------------------------------------------------------------------------------
 * Function: Create directory
 *
 * Parameter:
 *    <path>: 	[IN] Directory path.
 *    <mode>: 	[IN] create mode.
 *		
 * Return:
 *    LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_mkdir(const char *path, u32 mode);

/*-----------------------------------------------------------------------------------------
 * Function: Open directory
 *
 * Parameter:
 *    <path>: 	[IN] Directory path.
 *    <mode>: 	[IN] create mode.
 *		
 * Return:
 *    Directory stream.
-----------------------------------------------------------------------------------------*/
QDIR * ql_opendir(const char *path);

/*-----------------------------------------------------------------------------------------
 * Function: Open directory
 *
 * Parameter:
 *    <dp>: 	[IN] Directory stream.
 *		
 * Return:
 *    Directory stream.
-----------------------------------------------------------------------------------------*/
int ql_closedir(QDIR *dp);

/*-----------------------------------------------------------------------------------------
 * Function: Read directory
 *
 * Parameter:
 *    <dp>: 	[IN] Directory stream.
 *    <info>: 	[IN] File info structure ..
 *		
 * Return:
 *    LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_readdir(QDIR *dp, struct lfs_info *info);

/*-----------------------------------------------------------------------------------------
 * Function: Relocate directory pointer
 *
 * Parameter:
 *    <dp>: 	[IN] Directory stream.
 *    <loc>: 	[IN] Relocate position.
 *		
 * Return:
 *    
-----------------------------------------------------------------------------------------*/
int ql_seekdir(QDIR *dp, long int loc);

/*-----------------------------------------------------------------------------------------
 * Function: Get the current location of the directory pointer
 *
 * Parameter:
 *    <dp>: 	[IN] Directory stream.
 *		
 * Return:
 *    Current location of the directory pointer.
-----------------------------------------------------------------------------------------*/
long ql_telldir(QDIR *dp);

/*-----------------------------------------------------------------------------------------
 * Function: Set directory location to given stream
 *
 * Parameter:
 *    <dp>: 	[IN] Directory stream.
 *		
 * Return:
 *    
-----------------------------------------------------------------------------------------*/
int ql_rewinddir(QDIR *dp);

/*-----------------------------------------------------------------------------------------
 * Function: Remove files in the file system
 *
 * Parameter:
 *    <fname>: 	[IN] File name.
 *		
 * Return:
 *    LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_remove(const char *fname);

/*-----------------------------------------------------------------------------------------
 * Function: Rename files 
 *
 * Parameter:
 *    <oldpath>: 	[IN] File oldpath.
 *    <newpath>: 	[IN] File newpath.
 *		
 * Return:
 *    LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_rename(const char *oldpath, const char *newpath);

/*-----------------------------------------------------------------------------------------
 * Function: Copy files 
 *
 * Parameter:
 *    <oldpath>: 	[IN] File old path.
 *    <newpath>: 	[IN] File new path.
 *		
 * Return:
 *    LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_copy(const char *oldpath, const char *newpath);

/*-----------------------------------------------------------------------------------------
 * Function: Judge whether the file exists
 *
 * Parameter:
 *    <path>: 	[IN] File path.
 *    <mode>: 	[IN] File mode.
 *		
 * Return:
 *    LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_access(const char *path, u32 mode);

/*-----------------------------------------------------------------------------------------
 * Function: Find info about a directory
 *
 * Parameter:
 *    <path>: 	[IN] File path.
 *    <info>: 	[IN] File info structure.
 *		
 * Return:
 *    LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_stat(const char *path, struct lfs_info *info);
/***********************************************************************
 *
 * Name:		ql_FDI_fopen
 *
 * Description: used in an implementation-specified matter to open or create a file and
*    associate it with a stream.
 *
 * Parameters:
 *  char                 *filename_ptr      [IN]    const character string for file name specifier.
*  char			*mode                [IN] 	const character string for type specification;
 *
 * Returns:
 *	the stream index used for the opened file.
 *    If an error is detected, FDI_fopen returns 0.
 *
 * Notes:
 *
 ***********************************************************************/
FILE_ID ql_FDI_fopen(const char *filename_ptr, const char *mode);
/***********************************************************************
 *
 * Name:		ql_FDI_fclose
 *
 * Description: used to close a file stream.
 *
 * Parameters:
 *  FILE_ID                 stream      [IN]    stream index for the file to be closed.
 *
 * Returns:
 *		0:   pass
 * 	 	EOF: fail
 * Notes:
 *
 ***********************************************************************/
int ql_FDI_fclose(FILE_ID stream);
/***********************************************************************
 *
 * Name:		ql_FDI_fread
 *
 * Description: read file.
 *
 * Parameters:
 *	 void		*buffer_ptr   	[OUT]	pointer to buffer to place data read
 *	size_t		element_size 	[IN] 		size of element referenced by buffer pointer
 *	size_t		count    		[IN]		number of elements to be read
 *	FILE_ID 		stream		[IN]		stream index for the file to be closed.
 *
 * Returns:
 *		number of elements succesfully read
 * Notes:
 *
 ***********************************************************************/
size_t ql_FDI_fread(void *buffer_ptr, size_t element_size, size_t count, FILE_ID stream);
/***********************************************************************
 *
 * Name:		ql_FDI_fwrite
 *
 * Description: write file.
 *
 * Parameters:
 *	 void		*buffer_ptr   	[IN]		pointer to buffer to be written
 *	size_t		element_size 	[IN] 		size of element referenced by buffer pointer
 *	size_t		count    		[IN]		number of elements to be read
 *	FILE_ID 		stream		[IN]		stream index for the file to be closed.
 *
 * Returns:
 *		number of elements succesfully write
 * Notes:
 *
 ***********************************************************************/
size_t ql_FDI_fwrite(const void *buffer_ptr,size_t element_size,size_t count,FILE_ID stream);
/***********************************************************************
 *
 * Name:		ql_FDI_fseek
 *
 * Description: sets the file position indicator of the file specified  by stream.
 *				The new position, measured in bytes from the beginning of the file
 *				is obtained by adding offset to the position specified by wherefrom.
 *
 * Parameters:
 *    FILE_ID                 stream      [IN]    stream index for the file
 *	long				offset 	[IN] 		the offset to obtain to the position indicator (in bytes)
 *	int				wherefrom    		[IN]		the position to add offset(SEEK_SET, SEEK_CUR, SEEK_END)

 *
 * Returns:
  *		0:  pass
 * 	 	EOF: fail
 * Notes:
 *
 ***********************************************************************/

int ql_FDI_fseek(FILE_ID stream, long offset, int wherefrom);

/***********************************************************************
 *
 * Name:		ql_FDI_GetFileSize
 *
 * Description:  get file size
 *
 * Parameters:
 *  int                 fd      [IN]    file handler
 *
 * Returns:
 * 	 	file length
 * Notes:
 *
 ***********************************************************************/
unsigned int ql_FDI_GetFileSize(int fd);
/*-----------------------------------------------------------------------------------------
 * Function: Open file in the nand flash
 *
 * Parameter:
 *    <fs_id>: 	[IN] Disk character.
 *    <mode>: 	[IN] Open mode .
 *		
 * Return:
 *    File stream.
-----------------------------------------------------------------------------------------*/
FILE_ID ql_nand_fopen(const char *filename_ptr, const char *mode);

/*-----------------------------------------------------------------------------------------
 * Function: Open file in the nand flash
 *
 * Parameter:
 *    <fp>: 	[IN] File stream.
 *		
 * Return:
 *   LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_nand_fclose(FILE_ID stream);

/*-----------------------------------------------------------------------------------------
 * Function: Read file in the nand flash
 *
 * Parameter:
 *    <buff>: [OUT] File read buff.
 *    <size>: 	[IN] File read size.
 *    <count>:	[IN] File read format size.
 *    <stream>: 	[IN] File stream.
 *		
 * Return:
 *    Real read size.
-----------------------------------------------------------------------------------------*/
int ql_nand_fread(void *buff, size_t element_size, size_t count, FILE_ID stream);

/*-----------------------------------------------------------------------------------------
 * Function: Write file in the nand flash
 *
 * Parameter:
 *    <buff>: [IN] File write buff.
 *    <size>: 	[IN] File write size.
 *    <count>:	[IN] File write format size.
 *    <stream>: 	[IN] File stream.
 *		
 * Return:
 *    Real write size.
-----------------------------------------------------------------------------------------*/
int ql_nand_fwrite(const void *buff, size_t element_size, size_t count, FILE_ID stream);

/*-----------------------------------------------------------------------------------------
 * Function: Relocate file pointer in the nand flash
 *
 * Parameter:
 *    <stream>:         [IN] File stream.
 *    <offset>: 	[IN] off set.
 *    <wherefrom>:     [IN] Starting position.
 *		
 * Return:
 *     LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_nand_fseek(FILE_ID stream, long offset, int wherefrom);

/*-----------------------------------------------------------------------------------------
 * Function: Remove files in the nand flash
 *
 * Parameter:
 *    <filename_ptr>: 	[IN] File name.
 *		
 * Return:
 *    LFS_ERR_OK: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int ql_nand_fremove(const char *filename_ptr);

//20201013 august end


//20201221 august add to SPI nand flash
/*-----------------------------------------------------------------------------------------
 * Function: Rename the nand file
 *
 * Parameter:
 *    <oldpath>: 	[IN] File oldpath.
 *    <newpath>: 	[IN] File newpath.
 *		
 * Return:
 *    0: no error.
 *   -1:  error
-----------------------------------------------------------------------------------------*/
int ql_nand_frename(char *name, char *new_name);

/*-----------------------------------------------------------------------------------------
  * Function: Get nand file size
 *
 * Parameter:
 *    <fp>:         [IN] File stream.
 *		
 * Return:
 *    File size.
-----------------------------------------------------------------------------------------*/
int ql_nand_fsize(char *file_name);

/*-----------------------------------------------------------------------------------------
 * Function: Create directory
 *
 * Parameter:
 *    <path>: 	[IN] Directory path.
 *		
 * Return:
 *    0: no error.
 *    other:  error
-----------------------------------------------------------------------------------------*/
int	ql_nand_mkdir(char *dir_name);

/*-----------------------------------------------------------------------------------------
 * Function: Judge whether the file exists
 *
 * Parameter:
 *    <path>: 	[IN] File name.
 *		
 * Return:
 *    1: exists.
 *    0: no exists
-----------------------------------------------------------------------------------------*/
int ql_nand_access(char *file_name);
//20201221 august end

/*-----------------------------------------------------------------------------------------
 * Function: Get the remaining space of the file system
 *
 * Parameter:
 *		
 * Return:
 *   	Free space size(For reference only)
-----------------------------------------------------------------------------------------*/
int ql_nand_get_free_size(void);

/*-----------------------------------------------------------------------------------------
 * Function: Format the file system
 *
 * Parameter:
 *		
 * Return:
 *   	
-----------------------------------------------------------------------------------------*/
void ql_nand_format(void);

/*-----------------------------------------------------------------------------------------
 * Function: qfs_init 挂载文件系统到指定分区
 *
 * Parameter:
 *		
 * Return:
 *   	
-----------------------------------------------------------------------------------------*/
int qfs_init(char disk_sym, char *patition_name, unsigned char is_format);
/*-----------------------------------------------------------------------------------------
 * Function: qextfs_init 挂载文件系统到外部flash
 *
 * Parameter:
 *		
 * Return:
 *   	
-----------------------------------------------------------------------------------------*/
int qextfs_init(char disk_sym, char *patition_name, unsigned char is_format, unsigned char spi_port, unsigned int startaddr, unsigned int size);

#endif

