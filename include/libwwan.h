#ifndef LIBWWAN_H
#define LIBWWAN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#if 0
#include <linux/types.h>
#else
#include <sys/types.h>
#endif
#include <time.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <termios.h>
#include <sys/statfs.h>
#include <sys/vfs.h>
#include <sys/sysinfo.h>
#include <errno.h>
#include <sys/socket.h>
#include <linux/if_ether.h>
#include <netdb.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <net/if.h>
#include <netpacket/packet.h>
#include <arpa/inet.h>
#include <pcap.h>

#include <libsg.h>

#if 0
#include <netinet/in.h>
#endif

#define TO_ALIVE	5
#define TO_PPPD_IDL	5
#define TO_PPPD_CALL	20
#define TO_CHKUSB	5

#define WWAN_STA_FILE		"/etc/ppp/.wwan_sta.json"
/* ----------------------------------------- */

#if 1
typedef struct apn_data {
	char	apnnm[16];
	char	user[16];
	char	passwd[16];
	char	pap[16];
	char	device[16];
	int	priority;
} apn_t;
#endif

apn_t* apn_selector(int idxnow, char *apnnmstr, char *devicestr);

#endif /* End of LIBWWAN_H */
