
/*********************************Copyright(c)************************************
*                         ������о΢���ӿƼ����޹�˾                          
*                              ͨ�ſ�����ҵ��                                      
*--------------------------------FileInfo-----------------------------------------
*@File Name: lib_print.h
*@Last modified Date: 2017-12-25               //�������
*@Last Version:1.0.1                                     //�汾��Ϣ
*@Cread By: zxk                                   //����
*@Modified by:                                         //�޸���
*@Modified Time:                                       //�޸�ʱ��
*@brief: for all the modules                           //����
**********************************************************************************
*@note 
* 
* 
* 
* 
* 
*********************************************************************************/
#ifndef __LIB_PRINT_H__
#define __LIB_PRINT_H__

#include "globalbase.h"
#define	DEBUG_FILR_LINE	1	//�Ƿ��ӡ���ļ������к�

#define _SAVE_LOG_ 	//Log  �ļ�����ʹ��

#define HOST_LOG 	1
#define MQTT_LOG 	2
#define MSG_QUEUE_LOG 3


//#define tool_printf (co_printf(__FILE__,__LINE__));printf_col

#define	SOURCE	__FILE__,__LINE__
void co_printf(const char *fp,const int line);

#define h_printf(EN,fmt,...)\
	if(EN &&DEBUG_FILR_LINE)\
	co_printf(__FILE__,__LINE__);\
	if(EN)\
	printf(fmt,##__VA_ARGS__);\

#define t_printf(EN,fmt,...)\
	if(EN)\
	printf(fmt,##__VA_ARGS__);\

/* ִ��ϵͳ���� */
#endif  /*ifndef __LIB_PRINT_H__.2017-12-25 18:13:31 zxk*/


