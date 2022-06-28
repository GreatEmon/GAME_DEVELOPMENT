#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "iGraphics.h"

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720

using namespace std;

/*-----------------------------------------------------------------

    Title                    : SHOOT DADDY
    Description              : A shooting game to shoot bird
    Developer                : EMON SHERKAR
    Version                  : 1.00.00
    Programming Language     : C and C++
    Graphics Utility         : IGRAPHICS(OPENGL Short version)

-------------------------------------------------------------------*/


//All used function prototype
int getScore();
void enterName();
void changePosition();
void changeimg();
void setEnemy();
void checkIsAlive();
int sethighscore();



//Include File and asset
char screen[7][40]       = {"project//images//firstscreen.bmp","project//images//bgmain.bmp","project//images//highbg.bmp","project//images//insbg.bmp","project//images//settingsbg.bmp","project//images//name.bmp","project//images//score.bmp"};
char button[4][40]       = {"project//images//newgame.bmp","project//images//high.bmp","project//images//ins.bmp","project//images//settings.bmp"};
char asset[5][40]        = {"project//images//gun.bmp","project//images//gunfront.bmp","project//images//gun2.bmp","project//images//life.bmp","project//images//extra//shooter.bmp"};
char background[12][50]  = {"project//images//background//bg1//11.bmp","project//images//background//bg1//12.bmp","project//images//background//bg1//13.bmp","project//images//background//bg1//14.bmp","project//images//background//bg1//15.bmp","project//images//background//bg1//16.bmp","project//images//background//bg1//17.bmp","project//images//background//bg1//18.bmp","project//images//background//bg1//19.bmp","project//images//background//bg1//110.bmp","project//images//background//bg1//111.bmp","project//images//background//bg1//112.bmp"};
char greenbird[9][50]    = {"project//images//birds//green//green1.bmp","project//images//birds//green//green2.bmp","project//images//birds//green//green3.bmp","project//images//birds//green//green4.bmp","project//images//birds//green//green5.bmp","project//images//birds//green//green6.bmp","project//images//birds//green//green7.bmp","project//images//birds//green//green8.bmp","project//images//birds//green//green9.bmp"};
char redbird[14][50]     = {"project//images//birds//red//red1.bmp","project//images//birds//red//red2.bmp","project//images//birds//red//red3.bmp","project//images//birds//red//red4.bmp","project//images//birds//red//red5.bmp","project//images//birds//red//red6.bmp","project//images//birds//red//red7.bmp","project//images//birds//red//red8.bmp","project//images//birds//red//red9.bmp","project//images//birds//red//red10.bmp","project//images//birds//red//red11.bmp","project//images//birds//red//red12.bmp","project//images//birds//red//red13.bmp","project//images//birds//red//red14.bmp"};
char vanish[7][40]       = {"project//images//vanish//v1.bmp","project//images//vanish//v2.bmp","project//images//vanish//v3.bmp","project//images//vanish//v4.bmp","project//images//vanish//v5.bmp","project//images//vanish//v6.bmp","project//images//vanish//v7.bmp"};
char shoot[4][40]        = {"project//images//shoot//s1.bmp","project//images//shoot//s2.bmp","project//images//shoot//s3.bmp","project//images//shoot//s4.bmp"};
char music[3][40]        = {"project//music//mainback.wav","project//music//gameend.wav","project//music//shoot.wav"};
char backupbg[40]        = {"project//images//bg2.bmp"};
char filelocation[40]    = {"project//file//highScore.txt"};


//Structure for Coordinates
typedef struct coordinate
{
    int x;
    int y;
} bcoordinate[4];

typedef struct lifes
{
    int x;
    int y;
} love[5];

const int birdNum = 200;

typedef struct greenbird
{
    int x;
    int y;
    int birdindex;
    bool alive;
} gbird[birdNum];

typedef struct redbird
{
    int x;
    int y;
    int birdindex;
    bool alive;
} rbird[birdNum];


/*----------------------------------------------------

    GAMESTATE VALUE     |    SCREEN
    -------------------------------------
         0              : Splash Screen
         1              : Main Screen
         2              : High Score
         3              : Instruction
         4              : Settings
         5              : Input Name
         6              : Start game
         7              : Score Board

------------------------------------------------------*/



//main variable
int i=0;
int j=0;
int cosum=170;


//integer variable
int gamestate = 0;
int firstscreencounter =0;
int fscore;
int settingsx=456;
int settingsy=377;
int rl=140;
int rw=72;
int strIndex = 0;
int gunx=0;
int gunIndex=0;
int life=5;
int sumlife = 60;
int gbirdNum = 1;
int rbirdNum = 10;
int gBirdSpeed = 1;
int rBirdSpeed = 1;
int gbirdcounter = 0;
int rbirdcounter = 0;
int score;
int highscore;
int rbirdadd = 8;
int gbirdadd = 2;
int vanishx;
int vanishy;
int vanishindex=0;
int shootx;
int shooty;
int shootindex=0;
int hitcounter=0;

//char variable for itext
char ch1[20] = "SHOOT DADDY";
char ch2[10] = "SCORE : ";
char ch3[30] = "Please Enter Your Name !";
char ch4[30] = "First C++ Game Development";
char str[50];
char scorec[10];
char highc[10];


//structure decleration
bcoordinate buttonxy;
love lifexy;
gbird gxy;
rbird rxy;


//boolian variable
bool musicon=true;
bool musicoff = false;
bool hasName = true;
bool IsVanish = false ;
bool IsShoot = false;
bool ishit = false;


//File pointer
FILE *fptr;



//Main Function
void iDraw()
{
    //place your drawing codes here
    iClear();

    if(gamestate == 0)
    {
        iShowBMP(0,0,screen[gamestate]);
        firstscreencounter++;
        //Splash screen timer
        if(firstscreencounter>=200)
        {
            gamestate=1;
        }
    }
    else if(gamestate==1)
    {
        iShowBMP(0,0,screen[gamestate]);
        for(i=0; i<4; i++)
        {
            iShowBMP(buttonxy[i].x,buttonxy[i].y,button[i]);
        }
    }

    //High Score
    else if(gamestate==2)
    {
        iShowBMP(0,0,screen[gamestate]);
        //high Score fetching
        sprintf(highc, "%d", highscore);
        iSetColor(255,255,255);
        iText(430,455,highc,GLUT_BITMAP_TIMES_ROMAN_24);
        iRectangle(420,445,120,37);
    }

    //Instruction
    else if(gamestate==3)
    {
        iShowBMP(0,0,screen[gamestate]);
    }

    //Settings
    else if(gamestate==4)
    {
        iShowBMP(0,0,screen[gamestate]);
        iSetColor(255,255,255);
        iFilledRectangle(settingsx,settingsy,rl,rw);
    }

    //Enter Name
    else if(gamestate==5)
    {
        iShowBMP(0,0,screen[gamestate]);
        if(!hasName)
        {
            enterName();
        }
        iSetColor(0,0,0);
        iText(115,250,str,GLUT_BITMAP_TIMES_ROMAN_24);
    }


    //Game Screeen
    else if(gamestate == 6)
    {
        iShowBMP(0,0,backupbg);
        if(ishit)
        {
            iSetColor(255,0,0);
            hitcounter++;
            if(hitcounter>=30){
                hitcounter=0;
                ishit = false;
            }
        }
        else
        {
            iSetColor(0,0,0);
        }
        iFilledRectangle(0,0,8,720);
        iSetColor(0,0,0);
        iFilledRectangle(0,680,1280,40);
        for(i=0; i<life; i++)
        {
            iShowBMP2(lifexy[i].x,lifexy[i].y,asset[3],0);
        }
        iSetColor(255,255,255);
        iText(530,690,ch1,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(1010,690,ch2,GLUT_BITMAP_TIMES_ROMAN_24);
        sprintf(scorec, "%d", score);
        iText(1110,690,scorec,GLUT_BITMAP_TIMES_ROMAN_24);
        changePosition();
        for(i=0; i<gbirdNum; i++)
        {
            if(gxy[i].alive)
            {
                iShowBMP2(gxy[i].x,gxy[i].y,greenbird[gxy[i].birdindex],0);
            }
        }
        for(i=0; i<rbirdNum; i++)
        {
            if(rxy[i].alive)
            {
                iShowBMP2(rxy[i].x,rxy[i].y,redbird[rxy[i].birdindex],0);
            }
        }

        if(IsShoot)
        {
            iShowBMP2(shootx,shooty,shoot[shootindex],0);
            shootindex++;
            if(shootindex >= 4)
            {
                shootindex = 0;
                IsShoot = false;
                IsVanish = true;
            }
        }
        iShowBMP2(gunx,0,asset[gunIndex],255);
        if(IsVanish)
        {
            iShowBMP2(vanishx,vanishy,vanish[vanishindex],0);
            vanishindex++;
            if(vanishindex >= 7)
            {
                vanishindex = 0;
                IsVanish = false;
            }
        }
    }

    //Score Board
    else if(gamestate == 7)
    {
        iShowBMP(0,0,screen[6]);
        iShowBMP2(800,170,asset[4],255);
        iRectangle(440,422,100,35);
        iRectangle(440,347,100,35);
        iSetColor(255,255,255);
        sprintf(scorec, "%d", score);
        iText(445,430,scorec,GLUT_BITMAP_TIMES_ROMAN_24);
        if(score > highscore)
        {
            highscore = sethighscore();
        }
        sprintf(highc, "%d", highscore);
        iText(445,356,highc,GLUT_BITMAP_TIMES_ROMAN_24);
    }
}


void iMouseMove(int mx, int my)
{

    //place your codes here
}


void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        //printf("x = %d, y= %d\n",mx,my);
        //Main Screen
        if(gamestate==1)
        {
            if((mx>=100 && mx<=500))
            {
                if((my>=47 && my<=137))
                {
                    exit(0);
                }
                else if(my>=167 && my<=257)
                {
                    gamestate=4;
                }
                else if(my>=287 && my<=377)
                {
                    gamestate=3;
                }
                else if(my>=407 && my<=497)
                {
                    gamestate=2;
                }
                else if(my>=527 && my<=617)
                {
                    gamestate=5;

                }

            }
        }

        //high Score
        if(gamestate==2)
        {
            if((mx>=100 && mx<=350) && (my>=67 && my<=147))
            {
                gamestate=1;
            }
        }

        //Instruction
        if(gamestate==3)
        {
            if((mx>=100 && mx<=350) && (my>=83 && my<=163))
            {
                gamestate=1;
            }
        }

        //settings
        if(gamestate==4)
        {
            if((mx>=100 && mx<=500) && (my>=47 && my<=137))
            {
                gamestate=1;
            }
            else if((mx>=601 && mx<=746) && (my>=377 && my<=449))
            {
                if(musicon && !musicoff)
                {
                    settingsx = settingsx + 145;
                    rl = rl + 5;
                    musicon=false;
                    musicoff=true;
                    PlaySound(0,0,0);
                }

            }
            else if((mx>=456 && mx<=596) && (my>=377 && my<=449))
            {
                if(!musicon && musicoff)
                {
                    settingsx = settingsx - 145;
                    rl = rl - 5;
                    musicon=true;
                    musicoff=false;
                    PlaySound(music[0],NULL,SND_LOOP | SND_ASYNC);
                }
            }
        }

        //name screen
        if(gamestate==5)
        {
            if((mx>=92 && mx<=342) && (my>=72 && my<=162))
            {
                gamestate=1;
            }
            else if((mx>=841 && mx<=1241) && (my>=72 && my<=162))
            {
                if(strlen(str) <= 0)
                {
                    hasName = false ;
                }
                for(i=0; i<strlen(str); i++)
                {
                    if(str[i] == ' ')
                    {
                        hasName = false ;
                        continue;
                    }
                    else
                    {
                        hasName = true;
                        gamestate=6;
                    }
                }

            }
            else if((mx>=92 && mx<=559) && (my>=222 && my<=292))
            {
                //use keyboard
            }
        }

        //main game screen
        if(gamestate == 6)
        {
            if(my>300 && my<680)
            {
                if(mx-30<gunx<mx+30)
                {
                    gunIndex=1;
                }
                if(mx<175)
                {
                    gunx=0;
                }
                else if(mx>SCREENWIDTH-350)
                {
                    gunx=SCREENWIDTH-350;
                }
                else if(175<= mx <=SCREENWIDTH-350)
                {
                    gunx=mx-175;
                }
            }

            for(i=0; i<gbirdNum; i++)
            {
                if((mx >= gxy[i].x && mx<=gxy[i].x + 80) && (my >= gxy[i].y && my <= gxy[i].y +70))
                {
                    IsShoot = true;
                    shootx = gunx + 180;
                    shooty = 250;
                    vanishx = mx-40;
                    vanishy = my-40;
                    gxy[i].alive= false;
                    life -=1;
                    if(life <= 0)
                    {
                        if(musicon && !musicoff)
                        {
                            PlaySound(music[1],NULL,SND_ASYNC);
                        }
                        gamestate = 7;
                    }
                }
            }
            for(i=0; i<rbirdNum; i++)
            {
                if((mx >= rxy[i].x && mx<=rxy[i].x + 60) && (my >= rxy[i].y && my <= rxy[i].y +55))
                {
                    IsShoot = true;
                    shootx = gunx + 175;
                    shooty = 220;
                    vanishx = mx-30;
                    vanishy = my-30;
                    rxy[i].alive= false;
                    score +=100;
                }
            }
        }


        //score board
        if(gamestate == 7)
        {
            if((mx>=96 && mx <=496) && (my>=70 && my<=160))
            {
                score = 0;
                setEnemy();
                gunx=0;
                life = 5;
                gbirdNum = 1;
                rbirdNum = 5;
                gBirdSpeed = 1;
                rBirdSpeed = 1;
                gbirdcounter = 0;
                rbirdcounter = 0;
                vanishx=0;
                vanishy=0;
                shootx=0;
                shooty=0;
                hasName = true;
                IsVanish = false ;
                IsShoot = false;
                if(musicon && !musicoff)
                {
                    PlaySound(music[0],NULL,SND_LOOP | SND_ASYNC);
                }
                gamestate = 1;
            }
            if((mx>=818 && mx <=1218) && (my>=70 && my<=160))
            {
                score = 0;
                setEnemy();
                life = 5;
                gunx=0;
                gbirdNum = 1;
                rbirdNum = 5;
                gBirdSpeed = 1;
                rBirdSpeed = 1;
                gbirdcounter = 0;
                rbirdcounter = 0;
                vanishx=0;
                vanishy=0;
                shootx=0;
                shooty=0;
                hasName = true;
                IsVanish = false ;
                IsShoot = false;
                if(musicon && !musicoff)
                {
                    PlaySound(music[0],NULL,SND_LOOP | SND_ASYNC);
                }
                gamestate = 6;
            }
        }
    }


    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here

    }
}


void iKeyboard(unsigned char key)
{
    //place your codes for other keys here
    if(gamestate == 5)
    {
        if(key != '\b')
        {
            str[strIndex] = toupper(key);
            strIndex++;
        }
        else
        {
            if(strIndex>0)
            {
                strIndex--;
                str[strIndex] = '\0';
            }
        }

        printf("%c",key);
    }

    //Enter key work
    if(key == 13)
    {
        if(gamestate == 1)
        {
            gamestate = 5;
        }
    }



}


void iSpecialKeyboard(unsigned char key)
{

    //place your codes for other keys here
}



// DEFINNATION of function
int getScore()
{
    fptr = fopen(filelocation,"r");
    if(fptr== NULL)
    {
        return 0;
    }
    else
    {
        fscanf(fptr,"%d", &fscore);
        return fscore;
    }
    fclose(fptr);
}


int sethighscore()
{
    fptr = fopen(filelocation,"w");
    fprintf(fptr,"%d",score);
    return score;
}


void enterName()
{
    iSetColor(255,0,0);
    iText(105,190,ch3,GLUT_BITMAP_TIMES_ROMAN_24);
}


void changePosition()
{
    for(i=0; i<gbirdNum; i++)
    {
        if(gxy[i].alive)
        {
            gxy[i].x -= gBirdSpeed;
            if(gxy[i].x <= 0)
            {
                gxy[i].x = SCREENWIDTH + rand()%200;
            }
        }
    }

    for(i=0; i<rbirdNum; i++)
    {

        if(rxy[i].alive)
        {
            rxy[i].x -= rBirdSpeed;
            if(rxy[i].x <= 0)
            {
                life = life -1;
                ishit = true ;
                if(life <= 0)
                {
                    if(musicon && !musicoff)
                    {
                            PlaySound(music[1],NULL,SND_ASYNC);
                    }
                    gamestate = 7;
                }
                rxy[i].x = SCREENWIDTH + rand()%SCREENWIDTH;
            }
        }
    }
    gbirdcounter++;
    rbirdcounter++;
    if(gbirdcounter>=1280)
    {
        gbirdNum+=gbirdadd;
        gbirdcounter=0;
        if(gbirdNum%2 == 0)
        {
            gBirdSpeed +=1;
            rBirdSpeed +=1;
        }
        if(gbirdNum >= birdNum)
        {
            gbirdNum = birdNum;
        }
    }
    if(rbirdcounter>=1280)
    {
        rbirdNum += rbirdadd ;
        rbirdcounter=0;
        if(rbirdNum >= birdNum)
        {
            rbirdNum = birdNum;
        }
    }
}


void changeimg()
{
    for(i=0; i<gbirdNum; i++)
    {
        gxy[i].birdindex +=1 ;
        if(gxy[i].birdindex >= 9)
        {
            gxy[i].birdindex = 0;
        }
    }

    for(i=0; i<rbirdNum; i++)
    {
        rxy[i].birdindex+=1;
        if(rxy[i].birdindex >= 14)
        {
            rxy[i].birdindex = 0;
        }
    }
}


void setEnemy()
{
    for(i=0; i<birdNum; i++)
    {
        gxy[i].x = SCREENWIDTH + rand()%SCREENWIDTH;
        gxy[i].y = 300 + rand()%300;
        gxy[i].birdindex = rand()%9;
        gxy[i].alive = true;
    }

    for(i=0; i<birdNum; i++)
    {
        rxy[i].x = SCREENWIDTH + rand()%SCREENWIDTH;
        rxy[i].y = 300 + rand()%300;
        rxy[i].birdindex =  rand()%14;
        rxy[i].alive = true;
    }
}


void checkIsAlive()
{
    for(i=0; i<gbirdNum; i++)
    {
        if(!gxy[i].alive)
        {
            gxy[i].x = SCREENWIDTH + rand()%SCREENWIDTH;
            gxy[i].y = 300 + rand()%300;
            gxy[i].birdindex = rand()%9;
            gxy[i].alive = true;
        }
    }

    for(i=0; i<rbirdNum; i++)
    {
        if(!rxy[i].alive)
        {
            rxy[i].x = SCREENWIDTH + rand()%SCREENWIDTH;
            rxy[i].y = 300 + rand()%300;
            rxy[i].birdindex = rand()%14;
            rxy[i].alive = true;
        }
    }
}



int main()
{
    highscore = getScore();
    if(musicon && !musicoff)
    {
        PlaySound(music[0],NULL,SND_LOOP | SND_ASYNC);
    }
    for(i=3; i>=0; i--)
    {
        buttonxy[i].x = 100;
        buttonxy[i].y = cosum;
        cosum=cosum+120;
    }

    for(i=0; i<life; i++)
    {
        lifexy[i].x = sumlife;
        lifexy[i].y = 685;
        sumlife+=28;
    }

    setEnemy();
    iSetTimer(100,changeimg);
    iSetTimer(20,checkIsAlive);

    //place your own initialization codes here.
    iInitialize(SCREENWIDTH, SCREENHEIGHT, ch4);
    return 0;
}
