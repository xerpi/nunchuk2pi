/* by xerpi (c) 2013 */

#ifndef _UINPUT_H_
#define _UINPUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <stdint.h>
#include <time.h>

#define release    0
#define press      1
#define autorepeat 2


int uinput_init();
int uinput_exit();
int send_event(uint16_t type, uint16_t code, int32_t value);
int send_report();
int send_rel_mouse(int32_t x, int32_t y);
int send_abs_mouse(int32_t x, int32_t y);

#endif
