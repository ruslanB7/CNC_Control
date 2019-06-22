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
		if ((x ==14 )  || (x == (mx-15)) )
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
	move (1,14);
	echochar(0x400059);
	move (1,mx-15);
	echochar(0x400059);
	move (1,mx-1);
	echochar(0x400059);
	move (2,0);
	echochar(0x400046);
	for (x=1; x < (mx-1); x++)
	{
		if ((x ==14 )  || (x == (mx-15)) )
		{
			echochar(0x400048);
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
//	qpltab(5,5);
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
	for (pty=0; pty<16; pty++)
	{
		for (ptx=0; ptx<8; ptx++)
		{
			
			
			
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

    move (1,mx-11);
    strftime(a,50,"%H:%M:%S",tim);
    attron(COLOR_PAIR(pair2));
    printw("%s",a);
///////////
	//char pathf[]="/sys/class/power_supply/BAT0/capasity";
	fl = fopen( "/sys/class/power_supply/BAT0/capacity", "r");
    if ( fl != 0 )
	{
		fscanf (fl, "%s", cap);
		move (1, 4);
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


	refresh();


}
