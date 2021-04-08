#ifndef GPIO_COMM_H
#define GPIO_COMM_H

#define GPIODRV		"gpio_sg"
const char *gpiodrv = "/dev/"GPIODRV;

#define	TGPIO_IOC_MAGIC		'T'

#define TGPIO_IOC_GETVAL	_IOR(TGPIO_IOC_MAGIC, 1, __u8)
#define TGPIO_IOC_GETSTA	_IOR(TGPIO_IOC_MAGIC, 2, __u8)
#define TGPIO_IOC_SETVAL	_IOW(TGPIO_IOC_MAGIC, 1, __u8)
#define TGPIO_IOC_SETHIGH	_IOW(TGPIO_IOC_MAGIC, 2, __u8)
#define TGPIO_IOC_SETLOW	_IOW(TGPIO_IOC_MAGIC, 3, __u8)
#define TGPIO_IOC_TOGGLE	_IOW(TGPIO_IOC_MAGIC, 4, __u8)

#define GH	1
#define GL	0

char *tgpio_nms[20] = {
	"ltepw",
	"lterst",
	"lteonf",
	"ltepctrl",
	"ledrun",
	"ledrune",
	"ledconn",
	"ledwwan",
	"uart1ms",
	"uart2ms",
	"mcu1rst",
	"mcu2rst",
	"dogfeed",
	"dogen",
	"zbrst",
	"leduartm1",
	"leduartm2",
};

/* ------------------------------- */
/* GPIO interrupt */

char* intr_nms[] = {
	"uart1msk"	,
	"uart2msk"	,
	"plcplg"	,
	"pressk1"	,
	"pressk2"	,
	"lteplg"	,
	"pwfail"	,
	"extrst"	,
};

#endif /* GPIO_COMM_H */
