/* OZ Monopoly */

#include <oz.h>

/* All the prices of all the properties */
int prices[41] = { 0, 0, 60, 0, 60, 0, 200, 100, 0, 100, 120, 0, 140, 150, 140, 160, 200, 180, 0, 180, 200, 0, 220, 0, 220, 240, 200, 260, 260, 150, 280, 0, 300, 300, 0, 320, 200, 0, 350, 0, 400 };

/* All the rents for all the properties */
int rent0[41] = { 0, -200, 2, 0, 4, 0, 0, 6, 0, 6, 8, 0, 10, 0, 10, 12, 0, 14, 0, 14, 16, 0, 18, 0, 18, 20, 0, 22, 22, 0, 24, 0, 26, 26, 0, 28, 0, 0, 35, 75, 50 };
int rent1[41] = { 0, -200, 10, 0, 20, 0, 0, 30, 0, 30, 40, 0, 50, 0, 50, 60, 0, 70, 0, 70, 80, 0, 90, 0, 90, 100, 0, 110, 110, 0, 120, 0, 130, 130, 0, 150, 0, 0, 175, 75, 200 };
int rent2[41] = { 0, -200, 30, 0, 60, 0, 0, 90, 0, 90, 100, 0, 150, 0, 150, 180, 0, 200, 0, 200, 250, 0, 250, 0, 250, 300, 0, 330, 330, 0, 360, 0, 390, 390, 0, 450, 0, 0, 500, 75, 600 };
int rent3[41] = { 0, -200, 90, 0, 180, 0, 0, 270, 0, 270, 300, 0, 450, 0, 450, 500, 0, 550, 0, 550, 600, 0, 700, 0, 700, 750, 0, 800, 800, 0, 850, 0, 900, 900, 0, 1000, 0, 0, 1100, 75, 1400 };
int rent4[41] = { 0, -200, 160, 0, 320, 0, 0, 400, 0, 400, 450, 0, 625, 0, 625, 700, 0, 750, 0, 750, 800, 0, 875, 0, 875, 925, 0, 975, 975, 0, 1025, 0, 1100, 1100, 0, 1200, 0, 0, 1300, 75, 1700 };
int rent5[41] = { 0, -200, 250, 0, 450, 0, 0, 550, 0, 550, 600, 0, 750, 0, 750, 900, 0, 950, 0, 950, 1000, 0, 1050, 0, 1050, 1100, 0, 1150, 1150, 0, 1200, 0, 1275, 1275, 0, 1400, 0, 0, 1500, 75, 2000 };

/* Names of all the spaces */
static char *names[41][20]={
					{""},
					{"GO!"},
					{"Mediterranean"},
					{"Community Chest"},
					{"Baltic"},
					{"Income Tax"},
					{"Reading Railroad"},
					{"Oriental"},
					{"Chance"},
					{"Vermont"},
					{"Connecticut"},
					{"Jail/Just Visiting"},
					{"St. Charles"},
					{"Electric Company"},
					{"States"},
					{"Virginia"},
					{"Pennsylvania Railroad"},
					{"St. James"},
					{"Community Chest"},
					{"Tennessee"},
					{"New York"},
					{"Free Parking"},
					{"Kentucky"},
					{"Chance"},
					{"Indiana"},
					{"Illinois"},
					{"B. & O. Railroad"},
					{"Atlantic"},
					{"Ventnor"},
					{"Water Works"},
					{"Marvin Gardens"},
					{"Go To Jail!"},
					{"Pacific"},
					{"N. Carolina"},
					{"Community Chest"},
					{"Pennsylvania"},
					{"Short Line"},
					{"Chance"},
					{"Park Place"},
					{"Luxury Tax"},
					{"Boardwalk"}
					};

/* Owner array */
int owner[41] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

/* Indicates how many houses or hotel; e.g. 1 house=1, hotel=5 */
int hothouse[41] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

/* Variable to store property name for spaceinfo() routine */
static char *name[20];

/* This is the board */
int picdata[] = {  17, 1, 23, 1, 29, 1, 36, 1, 37, 1, 38, 1, 39, 1, 43, 1, 50, 1, 56, 1, 62, 1, 78, 1, 3, 2, 4, 2, 5, 2, 17, 2, 23, 2, 29, 2, 36, 2, 39, 2, 43, 2, 50, 2, 56, 2, 62, 2, 75, 2, 77, 2, 3, 3, 17, 3, 23, 3, 29, 3, 36, 3, 37, 3, 38, 3, 39, 3, 43, 3, 50, 3, 56, 3, 62, 3, 75, 3, 76, 3, 3, 4, 4, 4, 17, 4, 23, 4, 29, 4, 36, 4, 37, 4, 43, 4, 50, 4, 56, 4, 62, 4, 75, 4, 76, 4, 77, 4, 3, 5, 6, 5, 7, 5, 17, 5, 23, 5, 29, 5, 36, 5, 37, 5, 38, 5, 39, 5, 43, 5, 50, 5, 56, 5, 62, 5, 3, 6, 6, 6, 8, 6, 17, 6, 23, 6, 29, 6, 36, 6, 39, 6, 40, 6, 41, 6, 43, 6, 50, 6, 56, 6, 62, 6, 71, 6, 72, 6, 73, 6, 6, 7, 7, 7, 17, 7, 23, 7, 29, 7, 36, 7, 39, 7, 43, 7, 50, 7, 56, 7, 62, 7, 72, 7, 6, 8, 17, 8, 23, 8, 29, 8, 36, 8, 39, 8, 40, 8, 41, 8, 43, 8, 50, 8, 56, 8, 62, 8, 70, 8, 72, 8, 6, 9, 17, 9, 23, 9, 29, 9, 36, 9, 39, 9, 41, 9, 43, 9, 50, 9, 56, 9, 62, 9, 71, 9, 17, 10, 23, 10, 29, 10, 36, 10, 39, 10, 40, 10, 41, 10, 43, 10, 50, 10, 56, 10, 62, 10, 14, 12, 26, 12, 33, 12, 46, 12, 53, 12, 65, 12, 14, 13, 15, 13, 16, 13, 17, 13, 18, 13, 19, 13, 20, 13, 21, 13, 22, 13, 23, 13, 24, 13, 25, 13, 26, 13, 27, 13, 28, 13, 29, 13, 30, 13, 31, 13, 32, 13, 33, 13, 46, 13, 47, 13, 48, 13, 49, 13, 50, 13, 51, 13, 52, 13, 53, 13, 54, 13, 55, 13, 56, 13, 57, 13, 58, 13, 59, 13, 60, 13, 61, 13, 62, 13, 63, 13, 64, 13, 65, 13, 12, 14, 13, 14, 66, 14, 67, 14, 13, 15, 66, 15, 13, 16, 66, 16, 1, 17, 2, 17, 3, 17, 4, 17, 5, 17, 6, 17, 7, 17, 8, 17, 9, 17, 10, 17, 13, 17, 66, 17, 69, 17, 70, 17, 71, 17, 72, 17, 73, 17, 74, 17, 75, 17, 76, 17, 77, 17, 78, 17, 13, 18, 66, 18, 13, 19, 66, 19, 12, 20, 13, 20, 66, 20, 67, 20, 13, 21, 66, 21, 13, 22, 66, 22, 1, 23, 2, 23, 3, 23, 4, 23, 5, 23, 6, 23, 7, 23, 8, 23, 9, 23, 10, 23, 13, 23, 66, 23, 69, 23, 70, 23, 71, 23, 72, 23, 73, 23, 74, 23, 75, 23, 76, 23, 77, 23, 78, 23, 13, 24, 66, 24, 13, 25, 66, 25, 13, 26, 66, 26, 13, 27, 66, 27, 13, 28, 66, 28, 1, 29, 2, 29, 3, 29, 4, 29, 5, 29, 6, 29, 7, 29, 8, 29, 9, 29, 10, 29, 13, 29, 66, 29, 69, 29, 70, 29, 71, 29, 72, 29, 73, 29, 74, 29, 75, 29, 76, 29, 77, 29, 78, 29, 13, 30, 66, 30, 13, 31, 66, 31, 13, 32, 66, 32, 12, 33, 13, 33, 66, 33, 67, 33, 1, 36, 2, 36, 3, 36, 4, 36, 5, 36, 6, 36, 7, 36, 8, 36, 9, 36, 10, 36, 69, 36, 70, 36, 71, 36, 72, 36, 73, 36, 74, 36, 75, 36, 76, 36, 77, 36, 78, 36, 3, 38, 5, 38, 6, 38, 7, 38, 70, 38, 71, 38, 72, 38, 74, 38, 75, 38, 76, 38, 3, 39, 5, 39, 72, 39, 74, 39, 3, 40, 5, 40, 6, 40, 7, 40, 71, 40, 72, 40, 74, 40, 75, 40, 76, 40, 3, 41, 5, 41, 7, 41, 72, 41, 74, 41, 76, 41, 3, 42, 5, 42, 6, 42, 7, 42, 70, 42, 71, 42, 72, 42, 74, 42, 75, 42, 76, 42, 1, 43, 2, 43, 3, 43, 4, 43, 5, 43, 6, 43, 7, 43, 8, 43, 9, 43, 10, 43, 69, 43, 70, 43, 71, 43, 72, 43, 73, 43, 74, 43, 75, 43, 76, 43, 77, 43, 78, 43, 12, 46, 13, 46, 13, 47, 13, 48, 13, 49, 1, 50, 2, 50, 3, 50, 4, 50, 5, 50, 6, 50, 7, 50, 8, 50, 9, 50, 10, 50, 13, 50, 69, 50, 70, 50, 71, 50, 72, 50, 73, 50, 74, 50, 75, 50, 76, 50, 77, 50, 78, 50, 13, 51, 16, 51, 17, 51, 18, 51, 19, 51, 20, 51, 21, 51, 22, 51, 23, 51, 24, 51, 25, 51, 26, 51, 27, 51, 28, 51, 29, 51, 30, 51, 49, 51, 50, 51, 51, 51, 52, 51, 53, 51, 54, 51, 55, 51, 56, 51, 57, 51, 58, 51, 59, 51, 60, 51, 61, 51, 62, 51, 63, 51, 13, 52, 16, 52, 30, 52, 49, 52, 63, 52, 12, 53, 13, 53, 16, 53, 30, 53, 49, 53, 63, 53, 66, 53, 67, 53, 13, 54, 16, 54, 30, 54, 49, 54, 63, 54, 66, 54, 13, 55, 16, 55, 30, 55, 49, 55, 63, 55, 66, 55, 1, 56, 2, 56, 3, 56, 4, 56, 5, 56, 6, 56, 7, 56, 8, 56, 9, 56, 10, 56, 13, 56, 16, 56, 30, 56, 49, 56, 63, 56, 66, 56, 69, 56, 70, 56, 71, 56, 72, 56, 73, 56, 74, 56, 75, 56, 76, 56, 77, 56, 78, 56, 13, 57, 16, 57, 17, 57, 18, 57, 19, 57, 20, 57, 21, 57, 22, 57, 23, 57, 24, 57, 25, 57, 26, 57, 27, 57, 28, 57, 29, 57, 30, 57, 49, 57, 50, 57, 51, 57, 52, 57, 53, 57, 54, 57, 55, 57, 56, 57, 57, 57, 58, 57, 59, 57, 60, 57, 61, 57, 62, 57, 63, 57, 66, 57, 13, 58, 66, 58, 13, 59, 21, 59, 22, 59, 25, 59, 26, 59, 56, 59, 57, 59, 66, 59, 13, 60, 20, 60, 24, 60, 55, 60, 66, 60, 13, 61, 20, 61, 24, 61, 55, 61, 66, 61, 1, 62, 2, 62, 3, 62, 4, 62, 5, 62, 6, 62, 7, 62, 8, 62, 9, 62, 10, 62, 13, 62, 20, 62, 24, 62, 55, 62, 66, 62, 69, 62, 70, 62, 71, 62, 72, 62, 73, 62, 74, 62, 75, 62, 76, 62, 77, 62, 78, 62, 13, 63, 21, 63, 22, 63, 25, 63, 26, 63, 56, 63, 57, 63, 66, 63, 13, 64, 66, 64, 12, 65, 13, 65, 66, 65, 67, 65, 14, 66, 15, 66, 16, 66, 17, 66, 18, 66, 19, 66, 20, 66, 21, 66, 22, 66, 23, 66, 24, 66, 25, 66, 26, 66, 27, 66, 28, 66, 29, 66, 30, 66, 31, 66, 32, 66, 33, 66, 53, 66, 54, 66, 55, 66, 56, 66, 57, 66, 58, 66, 59, 66, 60, 66, 61, 66, 62, 66, 63, 66, 64, 66, 65, 66, 14, 67, 20, 67, 33, 67, 53, 67, 65, 67, 4, 69, 17, 69, 23, 69, 29, 69, 36, 69, 43, 69, 50, 69, 56, 69, 62, 69, 4, 70, 7, 70, 8, 70, 9, 70, 17, 70, 23, 70, 29, 70, 36, 70, 43, 70, 50, 70, 56, 70, 62, 70, 4, 71, 8, 71, 12, 71, 14, 71, 15, 71, 16, 71, 17, 71, 19, 71, 20, 71, 21, 71, 23, 71, 25, 71, 26, 71, 27, 71, 29, 71, 31, 71, 32, 71, 33, 71, 36, 71, 38, 71, 39, 71, 40, 71, 41, 71, 43, 71, 45, 71, 46, 71, 47, 71, 48, 71, 50, 71, 52, 71, 54, 71, 56, 71, 58, 71, 59, 71, 60, 71, 62, 71, 64, 71, 65, 71, 66, 71, 73, 71, 4, 72, 6, 72, 8, 72, 12, 72, 14, 72, 16, 72, 17, 72, 19, 72, 21, 72, 23, 72, 25, 72, 27, 72, 29, 72, 33, 72, 36, 72, 38, 72, 43, 72, 45, 72, 50, 72, 52, 72, 54, 72, 56, 72, 60, 72, 62, 72, 66, 72, 72, 72, 73, 72, 4, 73, 7, 73, 12, 73, 14, 73, 16, 73, 17, 73, 19, 73, 20, 73, 21, 73, 23, 73, 25, 73, 26, 73, 27, 73, 29, 73, 33, 73, 36, 73, 38, 73, 39, 73, 40, 73, 41, 73, 43, 73, 45, 73, 46, 73, 47, 73, 48, 73, 50, 73, 52, 73, 53, 73, 54, 73, 56, 73, 59, 73, 60, 73, 62, 73, 64, 73, 65, 73, 66, 73, 71, 73, 72, 73, 73, 73, 74, 73, 75, 73, 76, 73, 77, 73, 78, 73, 4, 74, 12, 74, 14, 74, 16, 74, 17, 74, 21, 74, 23, 74, 25, 74, 27, 74, 29, 74, 33, 74, 36, 74, 38, 74, 41, 74, 43, 74, 48, 74, 50, 74, 54, 74, 56, 74, 60, 74, 62, 74, 64, 74, 70, 74, 71, 74, 72, 74, 73, 74, 74, 74, 75, 74, 76, 74, 77, 74, 78, 74, 4, 75, 5, 75, 6, 75, 7, 75, 8, 75, 9, 75, 10, 75, 12, 75, 14, 75, 15, 75, 16, 75, 17, 75, 19, 75, 20, 75, 21, 75, 23, 75, 25, 75, 26, 75, 27, 75, 29, 75, 33, 75, 36, 75, 38, 75, 39, 75, 40, 75, 41, 75, 43, 75, 45, 75, 46, 75, 47, 75, 48, 75, 50, 75, 54, 75, 56, 75, 58, 75, 59, 75, 60, 75, 62, 75, 64, 75, 65, 75, 66, 75, 71, 75, 72, 75, 73, 75, 74, 75, 75, 75, 76, 75, 77, 75, 78, 75, 17, 76, 23, 76, 29, 76, 36, 76, 43, 76, 50, 76, 56, 76, 62, 76, 72, 76, 73, 76, 17, 77, 23, 77, 29, 77, 36, 77, 43, 77, 50, 77, 56, 77, 62, 77, 73, 77, 17, 78, 23, 78, 29, 78, 36, 78, 43, 78, 50, 78, 56, 78, 62, 78 };

/* All the int variables */
int sound=0;
int start=0;
int startgame=0;
int currentplayer=1;
int d1=0;
int d2=0;
int dtotal;
int p1money=1500;
int p2money=1500;
int spacenum=1;
int player1spc=1;
int player2spc=1;
int p1injail=0;
int p2injail=0;
int spcnum=1;
int *psp=NULL;
int *pmp=NULL;
int *pmp2=NULL;
int charge=0;
int spcrent=0;
int plyr=0;
int loops=0;
int switchp=0;
int inctax=0;
int dowhat, x=0;
int paid=0;
int otherutil=0;
int otherrr[3]={0,0,0};
int winner=0;
int p1rollnum=0;
int p2rollnum=0;
int *r=NULL;
int y=0;

/* All the char variables */
static char player1[9];
static char player2[9];
static char dice[9];
static char space[10];
static char dollars[15];
static char eins[23];
static char zwei[10];
static char drei[51];
static char vier[20];
static char funf[11];
static char *spcname[50];
static char tax[20];
static char ownedby[41];
static char cntnue[29]="Press Any Key to Continue...";

/* byte variables for save() and load() */
byte writebuf[105];
byte readbuf[105];
byte moneyspace[22];

save()
{
	ozcls();
	ozputs(0,70,"Saving...");
	ozopendatamemowrite("zz:monopoly.sav",'1');
	ozwritedatamemo(player1,sizeof(player1));
	ozwritedatamemo(player2,sizeof(player2));
	ozwritedatamemo(owner,sizeof(owner));
	ozwritedatamemo(hothouse,sizeof(hothouse));
	ozwritedatamemo(&p1money,sizeof(p1money));
	ozwritedatamemo(&p2money,sizeof(p2money));
	ozwritedatamemo(&player1spc,sizeof(player1spc));
	ozwritedatamemo(&player2spc,sizeof(player2spc));
	ozwritedatamemo(&p1injail,sizeof(p1injail));
	ozwritedatamemo(&p2injail,sizeof(p2injail));
	ozwritedatamemo(&currentplayer,sizeof(currentplayer));
	ozclosedatamemowrite();
}

load()
{
	ozcls();
	ozputs(0,70,"Loading...");
	x=ozopendatamemoread("zz:monopoly.sav");
	if(x<0)
	{
		ozputs(0,0,"Save file not found!");
		ozputs(0,70,cntnue);
		ozngetch();
		return;
	}
	ozreaddatamemo(player1,sizeof(player1));
	ozreaddatamemo(player2,sizeof(player2));
	ozreaddatamemo(owner,sizeof(owner));
	ozreaddatamemo(hothouse,sizeof(hothouse));
	ozreaddatamemo(&p1money,sizeof(p1money));
	ozreaddatamemo(&p2money,sizeof(p2money));
	ozreaddatamemo(&player1spc,sizeof(player1spc));
	ozreaddatamemo(&player2spc,sizeof(player2spc));
	ozreaddatamemo(&p1injail,sizeof(p1injail));
	ozreaddatamemo(&p2injail,sizeof(p2injail));
	ozreaddatamemo(&currentplayer,sizeof(currentplayer));
	startgame=1;
	play();
}

endgame()
{
	ozcls();
	switch(winner)
	{
		case 1: sprintf(drei,"%s won this game.",player1);
		case 2: sprintf(drei,"%s won this game.",player2);
	}
	ozputs(0,0,"Game Over!");
	ozputs(0,10,drei);
	ozputs(0,70,cntnue);
	ozngetch();
	main();
}

list()
{
	for(;;)
	{
		ozcls();
		putspace();
		sprintf(drei,"%s",*names[spcnum]);
		ozputs(0,10,space);
		ozputs(0,20,drei);
		ozputs(0,40,"Press <ENTER> for details.");
		ozputs(0,70,"Press <ESC> to return to main.");
		switch(ozngetch())
		{
			case KEY_PAGEUP:
			{
				if(spacenum<40)
				{
					spacenum+=1;
					spcnum=spacenum;
				}
				else if(spacenum==40)
				{
					spacenum=1;
					spcnum=spacenum;
				}
				break;
			}
			case KEY_PAGEDOWN:
			{
				if(spacenum>1)
				{
					spacenum-=1;
					spcnum=spacenum;
				}
				else if(spacenum==1)
				{
					spacenum=40;
					spcnum=spacenum;
				}
				break;
			}
			case KEY_LOWER_ENTER:
			case KEY_UPPER_ENTER: ozcls(); spaceinfo(); break;
			case KEY_LOWER_ESC:
			case KEY_UPPER_ESC: return;
		}
	}
}

buyh()
{
	int houseprice=0;
	int housenum=0;
	int h=0;
	ozcls();
	if(spcnum>1&&spcnum<11) houseprice=50;
	else if(spcnum>11&&spcnum<21) houseprice=100;
	else if(spcnum>21&&spcnum<31) houseprice=150;
	else if(spcnum>31&&spcnum<41) houseprice=200;
	ozputs(0,0,"Buy Houses/Hotels");
	ozputs(0,20,"How many houses to buy?");
	ozputs(0,30,"a) 1  b) 2  c) 3  d) 4  e) 4 houses and hotel");
	sprintf(drei,"Cost per house: $%d",houseprice);
	switch(ozngetch())
	{
		case 'a': housenum=1; break;
		case 'b': housenum=2; break;
		case 'c': housenum=3; break;
		case 'd': housenum=4; break;
		case 'e': housenum=5; break;
	}
	switch(currentplayer)
	{
		case 1: pmp=&p1money; break;
		case 2: pmp=&p2money; break;
	}
	if(housenum+hothouse[spcnum]>5)
	{
		x=ozputs(0,70,"Too many houses.  ");
		ozputs(x,70,cntnue);
		ozngetch();
		buyh();
	}
	if(houseprice*housenum>*pmp)
	{
		x=ozputs(0,70,"Not enough cash!  ");
		ozputs(x,70,cntnue);
		ozngetch();
		buyh();
	}
	else
	{
		for(h=housenum;h>0;h--)
		{
			hothouse[spcnum]++;
			*pmp-=houseprice;
		}
	}
}

rentrr()
{
	paid=0;
	charge=50;
	switch(currentplayer)
	{
		case 1: pmp=&p1money; pmp2=&p2money; plyr=2; break;
		case 2: pmp=&p2money; pmp2=&p1money; plyr=1; break;
	}
	switch(*psp)
	{
		case 6: otherrr[0]=16; otherrr[1]=26; otherrr[2]=36; break;
		case 16: otherrr[0]=6; otherrr[1]=26; otherrr[2]=36; break;
		case 26: otherrr[0]=6; otherrr[1]=16; otherrr[2]=36; break;
		case 36: otherrr[0]=6; otherrr[1]=16; otherrr[2]=26; break;
	}
	if(owner[otherrr[0]]==plyr) charge+=50;
	if(owner[otherrr[1]]==plyr) charge+=50;
	if(owner[otherrr[2]]==plyr) charge+=50;
	*pmp=(*pmp-charge);
	*pmp2=(*pmp2+charge);
	rentnotice();
	ozngetch();
}

rentutil()
{
	paid=0;
	switch(currentplayer)
	{
		case 1: pmp=&p1money; pmp2=&p2money; plyr=2; break;
		case 2: pmp=&p2money; pmp2=&p1money; plyr=1; break;
	}
	switch(*psp)
	{
		case 13: otherutil=29; break;
		case 29: otherutil=13; break;
	}
	if((owner[*psp]==plyr)&&(owner[otherutil]==plyr))
	{
		charge=(dtotal*10);
	}
	else charge=(dtotal*4);
	*pmp=(*pmp-charge);
	*pmp2=(*pmp2+charge);
	rentnotice();
	ozngetch();
}

rentspace()
{
	paid=0;
	switch(currentplayer)
	{
		case 1: pmp=&p1money; plyr=2; break;
		case 2: pmp=&p2money; plyr=1; break;
	}
	switch(hothouse[*psp])
	{
		case 0:
		{
			spcrent=rent0[*psp];
			switch(owner[*psp])
			{
				case 1: pmp2=&p1money; break;
				case 2: pmp2=&p2money; break;
			}
			switch(monopoly())
			{
				case -1: charge=spcrent; break;
				case 1: charge=(spcrent*2); break;
			}
			*pmp=(*pmp-charge);
			*pmp2=(charge+*pmp2);
			paid=1;
			break;
		}
		case 1: spcrent=rent1[*psp]; break;
		case 2: spcrent=rent2[*psp]; break;
		case 3: spcrent=rent3[*psp]; break;
		case 4: spcrent=rent4[*psp]; break;
		case 5: spcrent=rent5[*psp]; break;
	}
	switch(paid)
	{
		case 0:
		{
			charge=spcrent;
			*pmp=(*pmp-charge);
			switch(owner[*psp])
			{
				case 1: pmp2=&p1money; break;
				case 2: pmp2=&p2money; break;
			}
			*pmp2+=charge;
			break;
		}
		case 1: break;
	}
	rentnotice();
	ozngetch();
}

rentnotice()
{
	ozcls();
	ozputs(0,0,"RENT DUE!");
	sprintf(drei,"You have landed on %s.",*names[*psp]);
	ozputs(0,10,drei);
	sprintf(drei,"It is owned by %s.",*spcname);
	ozputs(0,20,drei);
	sprintf(drei,"You have been charged $%d rent.  Have a nice day!",charge);
	ozputs(0,30,drei);
	ozputs(0,70,cntnue);
}

buyrr()
{
	ozcls();
	*name=*names[*psp];
	sprintf(eins,"%s: $%d",*name,prices[*psp]);
	ozputs(0,0,eins);
	rr();
	ozputs(0,60,"Buy this property? (y/N)");
	putmoney();
	ozputs(0,70,dollars);
	switch(ozngetch())
	{
		case 'y': purchase(); break;
	}
}

buyutil()
{
	ozcls();
	*name=*names[*psp];
	sprintf(eins,"%s: $%d",*name,prices[*psp]);
	ozputs(0,0,eins);
	util();
	ozputs(0,60,"Buy this property? (y/N)");
	putmoney();
	ozputs(0,70,dollars);
	switch(ozngetch())
	{
		case 'y': purchase(); break;
	}
}

jail()
{
	ozcls();
	switch(currentplayer)
	{
		case 1: p1injail=1; player1spc=11; p1rollnum=0; break;
		case 2: p2injail=1; player2spc=11; p2rollnum=0; break;
	}
	x=ozputs(0,0,"You are in Jail!  ");
	ozputs(x,0,cntnue);
	ozngetch();
}

purchase()
{
	owner[*psp]=currentplayer;
	putmoney();
	if(*pmp<prices[*psp])
	{
		x=ozputs(0,70,"Not enough cash!  ");
		ozputs(x,70,cntnue);
		ozngetch();
		return;
	}
	*pmp-=prices[*psp];
	x=ozputs(0,70,"Purchased.  ");
	ozputs(x,70,cntnue);
	ozngetch();
}

buyspace()
{
	if(owner[*psp]!=0) return;
	if(*psp==1|*psp==3|*psp==5|*psp==8|*psp==11|*psp==18|*psp==21|*psp==23|*psp==31|*psp==34|*psp==37|*psp==39)
	{
		return;
	}
	ozcls();
	*name=*names[*psp];
	sprintf(eins,"%s: $%d",*name,prices[*psp]);
	sprintf(zwei,"Rent: $%d",rent0[*psp]);
	sprintf(drei,"With 1 HOUSE: $%d  2: $%d  3: $%d  4: $%d",rent1[*psp],rent2[*psp],rent3[*psp],rent4[*psp]);
	sprintf(vier,"With HOTEL: $%d",rent5[*psp]);
	ozputs(0,0,eins);
	ozputs(0,10,zwei);
	ozputs(0,20,drei);
	ozputs(0,30,vier);
	ozputs(0,40,funf);
	ozputs(0,50,"Would you like to buy this? (y/N)");
	putmoney();
	ozputs(0,60,dollars);
	switch(ozngetch())
	{
		case 'y': purchase(); break;
	}
}

incometax()
{
	if(currentplayer==1) pmp=&p1money;
	else if(currentplayer==2) pmp=&p2money;
	inctax=(*pmp/10);
	*pmp-=inctax;
	sprintf(tax,"-$%d (10 percent)",inctax);
	ozcls();
	x=ozputs(0,0,"Income Tax!  ");
	ozputs(x,0,tax);
	ozputs(115,72,cntnue);
	ozngetch();
}

luxtax()
{
	if(currentplayer==1) pmp=&p1money;
	else if(currentplayer==2) pmp=&p2money;
	*pmp-=75;
	ozcls();
	ozputs(0,0,"$75 Luxury Tax!");
	ozputs(115,72,cntnue);
	ozngetch();
}

checkspace()
{
	switch(owner[*psp])
	{
		case 1: *spcname=player1; break;
		case 2: *spcname=player2; break;
	}
	switch(currentplayer)
	{
		case 1:
		{
			psp=&player1spc;
			switch(owner[*psp])
			{
				case 1: dowhat=0; break;
				case 2: dowhat=1; break;
				case 0: dowhat=2; break;
			}
			break;
		}
		case 2:
		{
			psp=&player2spc;
			switch(owner[*psp])
			{
				case 2: dowhat=0; break;
				case 1: dowhat=1; break;
				case 0: dowhat=2; break;
			}
			break;
		}
	}
	if(*psp==5) incometax();
	if(*psp==31) jail();
	if(*psp==39) luxtax();
	switch(dowhat)
	{
		case 0: return;
		case 2:
		{
			if(*psp==6|*psp==16|*psp==26|*psp==36) buyrr();
			else if(*psp==13|*psp==29) buyutil();
			else buyspace();
			break;
		}
		case 1:
		{
			switch(*psp)
			{
				case 6:
				case 16:
				case 26:
				case 36: rentrr(); break;
				case 13:
				case 29: rentutil(); break;
				default: rentspace(); break;
			}
			break;
		}
	}
}

move()
{
	switch(currentplayer)
	{
		case 1:
		{
			for(loops=dtotal;loops>0;loops--)
			{
				switch(player1spc)
				{
					case 40: player1spc=0; break;
				}
				player1spc++;
				if(player1spc==1) p1money+=200;
			}
			break;
		}
		case 2:
		{
			for(loops=dtotal;loops>0;loops--)
			{
				switch(player2spc)
				{
					case 40: player2spc=0; break;
				}
				player2spc++;
				if(player2spc==1) p2money+=200;
			}
			break;
		}
	}
	checkspace();
}

rolldice()
{
	switch(rand()%6)
	{
		case 0: d1=1; break;
		case 1: d1=2; break;
		case 2: d1=3; break;
		case 3: d1=4; break;
		case 4: d1=5; break;
		case 5: d1=6; break;
	}
	srand(ozsec()+60*ozmin());
	switch(rand()%6)
	{
		case 0: d2=1; break;
		case 1: d2=2; break;
		case 2: d2=3; break;
		case 3: d2=4; break;
		case 4: d2=5; break;
		case 5: d2=6; break;
	}
	dtotal=(d1+d2);
	sprintf(dice,"Dice: %d",dtotal);
	move();
}

rr()
{
	ozputs(0,10,"Rent: $25");
	ozputs(0,20,"If 2 R.R.'s are owned: $50, If 3: $100, If 4: $200");
	switch(owner[*psp])
	{
		case 0: *spcname="no one"; break;
		case 1: *spcname=&player1; break;
		case 2: *spcname=&player2; break;
	}
	sprintf(ownedby,"Owned by %s.",*spcname);
	ozputs(0,50,ownedby);
}

util()
{
	ozputs(0,10,"If one Utility is owned,");
	ozputs(0,20,"rent is 4x dice.  If both are");
	ozputs(0,30,"owned, rent is 10x dice.");
	switch(owner[*psp])
	{
		case 0: *spcname="no one"; break;
		case 1: *spcname=&player1; break;
		case 2: *spcname=&player2; break;
	}
	sprintf(ownedby,"Owned by %s.",*spcname);
	ozputs(0,50,ownedby);
}

cc()
{
}

c()
{
}

int monopoly()
{
	switch(spcnum)
	{
		case 2:
		case 4: if(owner[2]==plyr&&owner[4]==plyr) return 1;
		case 7:
		case 9:
		case 10: if(owner[7]==plyr&&owner[9]==plyr&&owner[10]==plyr) return 1;
		case 12:
		case 14:
		case 15: if(owner[12]==plyr&&owner[14]==plyr&&owner[15]==plyr) return 1;
		case 17:
		case 19:
		case 20: if(owner[17]==plyr&&owner[19]==plyr&&owner[20]==plyr) return 1;
		case 22:
		case 24:
		case 25: if(owner[22]==plyr&&owner[24]==plyr&&owner[25]==plyr) return 1;
		case 27:
		case 28:
		case 30: if(owner[27]==plyr&&owner[28]==plyr&&owner[30]==plyr) return 1;
		case 32:
		case 33:
		case 35: if(owner[32]==plyr&&owner[33]==plyr&&owner[35]==plyr) return 1;
		case 38:
		case 40: if(owner[38]==plyr&&owner[40]==plyr) return 1;
	}
	return -1;
}

spacefilter()
{
	sprintf(eins,"%s: $%d",*names[spcnum],prices[spcnum]);
	sprintf(zwei,"Rent: $%d",rent0[spcnum]);
	sprintf(drei,"With 1 HOUSE: $%d  2: $%d  3: $%d  4: $%d",rent1[spcnum],rent2[spcnum],rent3[spcnum],rent4[spcnum]);
	sprintf(vier,"With HOTEL: $%d",rent5[spcnum]);
	ozputs(0,0,eins);
	ozputs(0,10,zwei);
	ozputs(0,20,drei);
	ozputs(0,30,vier);
	ozputs(0,40,funf);
	switch(owner[spcnum])
	{
		case 0: *spcname="no one"; break;
		case 1: *spcname=&player1; break;
		case 2: *spcname=&player2; break;
	}
	sprintf(ownedby,"Owned by %s.",*spcname);
	ozputs(0,50,ownedby);
	switch(hothouse[spcnum])
	{
		case 0: x=ozputs(0,60,"No houses."); break;
		case 1: x=ozputs(0,60,"1 house"); break;
		case 2: x=ozputs(0,60,"2 houses"); break;
		case 3: x=ozputs(0,60,"3 houses"); break;
		case 4: x=ozputs(0,60,"4 houses"); break;
		case 5: x=ozputs(0,60,"Hotel"); break;
	}
	plyr=currentplayer;
	if(owner[spcnum]==currentplayer&&monopoly()==1)
	{
		ozputs(x,60,"  Press 'B' to buy houses/hotels");
		ozputs(95,72,cntnue);
		switch(ozngetch())
		{
			case 'b': buyh(); break;
		}
	}
	else
	{
		ozputs(115,72,cntnue);
		ozngetch();
	}
}

specialspacefilter()
{
	ozputs(0,0,*names[spcnum]);
	psp=&spcnum;
	switch(spcnum)
	{
		case 1:
		{
			ozputs(0,0,"GO!  Collect $200 as you pass!");
			break;
		}
		case 3:
		{
			cc();
			break;
		}
		case 5:
		{
			ozputs(0,10,"Pay 10%");
			break;
		}
		case 6:
		case 16:
		case 26:
		case 36: rr(); break;
		case 8:
		{
			c();
			break;
		}
		case 11:
		{
			break;
		}
		case 13:
		{
			util();
			break;
		}
		case 18:
		{
			cc();
			break;
		}
		case 21:
		{
			ozputs(0,10,"This space is only a resting place for your piece.");
			break;
		}
		case 23:
		{
			c();
			break;
		}
		case 29:
		{
			util();
			break;
		}
		case 31:
		{
			break;
		}
		case 34:
		{
			cc();
			break;
		}
		case 37:
		{
			c();
			break;
		}
		case 39:
		{
			ozputs(0,10,"Pay $75");
			break;
		}
	}
	start=0;
	ozputs(115,70,cntnue);
	ozngetch();
}

spaceinfo()
{
	start=0;
	if(spcnum==1|spcnum==3|spcnum==5|spcnum==6|spcnum==8|spcnum==11|spcnum==13|spcnum==16|spcnum==18|spcnum==21|spcnum==23|spcnum==26|spcnum==29|spcnum==31|spcnum==34|spcnum==36|spcnum==37|spcnum==39)
	{
		specialspacefilter();
	}
	else spacefilter();
}

putspace()
{
	sprintf(space,"Space: %d",spacenum);
}

putmoney()
{
	switch(currentplayer)
	{
		case 1: pmp=&p1money; break;
		case 2: pmp=&p2money; break;
	}
	sprintf(dollars,"Money: $%d",*pmp);
}

about()
{
	ozcls();
	ozputs(0,0,"OZ Monopoly Copyright (C) Chris Daniel 2002");
	ozputs(0,10,"Monopoly is a trademark of Parker Brothers, Inc.");
	ozputs(0,30,"Source available: http://cjd1701.vze.com");
	ozputs(0,70,cntnue);
	ozngetch();
}

switchplayer()
{
	switch(currentplayer)
	{
		case 1: currentplayer=2; break;
		case 2: currentplayer=1; break;
	}
}

paybail()
{
	switch(currentplayer)
	{
		case 1: pmp=&p1money; r=&p1rollnum; break;
		case 2: pmp=&p2money; r=&p2rollnum; break;
	}
	if(*pmp<=50)
	{
		ozcls();
		ozputs(0,10,"Not enough cash.");
		if(*r==3)
		{
			switch(currentplayer)
			{
				case 1: winner=2; break;
				case 2: winner=1; break;
			}
			endgame();
		}
		ozngetch();
	}
	else
	{
		ozcls();
		*pmp-=50;
		switch(currentplayer)
		{
			case 1: p1injail=0; break;
			case 2: p2injail=0; break;
		}
		ozputs(0,10,"$50 bail has been deducted from your cash.");
		ozputs(0,20,"You are now free!");
		ozputs(115,70,cntnue);
		ozngetch();
	}
}

jaildice()
{
	switch(currentplayer)
	{
		case 1: r=&p1rollnum; break;
		case 2: r=&p2rollnum; break;
	}
	switch(rand()%6)
	{
		case 0: d1=1; break;
		case 1: d1=2; break;
		case 2: d1=3; break;
		case 3: d1=4; break;
		case 4: d1=5; break;
		case 5: d1=6; break;
	}
	switch(rand()%6)
	{
		case 0: d2=1; break;
		case 1: d2=2; break;
		case 2: d2=3; break;
		case 3: d2=4; break;
		case 4: d2=5; break;
		case 5: d2=6; break;
	}
	switch(*r)
	{
		case 0: *r++; break;
		case 1: *r++; break;
		case 2: *r++; break;
		case 3:
		{
			ozputs(0,20,"You did not get doubles.");
			paybail();
			break;
		}
	}
	dtotal=(d1+d2);
	if(d1==d2)
	{
		switch(currentplayer)
		{
			case 1: p1injail=0; break;
			case 2: p2injail=0; break;
		}
		ozcls();
		switchp=0;
		ozputs(0,0,"You have been released!");
		sprintf(drei,"You rolled doubles; two %ds.",d1);
		ozputs(0,10,drei);
		ozputs(0,70,cntnue);
		ozngetch();
		return;
	}
	else switchp=1;
}

playjail()
{
	if(start==0)
	{
		ozcls();
		drawboard();
		putmoney();
		switch(currentplayer)
		{
			case 1: x=ozputs(90,0,player1); ozputs(x,0,"'s turn"); break;
			case 2: x=ozputs(90,0,player2); ozputs(x,0,"'s turn"); break;
		}
		ozputs(90,10,"You are in Jail!");
		ozputs(90,20,"'R' to roll dice, or");
		ozputs(90,30,"'P' to pay $50 bail.");
		ozputs(90,70,dollars);
	}
	switch(ozngetch())
	{
		case 'r': jaildice(); start=0; break;
		case KEY_NEWLINE: ozsnap(); ozsnap(); ozsnap(); break;
		case 'p':
		{
			paybail();
			break;
		}
	}
	play();
}

play()
{
	while(1)
	{
		if(switchp==1) switchplayer(); switchp=0;
		switch(currentplayer)
		{
			case 1: if(p1injail==1) playjail(); break;
			case 2: if(p2injail==1) playjail(); break;
		}
		if(startgame==0)
		{
			ozcls();
			ozputs(0,0,"Player 1, Enter Your Name:");
			ozeditline(0,10,player1,31,239);
			ozputs(0,20,"Player 2, Enter Your Name:");
			ozeditline(0,30,player2,31,239);
			startgame=1;
		}
		if(start==0)
		{
			ozcls();
			drawboard();
			switch(currentplayer)
			{
				case 1: x=ozputs(90,0,player1); ozputs(x,0,"'s turn"); break;
				case 2: x=ozputs(90,0,player2); ozputs(x,0,"'s turn"); break;
			}
			ozputs(90,10,"'R': Roll dice");
			ozputs(160,10,dice);
			ozputs(90,20,"'I': Info and houses");
			ozputs(90,30,"'S': Save Game");
			switch(currentplayer)
			{
				case 1:
				{
					if(p1money<=0)
					{
						winner=2;
						endgame();
					}
					switch(p1injail)
					{
						case 0: sprintf(drei,"%d: %s",player1spc,*names[player1spc]); break;
						case 1: sprintf(drei,"In Jail!"); break;
					}
					break;
				}
				case 2:
				{
					if(p2money<=0)
					{
						winner=1;
						endgame();
					}
					switch(p2injail)
					{
						case 0: sprintf(drei,"%d: %s",player2spc,*names[player2spc]); break;
						case 1: sprintf(drei,"In Jail!"); break;
					}
					break;
				}
			}
			ozputs(90,50,drei);
			start=1;
		}
		putmoney();
		ozputs(90,70,dollars);
		switch(ozngetch())
		{
			case 'r': rolldice(); start=0; switchp=1; break;
			case 'i': ozcls(); list(); start=0; break;
			case 's': save(); start=0; break;
			case KEY_NEWLINE: ozsnap(); ozsnap(); ozsnap(); break;
		}
	}
}

drawboard()
{
	int i;
	_ozvline(0,0,80,BLACK);
	_ozvline(11,0,80,BLACK);
	_ozvline(68,0,80,BLACK);
	_ozvline(79,0,80,BLACK);
	_ozhline(0,0,80,BLACK);
	_ozhline(0,11,80,BLACK);
	_ozhline(0,68,80,BLACK);
	_ozhline(0,79,80,BLACK);
	for(i=0;i<=sizeof(picdata)/2;i+=2)
	{
		ozpoint(picdata[i],picdata[i+1],BLACK);
	}
	ozputs(15,37,"MONOPOLY");
}

main()
{
	while(1)
	{
		ozclick(0);
		srand(ozsec()+60*ozmin());
		ozcls();
		switchp=0;
		ozsetfont(FONT_OZ_LARGE);
		ozputs(0,0,"OZ Monopoly");
		ozsetfont(FONT_OZ_NORMAL);
		ozputs(80,3,"Version 0.9b");
		ozputs(0,13,"Made with Hi-Tech C; USE AT YOUR OWN RISK!");
		ozputs(0,72,"Wizard Version Copyright (C) 2002 Christopher J. Daniel");
		ozputs(0,28,"(1) Play OZ Monopoly");
		ozputs(0,38,"(2) Load Saved Game");
		ozputs(0,48,"(3) About");
		ozputs(0,58,"(4) Quit OZ Monopoly");
		switch(ozngetch())
		{
			case '1': play(); break;
			case '2': load(); break;
			case '3': about(); break;
			case '4': exit(0);
		}
	}
}