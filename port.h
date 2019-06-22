

#ifndef _porth_
#define _porth_

int port_init (void);
int send_port (char * str, int nchr);
int read_port (char * str, int * nbyt);
int close_port (void);







#endif
