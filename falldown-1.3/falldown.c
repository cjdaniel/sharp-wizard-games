/* Falldown: a game where you guide an eternally falling ball down through openings
   Copyright 2001-2004 Christopher J. Daniel 
   You may use the code contained herein for any purpose you deem necessary,
   commercial or noncommercial, as long as the author(s) are given due credit. */

#include <oz.h>

int bar[5]={0,0,0,0,0};
int i;
int x;
int spot=0;
int load=1;
int ballpos=0;
int prevballpos=0;
int scrolldelay=30000;
int level=0;
int sound=1;
int delays[10]={100*300,100*275,100*250,100*225,100*200,100*175,100*150,100*125,100*100,100*75};

long score=0;
long score0=0;

static char scorestat[15];
static char levelstat[10];
static char initials[4];
static char savechar[14];
static char soundstat[10];

wait(unsigned c)
{
    while(c) c--;
}

hitsound()
{
	if(sound==1)
	{
		ozclick(0);
		ozsound(48);
		wait(1500);
		ozsound(54);
		wait(1500);
		ozsound(110);
		wait(1500);
		ozsound(131);
		wait(1500);
		ozsound(139);
		wait(1500);
		ozsound(147);
		wait(1500);
		ozsound(248);
		wait(1500);
		ozquiet();
	}
}

levelupsound()
{
	if(sound==1)
	{
		ozclick(0);
		ozsound(17);
		wait(1500);
		ozsound(15);
		wait(1500);
		ozsound(14);
		wait(1500);
		ozsound(12);
		wait(1500);
		ozquiet();
	}
}

levelup()
{
	if(level==9)
	{
		return;
	}
	level+=1;
	levelupsound();
}

int didithit()
{
	switch(ballpos)
	{
		case 0: spot=10; break;
		case 1: spot=26; break;
		case 2: spot=42; break;
		case 3: spot=58; break;
		case 4: spot=74; break;
	}
	switch(ozgetpoint(spot,36))
	{
		case 1: return 1;
		case 0: return 0;
	}
}

/* Here's the highscore-saving function */
int savehighscore(char *name)
{
	if(open1(name,O_WRONLY)==-1)
	{
		ozputs(0,0,"Error opening file.  Press any key.");
		ozngetch();
		close1();
		return -1;
	}
	sprintf(savechar,"%s %ld",initials,score);
	if(write1(savechar,14)==-1)
	{
		ozputs(0,0,"Error writing file.  Press any key.");
		ozngetch();
		close1();
		return -1;
	}
	close1();
	return 0;
}

int loadhighscore()
{
	sprintf(savechar,"");
	sprintf(initials,"");
	score0=0;
	open1("falldown/hiscore",O_RDONLY);
	read1(savechar,14);
	close1();
	sscanf(savechar,"%3c %ld",&initials,&score0);
	return 0;
}

getinitials(byte x3,byte y3)
{
    static byte i;
    static unsigned k;
    i=0;
    while(i<3)
    {
        switch(k=ozgetch())
        {
/*          case KEY_BACKSPACE:
            case 8:
                if(i)
                {
                    i--;
                    x3-=ozputs(x3,y3,initials+i);
                    ozputs(x3,y3,"   ");
                }
                break;*/
            case KEY_LOWER_ESC:
            case KEY_UPPER_ESC:
                exit(0);
            default:
                if(k<127 && (isalpha(k) || isdigit(k)))
                {
                    initials[i]=toupper(k);
                    initials[i+1]=0;
                    x3=ozputs(x3,y3,initials+i);
                    i++;
                }
                break;
        }
    }
}

endgameswitch()
{
	ozcopypage(1,0);
	ozcls();
	ozputs(0,70,"Are you sure you want to leave this game?  (Y/N)");
	switch(ozgetch())
	{
		case 'y': endgame(); break;
		case 'n': ozcopypage(0,1); return;
		default: ozcopypage(0,1); return;
	}
}

endgame()
{
	ozcls();
	loadhighscore();
	if(score<=score0) exit(0);
	else if(score>score0)
	{
		x=ozputs(0,70,"New high score!  Enter your initials: ");
		getinitials(x,70);
		ozcls();
		ozputs(0,70,"Saving Score...");
		savehighscore("falldown/hiscore");
	}
	exit(0);
}
putstats()
{
	sprintf(scorestat,"Score: %ld",score);
	sprintf(levelstat,"Level: %d",level);
	ozputs(95,0,scorestat);
	ozputs(151,0,levelstat);
	getsound();
	ozputs(190,0,soundstat);
}

pause()
{
	ozcopypage(1,0);
	ozcls();
	ozputs(0,70,"Paused.  Press any key to continue...");
	ozgetch();
	ozcopypage(0,1);
}

help()
{
	ozcopypage(1,0);
	ozcls();
	ozsetfont(FONT_OZ_LARGE);
	ozputs(0,0,"Game Control Keys:");
	ozsetfont(FONT_OZ_NORMAL);
	ozputs(0,20,"Left/Right Arrows: Move ball");
	ozputs(0,30,"P: Pause Game     S: Toggle Sound");
	ozputs(0,40,"H/Menu: This screen");
	ozputs(0,50,"ESC: Quit to Main Menu");
	ozputs(0,60,"My Programs: Exit game");
	ozputs(0,70,"PRESS ANY KEY TO CONTINUE...");
	ozgetch();
	ozcopypage(0,1);
}

randbar()
{
	bar[0]=(rand()&1);
	bar[1]=(rand()&1);
	bar[2]=(rand()&1);
	bar[3]=(rand()&1);
	bar[4]=(rand()&1);
	if((bar[0]==1)&&(bar[1]==1)&&(bar[2]==1)&&(bar[3]==1)&&(bar[4]==1))
	{
		bar[0]=0;
		bar[1]=0;
		bar[2]=0;
		bar[3]=0;
		bar[4]=0;
	}
}

drawbar()
{
	if(bar[0]==1) ozbox(3,76,15,3);
	if(bar[1]==1) ozbox(19,76,15,3);
	if(bar[2]==1) ozbox(35,76,15,3);
	if(bar[3]==1) ozbox(51,76,15,3);
	if(bar[4]==1) ozbox(67,76,15,3);
	_ozvline(0,70,10,BLACK);
	_ozvline(1,70,10,BLACK);
	_ozvline(83,70,10,BLACK);
	_ozvline(84,70,10,BLACK);
}

clearball()
{
	ozfilledbox(8,20,69,5,WHITE);
	switch(prevballpos)
	{
		case 0: ozcircle(10,32,2,WHITE|4); break;
		case 1: ozcircle(26,32,2,WHITE|4); break;
		case 2: ozcircle(42,32,2,WHITE|4); break;
		case 3: ozcircle(58,32,2,WHITE|4); break;
		case 4: ozcircle(74,32,2,WHITE|4); break;
	}
}

drawball()
{
	switch(ballpos)
	{
		case 0: ozcircle(10,32,2,BLACK|4); break;
		case 1: ozcircle(26,32,2,BLACK|4); break;
		case 2: ozcircle(42,32,2,BLACK|4); break;
		case 3: ozcircle(58,32,2,BLACK|4); break;
		case 4: ozcircle(74,32,2,BLACK|4); break;
	}
}

play()
{
	ballpos=2;
	prevballpos=ballpos;
	ozcls();
	_ozvline(0,0,70,BLACK);
	_ozvline(1,0,70,BLACK);
	_ozvline(83,0,70,BLACK);
	_ozvline(84,0,70,BLACK);
	srand(ozsec()+60*ozmin());
	for(;;)
	{
		clearball();
		randbar();
		drawbar();
		drawball();
		if(score==100) levelup();
		if(score==200) levelup();
		if(score==300) levelup();
		if(score==500) levelup();
		if(score==750) levelup();
		if(score==1000) levelup();
		if(score==1250) levelup();
		if(score==1500) levelup();
		if(score==2000) levelup();
		putstats();
		for(i=0;i<delays[level];i++)
		{
			if(ozkeyhit()) switch(ozgetch())
			{
				case KEY_LEFT:
				{
					if(ballpos==0)
					{
						clearball();
						drawball();
						prevballpos=ballpos;
						break;
					}
					else ballpos-=1;
					clearball();
					drawball();
					prevballpos=ballpos;
					break;
				}
				case KEY_RIGHT:
				{
					if(ballpos==4)
					{
						clearball();
						drawball();
						prevballpos=ballpos;
						break;
					}
					else ballpos+=1;
					clearball();
					drawball();
					prevballpos=ballpos;
					break;
				}
				case KEY_BACKLIGHT: oztogglelight(); break;
				case KEY_MYPROGRAMS: endgameswitch(); break;
				case KEY_LOWER_ESC:
				case KEY_UPPER_ESC: endgameswitch(); break;
				case KEY_LOWER_MENU:
				case KEY_UPPER_MENU:
				case 'h': help(); break;
				case 'p': pause(); break;
				case 's': changesound(); putstats(); break;
				case KEY_NEWLINE: ozsnap(); ozsnap(); ozsnap(); break;
			}
		}
		if(didithit()==1)
		{
			hitsound();
			ozputs(90,70,"Game Over!  Press any key...");
			ozgetch();
			endgame();
			main();
		}
		ozscrollclear();
		score+=1;
	}
}

getsound()
{
	if(sound==0)
	{
		sprintf(soundstat,"Sound Off");
	}
	if(sound==1)
	{
		sprintf(soundstat,"Sound On");
	}
}

changesound()
{
	if(sound==0) sound=1;
	else if(sound==1) sound=0;
}

option()
{
	ozcls();
	ozputs(0,0,"Options (Press ENTER when done)");
	ozputs(0,20,"S: Toggle Sound");
	ozputs(0,30,"D: Delete Highscore");
	ozputs(0,70,"Coded for the Wizard by Chris Daniel     cjd1701@mail.com");
	getsound();
	ozputs(135,20,soundstat);
	switch(ozgetch())
	{
		case KEY_BACKLIGHT: oztogglelight(); break;
		case 's': changesound(); break;
		case 'd': ozcls(); ozputs(0,70,"Deleting..."); unlink("falldown/hiscore"); break;
		case KEY_LOWER_ENTER:
		case KEY_UPPER_ENTER:
		case KEY_LOWER_ESC:
		case KEY_UPPER_ESC: return;
	}
	option();
}

howtoplay()
{
	ozcls();
	ozputs(0,0,"Falldown is a game in which you guide an eternally falling");
	ozputs(0,8,"ball down without hitting a ledge.  If you do hit a ledge,");
	ozputs(0,16,"the game ends.");
	ozputs(0,24,"In the Texas Instruments graphing calculator version,");
	ozputs(0,32,"and on most other versions of the game, the ball just");
	ozputs(0,40,"stops when it hits a ledge.  The screen keeps scrolling,");
	ozputs(0,48,"however, and when the ball is at the top of the screen,");
	ozputs(0,56,"the game ends.");
	ozputs(0,72,"Press any key to continue...");
	ozngetch();
}

main()
{
	ozclick(0);
	if(load==1)
	{
		ozcls();
		ozputs(0,70,"Loading...");
		loadhighscore();
		load=0;
	}
	score=0;
	ozcls();
	ozsetfont(FONT_OZ_LARGE);
	ozputs(0,0,"Falldown");
	ozsetfont(FONT_OZ_NORMAL);
	ozputs(80,3,"Version 1.3");
	ozputs(0,16,"Select Level: [0-9]");
	ozputs(0,24,"[O]ptions");
	ozputs(0,32,"[K]eys");
	ozputs(0,40,"[H]ow to Play");
	ozputs(0,48,"[Q]uit");
	ozputs(0,70,"Coded for the Wizard by Chris Daniel");
	x=ozputs(100,32,"Highscore: ");
	ozputs(x,32,savechar);
	switch(ozngetch())
	{
		case '0': level=0; load=1; play(); break;
		case '1': level=1; load=1; play(); break;
		case '2': level=2; load=1; play(); break;
		case '3': level=3; load=1; play(); break;
		case '4': level=4; load=1; play(); break;
		case '5': level=5; load=1; play(); break;
		case '6': level=6; load=1; play(); break;
		case '7': level=7; load=1; play(); break;
		case '8': level=8; load=1; play(); break;
		case '9': level=9; load=1; play(); break;
		case 'o': option(); load=1; break;
		case 'k': help(); break;
		case 'h': howtoplay(); load=1; break;
		case KEY_UPPER_ESC:
		case KEY_LOWER_ESC:
		case 'q':
		case 'x': exit(0); load=1; break;
		case KEY_NEWLINE: ozsnap(); break;
	}
	main();
}
