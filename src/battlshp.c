/* WizBattleship */
static char version[12] = { "Version 0.1" };
/* Copyright (C) Christopher J. Daniel 2002-2004
   You may use the code contained herein for any purpose you deem necessary,
   commercial or noncommercial, as long as the author(s) are given due credit. */

#include <oz.h>
#include "arrays.c"

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

#define EMPTY 0      /* A */
#define HIT 1	     /* B */
#define MISS 2	     /* C */

#define VTNEND 3     /* D */
#define VTNENDHIT 4  /* E */
#define VTSEND 5     /* F */
#define VTSENDHIT 6  /* G */
#define VTMID 7      /* H */
#define VTMIDHIT 8   /* I */

#define HRWEND 9     /* J */
#define HRWENDHIT 10 /* K */
#define HREEND 11    /* L */
#define HREENDHIT 12 /* M */
#define HRMID 13     /* N */
#define HRMIDHIT 14  /* O */

int x=0;
int i=0;
int b=0;
int start=0;
int gametype=0;
int currentplayer=1;
int eins, zwei, drei=0;
int hit=0;
int end=0;

byte tempx=0;
byte tempy=0;
byte tempdir=0;

clearside()
{
	ozfilledbox(162,0,76,80,WHITE);
}

drawscreen()
{
	_ozvline(9,0,80,BLACK);
	_ozhline(0,9,81,BLACK);
	_ozvline(90,0,80,BLACK);
	_ozhline(81,9,81,BLACK);
	for(i=0;i<=sizeof(screendata)/2;i+=2)
	{
		ozpoint(screendata[i],screendata[i+1],BLACK);
	}
	for(i=0;i<=sizeof(screendata)/2;i+=2)
	{
		ozpoint((screendata[i]+81),screendata[i+1],BLACK);
	}
	switch(currentplayer)
	{
		case 1: grid1=&grid1_1[0][0]; grid2=&grid1_2[0][0]; break;
		case 2: grid1=&grid2_1[0][0]; grid2=&grid2_2[0][0]; break;
	}
	ozsetfontpointer(shipfont_data);
	for(eins=0,zwei=0,drei=0;eins<100;eins++,drei++)
	{
		if(drei==10)
		{
			zwei++;
			drei=0;
		}
		switch(*(grid1+zwei*10+drei))
		{
			case EMPTY:	ozputs(grid1coor[drei],grid1coor[zwei],"A"); break;
			case HIT:	ozputs(grid1coor[drei],grid1coor[zwei],"B"); break;
			case MISS:	ozputs(grid1coor[drei],grid1coor[zwei],"C"); break;
			case VTNEND:	ozputs(grid1coor[drei],grid1coor[zwei],"D"); break;
			case VTNENDHIT: ozputs(grid1coor[drei],grid1coor[zwei],"E"); break;
			case VTSEND:	ozputs(grid1coor[drei],grid1coor[zwei],"F"); break;
			case VTSENDHIT: ozputs(grid1coor[drei],grid1coor[zwei],"G"); break;
			case VTMID:	ozputs(grid1coor[drei],grid1coor[zwei],"H"); break;
			case VTMIDHIT:	ozputs(grid1coor[drei],grid1coor[zwei],"I"); break;
			case HRWEND:	ozputs(grid1coor[drei],grid1coor[zwei],"J"); break;
			case HRWENDHIT: ozputs(grid1coor[drei],grid1coor[zwei],"K"); break;
			case HREEND:	ozputs(grid1coor[drei],grid1coor[zwei],"L"); break;
			case HREENDHIT: ozputs(grid1coor[drei],grid1coor[zwei],"M"); break;
			case HRMID:	ozputs(grid1coor[drei],grid1coor[zwei],"N"); break;
			case HRMIDHIT:	ozputs(grid1coor[drei],grid1coor[zwei],"O"); break;
		}
	}
	for(eins=0,zwei=0,drei=0;eins<100;eins++,drei++)
	{
		if(drei==10)
		{
			zwei++;
			drei=0;
		}
		switch(*(grid2+zwei*10+drei))
		{
			case EMPTY: ozputs(grid2xcoor[drei],grid1coor[zwei],"A"); break;
			case HIT:   ozputs(grid2xcoor[drei],grid1coor[zwei],"B"); break;
			case MISS:  ozputs(grid2xcoor[drei],grid1coor[zwei],"C"); break;
		}
	}
	ozsetfont(FONT_OZ_NORMAL);
}

int drawbattleship(int xcoor, int ycoor, int restdir)
{
	switch(restdir)
	{
		case NORTH:
		{
			if((ycoor-3)<0) return -1;
			if(*(grid1+(ycoor)*10+xcoor)!=0|*(grid1+(ycoor-1)*10+xcoor)!=0|*(grid1+(ycoor-2)*10+xcoor)!=0|*(grid1+(ycoor-3)*10+xcoor)!=0) return -1;
			*(grid1+(ycoor)*10+xcoor)=VTSEND;
			*(grid1+(ycoor-1)*10+xcoor)=VTMID;
			*(grid1+(ycoor-2)*10+xcoor)=VTMID;
			*(grid1+(ycoor-3)*10+xcoor)=VTNEND;
			*(shipgrid+(ycoor)*10+xcoor)=1;
			*(shipgrid+(ycoor-1)*10+xcoor)=1;
			*(shipgrid+(ycoor-2)*10+xcoor)=1;
			*(shipgrid+(ycoor-3)*10+xcoor)=1;
			break;
		}
		case SOUTH:
		{
			if((ycoor+3)>9) return -1;
			if(*(grid1+(ycoor)*10+xcoor)!=0|*(grid1+(ycoor+1)*10+xcoor)!=0|*(grid1+(ycoor+2)*10+xcoor)!=0|*(grid1+(ycoor+3)*10+xcoor)!=0) return -1;
			*(grid1+(ycoor)*10+xcoor)=VTNEND;
			*(grid1+(ycoor+1)*10+xcoor)=VTMID;
			*(grid1+(ycoor+2)*10+xcoor)=VTMID;
			*(grid1+(ycoor+3)*10+xcoor)=VTSEND;
			*(shipgrid+(ycoor)*10+xcoor)=1;
			*(shipgrid+(ycoor+1)*10+xcoor)=1;
			*(shipgrid+(ycoor+2)*10+xcoor)=1;
			*(shipgrid+(ycoor+3)*10+xcoor)=1;
			break;
		}
		case EAST:
		{
			if((xcoor+3)>9) return -1;
			if(*(grid1+(ycoor)*10+xcoor)!=0|*(grid1+(ycoor)*10+xcoor+1)!=0|*(grid1+(ycoor)*10+xcoor+2)!=0|*(grid1+(ycoor)*10+xcoor+3)!=0) return -1;
			*(grid1+(ycoor)*10+xcoor)=HRWEND;
			*(grid1+(ycoor)*10+xcoor+1)=HRMID;
			*(grid1+(ycoor)*10+xcoor+2)=HRMID;
			*(grid1+(ycoor)*10+xcoor+3)=HREEND;
			*(shipgrid+(ycoor)*10+xcoor)=1;
			*(shipgrid+(ycoor)*10+xcoor+1)=1;
			*(shipgrid+(ycoor)*10+xcoor+2)=1;
			*(shipgrid+(ycoor)*10+xcoor+3)=1;
			break;
		}
		case WEST:
		{
			if((xcoor-3)<0) return -1;
			if(*(grid1+(ycoor)*10+xcoor)!=0|*(grid1+(ycoor)*10+xcoor-1)!=0|*(grid1+(ycoor)*10+xcoor-2)!=0|*(grid1+(ycoor)*10+xcoor-3)!=0) return -1;
			*(grid1+(ycoor)*10+xcoor)=HREEND;
			*(grid1+(ycoor)*10+xcoor-1)=HRMID;
			*(grid1+(ycoor)*10+xcoor-2)=HRMID;
			*(grid1+(ycoor)*10+xcoor-3)=HRWEND;
			*(shipgrid+(ycoor)*10+xcoor)=1;
			*(shipgrid+(ycoor)*10+xcoor-1)=1;
			*(shipgrid+(ycoor)*10+xcoor-2)=1;
			*(shipgrid+(ycoor)*10+xcoor-3)=1;
			break;
		}
	}
	return 1;
}

int drawcarrier(int xcoor, int ycoor, int restdir)
{
	switch(restdir)
	{
		case NORTH:
		{
			if((ycoor-4)<0) return -1;
			if(*(grid1+(ycoor)*10+xcoor)!=0|*(grid1+(ycoor-1)*10+xcoor)!=0|*(grid1+(ycoor-2)*10+xcoor)!=0|*(grid1+(ycoor-3)*10+xcoor)!=0|*(grid1+(ycoor-4)*10+xcoor)!=0) return -1;
			*(grid1+(ycoor)*10+xcoor)=VTSEND;
			*(grid1+(ycoor-1)*10+xcoor)=VTMID;
			*(grid1+(ycoor-2)*10+xcoor)=VTMID;
			*(grid1+(ycoor-3)*10+xcoor)=VTMID;
			*(grid1+(ycoor-4)*10+xcoor)=VTNEND;
			*(shipgrid+(ycoor)*10+xcoor)=2;
			*(shipgrid+(ycoor-1)*10+xcoor)=2;
			*(shipgrid+(ycoor-2)*10+xcoor)=2;
			*(shipgrid+(ycoor-3)*10+xcoor)=2;
			*(shipgrid+(ycoor-4)*10+xcoor)=2;
			break;
		}
		case SOUTH:
		{
			if((ycoor+4)>9) return -1;
			if(*(grid1+(ycoor)*10+xcoor)!=0|*(grid1+(ycoor+1)*10+xcoor)!=0|*(grid1+(ycoor+2)*10+xcoor)!=0|*(grid1+(ycoor+3)*10+xcoor)!=0|*(grid1+(ycoor+4)*10+xcoor)!=0) return -1;
			*(grid1+(ycoor)*10+xcoor)=VTNEND;
			*(grid1+(ycoor+1)*10+xcoor)=VTMID;
			*(grid1+(ycoor+2)*10+xcoor)=VTMID;
			*(grid1+(ycoor+3)*10+xcoor)=VTMID;
			*(grid1+(ycoor+4)*10+xcoor)=VTSEND;
			*(shipgrid+(ycoor)*10+xcoor)=2;
			*(shipgrid+(ycoor+1)*10+xcoor)=2;
			*(shipgrid+(ycoor+2)*10+xcoor)=2;
			*(shipgrid+(ycoor+3)*10+xcoor)=2;
			*(shipgrid+(ycoor+4)*10+xcoor)=2;
			break;
		}
		case EAST:
		{
			if((xcoor+4)>9) return -1;
			if(*(grid1+(ycoor)*10+xcoor)!=0|*(grid1+(ycoor)*10+xcoor+1)!=0|*(grid1+(ycoor)*10+xcoor+2)!=0|*(grid1+(ycoor)*10+xcoor+3)!=0|*(grid1+(ycoor)*10+xcoor+4)!=0) return -1;
			*(grid1+(ycoor)*10+xcoor)=HRWEND;
			*(grid1+(ycoor)*10+xcoor+1)=HRMID;
			*(grid1+(ycoor)*10+xcoor+2)=HRMID;
			*(grid1+(ycoor)*10+xcoor+3)=HRMID;
			*(grid1+(ycoor)*10+xcoor+4)=HREEND;
			*(shipgrid+(ycoor)*10+xcoor)=2;
			*(shipgrid+(ycoor)*10+xcoor+1)=2;
			*(shipgrid+(ycoor)*10+xcoor+2)=2;
			*(shipgrid+(ycoor)*10+xcoor+3)=2;
			*(shipgrid+(ycoor)*10+xcoor+4)=2;
			break;
		}
		case WEST:
		{
			if((xcoor-4)<0) return -1;
			if(*(grid1+(ycoor)*10+xcoor)!=0|*(grid1+(ycoor)*10+xcoor-1)!=0|*(grid1+(ycoor)*10+xcoor-2)!=0|*(grid1+(ycoor)*10+xcoor-3)!=0|*(grid1+(ycoor)*10+xcoor-4)!=0) return -1;
			*(grid1+(ycoor)*10+xcoor)=HREEND;
			*(grid1+(ycoor)*10+xcoor-1)=HRMID;
			*(grid1+(ycoor)*10+xcoor-2)=HRMID;
			*(grid1+(ycoor)*10+xcoor-3)=HRMID;
			*(grid1+(ycoor)*10+xcoor-4)=HRWEND;
			*(shipgrid+(ycoor)*10+xcoor)=2;
			*(shipgrid+(ycoor)*10+xcoor-1)=2;
			*(shipgrid+(ycoor)*10+xcoor-2)=2;
			*(shipgrid+(ycoor)*10+xcoor-3)=2;
			*(shipgrid+(ycoor)*10+xcoor-4)=2;
			break;
		}
	}
	return 1;
}

int drawcrusub(int xcoor, int ycoor, int restdir)
{
	switch(restdir)
	{
		case NORTH:
		{
			if((ycoor-2)<0) return -1;
			if(*(grid1+(ycoor)*10+xcoor)!=0|*(grid1+(ycoor-1)*10+xcoor)!=0|*(grid1+(ycoor-2)*10+xcoor)!=0) return -1;
			*(grid1+(ycoor)*10+xcoor)=VTSEND;
			*(grid1+(ycoor-1)*10+xcoor)=VTMID;
			*(grid1+(ycoor-2)*10+xcoor)=VTNEND;
			*(shipgrid+(ycoor)*10+xcoor)=3;
			*(shipgrid+(ycoor-1)*10+xcoor)=3;
			*(shipgrid+(ycoor-2)*10+xcoor)=3;
			break;
		}
		case SOUTH:
		{
			if((ycoor+2)>9) return -1;
			if(*(grid1+(ycoor)*10+xcoor)!=0|*(grid1+(ycoor+1)*10+xcoor)!=0|*(grid1+(ycoor+2)*10+xcoor)!=0) return -1;
			*(grid1+(ycoor)*10+xcoor)=VTNEND;
			*(grid1+(ycoor+1)*10+xcoor)=VTMID;
			*(grid1+(ycoor+2)*10+xcoor)=VTSEND;
			*(shipgrid+(ycoor)*10+xcoor)=3;
			*(shipgrid+(ycoor+1)*10+xcoor)=3;
			*(shipgrid+(ycoor+2)*10+xcoor)=3;
			break;
		}
		case EAST:
		{
			if((xcoor+2)>9) return -1;
			if(*(grid1+(ycoor)*10+xcoor)!=0|*(grid1+(ycoor)*10+xcoor+1)!=0|*(grid1+(ycoor)*10+xcoor+2)!=0) return -1;
			*(grid1+(ycoor)*10+xcoor)=HRWEND;
			*(grid1+(ycoor)*10+xcoor+1)=HRMID;
			*(grid1+(ycoor)*10+xcoor+2)=HREEND;
			*(shipgrid+(ycoor)*10+xcoor)=3;
			*(shipgrid+(ycoor)*10+xcoor+1)=3;
			*(shipgrid+(ycoor)*10+xcoor+2)=3;
			break;
		}
		case WEST:
		{
			if((xcoor-2)<0) return -1;
			if(*(grid1+(ycoor)*10+xcoor)!=0|*(grid1+(ycoor)*10+xcoor-1)!=0|*(grid1+(ycoor)*10+xcoor-2)!=0) return -1;
			*(grid1+(ycoor)*10+xcoor)=HREEND;
			*(grid1+(ycoor)*10+xcoor-1)=HRMID;
			*(grid1+(ycoor)*10+xcoor-2)=HRWEND;
			*(shipgrid+(ycoor)*10+xcoor)=3;
			*(shipgrid+(ycoor)*10+xcoor-1)=3;
			*(shipgrid+(ycoor)*10+xcoor-2)=3;
			break;
		}
	}
	return 1;
}

int drawptboat(int xcoor, int ycoor, int restdir)
{
	switch(restdir)
	{
		case NORTH:
		{
			if((ycoor-1)<0) return -1;
			if(*(grid1+(ycoor)*10+xcoor)!=0|*(grid1+(ycoor-1)*10+xcoor)!=0) return -1;
			*(grid1+(ycoor)*10+xcoor)=VTSEND;
			*(grid1+(ycoor-1)*10+xcoor)=VTNEND;
			*(shipgrid+(ycoor)*10+xcoor)=4;
			*(shipgrid+(ycoor-1)*10+xcoor)=4;
			break;
		}
		case SOUTH:
		{
			if((ycoor+1)>9) return -1;
			if(*(grid1+(ycoor)*10+xcoor)!=0|*(grid1+(ycoor+1)*10+xcoor)!=0) return -1;
			*(grid1+(ycoor)*10+xcoor)=VTNEND;
			*(grid1+(ycoor+1)*10+xcoor)=VTSEND;
			*(shipgrid+(ycoor)*10+xcoor)=4;
			*(shipgrid+(ycoor+1)*10+xcoor)=4;
			break;
		}
		case EAST:
		{
			if((xcoor+1)>9) return -1;
			if(*(grid1+(ycoor)*10+xcoor)!=0|*(grid1+(ycoor)*10+xcoor+1)!=0) return -1;
			*(grid1+(ycoor)*10+xcoor)=HRWEND;
			*(grid1+(ycoor)*10+xcoor+1)=HREEND;
			*(shipgrid+(ycoor)*10+xcoor)=4;
			*(shipgrid+(ycoor)*10+xcoor+1)=4;
			break;
		}
		case WEST:
		{
			if((xcoor-1)<0) return -1;
			if(*(grid1+(ycoor)*10+xcoor)!=0|*(grid1+(ycoor)*10+xcoor-1)!=0) return -1;
			*(grid1+(ycoor)*10+xcoor)=HREEND;
			*(grid1+(ycoor)*10+xcoor-1)=HRWEND;
			*(shipgrid+(ycoor)*10+xcoor)=4;
			*(shipgrid+(ycoor)*10+xcoor-1)=4;
			break;
		}
	}
	return 1;
}

placeships(int player)
{
	for(b=0;b<=4;b++)
	{
REDO1:		clearside();
		ozputs(165,0,"Letter coor. for");
		ozputs(165,10,ships[b]);
		switch(ozngetch())
		{
			case 'a': tempx=0; x=ozputs(165,20,"A,"); break;
			case 'b': tempx=1; x=ozputs(165,20,"B,"); break;
			case 'c': tempx=2; x=ozputs(165,20,"C,"); break;
			case 'd': tempx=3; x=ozputs(165,20,"D,"); break;
			case 'e': tempx=4; x=ozputs(165,20,"E,"); break;
			case 'f': tempx=5; x=ozputs(165,20,"F,"); break;
			case 'g': tempx=6; x=ozputs(165,20,"G,"); break;
			case 'h': tempx=7; x=ozputs(165,20,"H,"); break;
			case 'i': tempx=8; x=ozputs(165,20,"I,"); break;
			case 'j': tempx=9; x=ozputs(165,20,"J,"); break;
			default: goto REDO1;
		}
REDO2:		ozputs(165,0,"Number coor. for");
		ozputs(165,10,ships[b]);
		switch(ozngetch())
		{
			case '1': tempy=0; ozputs(x,20,"1"); break;
			case '2': tempy=1; ozputs(x,20,"2"); break;
			case '3': tempy=2; ozputs(x,20,"3"); break;
			case '4': tempy=3; ozputs(x,20,"4"); break;
			case '5': tempy=4; ozputs(x,20,"5"); break;
			case '6': tempy=5; ozputs(x,20,"6"); break;
			case '7': tempy=6; ozputs(x,20,"7"); break;
			case '8': tempy=7; ozputs(x,20,"8"); break;
			case '9': tempy=8; ozputs(x,20,"9"); break;
			case '0': tempy=9; ozputs(x,20,"0"); break;
			default: goto REDO2;
		}
REDO3:		ozputs(165,30,"Rest of ship?");
		ozputs(165,40,"(N,S,E,W)");
		switch(ozngetch())
		{
			case 'n': tempdir=NORTH; break;
			case 's': tempdir=SOUTH; break;
			case 'e': tempdir=EAST; break;
			case 'w': tempdir=WEST; break;
			default: goto REDO3;
		}
		switch(currentplayer)
		{
			case 1: grid1=&grid1_1[0][0]; grid2=&grid1_2[0][0]; shipgrid=&p1ships[0][0]; break;
			case 2: grid1=&grid2_1[0][0]; grid2=&grid2_2[0][0]; shipgrid=&p2ships[0][0]; break;
		}
		switch(b)
		{
			case 0: if(drawbattleship(tempx,tempy,tempdir)==-1) goto REDO1; break;
			case 1: if(drawcarrier(tempx,tempy,tempdir)==-1) goto REDO1; break;
			case 2: if(drawcrusub(tempx,tempy,tempdir)==-1) goto REDO1; break;
			case 3: if(drawcrusub(tempx,tempy,tempdir)==-1) goto REDO1; break;
			case 4: if(drawptboat(tempx,tempy,tempdir)==-1) goto REDO1; break;
		}
		drawscreen();
	}
}

switchplayer()
{
	switch(currentplayer)
	{
		case 1: currentplayer=2; break;
		case 2: currentplayer=1; break;
	}
}

int shoot(int xcoor, int ycoor)
{
	switch(currentplayer)
	{
		case 1: grid1=&grid2_1[0][0]; grid2=&grid1_2[0][0]; shipgrid=&p2ships[0][0]; break;
		case 2: grid1=&grid1_1[0][0]; grid2=&grid2_2[0][0]; shipgrid=&p1ships[0][0]; break;
	}
	switch(*(grid1+(ycoor)*10+xcoor))
	{
		case EMPTY:	hit=0; *(grid1+(ycoor)*10+xcoor)=MISS; break;
		case HIT:	hit=1; *(grid1+(ycoor)*10+xcoor)=HIT; break;
		case MISS:	hit=0; *(grid1+(ycoor)*10+xcoor)=MISS; break;
		case VTNEND:	hit=1; *(grid1+(ycoor)*10+xcoor)=VTNENDHIT; break;
		case VTNENDHIT: hit=1; *(grid1+(ycoor)*10+xcoor)=VTNENDHIT; break;
		case VTSEND:	hit=1; *(grid1+(ycoor)*10+xcoor)=VTSENDHIT; break;
		case VTSENDHIT: hit=1; *(grid1+(ycoor)*10+xcoor)=VTSENDHIT; break;
		case VTMID:	hit=1; *(grid1+(ycoor)*10+xcoor)=VTMIDHIT; break;
		case VTMIDHIT:	hit=1; *(grid1+(ycoor)*10+xcoor)=VTMIDHIT; break;
		case HRWEND:	hit=1; *(grid1+(ycoor)*10+xcoor)=HRWENDHIT; break;
		case HRWENDHIT: hit=1; *(grid1+(ycoor)*10+xcoor)=HRWENDHIT; break;
		case HREEND:	hit=1; *(grid1+(ycoor)*10+xcoor)=HREENDHIT; break;
		case HREENDHIT: hit=1; *(grid1+(ycoor)*10+xcoor)=HREENDHIT; break;
		case HRMID:	hit=1; *(grid1+(ycoor)*10+xcoor)=HRMIDHIT; break;
		case HRMIDHIT:	hit=1; *(grid1+(ycoor)*10+xcoor)=HRMIDHIT; break;
	}
	switch(*(shipgrid+(ycoor)*10+xcoor))
	{
		case 0: break;
		case 1: ozputs(165,10,ships[0]); break;
		case 2: ozputs(165,10,ships[1]); break;
		case 3: x=ozputs(165,10,ships[2]); ozputs(x,10," or"); ozputs(165,20,ships[3]); break;
		case 4: ozputs(165,10,ships[4]); break;
	}
	switch(hit)
	{
		case 0: ozputs(165,0,"Miss."); *(grid2+(ycoor)*10+xcoor)=MISS; break;
		case 1: ozputs(165,0,"HIT!"); *(grid2+(ycoor)*10+xcoor)=HIT; *(shipgrid+(ycoor)*10+xcoor)=0; break;
	}
	ozputs(165,30,"Any key...");
	drawscreen();
	ozngetch();
}

play()
{
	while(1)
	{
		if(start==1)
		{
	REDO4:	ozcls();
			ozputs(0,0,"Specify which type of game you would like to play:");
			ozputs(0,10,"(1)  Human vs. human");
			ozputs(0,20,"(2)  Human vs. computer");
			switch(ozngetch())
			{
				case '1':
				{
					ozcls();
					ozputs(0,0,"Specify how you would like to play the game:");
					ozputs(0,10,"(1)  Same Wizard");
					ozputs(0,20,"(2)  Wizard to Wizard (requires serial connection)");
					switch(ozngetch())
					{
						case '1':
						{
							ozcls();
							ozputs(0,0,"Human vs. human game on the same Wizard.  OK?  (Y/n)");
							switch(ozngetch())
							{
								case 'n': goto REDO4;
								default: gametype=1; break;
							}
							break;
						}
						case '2': ozcls(); ozputs(0,0,"Not implemented yet!"); ozngetch(); break;
					}
					break;
				}
				case '2': ozcls(); ozputs(0,0,"Not implemented yet!"); ozngetch(); break;
			}
			switch(gametype)
			{
				case 1:
				{
					ozcls();
					ozputs(0,0,"Player 1, Enter Your Name (12 chars)");
					ozeditline(0,10,player1,13,239);
					ozputs(0,20,"Player 2, Enter Your Name (12 chars)");
					ozeditline(0,30,player2,13,239);
					ozcls();
					drawscreen();
					ozputs(165,0,player1);
					ozputs(165,10,"Place ships");
					ozputs(165,20,"Press a key...");
					ozngetch();
					placeships(1);
					switchplayer();
					ozcls();
					drawscreen();
					ozputs(165,0,player2);
					ozputs(165,10,"Place ships");
					ozputs(165,20,"Press a key...");
					ozngetch();
					placeships(2);
					break;
				}
				case 2:
				{
					break;
				}
				case 3:
				{
					break;
				}
			}
			start=0;
		}
		switchplayer();
		switch(currentplayer)
		{
			case 1: sprintf(player,"%s",player1); break;
			case 2: sprintf(player,"%s",player2); break;
		}
		ozcls();
		ozputs(165,0,player);
		ozputs(165,10,"Shoot!");
		ozputs(165,20,"Press a key...");
		ozngetch();
		ozcls();
		drawscreen();
REDO1:		ozputs(165,0,"Letter coor.");
		switch(ozngetch())
		{
			case 'a': tempx=0; x=ozputs(165,20,"A,"); break;
			case 'b': tempx=1; x=ozputs(165,20,"B,"); break;
			case 'c': tempx=2; x=ozputs(165,20,"C,"); break;
			case 'd': tempx=3; x=ozputs(165,20,"D,"); break;
			case 'e': tempx=4; x=ozputs(165,20,"E,"); break;
			case 'f': tempx=5; x=ozputs(165,20,"F,"); break;
			case 'g': tempx=6; x=ozputs(165,20,"G,"); break;
			case 'h': tempx=7; x=ozputs(165,20,"H,"); break;
			case 'i': tempx=8; x=ozputs(165,20,"I,"); break;
			case 'j': tempx=9; x=ozputs(165,20,"J,"); break;
			default: goto REDO1;
		}
REDO2:		ozputs(165,0,"Number coor.");
		switch(ozngetch())
		{
			case '1': tempy=0; ozputs(x,20,"1"); break;
			case '2': tempy=1; ozputs(x,20,"2"); break;
			case '3': tempy=2; ozputs(x,20,"3"); break;
			case '4': tempy=3; ozputs(x,20,"4"); break;
			case '5': tempy=4; ozputs(x,20,"5"); break;
			case '6': tempy=5; ozputs(x,20,"6"); break;
			case '7': tempy=6; ozputs(x,20,"7"); break;
			case '8': tempy=7; ozputs(x,20,"8"); break;
			case '9': tempy=8; ozputs(x,20,"9"); break;
			case '0': tempy=9; ozputs(x,20,"0"); break;
			default: goto REDO2;
		}
		ozputs(165,30,"Fire? (Y/n)");
		switch(ozngetch())
		{
			case KEY_NEWLINE: ozsnap(); ozsnap(); ozsnap(); break;
			case 'n': clearside(); goto REDO1;
			default: break;
		}
		clearside();
		shoot(tempx, tempy);
		for(eins=0,zwei=0,drei=0;eins<100;eins++,drei++)
		{
			if(drei==10)
			{
				  zwei++;
				  drei=0;
			}
			switch(*(shipgrid+zwei*10+drei))
			{
				case 0: break;
				case 1: end=0; eins=101; break;
				case 2: end=0; eins=101; break;
				case 3: end=0; eins=101; break;
				case 4: end=0; eins=101; break;
			}
			if(eins==99) end=1;
		}
		if(end==1) endgame();
	}
}

endgame()
{
	ozcls();
	switch(currentplayer)
	{
		case 1: x=ozputs(0,0,player1); break;
		case 2: x=ozputs(0,0,player2); break;
	}
	ozputs(x,0," wins!");
	ozputs(0,70,"Any key to exit WizBattleship...");
	ozngetch();
	exit(0);
}

about()
{
	ozcls();
	ozputs(0,0,"WizBattleship is the Wizard version of the classic game");
	ozputs(0,8,"by Milton Bradley, Battleship.");
	ozputs(0,16,"The object of the game is to sink all of your opponent's");
	ozputs(0,24,"ships by firing once each turn at specified coordinates.");
	ozputs(0,32,"These ships consist of the Battleship (4 spaces long),");
	ozputs(0,40,"Aircraft Carrier (5), Cruiser (3), Submarine (3), and");
	ozputs(0,48,"Patrol Boat (2).");
	ozputs(0,64,"Copyright (C) 2002 Christopher J. Daniel");
	ozputs(0,72,"Website URL: http://cjd1701.vze.com");
	ozngetch();
}

main()
{
	start=0;
	ozcls();
	ozrestorekeysettings();
	ozsinglepage();
	ozsetfont(FONT_OZ_LARGE);
	ozputs(0,0,"WizBattleship");
	ozsetfont(FONT_OZ_NORMAL);
	ozputs(80,3,version);
	ozputs(0,13,"Made with Hi-Tech C; USE AT YOUR OWN RISK!");
	ozputs(0,28,"(1) Play");
	ozputs(0,38,"(2) About");
	ozputs(0,48,"(3) Quit");
	ozputs(0,72,"Copyright (C) 2002 Christopher J. Daniel");
	switch(ozngetch())
	{
		case '1': start=1; play(); break;
		case '2': about(); break;
		case '3': exit(0);
	}
}
