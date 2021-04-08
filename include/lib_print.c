#include "lib_print.h"
#include "main.h"

//#define BASE_PATH_FILE "HISTORY/" //�ļ��Ļ���·��
#define	PATHNAME_ZHIXINLOG		"/data/app/pro104/104Log"		/*������־*/
//#define	PATHNAME_ZHIXINLOG		"104Log"		/*������־*/

void co_printf(const char *fp,const int line)
{
	CHAR sDebug[1024];
	char *ptr=NULL;
	va_list args;
	CP56_TIME2A	Clock_u;

	memset(sDebug,'\0',sizeof(sDebug));
	
	sys_gettime_CP56(&Clock_u);

	sprintf(sDebug,"%02d-%02d-%02d %02d:%02d:%02d:%03d ",Clock_u.time_t.year,Clock_u.time_t.month,
		   Clock_u.time_t.day,Clock_u.time_t.hour,Clock_u.time_t.min,Clock_u.time_t.ms/1000,Clock_u.time_t.ms%1000);

	ptr=strrchr(fp,'/');

	if(ptr)
	{
		sprintf(sDebug+strlen(sDebug),"%s[%d]:",ptr+1,line);
	}
	else
	{
		sprintf(sDebug+strlen(sDebug),"%s[%d]:",fp,line);
	}

	printf("%s",sDebug);
}

/*

void printf_col(const char *format,...)
{
#if COL_DBUG_PT
	va_list args;

	va_start(args,format);
	vprintf(format,args);
	va_end(args);
	

#endif

}
*/
/* ִ��ϵͳ���� */
/*
int SystemCmd(CHAR *cmdline)
{
	FILE * fp; 
	int res; char buf[1024]; 
	
	if (cmdline == NULL) 
	{ 
		t_printf(MAIN_DEBUG_EN,"SystemCmd cmdline is NULL!\r\n");
 		return -1;
 	} 

	t_printf(MAIN_DEBUG_EN,"call SystemCmd %s \r\n", cmdline);
	
	if ((fp = popen(cmdline, "r") ) == NULL) 
	{ 
		perror("popen");
 		t_printf(MAIN_DEBUG_EN,"popen error: %s \r\n", strerror(errno)); 
		return -1; 
	} 
	else
 	{
		while(fgets(buf, sizeof(buf), fp)) 
		{ 
			t_printf(MAIN_DEBUG_EN,"%s", buf); 
		} 
		if ( (res = pclose(fp)) == -1) 
		{ 
			t_printf(MAIN_DEBUG_EN,"close popen file pointer fp error!\r\n"); 
			//signal(SIGCHLD,SIG_IGN)
			//���SIGCHLD�ź���Ϊ������ΪSIG_IGNʱ��
			//waitpid()�����п�����Ϊ�Ҳ����ӽ��̶���ECHILD����
			//����pclose����-1,���ó�SIG_DFL��û����
			return res;
 		} 
		else if (res == 0) 
		{
			 return res;
 		} 
		else 
		{ 
			t_printf(MAIN_DEBUG_EN,"popen res is :%d \r\n", res); 
			return res; 
		} 
	}
}
*/
/*
 дlog�ļ�
 const char* szName, �˿�����
 SBYTE* pBuff,		���������
 int Len				���������
*/
/*
void WriteLogFile(const char* szName,uint8* pBuff,uint16 Len)
{
#ifdef _SAVE_LOG_
	char szFileName[256]={0};
	struct stat FileState;
	FILE *fd;

	if(FileAttrib(PATHNAME_ZHIXINLOG) != ISDIR)
	{
		if(mkdir(PATHNAME_ZHIXINLOG,S_IRWXU|S_IRWXG|S_IRWXO ) == -1)
		{
			return;
		}
	}
	
	memset(szFileName,'\0',sizeof(szFileName));
	strcpy(szFileName,PATHNAME_ZHIXINLOG);
	strcat(szFileName,"/");
	strcat(szFileName,szName);
	strcat(szFileName,".log");

	fd = fopen(szFileName, "a");
	if(fd == NULL)
	{
		return;
	}
	
	fwrite(pBuff, 1, Len, fd);
	
	fclose(fd);

	if(stat(szFileName, &FileState)==-1)
	{
		return;
	}
	
	//log�ļ�����50M,wrap
	if(FileState.st_size > 50*1024*1024)
	{
		char  szCMD[100];
		strcpy(szCMD,"sed -i \'1,2000d\' " );
		strcat(szCMD,szFileName);
		puts(szCMD);
		SystemCmd(szCMD);
	}
#endif

	return;

}
*/
/*
int8 LogID2Name(uint8 index, CHAR *pStr,CHAR *bpStr)
{
#ifdef _SAVE_LOG_
	switch(index)
	{
	case  HOST_LOG:	
		strcpy(pStr,"Host");
		strcpy(bpStr,"HostBak");
		break;
	case  MQTT_LOG:	
		strcpy(pStr,"Mqtt");
		strcpy(bpStr,"MqttBak");
		break;
	case  MSG_QUEUE_LOG:	
		strcpy(pStr,"MsgQ");
		strcpy(bpStr,"MsgQBak");
		break;
	default:
		strcpy(pStr,"      ");
		strcpy(bpStr,"      ");
		return -1;
	}
#endif

	return 0;
}
*/
/*
void GetWriteLock(int fd,int start,int len) 
{ 
   struct flock arg; 
   arg.l_type=F_WRLCK; 
   arg.l_whence=SEEK_SET; 
   arg.l_start=start; 
   arg.l_len=len; 
   
   if(fcntl(fd,F_SETLKW,&arg)==-1) 
     fprintf(stderr,"[%d] Set Write Lock failed./n",getpid()); 
   //else  
    // fprintf(stderr,"[%d] Set Write Lock From %d To %d",getpid(),start,len); 
 } 

void save_log_file(uint8 *str,char *filename,char *bakfile)
{

	int fd;
	uint32 len = 0;
	static struct stat state;

	char cmd[100];
	uint8 logbuf[2400];
	uint8 converbuf[1200];
	char szFileName[256]={0};
	CP56_TIME2A Clock_u;

//	struct stat FileState;
	if(FileAttrib(PATHNAME_ZHIXINLOG) != ISDIR)
	{
		if(mkdir(PATHNAME_ZHIXINLOG,S_IRWXU|S_IRWXG|S_IRWXO ) == -1)
		{
			return;
		}
	}
	
	memset(szFileName,'\0',sizeof(szFileName));
	strcpy(szFileName,PATHNAME_ZHIXINLOG);
	strcat(szFileName,"/");
	strcat(szFileName,filename);
	strcat(szFileName,".log");
        memset(converbuf,'\0',sizeof(converbuf));
        memset(logbuf,'\0',sizeof(logbuf));

	fd= open(szFileName,O_RDWR|O_APPEND|O_CREAT);//û���򴴽��ļ����Ը��ӵķ�ʽ�洢���ݣ�
	if( fd<0)
	{
		fprintf(stderr,"log fopen failed !\n");

	
		return;
	}
		
	GetWriteLock(fd,0,0) ;
	sys_gettime_CP56(&Clock_u);
	
	sprintf(converbuf,"[%02d-%02d-%02d %02d:%02d:%02d:%03d ] ",Clock_u.time_t.year,Clock_u.time_t.month,
		   Clock_u.time_t.day,Clock_u.time_t.hour,Clock_u.time_t.min,\
		   Clock_u.time_t.ms/1000,Clock_u.time_t.ms%1000);
	strcat(logbuf,converbuf);
	strcat(logbuf,str);

	//sprintf(buff,"[%02d-%02d-%02d %02d:%02d:%02d:%03d]  ",protocolTime_variables->Time.year,protocolTime_variables->Time.mon, protocolTime_variables->Time.day,protocolTime_variables->Time.hour,protocolTime_variables->Time.min,protocolTime_variables->Time.second);//�ļ��洢��ʱ���ʽ
	write(fd,logbuf,strlen(logbuf));	
	//write(fd,str,strlen(str));
	//write(fd,filename,strlen(filename));
	
	close(fd);

	stat(filename,&state);
	len = state.st_size;

	if(len > 20000000)
	{
		//ɾ�������ļ�
		unlink(bakfile);
		//���ɱ���
		memset(cmd,0,100);
		sprintf(cmd,"cp %s %s",filename,bakfile);
		system (cmd);
		//��յ�ǰ�ļ�
		memset(cmd,0,100);
		sprintf(cmd,"cat /dev/null > %s",filename);
		system (cmd);
	}
}
*/
/*
LOG ���
 uint8 Index,  log �ļ����1:104��վ2:MQTT 3:Message
 uint8* pBuff,	16���Ʊ���
 uint16 Len,	 16���Ʊ��ĳ���
 CHAR *szTip	 �ַ�������Ϣ
*/
/*
void SaveLog(uint8 Index,uint8* pBuff,uint16 Len,char *szTip)
{
	uint8 logbuf[2400];
	uint8 converbuf[1200];
	CHAR szName[64];
	CHAR szNameBak[64];
	uint16 i;

	


	memset(logbuf, 0, 2400);
	memset(converbuf, 0, 1200);
	memset(szName,'\0',sizeof(szName));
	memset(szNameBak,'\0',sizeof(szNameBak));
	if(LogID2Name(Index,szName,szNameBak) < 0)
	{
		return;
	}
	sprintf(converbuf," [Pro104] [%s]:",szTip);
	strcat(logbuf,converbuf);

	if((pBuff!=NULL)&&(Len>0))
	{
		memset(converbuf, 0, 1200);
				
		for(i = 0; i < Len; i++)
		{
			if(i>=600)  continue;
			sprintf(converbuf, " %02x", pBuff[i]);
			strcat(logbuf,converbuf);
		}
		
	}

	memset(converbuf,0,1200);
	converbuf[0]= '\n';
	strcat(logbuf,converbuf);
		
	save_log_file(logbuf,szName,szNameBak);



	return;	
}
*/
/*
LOG ���
 uint8 Index,  log �ļ����1:104��վ2:MQTT 3:Message
 uint8* pBuff,	16���Ʊ���
 uint16 Len,	 16���Ʊ��ĳ���
 CHAR *szTip	 �ַ�������Ϣ

void SaveLog(uint8 Index,uint8* pBuff,uint16 Len,CHAR *szTip)
{
#ifdef _SAVE_LOG_
	CHAR sDebug[256];
	CHAR szName[64];
	CHAR szBuff[2048];
	uint16 i,j;
	CP56_TIME2A	Clock_u;

	memset(szName,'\0',sizeof(szName));
	if(LogID2Name(Index,szName) < 0)
	{
		return;
	}

	sys_gettime_CP56(&Clock_u);
	memset(sDebug,'\0',sizeof(sDebug));
	sprintf(sDebug,"%02d-%02d-%02d %02d:%02d:%02d:%03d [",Clock_u.time_t.year,Clock_u.time_t.month,
		   Clock_u.time_t.day,Clock_u.time_t.hour,Clock_u.time_t.min,Clock_u.time_t.ms/1000,Clock_u.time_t.ms%1000);
	
	strcat(sDebug, szName);
	if(szTip!=NULL)
	{
		strcat(sDebug,"][");
		strcat(sDebug,szTip);
	}
	strcat(sDebug,"]:");
	if((pBuff == NULL) || (Len == 0))
	{
		strcat(sDebug,"\r\n");
	}
	WriteLogFile(szName,sDebug,strlen(sDebug));
	
	if((pBuff == NULL) || (Len == 0))
	{
		return;
	}
	for(i = 0,j = 0; i < Len; i++)
	{
		int t;
		t = (pBuff[i]&0xF0)>>4;
		szBuff[j++]=(t > 9)?(t-10+'A'):(t+'0');
		t = pBuff[i]&0xF;
		szBuff[j++]=(t > 9)?(t-10+'A'):(t+'0');
		szBuff[j++]=' ';

		if(j > sizeof(szBuff)-5)
		{
			if(i == Len-1)
			{
				szBuff[j++]='\r';
				szBuff[j++]='\n';
			}
			szBuff[j]='\0';
			WriteLogFile(szName,szBuff,j);
			j = 0;
		}
	}
	
	if(j > 0)
	{
		szBuff[j++]='\r';
		szBuff[j++]='\n';
		szBuff[j]='\0';
		WriteLogFile(szName,szBuff,j);
		j = 0;
	}
#endif

	return;	
}*/



