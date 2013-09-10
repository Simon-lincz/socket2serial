#include "serial_module.h"

static struct termios termios_old,termios_new;

//设置串口通信速率
int _BaudRate(int baudrate)
{
	switch(baudrate)
	{
		case B2400:
		return (2400);
		case B4800:
		return (4800);
		case B9600:
		return (9600);
		case B19200:
		return (19200);
		case B38400:
		return (38400);
		case B57600:
		return (57600);
		case B115200:
		return (115200);
		default:
		return (9600);
	}
}

int BaudRate( int baudrate)
{
switch(baudrate)
{
case 0:
return (B2400);
case 1:
return (B4800);
case 2:
return (B9600);
case 3:
return (B19200);
case 4:
return (B38400);
case 5:
return (B57600);
case 6:
return (B115200);
default:
return (B9600);
}
}



// 设置串口数据位，停止位，奇偶校验位，速度，超时设置等参数
int setPara(int serialfd,int speed,int databits , int stopbits ,int parity )
{
	bzero( &termios_new, sizeof(termios_new));
	cfmakeraw(&termios_new);
	termios_new.c_cflag=BaudRate(speed);
	termios_new.c_cflag |= CLOCAL | CREAD;
	termios_new.c_cflag &= ~CSIZE;
	switch (databits) //设置数据位
	{
		case 0:
			termios_new.c_cflag |= CS8;
		break;
		case 1:
			termios_new.c_cflag |= CS7;
		break;	
		case 2:
			termios_new.c_cflag |= CS6;
		break;
		case 3:
			termios_new.c_cflag |= CS5;
		break;	
		default:
			termios_new.c_cflag |= CS8;
		break;	
	}

	switch (parity) //设置奇偶位	
	{
		case 0: //as no parity
			termios_new.c_cflag &= ~PARENB; //Clear parity enable 
		break;	
		case 1:	
			termios_new.c_cflag |= PARENB; // Enable parity 
			termios_new.c_cflag &= ~PARODD; 
		break;
		case 2:	
			termios_new.c_cflag |= PARENB; 
			termios_new.c_cflag |= ~PARODD;
		break;	
		default:
			termios_new.c_cflag &= ~PARENB; // Clear parity enable 
		break;	
	}
	switch (stopbits)// set Stop Bit
	{
		case 0:
			termios_new.c_cflag &= ~CSTOPB;
		break;
		case 1:
			termios_new.c_cflag |= CSTOPB;
		break;
		default:
			termios_new.c_cflag &= ~CSTOPB;
		break;	
	}
	tcflush(serialfd,TCIFLUSH); // Update the termios_new and do it NOW 
	termios_new.c_cc[VTIME] = 1; /* unit: 1/10 second. */
	termios_new.c_cc[VMIN] = 1; /* minimal characters for reading */
	tcflush (serialfd, TCIFLUSH);
	return tcsetattr(serialfd,TCSANOW,&termios_new);
} 

int nwrite (int serialfd, const char *data, int datalength )
{
	int len = 0, total_len = 0;//modify8.8
	for (total_len = 0 ; total_len < datalength;) 
	{
		len = 0;
		len = write(serialfd, &data[total_len], datalength - total_len);
		if (len > 0) 
			total_len += len; 
	}
	return (total_len);
}

int GetBaudRate()
{
	return (_BaudRate(cfgetospeed(&termios_new)));
}

void closePort(int serialfd)
{
	tcsetattr (serialfd, TCSADRAIN, &termios_old);
	close (serialfd);
}

int openPort(int index)
{
	char *device;
	switch(index)
	{
		case 0:
			device="/dev/ttyUSB0";
		break;	
		case 1:
			device="/dev/ttyS0";
		//break;
		default:
		break;
	}
	int fd=open( device, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if ( fd<0)
	{ 
		return -1;
	}
	tcgetattr(fd , &termios_old);
	return fd;
}
