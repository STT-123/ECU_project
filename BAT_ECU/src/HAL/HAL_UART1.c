#include "HAL_UART1.h"
#include "DRV/LOG/Drv_ZLog.h"
#include "HAL/HAL_TIM1.h"

int HAL_open_port(int uart_num)
{
	// struct  sigaction sa;
	int portfd;
	static struct termios newtios, oldtios; /*termianal settings */

	char portname[20]; //={"/dev/ttyS6", "/dev/ttyS9"};

	sprintf(portname, "/dev/ttyS%d", uart_num);

	zlog_info(debug_out, "opening serial port:%s\n", portname);
	/*open serial port */
	if ((portfd = open(portname, O_RDWR | O_NOCTTY)) < 0)
	{
		zlog_info(debug_out, "open serial port %s fail \n ", portname);
		return portfd;
	}
	else
	{
		zlog_info(debug_out, "open serial port %s success \n ", portname);
	}
	/*get serial port parnms,save away */
	tcgetattr(portfd, &newtios);
	memcpy(&oldtios, &newtios, sizeof newtios);
	/* configure new values */
	cfmakeraw(&newtios);	   /*see man page */
	newtios.c_iflag |= IGNPAR; /*ignore parity on input */
	newtios.c_oflag &= ~(OPOST | ONLCR | OLCUC | OCRNL | ONOCR | ONLRET | OFILL);
	newtios.c_cflag = CS8 | CLOCAL | CREAD;
	//	newtios.c_cc[VMIN]=1; /* block until 1 char received */
	//	newtios.c_cc[VTIME]=0; /*no inter-character timer */

	//	newtios.c_cc[VMIN] = 64; /* block until 1 char received */
	//	newtios.c_cc[VTIME] = 5; /*no inter-character timer */

	newtios.c_cc[VMIN] = 1;	  /* block until 1 char received */
	newtios.c_cc[VTIME] = 64; /*no inter-character timer  1S */

	zlog_info(debug_out, "uar%d  %d c_iflag:0x%02X; c_oflag:0x%02X; c_cflog:0x%02X\r\n", uart_num, portfd, newtios.c_iflag, newtios.c_oflag, newtios.c_cflag);
	/* 115200 bps */
	cfsetospeed(&newtios, B115200);
	cfsetispeed(&newtios, B115200);
	// zlog_info(debug_out,"0x%x 0x%x 0x%x 0x%x \n",B115200,sizeof(newtios),(NCCS),sizeof(newtios.c_iflag));
	/* register cleanup stuff */
	/*	atexit(reset_tty_atexit);  */
	/*	memset(&sa,0,sizeof sa);*/
	/*	sa.sa_handler = reset_tty_handler;*/
	/*	sigaction(SIGHUP,&sa,NULL);*/
	/*	sigaction(SIGINT,&sa,NULL);*/
	/*	sigaction(SIGPIPE,&sa,NULL);*/
	/*	sigaction(SIGTERM,&sa,NULL);*/
	/*apply modified termios */
	// saved_portfd=portfd;
	tcflush(portfd, TCIFLUSH);
	tcsetattr(portfd, TCSADRAIN, &newtios);
	return portfd;
}