/* OZCP 2.0 -- Copyright 2000-2004 Christopher J. Daniel
   A skeet-shooting game for the Sharp Wizard OZ-7xx series 

   You may use the code contained herein for any purpose you deem necessary,
   commercial or noncommercial, as long as the author(s) are given due credit. */

#include <oz.h>
#include <ctype.h>
#include <stdlib.h>

#define LEFT 0
#define RIGHT 1

int random=0;
int gunpos=0;
int x;
int y;
int speed=2501;
long score;
long shots=25;
long bullseyes=0;
float hits=0, misses=0, total=0, acc=0;
int house;
int a=0;
int b=0;
int c=0;
int d=0;
int hit=0;
int high=1;
int prevhigh=0;
int sound=0;
int watch=1;
int load=1;

int mov=1;
int spd=2;

long score0;

static char bullseye[16];

static char einspeed[14];
static char zweispeed[14];
static char dreispeed[14];
static char randspeed[14];

static char savechar[14];
static char initials[4];

static char slow[14];
static char accrate[16];
static char soundstat[10];
static char moviestat[10];
static char config[6];

loadconfigswitch()
{
	sscanf(config,"%d %d %d",&mov,&spd,&sound);
	switch(spd)
	{
		case 0: speed=0; break;
		case 1: speed=1; break;
		case 2: speed=2501; break;
		case 3: speed=5001; break;
	}
}

configswitch()
{
	switch(speed)
	{
		case 0: spd=0; break;
		case 1: spd=1; break;
		case 2501: spd=2; break;
		case 5001: spd=3; break;
	}
}

int makenewconfigfile()
{
	if(open1("ozcp20/config",O_WRONLY)==-1)
	{
		ozcls();
		ozputs(0,70,"Error opening file.  Press any key.");
		ozngetch();
		return -1;
	}
	configswitch();
	sprintf(config,"%d %d %d",mov,spd,sound);
	if(write1(config,6)==-1)
	{
		ozcls();
		ozputs(0,70,"Error writing file.  Press any key.");
		ozngetch();
		return -1;
	}
	close1();
	return 0;
}

saveconfig()
{
	ozcls();
	ozputs(0,70,"Saving Configuration...");
	if(makenewconfigfile()==-1) return;
	ozcls();
	ozputs(0,70,"Done.  Press any key to continue.");
	ozngetch();
}

loadconfig()
{
	ozputs(0,70,"Loading configuration...");
	if(open1("ozcp20/config",O_RDONLY)==-1)
	{
		makenewconfigfile();
		if(makenewconfigfile()==-1) return;
	}
	read1(config,5);
	close1();
	loadconfigswitch();
	load=0;
}

int savehighscores(char *name)
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

int loadhighscores(int level)
{
	if(level==4)
	{
		open1("ozcp20/highscore0",O_RDONLY);
		read1(randspeed,14);
		close1();
		open1("ozcp20/highscore1",O_RDONLY);
		read1(dreispeed,14);
		close1();
		open1("ozcp20/highscore2",O_RDONLY);
		read1(zweispeed,14);
		close1();
		open1("ozcp20/highscore3",O_RDONLY);
		read1(einspeed,14);
		close1();
		return 0;
	}
	if(level==0)
	{
		open1("ozcp20/highscore0",O_RDONLY);
		read1(randspeed,14);
		close1();
		sscanf(randspeed,"%3c %ld",&initials,&score0);
		return 0;
	}
	if(level==1)
	{
		open1("ozcp20/highscore1",O_RDONLY);
		read1(dreispeed,14);
		close1();
		sscanf(dreispeed,"%3c %ld",&initials,&score0);
		return 0;
	}
	if(level==2)
	{
		open1("ozcp20/highscore2",O_RDONLY);
		read1(zweispeed,14);
		close1();
		sscanf(zweispeed,"%3c %ld",&initials,&score0);
		return 0;
	}
	if(level==3)
	{
		open1("ozcp20/highscore3",O_RDONLY);
		read1(einspeed,14);
		close1();
		sscanf(einspeed,"%3c %ld",&initials,&score0);
		return 0;
	}
	return -1;
}

highscores()
{
	sprintf(randspeed,"");
	sprintf(dreispeed,"");
	sprintf(zweispeed,"");
	sprintf(einspeed,"");
	ozcls();
	ozputs(0,70,"Loading High Scores...");
	if(loadhighscores(4)==-1) return;
	ozcls();
	ozsetfont(FONT_OZ_LARGE);
	ozputs(0,0,"OZCP High Scores");
	ozsetfont(FONT_OZ_NORMAL);
	ozputs(0,20,"Random Speed:");
	ozputs(0,30,"3rd Speed:");
	ozputs(0,40,"2nd Speed:");
	ozputs(0,50,"1st Speed:");
	ozputs(119,20,randspeed);
	ozputs(119,30,dreispeed);
	ozputs(119,40,zweispeed);
	ozputs(119,50,einspeed);
	ozputs(0,70,"R to reset scores, or any other key to continue.");
	switch(ozngetch())
	{
		case 'r':
		{
			ozcls();
			ozputs(0,70,"Deleting Highscores...");
			unlink("ozcp20/highscore0");
			unlink("ozcp20/highscore1");
			unlink("ozcp20/highscore2");
			unlink("ozcp20/highscore3");
			sprintf(randspeed,"");
			sprintf(dreispeed,"");
			sprintf(zweispeed,"");
			sprintf(einspeed,"");
			break;
		}
	}
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
	ozcopypage(0,1);
	ozcls();
	ozputs(0,70,"Are you sure you want to leave this game?  (Y/N)");
	switch(ozngetch())
	{
		case 'y': endgame(); break;
		case 'n': ozcopypage(1,0); play(); break;
	}
}

endgame()
{
	ozcls();
	configswitch();
	loadhighscores(spd);
	if(score<=score0) return;
	else if(score>score0)
	{
		x=ozputs(0,70,"New high score!  Enter your initials: ");
		getinitials(x,70);
		ozcls();
		ozputs(0,70,"Saving Score...");
		switch(spd)
		{
			case 0: savehighscores("ozcp20/highscore0"); break;
			case 1: savehighscores("ozcp20/highscore1"); break;
			case 2: savehighscores("ozcp20/highscore2"); break;
			case 3: savehighscores("ozcp20/highscore3"); break;
		}
	}
}

accuracy(int x2, int y2)
{
	total=hits+misses;
	acc=hits/(total/100);
	if((hits==0)&&(misses==0)) acc=0;
	sprintf(accrate,"Accuracy: %fd",acc);
	ozputs(x2,y2,accrate);
}

shatter()
{
	ozpoint(51,8,1);
	ozpoint(60,8,1);
	ozpoint(54,11,1);
	ozpoint(65,11,1);
	ozpoint(58,12,1);
	ozpoint(66,12,1);
	ozpoint(60,15,1);
	ozpoint(49,16,1);
	ozpoint(50,16,1);
	ozpoint(57,16,1);
	ozpoint(57,17,1);
	ozpoint(62,19,1);
	ozpoint(52,21,1);
	ozpoint(57,19,0);
	ozpoint(58,20,0);
	ozpoint(56,20,0);
	ozpoint(57,21,0);
	ozpoint(59,21,0);
	ozpoint(58,22,0);
	ozpoint(60,22,0);
	ozpoint(59,23,0);
}

movie()
{
	speed=501;
	ozcls();
	ozsetactivepage(1);
	ozsetdisplaypage(0);
	ozcls();
	for(x=0, y=79 ; y>20 ; x++, y--)
	{
		ozcls();
		drawgun();
		ozcircle(x,y,2,4|1);
		ozdelay(speed);
		ozswapactivedisplay();
	}
	ozsetactivepage(0);
	ozsetdisplaypage(0);
	ozline(97,60,37,0,1);
	shatter();
/*	movietext();*/
	ozsetfont(FONT_OZ_LARGE);
	ozputs(119,20,"OZ Clay Pigeons");
	ozsetfont(FONT_OZ_NORMAL);
	ozputs(0,70,"Press Any Key...");
	speed=2501;
	ozngetch();
}

wait(unsigned i)
{
    while(i) i--;
}

playsound()
{
	if(sound==1)
	{
		ozclick(0);
	ozsound(4);
	wait(1500);
	ozsound(3);
	wait(1500);
	ozsound(2);
	wait(1500);
	ozsound(1);
	wait(1500);
	ozquiet();
	}
}

hitsound()
{
	if(sound==1)
	{
		ozclick(0);
		ozsound(20);
		wait(1500);
		ozsound(40);
		wait(1500);
		ozsound(60);
		wait(1500);
		ozsound(80);
		wait(1500);
		ozsound(100);
		wait(1500);
		ozsound(104);
		wait(1500);
		ozsound(103);
		wait(1500);
		ozsound(102);
		wait(1500);
		ozquiet();
	}
}

highlight()
{
	if(high==1)
	{
		if(prevhigh==2)
		{
			ozfilledbox(0,29,102,10,2);
		}
		if(prevhigh==5)
		{
			ozfilledbox(0,59,102,10,2);
		}
		ozfilledbox(0,19,102,10,2);
	}
	if(high==2)
	{
		if(prevhigh==1)
		{
			ozfilledbox(0,19,102,10,2);
		}
		if(prevhigh==3)
		{
			ozfilledbox(0,39,102,10,2);
		}
		ozfilledbox(0,29,102,10,2);
	}
	if(high==3)
	{
		if(prevhigh==2)
		{
			ozfilledbox(0,29,102,10,2);
		}
		if(prevhigh==4)
		{
			ozfilledbox(0,49,102,10,2);
		}
		ozfilledbox(0,39,102,10,2);
	}
	if(high==4)
	{
		if(prevhigh==3)
		{
			ozfilledbox(0,39,102,10,2);
		}
		if(prevhigh==5)
		{
			ozfilledbox(0,59,102,10,2);
		}
		ozfilledbox(0,49,102,10,2);
	}
	if(high==5)
	{
		if(prevhigh==4)
		{
			ozfilledbox(0,49,102,10,2);
		}
		if(prevhigh==1)
		{
			ozfilledbox(0,19,102,10,2);
		}
		ozfilledbox(0,59,102,10,2);
	}
	switch(ozngetch())
	{
			case KEY_DOWN:
			case KEY_PAGEDOWN:
			{
				if(high<5)
				{
					high+=1;
					prevhigh=(high-1);
					highlight();
					break;
				}
				if(high==5)
				{
					high=1;
					prevhigh=5;
					highlight();
					break;
				}
				highlight();
				break;
			}
			case KEY_UP:
			case KEY_PAGEUP:
			{
				if(high>1)
				{
					high-=1;
					prevhigh=(high+1);
					highlight();
					break;
				}
				if(high==1)
				{
					high=5;
					prevhigh=1;
					highlight();
					break;
				}
				highlight();
				break;
			}
			case KEY_LOWER_ENTER:
			case KEY_UPPER_ENTER:
			{
				if(high==1)
				{
					playsound();
					play();
				}
				if(high==2)
				{
					highscores();
				}
				if(high==3)
				{
					keys();
				}
				if(high==4)
				{
					option();
				}
				if(high==5)
				{
					exit(0);
				}
				break;
			}
			case KEY_LOWER_ESC:
			case KEY_UPPER_ESC: exit(0);
			case KEY_LOWER_MENU: keys();
			case '1':
			{
				playsound();
				play();
			}
			case '2': highscores(); break;
			case '3': keys();
			case '4': option();
			case '5': exit(0);
			case KEY_NEWLINE: ozsnap(); break;
	}
	main();
}

putspeed()
{
	if(speed==5001)
	{
		sprintf(slow,"Speed: 1");
		random=0;
	}
	if(speed==2501)
	{
		sprintf(slow,"Speed: 2");
		random=0;
	}
	if(speed==1)
	{
		sprintf(slow,"Speed: 3");
		random=0;
	}
	if(speed==0)
	{
		sprintf(slow,"Speed: RANDOM");
		random=1;
	}
}

addtoshots(int t)
{
	static char bullets[24];
	shots+=t;
	sprintf(bullets,"Bullets: %ld",shots);
	ozputs(189,0,bullets);
}

addtoscore(int s)
{
	static char thescore[22];
	score+=s;
	sprintf(thescore,"Score: %ld",score);
	ozputs(0,0,thescore);
}

fire(int d)
{
	ozsetactivepage(ozgetdisplaypage());
	if(d==LEFT)
	{
		shots-=1;
		ozline(97,60,37,0,1);
		a=x-1;
		b=y+1;
		c=x+1;
		d=y-1;
		if((x==59&&y==20)|(a==59&&b==20)|(c==59&&d==20))
		{
			hit=1;
			addtoscore(50);
			addtoshots(2);
			ozputs(0,70,"HIT!");
			if(x==59&&y==20)
			{
				shatter();
				addtoscore(50);
				addtoshots(2);
				bullseyes+=1;
				ozputs(20,70,"Bullseye!");
				hitsound();
			}
		}
		switch(ozngetch())
		{
			case KEY_NEWLINE: ozsnap(); break;
			default: break;
		}
	}
	if(d==RIGHT)
	{
		shots-=1;
		ozline(141,60,201,0,1);
		a=x-1;
		b=y-1;
		c=x+1;
		d=y+1;
		if((x==179&&y==20)|(a==179&&b==20)|(c==179&&d==20))
		{
			hit=1;
			addtoscore(50);
			addtoshots(2);
			ozputs(0,70,"HIT!");
			if(x==179&&y==20)
			{
				ozpoint(183,10,1);
				ozpoint(185,12,1);
				ozpoint(182,14,1);
				ozpoint(182,15,1);
				ozpoint(180,17,1);
				ozpoint(186,18,1);
				ozpoint(185,20,1);
				ozpoint(186,20,1);
				ozpoint(181,19,0);
				ozpoint(180,20,0);
				ozpoint(182,20,0);
				ozpoint(179,21,0);
				ozpoint(181,21,0);
				ozpoint(178,22,0);
				ozpoint(180,22,0);
				ozpoint(179,23,0);
				addtoscore(50);
				addtoshots(2);
				bullseyes+=1;
				ozputs(20,70,"Bullseye!");
				hitsound();
			}
		}
		switch(ozngetch())
		{
			case KEY_NEWLINE: ozsnap(); break;
			default: break;
		}
	}
	if(ozgetdisplaypage()==0) ozsetactivepage(1);
	 else ozsetactivepage(0);
	if(hit==0)
	{
		misses+=1;
	}
	if(hit==1)
	{
		hits+=1;
		hit=0;
		y=0;
	}
}

drawgun()
{
	if(gunpos==LEFT)
	{
		ozline(119,79,99,59,1);
		ozline(99,59,96,62,1);
		ozline(96,62,113,79,1);
		ozline(105,72,105,75,1);
		ozline(105,75,109,79,1);
	}
	if(gunpos==RIGHT)
	{
		ozline(119,79,139,59,1);
		ozline(139,59,142,62,1);
		ozline(142,62,125,79,1);
		ozline(133,72,133,75,1);
		ozline(133,75,129,79,1);
	}
}

pull()
{
	ozsetactivepage(1);
	ozcls();
	if(speed==0)
	{
		srand(ozmin()+60*ozsec());
		switch(rand()%3)
		{
			case 0: speed=1; break;
			case 1: speed=2501; break;
			case 2: speed=5001; break;
		}
	}
	srand(ozsec()+60*ozmin());
	switch(rand()%4)
	{
		case 0: house=LEFT; break;
		case 1: house=RIGHT; break;
		case 2: house=RIGHT; break;
		case 3: house=LEFT; break;
	}
	if(house==LEFT)
	{
		for(x=0, y=79 ; y>0 ; x++, y--)
		{
			if(ozkeyhit())
			{
				switch(ozngetch())
				{
					case KEY_LEFT: gunpos=LEFT; break;
					case KEY_RIGHT: gunpos=RIGHT; break;
					case 32:
					{
						if(shots>=1)
						{
							fire(gunpos);
						}
						break;
					}
					case KEY_LOWER_MENU:
					case 'h':
					{
						help();
						break;
					}
				}
			}
			ozcls();
			drawgun();
			ozdelay(speed);
			ozcircle(x,y,2,4|1);
			ozswapactivedisplay();
		}
	}
	if(house==RIGHT)
	{
		for(x=238, y=79 ; y>0 ; x--, y--)
		{
			if(ozkeyhit())
			{
				switch(ozngetch())
				{
					case KEY_LEFT: gunpos=LEFT; break;
					case KEY_RIGHT: gunpos=RIGHT; break;
					case 32:
					{
						if(shots>=1)
						{
							fire(gunpos);
						}
						break;
					}
					case KEY_LOWER_MENU:
					case 'h':
					{
						help();
						break;
					}
				}
			}
			ozcls();
			drawgun();
			ozdelay(speed);
			ozcircle(x,y,2,4|1);
			ozswapactivedisplay();
		}
	}
	if(random==1)
	{
		speed=0;
	}
}


play()
{
	ozcls();
	ozsetactivepage(0);
	ozsetdisplaypage(0);
	ozcls();
	if(shots<1)
	{
		ozcls();
		ozputs(0,0,"Out of Bullets!  Game Over!");
		ozngetch();
		exit(0);
	}
	ozsetfont(FONT_OZ_NORMAL);
	drawgun();
	addtoscore(0);
	addtoshots(0);
	sprintf(bullseye,"Bullseyes: %ld",bullseyes);
	ozputs(170,60,bullseye);
	accuracy(170,70);
	getsound();
	ozputs(0,70,soundstat);
	ozputs(0,30,"Press <ENTER> to pull, then <SPACE> to fire.");
	switch(ozgetch())
	{
		case KEY_BACKLIGHT: oztogglelight(); break;
		case KEY_MYPROGRAMS: endgameswitch(); exit(0);
		case KEY_LOWER_ESC: endgameswitch(); main();
		case KEY_LOWER_ENTER: pull(); break;
		case KEY_LEFT: gunpos=LEFT; break;
		case KEY_RIGHT: gunpos=RIGHT; break;
		case KEY_LOWER_MENU: help(); break;
		case 'h': help(); break;
		case 's': changesound(); break;
		case KEY_NEWLINE: ozsnap(); break;
	}
	play();
}

keys()
{
	ozcls();
	ozsetfont(FONT_OZ_NORMAL);
	ozputs(0,0,"CONTROL KEYS:");
	ozputs(0,10,"Left/Right Arrows: Switch gun positions");
	ozputs(0,20,"Enter: Pull");
	ozputs(0,30,"Space: Fire Gun");
	ozputs(0,40,"H/Lower Menu Key: This screen");
	ozputs(0,50,"MY PROGRAMS: Quit OZCP");
	ozputs(0,60,"S: Toggle Sound");
	ozputs(0,70,"ANY KEY TO CONTINUE...");
	ozngetch();
	main();
}

help()
{
	ozcopypage(0,1);
	ozcls();
	ozsetfont(FONT_OZ_NORMAL);
	ozputs(0,0,"CONTROL KEYS:");
	ozputs(0,10,"Left/Right Arrows: Switch gun positions");
	ozputs(0,20,"Enter: Pull");
	ozputs(0,30,"Space: Fire Gun");
	ozputs(0,40,"H/Lower Menu Key: This screen");
	ozputs(0,50,"MY PROGRAMS: Quit OZCP");
	ozputs(0,60,"1/2: Sound On/Off");
	ozputs(0,70,"ANY KEY TO CONTINUE...");
	ozngetch();
	ozcopypage(1,0);
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

getmovie()
{
	if(mov==0)
	{
		sprintf(moviestat,"Movie Off");
	}
	if(mov==1)
	{
		sprintf(moviestat,"Movie On");
	}
}

changesound()
{
	if(sound==0) sound=1;
	else if(sound==1) sound=0;
}

changemovie()
{
	if(mov==0) mov=1;
	else if(mov==1) mov=0;
}

option()
{
	ozcls();
	getsound();
	getmovie();
	ozputs(0,0,"Options: (Press ENTER when done, MENU to save)");
	ozputs(0,20,"PgUp/PgDn: Clay Pigeon Speed");
	putspeed();
	ozputs(135,20,slow);
	ozputs(0,30,"S: Toggle Sound");
	ozputs(135,30,soundstat);
	ozputs(0,40,"M: Toggle Startup Movie");
	ozputs(135,40,moviestat);
	ozputs(0,55,"(You should save after changing startup movie option)");
	ozputs(0,70,"OZCP Concept by Danny Jackson, coded by Chris Daniel");
	switch(ozngetch())
	{
		case 's': changesound(); break;
		case 'm': changemovie(); break;
		case KEY_PAGEUP:
		{
			if(speed==5001|speed==2501)
			{
				speed-=2500;
			}
			else if(speed==1)
			{
				speed=0;
			}
			else if(speed==0)
			{
				speed=5001;
			}
			break;
		}
		case KEY_PAGEDOWN:
		{
			if(speed==2501|speed==1)
			{
				speed+=2500;
			}
			else if(speed==5001)
			{
				speed=0;
			}
			else if(speed==0)
			{
				speed=1;
			}
			break;
		}
		case KEY_LOWER_MENU: saveconfig(); break;
		case KEY_UPPER_MENU: saveconfig(); break;
		case KEY_LOWER_ENTER: main();
		case KEY_NEWLINE: ozsnap(); break;
	}
	option();
}

main()
{
	ozgetauxsize();
	ozclick(0);
	ozcls();
	if(load==1)
	{
		loadconfig();
	}
	if(mov==1)
	{
		if(watch==1)
		{
			movie();
			watch=0;
		}
	}
	ozcls();
	high=1;
	prevhigh=0;
	score=0;
	shots=25;
	hits=0;
	misses=0;
	acc=0;
	bullseyes=0;
	ozquiet();
	ozsetfont(FONT_OZ_LARGE);
	ozputs(0,0,"OZ Clay Pigeons");
	ozsetfont(FONT_OZ_NORMAL);
	ozputs(95,3,"Version 2.0");
	ozputs(0,20,"(1) Play OZ Clay Pigeons");
	ozputs(0,30,"(2) High Scores");
	ozputs(0,40,"(3) Keys");
	ozputs(0,50,"(4) Options");
	ozputs(0,60,"(5) Quit OZ Clay Pigeons");
	ozputs(130,20,"Made with Hi-Tech C;");
	ozputs(130,30,"USE AT YOUR OWN RISK!");
	ozputs(130,50,"Up/Dn arrows to select");
	highlight();
	main();
}
