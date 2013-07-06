/* by xerpi (c) 2013 */

#ifndef _NUNCHUK_H_
#define _NUNCHUK_H_

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <linux/uinput.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NUNCHUK_ADDRESS     0x52
#define NUNCHUK_DATA_LENGTH 6


struct nunchuk {
	uint8_t X, Y, Z, C;
	uint16_t aX, aY, aZ;
};

int nunchuk_init_nunchuk();
int nunchuk_init();
int nunchuk_read_data(struct nunchuk* n);
int nunchuk_exit();
inline int nunchuk_is_initiated();



#endif
