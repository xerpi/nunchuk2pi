/* by xerpi (c) 2013 */

#include "uinput.h"

static struct uinput_user_dev  ui_dev;
static struct input_event      ui_ev;
static int                     ui_fd;
static int                     ui_initiated = 0;

#define send_key_macro(x) \
    inline int send_key_##x(uint16_t key) {  \
        return send_event(EV_KEY, key, x);   \
    }
    
#define uinput_return_not_initiated() \
	if(!ui_initiated) {    \
		return -2;             \
	}


send_key_macro(press);
send_key_macro(release);
send_key_macro(autorepeat);

static int uinput_open_fd()
{
    if((ui_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK)) < 0) {
        if((ui_fd = open("/dev/input/uinput", O_WRONLY | O_NONBLOCK)) >= 0) {
            return 1;
        }
        return -1;
    }
    return 1;
}

int uinput_init()
{
	if(ui_initiated) {
		return 2;
	}
	
	if(uinput_open_fd() < 0) {
        printf("Unable to open uinput.\n");
        return -1;
    }

    //usleep(100);

    memset(&ui_ev,  0, sizeof(ui_ev));
    memset(&ui_dev, 0, sizeof(ui_dev));

    strncpy(ui_dev.name, "uinput-nunchuk2pi", UINPUT_MAX_NAME_SIZE);
    ui_dev.id.bustype = BUS_USB;
    ui_dev.id.vendor  = 0x1234;
    ui_dev.id.product = 0xABCD;
    ui_dev.id.version = 1;

    ioctl(ui_fd, UI_SET_EVBIT,  EV_KEY);
    ioctl(ui_fd, UI_SET_EVBIT,  EV_REP);
	
	int i;
    for(i = 0; i < KEY_MAX; i++) {
        ioctl(ui_fd, UI_SET_KEYBIT, i);
    }

    ioctl(ui_fd, UI_SET_EVBIT, EV_REL);
    ioctl(ui_fd, UI_SET_RELBIT, REL_X);
    ioctl(ui_fd, UI_SET_RELBIT, REL_Y);

    write(ui_fd, &ui_dev, sizeof(ui_dev));
    ioctl(ui_fd, UI_DEV_CREATE);

    //usleep(100);
    
    ui_initiated = 1;
    
    return 1;	
}

int uinput_exit()
{
	uinput_return_not_initiated();
	
	ioctl(ui_fd, UI_DEV_DESTROY);
	close(ui_fd);
	ui_initiated = 0;
	return 1;
}

int send_event(uint16_t type, uint16_t code, int32_t value)
{
	uinput_return_not_initiated();
	
    gettimeofday(&ui_ev.time, NULL);
    ui_ev.type = type;
    ui_ev.code = code;
    ui_ev.value = value;
    return write(ui_fd, &ui_ev, sizeof(ui_ev));
}

int send_report()
{
	uinput_return_not_initiated();
	
    return send_event(EV_SYN, SYN_REPORT, 0);
}

int send_rel_mouse(int32_t x, int32_t y)
{
	uinput_return_not_initiated();
	
    int ret;
    ret =  send_event(EV_REL, REL_X, x);
    ret += send_event(EV_REL, REL_Y, y);
    return ret;
}

int send_abs_mouse(int32_t x, int32_t y)
{
	uinput_return_not_initiated();
	
    int ret;
    ret =  send_event(EV_ABS, ABS_X, x);
    ret += send_event(EV_ABS, ABS_Y, y);
    return ret;
}
