#define _GNU_SOURCE
#include <ncursesw/ncurses.h>
#include <locale.h>
#include <math.h>
#include <wchar.h>
#include <string.h>
#include <time.h>
#include <stdio.h>	//for fopen
#include "face.h"

#define pair1 1
#define pair2 2
#define pair3 3

struct tm *tim;
time_t ntim;
char a[50];
int mx, my, x;


void mwin_init (void)
{

	setlocale(LC_ALL, "en_US.UTF-8");
	WINDOW *stdscr = initscr();
	getmaxyx(stdscr, my, mx);
	
	raw();
	keypad(stdscr, TRUE);
	halfdelay(1);
	curs_set(0);
	start_color();

	init_pair(pair1, COLOR_BLACK, COLOR_WHITE);
	init_pair(pair2, COLOR_GREEN, COLOR_WHITE);
	init_pair(pair3, COLOR_RED, COLOR_WHITE);

	attron(COLOR_PAIR(pair1));
	bkgdset (COLOR_PAIR(pair1));
	clear();
	refresh();
//attron(A_BOLD);
	move (0,0);
	echochar(0x400043);
	for (x=1; x < (mx-1); x++)
	{
		if ((x == 9 )  || (x == (mx-12)) )
		{
			echochar(0x400049);
		}
		else
		{
			echochar(0x400052);
		}
	}
	echochar(0x400042);
	move (1,0);
	echochar(0x400059);
	move (1,9);
	echochar(0x400059);
	move (1,mx-12);
	echochar(0x400059);
	move (1,mx-1);
	echochar(0x400059);
	move (2,0);
	echochar(0x400046);
	for (x=1; x < (mx-1); x++)
	{
		if (x == 9 ) 
		{
			echochar(0x400048);
		}
		else if (x==(mx-12)) 
		{
			echochar(0x400045);
		}
		else if ( (x==(mx-32)) || (x==(mx-22)) )
		{
			echochar(0x400049);
		}
		else
		{
			echochar(0x400052);
		}
	}
	echochar(0x400047);
//attron(COLOR_PAIR(2));
	for (x=3; x < (my-2); x++)
	{
		move (x,0);
		echochar(0x400059);
		move (x,mx-1);
		echochar(0x400059);
	}
	move (my-2,0);
	echochar(0x400044);
	for (x=1; x < (mx-1); x++)
	{
		echochar(0x400052);
	}
	echochar(0x400041);






	move (3,mx-32);
	echochar(0x400059);
	for (x=mx-31; x < (mx-1); x++)
	{
		if (x == (mx-22) ) 
		{
			echochar(0x400059);
		}
		else if (x==(mx-12)) 
		{
			echochar(0x400059);
		}
		else
		{
			echochar(0x20);
		}
	}

	move (4,mx-32);
	echochar(0x400046);
	for (x=mx-31; x < (mx-1); x++)
	{
		if (x == (mx-22) ) 
		{
			echochar(0x400045);
		}
		else if (x==(mx-12)) 
		{
			echochar(0x400045);
		}
		else
		{
			echochar(0x400052);
		}
	}
	echochar(0x400047);


	move (5,mx-32);
	echochar(0x400059);
	for (x=mx-31; x < (mx-1); x++)
	{
		if (x == (mx-22) ) 
		{
			echochar(0x400059);
		}
		else if (x==(mx-12)) 
		{
			echochar(0x400059);
		}
		else
		{
			echochar(0x20);
		}
	}

	move (6,mx-32);
	echochar(0x400046);
	for (x=mx-31; x < (mx-1); x++)
	{
		if (x == (mx-22) ) 
		{
			echochar(0x400045);
		}
		else if (x==(mx-12)) 
		{
			echochar(0x400045);
		}
		else
		{
			echochar(0x400052);
		}
	}
	echochar(0x400047);


	move (7,mx-32);
	echochar(0x400059);
	for (x=mx-31; x < (mx-1); x++)
	{
		if (x == (mx-22) ) 
		{
			echochar(0x400059);
		}
		else if (x==(mx-12)) 
		{
			echochar(0x400059);
		}
		else
		{
			echochar(0x20);
		}
	}

	move (8,mx-32);
	echochar(0x400044);
	for (x=mx-31; x < (mx-1); x++)
	{
		if (x == (mx-22) ) 
		{
			echochar(0x400048);
		}
		else if (x==(mx-12)) 
		{
			echochar(0x400048);
		}
		else
		{
			echochar(0x400052);
		}
	}
	echochar(0x400047);



	move (3,mx-27);
	printw("%c",'X');
	move (3,mx-17);
	printw("%c",'Y');
	move (3,mx-6);
	printw("%c",'Z');









	pltab(10,5);
//	move (1,3);
//	printw ("y=%d x=%d", my, mx);
	refresh();
//	ntim=time(NULL);
//	tim=localtime(&ntim);


	refresh();
}

//    getch();
void mwin_out (void)
{
    endwin();
}
void pltab (int py, int px)
{
	int ptx, pty;
	for (pty=0; pty<4; pty++)
	{
		for (ptx=0; ptx<16; ptx++)
		{
			move(pty+py, ptx*2+px);
			echochar(0x400040+(ptx+pty*16));
			
			
		}
	}


}


void wrefr (void)
{
	FILE *fl;
	char cap[15];
	ntim=time(NULL);
	tim=localtime(&ntim);
//    move (7,7);
//    printw("ttttt=%d", ntim);
//    printw(asctime(tim));
//    move (8,7);
//    printw("%d:%d:%d", tim->tm_hour, tim->tm_min, tim->tm_sec);

    move (1,mx-10);
    strftime(a,50,"%H:%M:%S",tim);
    attron(COLOR_PAIR(pair2));
    printw("%s",a);
///////////
	//char pathf[]="/sys/class/power_supply/BAT0/capasity";
	fl = fopen( "/sys/class/power_supply/BAT0/capacity", "r");
    if ( fl != 0 )
	{
		fscanf (fl, "%s", cap);
		move (1,3);
		attron(COLOR_PAIR(pair1));
		printw ("%s%% ", cap);
		fclose(fl);
	}
	else
	{
		//move (1,108);
		//attron(COLOR_PAIR(pair3));
		//printw ("%s","err");
	}

	move (5,mx-30);
	printw("%3.3f",123.4567);
	move (5,mx-20);
	printw("%3.3f",123.4567);
	move (5,mx-9);
	printw("%3.3f",123.4567);

	move (7,mx-30);
	printw("%3.3f",123.4567);
	move (7,mx-20);
	printw("%3.3f",123.4567);
	move (7,mx-9);
	printw("%3.3f",123.4567);


	refresh();


}
