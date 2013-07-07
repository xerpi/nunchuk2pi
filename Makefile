TARGET = n2pi
SOURCE = nunchuk2pi.c uinput.c nunchuk.c
CC     = gcc
LIB    = -lpthread

all:
	$(CC) -o $(TARGET) $(SOURCE) $(LIB)
	
clean:
	rm $(TARGET)

