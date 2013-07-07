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
#include <pthread.h>

#define NUNCHUK_ADDRESS      0x52
#define NUNCHUK_DATA_LENGTH  6
#define NUNCHUK_REQ_MIN_FREQ 0
#define NUNCHUK_REQ_MAX_FREQ 10000
#define NUNCHUK_THREAD_ARG   "Nunchuk thread"

struct nunchuk {
	uint8_t X, Y, Z, C;
	uint16_t aX, aY, aZ;
};

typedef void (*nuncuk_read_callback)(void*);


int nunchuk_init_nunchuk();
int nunchuk_init(struct nunchuk* n);
int nunchuk_read_data(struct nunchuk* n);
int nunchuk_exit();
inline int nunchuk_is_initiated();
void nunchuk_set_request_freq(int new_freq);
int nunchuk_get_request_freq();
void nunchuk_set_read_callback(nuncuk_read_callback func);


#endif
