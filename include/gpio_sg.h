#ifndef GPIO_AW_H
#define GPIO_AW_H
#include "gpio_sgcomm.h"

#define DRVNAME		"gpio_sg"

int major_sg;

#define GPIO_SYSNODE	"gpio_ttu"

enum tgpio_flagemu {
	ltepw		= 0,
	lterst		,
	lteonf		,
	ltepctrl	,
	ledrun		,
	ledrune		= 5,
	ledconn		,
	ledwwan		,
	uart1ms		,
	uart2ms		,
	mcu1rst		= 10,
	mcu2rst		,
	dogfeed		,
	dogen		,
	zbrst		,
	leduartm1	= 15,
	leduartm2	,
	gpiomax		= 17,
};

unsigned int tgpio_flag[gpiomax] = {};

/* ------------------------------- */
/* GPIO interrupt */

#define INTR_SYSNODE	"gpio_intr"

enum intr_idxenu {
	uart1msk	= 0,
	uart2msk	= 1,
	plcplg		,
	pressk1		,
	pressk2		,
	lteplg		= 5,
	pwfail		,
	extrst		,
	intrmax		= 8,
};

int gpio_intrs[] = {0,1,2,3,4,5,6,};

struct intr_gpio_data {
	char intr_nm[16];
	int intr_idx;	
	int pio_hdle;	
	int state;
	int pre_state;
	unsigned int gpio_flag;
};

#endif /* GPIO_AW_H */
