#define _GNU_SOURCE
#include <ncursesw/ncurses.h>
#include <math.h>
//#include <wchar.h>
//#include <string.h>
#include "face.h"
#include "port.h"

float Bm, g, Hg, U1min, U2, Kt, I1, I1ef, I2, I2ef, Le, Hm, IW, f, J, ko, Pu;
float ScSo, Sc, So, ew, w1, w2;
const float mo = 4 * M_PI * 1e-7;
int mod;
int inp;

int main(int argc, char *argv[])
{


mwin_init();

mod=0;

while ( mod < 100 )
{
	wrefr();
    if ( mod == 0)
	{
		if (inp == KEY_F(12) )
		{
			mod=100;
		}
		
	}

	////////////////////////////////////
	inp=getch();
	


}

/*    
move (10, 20);

//getyx(10,10);


	curs_set(2);
	printw ("Bm=\t");
//    refresh();
	scanw ("%f", &Bm);
	move (11,20);
	printw ("g=\t");
//    refresh();
	scanw ("%f", &g);
//	curs_set(0);
	Hg = Bm /mo;
	move (11,30);
	printw ("Hg=\t%8.4f", Hg);
	refresh();
	move (12,20);
	printw ("Le=\t");
	scanw ("%f", &Le);
	move (13,20);
	printw ("Hm=\t");
	scanw ("%f", &Hm);

	move (15,25);
	IW = Hg * g * 1e-3 + Hm * 1e-3 * Le;
	printw ("IW=\t%3.1f", IW);
	
	
	move (18,25);    
    printw("The End!");

//    attroff(A_BOLD);
*/
mwin_out();
}
