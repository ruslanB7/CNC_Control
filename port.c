#include <stdio.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>   /* File Control Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h>  /* UNIX Standard Definitions          */
#include <errno.h>   /* ERROR Number Definitions           */
#include "port.h"


char in_buf[1024];
int posin, posout;
int fd;

int port_init (void)
{


	fd=open ("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NONBLOCK);
	/*---------- Setting the Attributes of the serial port using termios structure --------- */
	if (fd < 0)
	{
		return 0x10;
	}
	struct termios SerialPortSettings;	/* Create the structure      */

	tcgetattr(fd, &SerialPortSettings);	/* Get the current attributes of the Serial port */

	cfsetispeed(&SerialPortSettings,B115200); /* Set Read  Speed as  */
	cfsetospeed(&SerialPortSettings,B115200); /* Set Write Speed as   */

	//SerialPortSettings.c_cflag=0;
	SerialPortSettings.c_cflag &= ~PARENB;   /* Disables the Parity Enable bit(PARENB),So No Parity   */
	SerialPortSettings.c_cflag &= ~CSTOPB;   /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
	SerialPortSettings.c_cflag &= ~CSIZE;	 /* Clears the mask for setting the data size             */
	SerialPortSettings.c_cflag |=  CS8;      /* Set the data bits = 8                                 */

	SerialPortSettings.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
	SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */


	SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY | INLCR | ICRNL); /*  <<<<<<<< &~ Disable XON/XOFF flow control both i/p and o/p */
//	SerialPortSettings.c_iflag |= (INLCR );
	SerialPortSettings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  /* Non Cannonical mode                            */

	SerialPortSettings.c_oflag &= ~OPOST;/*No Output Processing*/
	SerialPortSettings.c_cc[VMIN] = 16; /* Read at least 10 characters */
	SerialPortSettings.c_cc[VTIME] = 0; /* Wait indefinetly   */ //no pause breack

	if((tcsetattr(fd,TCSANOW,&SerialPortSettings)) != 0) /* Set the attributes to the termios structure*/
	{
		return 0x20;
	}


	tcflush(fd, TCIFLUSH);

	posin=0;
	posout=0;

	return 0;
}

int send_port (char * str, int nchr)
{
	int bk;
	bk=write (fd, str, nchr);
	if (bk == nchr)
	{
		return 0;
	}
	else
	{
		return 0x10;
	}
}

int read_port (char * str, int * nbyt)
{
	int bk, postm;
	char inchr;


	bk=1;
	while ( bk > 0 )
	{
		bk=read(fd, &inchr, 1 );
		if (bk>0)
		{
			in_buf[posin]=inchr;
			if (posin < 1023)
			{
				posin++;
			}
			else
			{
				posin=0;
			}
		}
	}

	bk=1;
	while ( bk > 0 )
	{
		if (in_buf[posout] < ' ')
		{
			if (posout != posin)
			{
				bk=1;
				if (posout < 1023)
				{
					posout++;
				}
				else
				{
					posout=0;
				}
			}
			else
			{
				bk=0;
			}
		}
		else
		{
			bk=0;
		}
	}


	if (posin != posout)
	{
		postm=posout;
		bk=1;
		*nbyt=0;
		while ( (bk > 0) && (posin != postm) )
		{
			*str=in_buf[postm];
			*nbyt++;
			if ( (in_buf[postm]==0x0a) || (in_buf[postm]==0x0d) )
			{
				bk=0;
			}
			if (postm < 1023)
			{
				postm++;
			}
			else
			{
				postm=0;
			}
		}

		if (bk==0)
		{
			posout=postm;
			bk=*nbyt;
			return bk;
		}
		else
		{
			return 0;
		}

	}
	else
	{
		return 0;
	}
	return 0;

}
////

int close_port (void)
{
	close (fd);
	return 0;
}







