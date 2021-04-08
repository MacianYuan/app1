#ifndef LIBSG_H
#define LIBSG_H

#ifdef __cplusplus
extern "C" 
{
#endif


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/types.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <sys/types.h>
#include <termios.h>
#include <sys/statfs.h>
#include <sys/vfs.h>
#include <sys/sysinfo.h>
#include <errno.h>

#define TARGET	"Lib Sgitg"

#if 1
#define NLDBG
#endif

#ifdef NLDBG
#define DBGP(format, ...)	printf (format, ##__VA_ARGS__)
#else
#define DBGP(format, ...)	
#endif

/* Err type */
enum errtype {
	ERR_NOOPT	= -99,
	ERR_SHCMD	= -98,

	/* ---  system/terminal -- */
	ERR_PWFAIL	= -89,

	/* ---  wwan_errs  --- */
	/* wwan */
	ERR_LTERE	= -30,
	ERR_UNKWWAN	= -29,
	ERR_WWAN	= -28,
	ERR_USBID	= -27,
	/* GPIO */
	ERR_WWANPW	= -20,
	ERR_WWANRST	= -19,
	ERR_WWANONF	= -18,
	/* USB */
	ERR_NOWWAN	= -17,
	/* TTY */
	ERR_WWANTTY	= -16,
	/* Operations */
	ERR_OPERATION	= -15,
	ERR_DIAL	= -14,
	ERR_DISCONN	= -13,

	ERR_NULLVAL	= -6,
	ERR_GPIO	= -5,
	ERR_THREAD	= -4,
	ERR_FORK	= -3,
	ERR_IDX		= -2,

	ERR_START	= -1,
	SUCCESS = 0,
};

/************************************************
 *
 *	sggpio 
 *
 ************************************************/

#define HW_V2_2
enum tgpio_flagemu {
	ltepw		= 0,
	lterst		,
	lteonf		,
	ltepctrl	,
//	ledrun		,
//	ledrune		,
//	ledconn		,
//	ledwwan		,
	uart1ms		,
	uart2ms		,
	mcu1rst		,
	mcu2rst		,
//	dogfeed		,
//	dogen		,
	plcrst		,
	leduartm1	,
	leduartm2	,
#ifndef HW_V2_2
	gpiomax		,
#else
	// hw-ver2.2
	lte2rst		,
	lte2onf		,
	plc12v		,
	usbuartrst	,
	blerst		,
	encryptrst	,
	blects		,
	ledrsv1		,
	ledrsv2		,
	gpiomax		,
#endif
};

enum intr_idxenu {
	uart1msk	= 0,
	uart2msk	= 1,
	plcplg		,
//	pressk1		,
//	pressk2		,
	lteplg		,
//	pwfail		,
#ifndef HW_V2_2
	extrst		,
	intrmax		,
#else
	exethintr	,
	pt100intr	,
	intrmax		,
#endif
};

int gpio_sta(int gpio_idx);
int gpio_intrsta(int intr_idx);
int gpio_opt(int gpio_idx, uint16_t val);

/************************************
 *
 * 	 sgutils 
 *
 *************************************/

/*
 * 从 strs 中找出 argv 的位置
 *
 */


typedef  struct statfs DISK,*pDISK;

typedef struct ifInfo {
	int idx;
	char ifName[16];
	char ifMac[18];
	char ifIP[16];
	char ifMsk[16];
	char ifBrd[16];
	char type[12];

} ifInfo_t;
int findidx(char* argv, char *strs[20], int max);
int seldly(int sec, int msec, int usec);

/* netutils */
int getLocalInfo(void);
int get_MAC(char *ethname, char *buf);

/* ********************************
 *
 *	wwan
 *
 * *******************************/

#define TRUE 0
#define FALSE -1

#define	PCA_GPIO_IOC_MAGIC		'z'

#define PCA95_VENDOR_CODE	_IOR(PCA_GPIO_IOC_MAGIC, 1, unsigned char)
#define PCA95_VENEER_TYPE	_IOR(PCA_GPIO_IOC_MAGIC, 2, unsigned char) 
#define PCA95_VENEER_VERSION	_IOR(PCA_GPIO_IOC_MAGIC, 3, unsigned char) 

#define PCA95_IOCTL_OUT_High	_IOW(PCA_GPIO_IOC_MAGIC, 1, unsigned char)
#define PCA95_IOCTL_OUT_Low	_IOW(PCA_GPIO_IOC_MAGIC, 2, unsigned char)

#define MainReset	7
#define MainPower	8
#define WwanLed		10
#define	Lte_2G		11 
#define	Lte_3G		12 
#define Wwan2Led	13
#define	Lte2_2G		14 
#define	Lte2_3G		15 


#define PCA95_AcSoc_TYPE	_IOR(TGPIO_IOC_MAGIC, 4, __u8) 

#define MainResetAc	7
#define MainPowerAc	8

#if 0
#define GL	0x0
#define GH	0x1
#endif

#define WWAN_RSTPRS	0x0
#define WWAN_RSTREL	0x1

int wwan_gpio_check(void);
int cmd_init_huawei(int fd);
int cmd_init_neoway(int fd);

/* --- operators --- */
typedef struct operator_data {
	int opidx;
	char apn[32];
	char atdt[32];
	char name[32];
} operator_t;

typedef struct usb_tty {
	char usbbus[16];
	char ttyusbs[8][10];
} usb_tty_t;

typedef struct pppd_data {
	int pid;
	char cmdline[32]; // pppd call wwan(x)_call &
	char ifname[8];
} pppd_data_t;

typedef struct module_data {
	int devidx;
	char usbID[10];
	int dbgttyfd;
	int dbgttyord;
	int dialttyord;
	int  (*cmd_init)(int fd);
} mod_data_t;

typedef struct wwan_data {
	int channel;
	char wwan_call[32];
	uint8_t primary;
	uint8_t exists;
	usb_tty_t usbdata;
	char *dbgtty;
	char *dailtty;
//	operator_t *operator;
	mod_data_t mod_type;
	pppd_data_t pppdata;
} wwan_data_t;

/* --- USB devices --- */
enum wwanDevTypeEnu {
	neoway		= 0,
	huawei		,
	wwandevIDmax	= 2,
};

typedef struct wwan_keepalive_data {
	wwan_data_t *wwan_dev;
	pthread_t pid_dial;
	pthread_t pid_keepalive;
	uint8_t pppdsta;
	uint8_t ppp0sta;
	uint8_t dialsta;
	uint8_t isalive;
} wwan_keepalive_t;

/* wwan */
enum modem_idxenu {
	mdm_start	= 0,
	mdm_stop	,
	mdm_reset	= 2,
	mdm_show	,
	modem_optmax	= 4,
};

/* --- ESAM --- */

/* --- system alter --- */
enum rqst_src {
	ESDK_FROM698 = 0,
};

/* --- MQTT --- */
typedef struct topic_type {
	char *app;
//	char *operator; // 操作类型
	char *infoType; // 信息类型
	char *infoTarget; // 目标app/服务/信息源
	char *infoPath; // 信息对象，clock/按键/中断/设备等
} topic_t;

int request_ifcfg(char *IPCfg, char *IPAddr, char *NetMask, char *GateWay, int source);
int version(char *verret);
void gettimenow(char *timstr);
int findidx(char* argv, char *strs[20], int max);
int seldly(int sec, int msec, int usec);
int shell_cmd(char *cmd, char *retbuf, int buflen);
int get_system_boot_time(struct tm *boottime);

#ifdef __cplusplus
}
#endif

#endif /* End of LIBSG_H */
