/*
 * main.c
 *
 *  Created on: 25 жовт. 2018 р.
 *      Author: ruslan
 */
#include <stdio.h>
#include <string.h>

#include <math.h>

#include <fcntl.h>   /* File Control Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h>  /* UNIX Standard Definitions 	   */
#include <errno.h> /* ERROR Number Definitions           */
#include "communication.h"


request_t request;//6
response_t  response;//7
uint8_t in_buf[16], out_buf[16];


int main (void)
{
	int comand, value, bk;//, sat
	int fd;
	int st, pr, stp, bt;//
	unsigned char chr[128], chr2, rq[16];//, chr3[10]
	printf ("open port \n");
	fd=open ("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NONBLOCK);
	//fcntl(fd, F_SETFL,0);
	printf ("op=%i\n", fd);
	/*---------- Setting the Attributes of the serial port using termios structure --------- */
		
	struct termios SerialPortSettings;	/* Create the structure                          */

	tcgetattr(fd, &SerialPortSettings);	/* Get the current attributes of the Serial port */

	cfsetispeed(&SerialPortSettings,B9600); /* Set Read  Speed as 9600                       */
	cfsetospeed(&SerialPortSettings,B9600); /* Set Write Speed as 9600                       */

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
		printf("\n  ERROR ! in Setting attributes");
		return 0;
	}
	else
	{
		printf("ok\n");
	}

	tcflush(fd, TCIFLUSH);

	st=0; pr=0;

	while (1)
	{
		printf ("input num comand -");
		scanf ("%d", &comand);
		printf ("input value - ");
		scanf ("%d", &value);

		request.address=0x03;
		request.command=comand;
		request.value=value;
		request_to_array(&request, out_buf);

		bk=write (fd, &out_buf, sizeof(request_t));
		//sleep(2);
		if (bk > 0)
		{
			printf ( "send %d byte\n", bk);
		}
		else
		{
			printf ("error!!!!");
		}
		chr2=0;
		//stp=0;
		while ( ( chr2 != 'q') && (chr2 != 'a'))
		{
			//usleep (100);
			bk=1;
			while ( bk > 0 )
			{
				//usleep (100);
				//stp++;
				bk=read(fd, &chr[st], 1 );
				if (bk>0)
				{
//					printf ( " %#x", chr[st]);
//					if (st<128)
//					{
						st++;
						if (st > 127) st-=128;
//					}
//					else
//					{
//						st=0;
//					}
//					stp=0;
				}

			}
//			if (stp >= 200)
//			{
//				printf ("\nempty\n");
//			}
//			else
//			{
//				printf ( "\n");
//			}

			if (st >= pr)
			{
				bt=st-pr;
			}
			else
			{
				bt=128+st-pr;
			}

			if (bt>5)
			{
//				for (stp=0; stp<=bt; stp++)
//				{
//					printf ( " \t%#x", pr+stp);
//				}
//				printf ( "\n");
				for (stp=0; stp<bt; stp++)
				{
					rq[stp]=chr[pr+stp];
					//printf ( " \t%#x", chr[pr+stp]);
				}
				//printf ( "\n");
				array_to_request(&request, rq);
				if (request.crc16 == (LiczCRC2((uint8_t *)&request, sizeof(request_t) - 2)) )
				{
					printf ("\trequest...\n");
					printf ("CRC - OK\n");
					printf ("adr = \t%#X\n", (unsigned int)request.address );
					printf ("com = \t%d\n", (unsigned int)request.command );
//					printf ("val = %#X\n", (unsigned int)request.value );
//
//					printf ("adr = %d\n", (unsigned int)request.address );
//					printf ("com = %d\n", (unsigned int)request.command );
					printf ("val = \t%d\n", (unsigned int)request.value );
					printf (" ----------------- \n");
					pr+=6;
					if (pr>127)
					{
						pr -=128;
					}
				}
				//printf ("CRC - \t%#X\n", LiczCRC2((uint8_t *)&request, sizeof(request_t) - 2)) ;
			}

			if (st >= pr)
			{
				bt=st-pr;
			}
			else
			{
				bt=128+st-pr;
			}

			if (bt > 6)
			{
//				for (stp=0; stp<=bt; stp++)
//				{
//					printf ( " \t%#x", pr+stp);
//				}
//				printf ( "\n");
				for (stp=0; stp<bt; stp++)
				{
					rq[stp]=chr[pr+stp];
					//printf ( " \t%#x2", chr[pr+stp]);
				}
				//printf ( "\n");
				array_to_response(&response, rq);
				if (response.crc16 == (LiczCRC2((uint8_t *)&response, sizeof(response_t) - 2)) )
				{
					printf ("\tresponse..\n");
					printf ("CRC - OK\n");
					printf ("adr = \t%#X\n", (unsigned int)response.address );
					printf ("com = \t%d\n", (unsigned int)response.command );
					printf ("stat= \t%d\n", (unsigned int)response.status_w );
					printf ("val = \t%d\n", (unsigned int)response.value );
					printf (" ----------------- \n");
					pr+=7;
				}
				else
				{
					pr++;

				}
				//printf ("CRC - \t%#X\n", LiczCRC2((uint8_t *)&response, sizeof(response_t) - 2));
				if (pr>127)
				{
					pr -=128;
				}
			}



//			printf ("st-%d\n",  st );
//			printf ("st-%d\n",  pr );
			printf ("bt-%d\n",  bt );

			chr2=getchar();
			//scanf ("%c", &chr2 );
			//printf ("%c",  chr2 );
			if (chr2 == 'q')
			{
				close (fd);
				printf ( "close\n");
				return 0;
			}



		}





		//sleep (2);

	}

}


